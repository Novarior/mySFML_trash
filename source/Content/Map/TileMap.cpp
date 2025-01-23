#include "TileMap.hpp"

void TileMap::initMapVariables()
{
    // Инициализация tilemap
    for (int x = 0; x < _map_dataNoice.mapSizeX; x++)
        for (int y = 0; y < _map_dataNoice.mapSizeY; y++)
            for (int z = 0; z < _map_dataNoice.mapSizeZ; z++) {
                this->tilemap[x][y][z] = NULL;
            }

    // Инициализация карт высот
    this->_map_heightMap.resize(_map_dataNoice.mapSizeX, std::vector<float>(_map_dataNoice.mapSizeY, 0.0f));
    this->_map_biomeMap.resize(_map_dataNoice.mapSizeX, std::vector<float>(_map_dataNoice.mapSizeY, 0.0f));
    this->_map_temperatureMap.resize(_map_dataNoice.mapSizeX, std::vector<float>(_map_dataNoice.mapSizeY, 0.0f));

    // Инициализация деревьев и списка блоков травы
    this->trees.clear();
    this->m_listGrassBlocks.clear();
}

void TileMap::Clear()
{
    // Сброс tilemap
    for (auto& x : this->tilemap) {
        for (auto& y : x) {
            for (auto& z : y) {
                z = nullptr;
            }
            y.clear();
        }
        x.clear();
    }
    this->tilemap.clear();

    // Сброс карт высот
    for (auto& row : this->_map_heightMap) {
        std::fill(row.begin(), row.end(), 0.0f);
    }
    for (auto& row : this->_map_biomeMap) {
        std::fill(row.begin(), row.end(), 0.0f);
    }
    for (auto& row : this->_map_temperatureMap) {
        std::fill(row.begin(), row.end(), 0.0f);
    }

    // Сброс деревьев и списка блоков травы
    this->trees.clear();
    this->m_listGrassBlocks.clear();
}

void TileMap::initTrees()
{
    // prepare generator
    this->_treeGenerator = std::make_unique<LSystem>(LSystem());
    this->_treeGenerator.get()->setRule('d', "qd");
    this->_treeGenerator.get()->setRule('s', "d[-qqs]+qqs");
    this->_treeGenerator.get()->setOffsetPos(
        sf::Vector2f(this->_map_dataNoice.RenderWindowX / 2,
                     this->_map_dataNoice.RenderWindowY * 0.70));

    this->_treeGenerator.get()->generate();
    // create texture with window size
    sf::Texture texture(sf::Vector2u(_map_dataNoice.RenderWindowX, _map_dataNoice.RenderWindowY));
    // get array shape


    std::vector<sf::RectangleShape> shapes;
    shapes.insert(shapes.end(), this->_treeGenerator.get()->internalArray(), this->_treeGenerator.get()->internalArray() + this->_treeGenerator.get()->getSizeArray());

    // get snapshoot
    sf::Image image = texture.copyToImage();

    // find Transparent pixels
    sf::Vector2u size = image.getSize();
    sf::Rect<unsigned> mrect({size.x, size.y}, {0, 0});

    for (unsigned int x = 0; x < size.x; x++)
        for (unsigned int y = 0; y < size.y; y++)
            if (image.getPixel({x, y}) != sf::Color::Transparent)
            {
                if (x < mrect.position.x)
                    mrect.position.x = x;
                if (y < mrect.position.y)
                    mrect.position.y = y;
                if (x > mrect.size.x)
                    mrect.size.x = x;
                if (y > mrect.size.y)
                    mrect.size.y = y;
            }
    // create newe image on mrect base
    sf::Image simg(sf::Vector2u(mrect.size.x - mrect.position.x, mrect.size.y - mrect.position.y), sf::Color::Transparent);

    // copy pixels from original image
    for (unsigned int x = mrect.position.x; x < mrect.size.x; x++)
        for (unsigned int y = mrect.position.y; y < mrect.size.x; y++)
            simg.setPixel(sf::Vector2u(x - mrect.position.x, y - mrect.position.y), image.getPixel({x, y}));
}
    sf::Texture buffT(simg);
    this->listTrees.push_back(buffT);
}

