#include "TileMap.hpp"

void TileMap::Clear()
{
    if (!this->tilemap.empty()) {
        for (unsigned long x = 0; x < this->tilemap.size(); x++) {
            for (unsigned long y = 0; y < this->tilemap[x].size(); y++) {
                for (unsigned long z = 0; z < this->tilemap[x][y].size(); z++) {
                    delete this->tilemap[x][y][z];
                    this->tilemap[x][y][z] = NULL;
                }
                this->tilemap[x][y].clear();
            }
            this->tilemap.clear();
        }
    }
    this->trees.clear();
}

void TileMap::initTrees()
{ // load a lot images from floder and push to array
  // find floder with trees
  // load all images from floder
  // push to array
    sf::Texture texture;
    for (const auto& it : std::filesystem::directory_iterator(myConst::f_Trees)) {
        if (it.path().extension() != ".png")
            continue;
        if (texture.loadFromFile(it.path().c_str())) {
            texture.setSmooth(true);
            this->listTrees.push_back(texture);
        } else
            printf("\nERROR::PROCESS::INIT::TREES::COULD_NOT_LOAD\n   %s\n", it.path().c_str());
    }
    std::cout << this->listTrees.size() << " trees loaded\n";
}

void TileMap::loadTextuteMap()
{
    if (!this->m_TexturesList["GRASS"].loadFromFile(myConst::texture_DIRT)) {
        sf::Image img;
        img.create(32, 32);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(20, 200, 20));
        this->m_TexturesList["GRASS"].loadFromImage(img);
    };
    if (!this->m_TexturesList["STONE"].loadFromFile(myConst::texture_STONE)) {
        sf::Image img;
        img.create(32, 32);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(50, 55, 45));
        this->m_TexturesList["STONE"].loadFromImage(img);
    };
    if (!this->m_TexturesList["OCEAN"].loadFromFile(myConst::texture_OCEAN)) {
        sf::Image img;
        img.create(32, 32);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(0, 25, 240));
        this->m_TexturesList["OCEAN"].loadFromImage(img);
    };
    if (!this->m_TexturesList["OCEAN_ANIM"].loadFromFile(myConst::texture_OCEAN_ANIM)) {
        sf::Image img;
        img.create(32, 32);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(0, 25, 240));
        this->m_TexturesList["OCEAN_ANIM"].loadFromImage(img);
    };
    if (!this->m_TexturesList["SAND"].loadFromFile(myConst::texture_SAND)) {
        sf::Image img;
        img.create(32, 32);
        for (int x = 0; x < img.getSize().x; x++)
            for (int y = 0; y < img.getSize().y; y++)
                img.setPixel(x, y, sf::Color(180, 180, 20));
        this->m_TexturesList["SAND"].loadFromImage(img);
    };
    if (!this->m_TexturesList["DIRT"].loadFromFile(myConst::texture_DIRT)) {
        sf::Image img;
        img.create(32, 32);
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
    this->trees.back().setPosition(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize);
    this->trees.back().setOrigin(0.01f, 0.01f);
}

void TileMap::generateMap()
{
    this->worldSizeGrid = sf::Vector2i(this->m_dnoice.mapSizeX, this->m_dnoice.mapSizeY);
    this->worldSizeFloat = sf::Vector2f(this->m_dnoice.mapSizeX * this->m_dnoice.gridSize, this->m_dnoice.mapSizeY * this->m_dnoice.gridSize);

    double writebuff;
    sf::Color buff;
    this->minimapImage.create(this->worldSizeGrid.x, this->worldSizeGrid.y, sf::Color::Red);

    this->tilemap.resize(this->worldSizeGrid.x, std::vector<std::vector<BrickBlock*>>());

    for (int x = 0; x < this->m_dnoice.mapSizeX; x++) {
        this->tilemap[x].resize(this->worldSizeGrid.y, std::vector<BrickBlock*>());

        for (int y = 0; y < this->m_dnoice.mapSizeY; y++) {
            writebuff = this->mGen_noice.getNoice(x, y);
            writebuff *= 255;
            writebuff = static_cast<int>(writebuff) % 255;
            if (writebuff < 0)
                writebuff = writebuff * -1;

            if (writebuff < 55) { // Ocean
                buff = sf::Color(0, 10 + writebuff * 1.6, 100 + writebuff * 1.9, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    true, this->m_TexturesList["OCEAN_ANIM"], BLOCK_OCEAN_ANIM, true));
            } else if (writebuff < 66) { // sand
                buff = sf::Color(140 + writebuff * 1.5, 120 + writebuff * 1.4, 80 + writebuff * 0.1, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    false, this->m_TexturesList["SAND"], BLOCK_SAND));
            } else if (writebuff < 160) { // grass
                buff = sf::Color(writebuff * 0.1, 50 + writebuff * 1.1, writebuff * 0.08, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    false, this->m_TexturesList["GRASS"], BLOCK_GRASS));

                // init Trees
                if (rand() % 100 < 1)
                    this->pushTree(x, y);

                // write grass block position on array
                this->m_listGrassBlocks.push_back(sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize));
            } else if (writebuff < 165) { // dirt
                buff = sf::Color(90 - writebuff * 0.1, 71 + writebuff * 0.15, 55 + writebuff * 0.1, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    false, this->m_TexturesList["DIRT"], BLOCK_DIRT));
            } else if (writebuff < 175) { // stone
                buff = sf::Color(40 + writebuff * 0.1, 71 - writebuff * 0.2, 55 - writebuff * 0.2, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    false, this->m_TexturesList["STONE"], BLOCK_STONE));
            } else { // other
                buff = sf::Color(writebuff, writebuff, writebuff, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    true, this->m_TexturesList["OCEAN"], NAN_DEF));
            }
            this->minimapImage.setPixel(x, y, this->tilemap[x][y].back()->getBlockColor());
        }
    }
}

