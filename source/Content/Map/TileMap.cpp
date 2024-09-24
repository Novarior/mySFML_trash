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
{ // load a lot images from floder and push to array
  // find floder with trees
  // load all images from floder
  // push to array
    sf::Texture texture;
    for (const auto& it : std::filesystem::directory_iterator(std::string(ApplicationsFunctions::get_resources_dir() + myConst::textures::f_Trees))) {
        if (it.path().extension() != ".png")
            continue;
        if (texture.loadFromFile(it.path().c_str())) {
            texture.setSmooth(true);
            this->listTrees.push_back(texture);
        } else
            Logger::log("Trees Could not load %s", "TILEMAP", logType::WARNING);
    }
    std::cout << this->listTrees.size() << " trees loaded\n";
}

void TileMap::loadTextuteMap()
{
    if (!this->m_TexturesList["GRASS"].loadFromFile(ApplicationsFunctions::get_resources_dir() + myConst::textures::texture_DIRT)) {
        Logger::log("TileMap::initTextures()::GRASS::ERROR::COULD_NOT_LOAD", "TILEMAP", logType::WARNING);

        sf::Image img;
        img.create(_map_dataNoice.gridSize, _map_dataNoice.gridSize);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(20, 200, 20));
        this->m_TexturesList["GRASS"].loadFromImage(img);
    };
    if (!this->m_TexturesList["STONE"].loadFromFile(ApplicationsFunctions::get_resources_dir() + myConst::textures::texture_STONE)) {
        Logger::log("TileMap::initTextures()::STONE::ERROR::COULD_NOT_LOAD", "TILEMAP", logType::WARNING);

        sf::Image img;
        img.create(_map_dataNoice.gridSize, _map_dataNoice.gridSize);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(50, 55, 45));
        this->m_TexturesList["STONE"].loadFromImage(img);
    };
    if (!this->m_TexturesList["OCEAN"].loadFromFile(ApplicationsFunctions::get_resources_dir() + myConst::textures::texture_OCEAN)) {
        Logger::log("TileMap::initTextures()::OCEAN::ERROR::COULD_NOT_LOAD", "TILEMAP", logType::WARNING);

        sf::Image img;
        img.create(_map_dataNoice.gridSize, _map_dataNoice.gridSize);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(0, 25, 240));
        this->m_TexturesList["OCEAN"].loadFromImage(img);
    };
    if (!this->m_TexturesList["OCEAN_ANIM"].loadFromFile(ApplicationsFunctions::get_resources_dir() + myConst::textures::texture_OCEAN_ANIM)) {
        Logger::log("TileMap::initTextures()::OCEAN_ANIM::ERROR::COULD_NOT_LOAD", "TILEMAP", logType::WARNING);

        sf::Image img;
        img.create(_map_dataNoice.gridSize, _map_dataNoice.gridSize);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(0, 25, 240));
        this->m_TexturesList["OCEAN_ANIM"].loadFromImage(img);
    };
    if (!this->m_TexturesList["SAND"].loadFromFile(ApplicationsFunctions::get_resources_dir() + myConst::textures::texture_SAND)) {
        Logger::log("TileMap::initTextures()::SAND::ERROR::COULD_NOT_LOAD", "TILEMAP", logType::WARNING);

        sf::Image img;
        img.create(_map_dataNoice.gridSize, _map_dataNoice.gridSize);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(180, 180, 20));
        this->m_TexturesList["SAND"].loadFromImage(img);
    };
    if (!this->m_TexturesList["DIRT"].loadFromFile(ApplicationsFunctions::get_resources_dir() + myConst::textures::texture_DIRT)) {
        Logger::log("TileMap::initTextures()::DIRT::ERROR::COULD_NOT_LOAD", "TILEMAP", logType::WARNING);

        sf::Image img;
        img.create(_map_dataNoice.gridSize, _map_dataNoice.gridSize);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(49, 40, 31));
        this->m_TexturesList["DIRT"].loadFromImage(img);
    };
}

void TileMap::pushTree(int x, int y)
{
    sf::RectangleShape tree;
    tree.setSize(sf::Vector2f(256.f, 256.f));
    tree.setTexture(&this->listTrees[rand() % this->listTrees.size()]);
    this->trees.push_back(tree);
    this->trees.back().setPosition(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize);
    this->trees.back().setOrigin(0.01f, 0.01f);
}