void TileMap::loadTextuteMap()
{
    this->m_TexturesList["BLOCK_DEEP_OCEAN"].update(TextureManager::getTexture("texture_deep_ocean"));
    this->m_TexturesList["BLOCK_OCEAN"].update(TextureManager::getTexture("texture_ocean"));
    this->m_TexturesList["BLOCK_SAND"].update(TextureManager::getTexture("texture_sand"));
    this->m_TexturesList["BLOCK_GRASS"].update(TextureManager::getTexture("texture_grass"));
    this->m_TexturesList["BLOCK_DIRT"].update(TextureManager::getTexture("texture_dirt"));
    this->m_TexturesList["BLOCK_STONE"].update(TextureManager::getTexture("texture_stone"));
    this->m_TexturesList["BLOCK_SNOWMOUNT"].update(TextureManager::getTexture("texture_snow"));

    Logger::logStatic("Textures LOADL", "CATCHED ME TileMap::loadTextuteMap()");
}

void TileMap::pushTree(int x, int y)
{
    sf::RectangleShape tree;
    tree.setSize(sf::Vector2f(256.f, 256.f));
    tree.setTexture(&this->listTrees[rand() % this->listTrees.size()]);
    this->trees.push_back(tree);
    this->trees.back().setPosition({x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize});
    this->trees.back().setOrigin({.01f, 0.01f});
}