TileMap::TileMap(noiceData datanoice, ProcessGenerationNoice* noice)
    : keyTime(0.f)
    , keyTimeMax(0.5f)
    , m_dnoice(datanoice)
    , mGen_noice(*noice)
{
    this->Clear();
    this->loadTextuteMap();
    this->initTrees();
    this->generateMap();
    this->updateRenderArea(sf::Vector2i(0, 0));

    this->m_renderArea.offsetX = (this->m_dnoice.RenderWindowX / this->m_dnoice.gridSize / 4) + 4;
    this->m_renderArea.offsetY = (this->m_dnoice.RenderWindowY / this->m_dnoice.gridSize / 4) + 4;

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
{ // TILES
    this->m_colisionArea.fromX = entity->e_getGridPositionInt(this->m_dnoice.gridSize).x - 1;
    if (this->m_colisionArea.fromX < 0)
        this->m_colisionArea.fromX = 0;
    else if (this->m_colisionArea.fromX > this->worldSizeGrid.x)
        this->m_colisionArea.fromX = this->worldSizeGrid.x;

    this->m_colisionArea.toX = entity->e_getGridPositionInt(this->m_dnoice.gridSize).x + 3;
    if (this->m_colisionArea.toX < 0)
        this->m_colisionArea.toX = 0;
    else if (this->m_colisionArea.toX > this->worldSizeGrid.x)
        this->m_colisionArea.toX = this->worldSizeGrid.x;

    this->m_colisionArea.fromY = entity->e_getGridPositionInt(this->m_dnoice.gridSize).y - 1;
    if (this->m_colisionArea.fromY < 0)
        this->m_colisionArea.fromY = 0;
    else if (this->m_colisionArea.fromY > this->worldSizeGrid.y)
        this->m_colisionArea.fromY = this->worldSizeGrid.y;

    this->m_colisionArea.toY = entity->e_getGridPositionInt(this->m_dnoice.gridSize).y + 3;
    if (this->m_colisionArea.toY < 0)
        this->m_colisionArea.toY = 0;
    else if (this->m_colisionArea.toY > this->worldSizeGrid.y)
        this->m_colisionArea.toY = this->worldSizeGrid.y;

    for (int x = this->m_colisionArea.fromX; x < this->m_colisionArea.toX; x++) {
        for (int y = this->m_colisionArea.fromY; y < this->m_colisionArea.toY; y++) {

            sf::FloatRect playerBounds = entity->getGlobalBounds();
            sf::FloatRect wallBounds = this->tilemap[x][y][0]->getGlobalBounds();
            sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(delta_time);

            if (this->tilemap[x][y][0]->getCollision() && this->tilemap[x][y][0]->intersects(nextPositionBounds)) {
                // Bottom collision
                if (playerBounds.top < wallBounds.top
                    && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width
                    && playerBounds.left + playerBounds.width > wallBounds.left) {
                    entity->getMovement()->stopVelocityY();
                    entity->e_setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                }
                // Top collision
                else if (playerBounds.top > wallBounds.top
                    && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width
                    && playerBounds.left + playerBounds.width > wallBounds.left) {
                    entity->getMovement()->stopVelocityY();
                    entity->e_setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                }
                // Right collision
                if (playerBounds.left < wallBounds.left
                    && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height
                    && playerBounds.top + playerBounds.height > wallBounds.top) {
                    entity->getMovement()->stopVelocityX();
                    entity->e_setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                }
                // Left collision
                else if (playerBounds.left > wallBounds.left
                    && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height
                    && playerBounds.top + playerBounds.height > wallBounds.top) {
                    entity->getMovement()->stopVelocityX();
                    entity->e_setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                }
            }
        }
    }
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

    this->checkreck = sf::Rect(
        this->m_renderArea.fromX * this->m_dnoice.gridSize, this->m_renderArea.fromY * this->m_dnoice.gridSize,
        this->m_renderArea.toX * this->m_dnoice.gridSize, this->m_renderArea.toY * this->m_dnoice.gridSize);
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
            this->tilemap[x][y][0]->render(target);

    // Render trees on screen area
    for (int i = 0; i < this->trees.size(); i++)
        if (this->checkreck.intersects(this->trees[i].getGlobalBounds()))
            target->draw(this->trees[i]);

    // bariere box
    target->draw(this->bariere_box);
}