void TileMap::generateMap()
{
    this->worldSizeGrid = sf::Vector2i(_map_dataNoice.mapSizeX, _map_dataNoice.mapSizeY);
    this->worldSizeFloat = sf::Vector2f(_map_dataNoice.mapSizeX * _map_dataNoice.gridSize, _map_dataNoice.mapSizeY * _map_dataNoice.gridSize);

    double writebuff;
    sf::Color buff;
    this->minimapImage.create(this->worldSizeGrid.x, this->worldSizeGrid.y, sf::Color::Red);

    this->tilemap.resize(this->worldSizeGrid.x, std::vector<std::vector<BrickBlock*>>());

    // init 2d arrays
    // first init height map of world

    for (int x = 0; x < _map_dataNoice.mapSizeX; x++) {
        this->tilemap[x].resize(this->worldSizeGrid.y, std::vector<BrickBlock*>());

        for (int y = 0; y < _map_dataNoice.mapSizeY; y++) {
            writebuff = this->mGen_noice.getNoice(x, y);
            writebuff *= 255;
            writebuff = static_cast<int>(writebuff) % 255;
            if (writebuff < 0)
                writebuff = writebuff * -1;

            if (writebuff < 55) { // Ocean
                buff = sf::Color(0, 10 + writebuff * 1.6, 100 + writebuff * 1.9, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2f(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    true, this->m_TexturesList["OCEAN_ANIM"], BLOCK_OCEAN_ANIM, true));
            } else if (writebuff < 66) { // sand

                buff = sf::Color(140 + writebuff * 1.5, 120 + writebuff * 1.4, 80 + writebuff * 0.1, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2f(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    false, this->m_TexturesList["SAND"], BLOCK_SAND));

            } else if (writebuff < 160) { // grass
                buff = sf::Color(writebuff * 0.1, 50 + writebuff * 1.1, writebuff * 0.08, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2f(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    false, this->m_TexturesList["GRASS"], BLOCK_GRASS));

                // init Trees
                if (rand() % 100 < 1)
                    this->pushTree(x, y);
                this->m_listGrassBlocks.push_back(sf::Vector2f(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize));

                // write grass block position on array
            } else if (writebuff < 165) { // dirt
                buff = sf::Color(90 - writebuff * 0.1, 71 + writebuff * 0.15, 55 + writebuff * 0.1, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2f(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    false, this->m_TexturesList["DIRT"], BLOCK_DIRT));
            } else if (writebuff < 175) { // stone
                buff = sf::Color(40 + writebuff * 0.1, 71 - writebuff * 0.2, 55 - writebuff * 0.2, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2f(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    false, this->m_TexturesList["STONE"], BLOCK_STONE));
            } else { // other
                buff = sf::Color(writebuff, writebuff, writebuff, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(_map_dataNoice.gridSize, _map_dataNoice.gridSize),
                    sf::Vector2f(x * _map_dataNoice.gridSize, y * _map_dataNoice.gridSize), buff,
                    true, this->m_TexturesList["OCEAN"], NAN_DEF));
            }
            this->minimapImage.setPixel(x, y, this->tilemap[x][y].back()->getBlockColor());
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
    } else if (entity->e_getPosition().x + entity->getGlobalBounds().width > this->worldSizeFloat.x) {
        entity->e_setPosition(this->worldSizeFloat.x - entity->getGlobalBounds().width, entity->e_getPosition().y);
        entity->getMovement()->stopVelocityX();
    }
    if (entity->e_getPosition().y < 0.f) {
        entity->e_setPosition(entity->e_getPosition().x, 0.f);
        entity->getMovement()->stopVelocityY();
    } else if (entity->e_getPosition().y + entity->getGlobalBounds().height > this->worldSizeFloat.y) {
        entity->e_setPosition(entity->e_getPosition().x, this->worldSizeFloat.y - entity->getGlobalBounds().height);
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
                        entity->e_setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                    } else {
                        entity->getMovement()->stopVelocityX();
                        entity->e_setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                    }
                } else {
                    // Вертикальная коллизия
                    if (collisionDepth.y > 0) {
                        entity->getMovement()->stopVelocityY();
                        entity->e_setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                    } else {
                        entity->getMovement()->stopVelocityY();
                        entity->e_setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                    }
                }
            }
        }
    }
}

sf::Vector2f TileMap::getCollisionDepth(const sf::IntRect& rectA, const sf::IntRect& rectB)
{
    float left = rectB.left - (rectA.left + rectA.width);
    float right = (rectB.left + rectB.width) - rectA.left;
    float top = rectB.top - (rectA.top + rectA.height);
    float bottom = (rectB.top + rectB.height) - rectA.top;

    float depthX = (left < right) ? left : right;
    float depthY = (top < bottom) ? top : bottom;

    return sf::Vector2f(depthX, depthY);
}

bool TileMap::checkBottomCollision(const sf::IntRect& playerBounds, const sf::IntRect& wallBounds)
{
    return playerBounds.top < wallBounds.top
        && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
        && playerBounds.left < wallBounds.left + wallBounds.width
        && playerBounds.left + playerBounds.width > wallBounds.left;
}

bool TileMap::checkTopCollision(const sf::IntRect& playerBounds, const sf::IntRect& wallBounds)
{
    return playerBounds.top > wallBounds.top
        && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
        && playerBounds.left < wallBounds.left + wallBounds.width
        && playerBounds.left + playerBounds.width > wallBounds.left;
}

bool TileMap::checkRightCollision(const sf::IntRect& playerBounds, const sf::IntRect& wallBounds)
{
    return playerBounds.left < wallBounds.left
        && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
        && playerBounds.top < wallBounds.top + wallBounds.height
        && playerBounds.top + playerBounds.height > wallBounds.top;
}

bool TileMap::checkLeftCollision(const sf::IntRect& playerBounds, const sf::IntRect& wallBounds)
{
    return playerBounds.left > wallBounds.left
        && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
        && playerBounds.top < wallBounds.top + wallBounds.height
        && playerBounds.top + playerBounds.height > wallBounds.top;
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
        this->m_renderArea.fromX * _map_dataNoice.gridSize, this->m_renderArea.fromY * _map_dataNoice.gridSize,
        this->m_renderArea.toX * _map_dataNoice.gridSize, this->m_renderArea.toY * _map_dataNoice.gridSize);
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
        if (this->checkreck.intersects(static_cast<sf::IntRect>(this->trees[i].getGlobalBounds())))
            target->draw(this->trees[i]);

    // bariere box
    target->draw(this->bariere_box);
}