void TileMap::generateMap()
{
    this->worldSizeGrid = sf::Vector2i(_map_dataNoice.mapSizeX, _map_dataNoice.mapSizeY);
    this->worldSizeInt = sf::Vector2i(_map_dataNoice.mapSizeX * _map_dataNoice.gridSize, _map_dataNoice.mapSizeY * _map_dataNoice.gridSize);
    this->worldSizeFloat = sf::Vector2f(_map_dataNoice.mapSizeX * _map_dataNoice.gridSize, _map_dataNoice.mapSizeY * _map_dataNoice.gridSize);

    float buff_height;
    sf::Color buff;
    this->minimapImage = sf::Image(sf::Vector2u(this->worldSizeGrid.x, this->worldSizeGrid.y), sf::Color::Red);

    this->tilemap.resize(this->worldSizeGrid.x, std::vector<std::vector<BrickBlock*>>());

    // init 2d arrays
    // first init height map of world

    for (int x = 0; x < _map_dataNoice.mapSizeX; x++) {
        this->tilemap[x].resize(this->worldSizeGrid.y, std::vector<BrickBlock*>());

        for (int y = 0; y < _map_dataNoice.mapSizeY; y++) {
            buff_height = mmath::normalize(this->mGen_noice.getNoice(x, y));

            if (buff_height < 45)
            {                                                     // Ocean
                double depth_intensity = 100 + buff_height * 1.2; // Интенсивность синего
                buff = sf::Color(0, std::max(0.0, 5 + buff_height * 0.4), std::min(255.0, depth_intensity), 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2i(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2i(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    true, this->m_TexturesList["BLOCK_DEEP_OCEAN"], BLOCK_DEEP_OCEAN, true));
            }
            else if (buff_height < 66)
            {
                double shore_intensity = 100 + buff_height * 2.0;
                buff = sf::Color(0, std::min(255.0, 15 + buff_height * 0.8), std::min(255.0, shore_intensity), 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2i(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2i(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    true, this->m_TexturesList["BLOCK_OCEAN"], BLOCK_OCEAN));
            }
            else if (buff_height < 85)
            { // sand
                buff = sf::Color(std::min(255.0, 200 + buff_height * 0.5), std::min(255.0, 180 + buff_height * 0.3), std::min(255.0, 100 + buff_height * 0.1), 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2i(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2i(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    false, this->m_TexturesList["BLOCK_SAND"], BLOCK_SAND));
            }
            else if (buff_height < 120)
            { // grass
                buff = sf::Color(std::min(255.0, buff_height * 0.08), std::min(255.0, 40 + buff_height * 0.9), std::min(255.0, buff_height * 0.05), 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2i(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2i(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    false, this->m_TexturesList["BLOCK_SAND"], BLOCK_GRASS));

                // init Trees
                if (rand() % 100 < 1)
                    this->pushTree(x, y);
                this->m_listGrassBlocks.push_back(sf::Vector2f(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize));
            }
            else if (buff_height < 165)
            { // dirt
                buff = sf::Color(90 - buff_height * 0.1, 71 + buff_height * 0.15, 55 + buff_height * 0.1, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2i(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2i(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    false, this->m_TexturesList["BLOCK_DIRT"], BLOCK_DIRT));
            }
            else if (buff_height < 200)
            { // stone
                buff = sf::Color(40 + buff_height * 0.1, 71 - buff_height * 0.2, 55 - buff_height * 0.2, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2i(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2i(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    false, this->m_TexturesList["BLOCK_STONE"], BLOCK_STONE));
            }
            else
            { // Snow
                double intensity = 200 + (buff_height - 200) * 0.275;
                buff = sf::Color(std::min(255.0, intensity), std::min(255.0, intensity), std::min(255.0, intensity), 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2i(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2i(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    false, this->m_TexturesList["BLOCK_SNOWMOUNT"], BLOCK_SNOWMOUNT));
            }
            this->minimapImage.setPixel(sf::Vector2u(x, y), this->tilemap[x][y].back()->getBlockColor());
        }
    }
}

TileMap::TileMap(mmath::noiceData datanoice, ProcessGenerationNoice* noice)
    : keyTime(0.f)
    , keyTimeMax(0.5f)
    , _map_dataNoice(datanoice)
    , mGen_noice(*noice)
{
    this->initMapVariables();
    this->loadTextuteMap();
    this->initTrees();
    this->generateMap();
    this->updateRenderArea(sf::Vector2i(0, 0));

    this->m_renderArea.offsetX = (_map_dataNoice.RenderWindowX / _map_dataNoice.gridSize / 4) + 4;
    this->m_renderArea.offsetY = (_map_dataNoice.RenderWindowY / _map_dataNoice.gridSize / 4) + 4;

    this->bariere_box.setFillColor(sf::Color::Transparent);
    this->bariere_box.setOutlineColor(sf::Color::Red);
    this->bariere_box.setOutlineThickness(3.f);
    this->bariere_box.setSize(this->worldSizeFloat);

    // sort this->trees by y position
    std::sort(this->trees.begin(), this->trees.end(), [](const sf::RectangleShape& lhs, const sf::RectangleShape& rhs) {
        return lhs.getPosition().y < rhs.getPosition().y;
    });
}

TileMap::~TileMap()
{
    this->Clear();
    this->listTrees.clear();
    this->m_TexturesList.clear();
}

bool TileMap::getCollision(const unsigned int x, const unsigned int y) const
{
    return this->tilemap[x][y][0]->getCollision();
}

sf::FloatRect TileMap::getGlobalBounds(const unsigned int x, const unsigned int y) const
{
    return this->tilemap[x][y][0]->getGlobalBounds();
}

const bool TileMap::getKeyTime()
{
    if (this->keyTime >= this->keyTimeMax) {
        this->keyTime = 0.f;
        return true;
    }
    return false;
}

void TileMap::updateKeyTime(const float& delta_time)
{
    if (this->keyTime < this->keyTimeMax)
        this->keyTime += delta_time;
}

void TileMap::updateWorldBoundsCollision(Entity* entity)
{ // WORLD BOUNDS
    if (entity->e_getPosition().x < 0.f) {
        entity->e_setPosition(0.f, entity->e_getPosition().y);
        entity->getMovement()->stopVelocityX();
    } else if (entity->e_getPosition().x + entity->getGlobalBounds().size.x > this->worldSizeFloat.x) {
        entity->e_setPosition(this->worldSizeFloat.x - entity->getGlobalBounds().size.x, entity->e_getPosition().y);
        entity->getMovement()->stopVelocityX();
    }
    if (entity->e_getPosition().y < 0.f) {
        entity->e_setPosition(entity->e_getPosition().x, 0.f);
        entity->getMovement()->stopVelocityY();
    } else if (entity->e_getPosition().y + entity->getGlobalBounds().size.y > this->worldSizeFloat.y) {
        entity->e_setPosition(entity->e_getPosition().x, this->worldSizeFloat.y - entity->getGlobalBounds().size.y);
        entity->getMovement()->stopVelocityY();
    }
}

void TileMap::updateTileCollision(Entity* entity, const float& delta_time)
{
    auto entityGridPos = entity->e_getGridPositionInt(_map_dataNoice.gridSize);

    this->m_colisionArea.fromX = std::max(0, entityGridPos.x - 1);
    this->m_colisionArea.toX = std::min(this->worldSizeGrid.x, entityGridPos.x + 3);
    this->m_colisionArea.fromY = std::max(0, entityGridPos.y - 1);
    this->m_colisionArea.toY = std::min(this->worldSizeGrid.y, entityGridPos.y + 3);

    for (int x = this->m_colisionArea.fromX; x < this->m_colisionArea.toX; x++) {
        for (int y = this->m_colisionArea.fromY; y < this->m_colisionArea.toY; y++) {

            auto tile = this->tilemap[x][y][0];
            if (!tile->getCollision())
                continue;

            sf::IntRect playerBounds = sf::IntRect(entity->getGlobalBounds());
            sf::IntRect wallBounds = sf::IntRect(tile->getGlobalBounds());
            sf::IntRect nextPositionBounds = sf::IntRect(entity->getNextPositionBounds(delta_time));

            if (tile->intersects(nextPositionBounds)) {
                sf::Vector2f collisionDepth = getCollisionDepth(playerBounds, wallBounds);

                // Определение направления коллизии по глубине пересечения
                if (collisionDepth.x < collisionDepth.y) {
                    // Горизонтальная коллизия
                    if (collisionDepth.x > 0) {
                        entity->getMovement()->stopVelocityX();
                        entity->e_setPosition(wallBounds.position.x - playerBounds.size.x, playerBounds.position.y);
                    } else {
                        entity->getMovement()->stopVelocityX();
                        entity->e_setPosition(wallBounds.position.x + wallBounds.size.x, playerBounds.position.y);
                    }
                } else {
                    // Вертикальная коллизия
                    if (collisionDepth.y > 0) {
                        entity->getMovement()->stopVelocityY();
                        entity->e_setPosition(playerBounds.position.x, wallBounds.position.x - playerBounds.size.y);
                    } else {
                        entity->getMovement()->stopVelocityY();
                        entity->e_setPosition(playerBounds.position.x, wallBounds.position.x + wallBounds.size.y);
                    }
                }
            }
        }
    }
}

sf::Vector2f TileMap::getCollisionDepth(const sf::IntRect& rectA, const sf::IntRect& rectB)
{
    float left = rectB.position.x - (rectA.position.x + rectA.size.x);
    float right = (rectB.position.x + rectB.size.x) - rectA.position.x;
    float top = rectB.position.y - (rectA.position.y + rectA.size.y);
    float bottom = (rectB.position.y + rectB.size.y) - rectA.position.y;

    float depthX = (left < right) ? left : right;
    float depthY = (top < bottom) ? top : bottom;

    return sf::Vector2f(depthX, depthY);
}

bool TileMap::checkBottomCollision(const sf::IntRect& playerBounds, const sf::IntRect& wallBounds)
{
    return playerBounds.position.y + playerBounds.size.y > wallBounds.position.y
        && playerBounds.position.x < wallBounds.position.x + wallBounds.size.x
        && playerBounds.position.x + playerBounds.size.x > wallBounds.position.x;
}

bool TileMap::checkTopCollision(const sf::IntRect& playerBounds, const sf::IntRect& wallBounds)
{
    return playerBounds.position.y < wallBounds.position.y + wallBounds.size.y
        && playerBounds.position.x < wallBounds.position.x + wallBounds.size.x
        && playerBounds.position.x + playerBounds.size.x > wallBounds.position.x;
}

bool TileMap::checkRightCollision(const sf::IntRect& playerBounds, const sf::IntRect& wallBounds)
{
    return playerBounds.position.x + playerBounds.size.x > wallBounds.position.x
        && playerBounds.position.y < wallBounds.position.y + wallBounds.size.y
        && playerBounds.position.y + playerBounds.size.y > wallBounds.position.y;
}

bool TileMap::checkLeftCollision(const sf::IntRect& playerBounds, const sf::IntRect& wallBounds)
{
    return playerBounds.position.x < wallBounds.position.x + wallBounds.size.x
        && playerBounds.position.y < wallBounds.position.y + wallBounds.size.y
        && playerBounds.position.y + playerBounds.size.y > wallBounds.position.y;
}

void TileMap::updateAnimationTiles(const float& delta_time)
{
    if (this->getKeyTime())
        for (int x = this->m_renderArea.fromX; x < this->m_renderArea.toX; x++)
            for (int y = this->m_renderArea.fromY; y < this->m_renderArea.toY; y++)
                this->tilemap[x][y][0]->updateAnimation();
}

void TileMap::updateRenderArea(const sf::Vector2i& playerPosition_grid) // update render area
{
    { // update render area
        this->m_renderArea.fromX = playerPosition_grid.x - this->m_renderArea.offsetX;
        if (this->m_renderArea.fromX < 0)
            this->m_renderArea.fromX = 0;
        else if (this->m_renderArea.fromX > this->worldSizeGrid.x)
            this->m_renderArea.fromX = this->worldSizeGrid.x;

        this->m_renderArea.toX = playerPosition_grid.x + this->m_renderArea.offsetX;
        if (this->m_renderArea.toX < 0)
            this->m_renderArea.toX = 0;
        else if (this->m_renderArea.toX > this->worldSizeGrid.x)
            this->m_renderArea.toX = this->worldSizeGrid.x;

        this->m_renderArea.fromY = playerPosition_grid.y - this->m_renderArea.offsetY;
        if (this->m_renderArea.fromY < 0)
            this->m_renderArea.fromY = 0;
        else if (this->m_renderArea.fromY > this->worldSizeGrid.y)
            this->m_renderArea.fromY = this->worldSizeGrid.y;

        this->m_renderArea.toY = playerPosition_grid.y + this->m_renderArea.offsetY;
        if (this->m_renderArea.toY < 0)
            this->m_renderArea.toY = 0;
        else if (this->m_renderArea.toY > this->worldSizeGrid.y)
            this->m_renderArea.toY = this->worldSizeGrid.y;
    }

    this->checkreck = sf::Rect<int>(
        { static_cast<int>(this->m_renderArea.fromX * _map_dataNoice.gridSize),
            static_cast<int>(this->m_renderArea.fromY * _map_dataNoice.gridSize) },
        { static_cast<int>(this->m_renderArea.toX * _map_dataNoice.gridSize),
            static_cast<int>(this->m_renderArea.toY * _map_dataNoice.gridSize) });
}

void TileMap::update(Entity* entity, const float& delta_time)
{
    this->updateKeyTime(delta_time);
    this->updateWorldBoundsCollision(entity);
    this->updateTileCollision(entity, delta_time);

    if (this->getKeyTime())
        this->updateAnimationTiles(delta_time);
}

void TileMap::render(sf::RenderTarget* target)
{ // Render tiles
    for (int x = this->m_renderArea.fromX; x < this->m_renderArea.toX; x++)
        for (int y = this->m_renderArea.fromY; y < this->m_renderArea.toY; y++)
            if (this->tilemap[x][y][0] != nullptr)
                this->tilemap[x][y][0]->render(target);

    // Render trees on screen area
    for (int i = 0; i < this->trees.size(); i++)
        if (this->checkreck.findIntersection(static_cast<sf::IntRect>(this->trees[i].getGlobalBounds())))
            target->draw(this->trees[i]);

    // bariere box
    target->draw(this->bariere_box);
}