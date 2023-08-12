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

void TileMap::pushTree(int x, int y, int seed)
{
    int i = (1 + x + seed + y) % 3;
    this->m_TreeSprite.setTextureRect(list_treeRect[i]);
    this->m_TreeSprite.setPosition(
        (x * this->m_dnoice.gridSize) - this->m_TreeSprite.getGlobalBounds().width * 0.5,
        (y * this->m_dnoice.gridSize) - this->m_TreeSprite.getGlobalBounds().height * 0.75);
    this->m_TreeArray.push_back(this->m_TreeSprite);
}

TileMap::TileMap(noiceData datanoice, ProcessGenerationNoice* noice)
{
    this->Clear();
    this->loadTextuteMap();

    double writebuff;

    this->m_dnoice = datanoice;
    this->maxSizeWorldGrid = sf::Vector2u(this->m_dnoice.mapSizeX, this->m_dnoice.mapSizeY);
    this->maxSizeWorldFloat = sf::Vector2f(this->m_dnoice.mapSizeX * datanoice.gridSize, this->m_dnoice.mapSizeY * datanoice.gridSize);

    this->m_Area.offsetX = (datanoice.RenderWindowX / datanoice.gridSize / 4) + 4;
    this->m_Area.offsetY = (datanoice.RenderWindowY / datanoice.gridSize / 4) + 4;
    this->m_Area.fromX = 0;
    this->m_Area.fromY = 0;
    this->m_Area.toX = 0;
    this->m_Area.toY = 0;

    sf::Color buff;

    if (this->m_TreeTexture.loadFromFile(myConst::texture_TREE)) {
        this->m_TreeSprite.setTexture(this->m_TreeTexture);
        this->m_TreeTexture.setSmooth(true);
    }

    this->tilemap.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<BrickBlock*>>());

    for (int x = 0; x < this->m_dnoice.mapSizeX; x++) {
        this->tilemap[x].resize(this->maxSizeWorldGrid.y, std::vector<BrickBlock*>());

        for (int y = 0; y < this->m_dnoice.mapSizeY; y++) {
            writebuff = noice->getNoice(x, y);
            writebuff *= 255;
            writebuff = static_cast<int>(writebuff) % 255;
            if (writebuff < 0)
                writebuff = writebuff * -1;

            if (writebuff < 55) { // Ocean
                buff = sf::Color(0, 10 + writebuff * 1.6, 100 + writebuff * 1.9, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    true, this->m_TexturesList["OCEAN"], BLOCK_OCEAN));
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

                if (rand() % 100 < 15)
                    this->pushTree(x, y, this->m_dnoice.seed);
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
        }
    }

    this->bariere_box.setFillColor(sf::Color::Transparent);
    this->bariere_box.setOutlineColor(sf::Color::Red);
    this->bariere_box.setOutlineThickness(3.f);
    this->bariere_box.setSize(this->maxSizeWorldFloat);
}

TileMap::~TileMap()
{
    this->Clear();
    this->m_TreeArray.clear();
}

renderArea TileMap::getRenderArea()
{
    return this->m_Area;
}

const sf::Vector2u TileMap::getMapSizeOnTiles()
{
    return this->maxSizeWorldGrid;
}

const sf::Vector2f TileMap::getMapSizeOnFloat()
{
    return this->maxSizeWorldFloat;
}

bool TileMap::getCollision(const unsigned int x, const unsigned int y) const
{
    return this->tilemap[x][y][0]->getCollision();
}

sf::FloatRect TileMap::getGlobalBounds(const unsigned int x, const unsigned int y) const
{
    return this->tilemap[x][y][0]->getGlobalBounds();
}

void TileMap::updateWorldBoundsCollision(Entity* entity)
{ // WORLD BOUNDS
    if (entity->e_getPosition().x < 0.f) {
        entity->e_setPosition(0.f, entity->e_getPosition().y);
        entity->getMovement()->stopVelocityX();
    } else if (entity->e_getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldFloat.x) {
        entity->e_setPosition(this->maxSizeWorldFloat.x - entity->getGlobalBounds().width, entity->e_getPosition().y);
        entity->getMovement()->stopVelocityX();
    }
    if (entity->e_getPosition().y < 0.f) {
        entity->e_setPosition(entity->e_getPosition().x, 0.f);
        entity->getMovement()->stopVelocityY();
    } else if (entity->e_getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldFloat.y) {
        entity->e_setPosition(entity->e_getPosition().x, this->maxSizeWorldFloat.y - entity->getGlobalBounds().height);
        entity->getMovement()->stopVelocityY();
    }
}

void TileMap::updateTileCollision(Entity* entity, const float& delta_time)
{ // TILES
    this->fromX = entity->e_getGridPositionInt(this->m_dnoice.gridSize).x - 1;
    if (this->fromX < 0)
        this->fromX = 0;
    else if (this->fromX > this->maxSizeWorldGrid.x)
        this->fromX = this->maxSizeWorldGrid.x;

    this->toX = entity->e_getGridPositionInt(this->m_dnoice.gridSize).x + 3;
    if (this->toX < 0)
        this->toX = 0;
    else if (this->toX > this->maxSizeWorldGrid.x)
        this->toX = this->maxSizeWorldGrid.x;

    this->fromY = entity->e_getGridPositionInt(this->m_dnoice.gridSize).y - 1;
    if (this->fromY < 0)
        this->fromY = 0;
    else if (this->fromY > this->maxSizeWorldGrid.y)
        this->fromY = this->maxSizeWorldGrid.y;

    this->toY = entity->e_getGridPositionInt(this->m_dnoice.gridSize).y + 3;
    if (this->toY < 0)
        this->toY = 0;
    else if (this->toY > this->maxSizeWorldGrid.y)
        this->toY = this->maxSizeWorldGrid.y;

    for (int x = this->fromX; x < this->toX; x++) {
        for (int y = this->fromY; y < this->toY; y++) {

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

void TileMap::update(Entity* entity, const float& dt)
{
}

void TileMap::update(sf::Vector2f pos_entity)
{
    int fromX = 0,
        fromY = 0,
        toX = 0,
        toY = 0;

    fromX = pos_entity.x / this->m_dnoice.gridSize - 2;
    if (fromX < 0)
        fromX = 0;
    else if (fromX > this->maxSizeWorldGrid.x)
        fromX = this->maxSizeWorldGrid.x;

    toX = pos_entity.x / this->m_dnoice.gridSize + 3;
    if (toX < 0)
        toX = 0;
    else if (toX > this->maxSizeWorldGrid.x)
        toX = this->maxSizeWorldGrid.x;

    fromY = pos_entity.y / this->m_dnoice.gridSize - 2;
    if (fromY < 0)
        fromY = 0;
    else if (fromY > this->maxSizeWorldGrid.y)
        fromY = this->maxSizeWorldGrid.y;

    toY = pos_entity.y / this->m_dnoice.gridSize + 3;
    if (toY < 0)
        toY = 0;
    else if (toY > this->maxSizeWorldGrid.y)
        toY = this->maxSizeWorldGrid.y;

    for (int x = fromX; x < toX; x++)
        for (int y = fromY; y < toY; y++)
            this->tilemap[x][y][0]->update();
}

void TileMap::render(sf::RenderTarget* target, const sf::Vector2i& gridPosition, const bool debug)
{ // Render tiles

    { // recalc render area
        this->m_Area.fromX = gridPosition.x - this->m_Area.offsetX;
        if (this->m_Area.fromX < 0)
            this->m_Area.fromX = 0;
        else if (this->m_Area.fromX > this->maxSizeWorldGrid.x)
            this->m_Area.fromX = this->maxSizeWorldGrid.x;

        this->m_Area.toX = gridPosition.x + this->m_Area.offsetX;
        if (this->m_Area.toX < 0)
            this->m_Area.toX = 0;
        else if (this->m_Area.toX > this->maxSizeWorldGrid.x)
            this->m_Area.toX = this->maxSizeWorldGrid.x;

        this->m_Area.fromY = gridPosition.y - this->m_Area.offsetY;
        if (this->m_Area.fromY < 0)
            this->m_Area.fromY = 0;
        else if (this->m_Area.fromY > this->maxSizeWorldGrid.y)
            this->m_Area.fromY = this->maxSizeWorldGrid.y;

        this->m_Area.toY = gridPosition.y + this->m_Area.offsetY;
        if (this->m_Area.toY < 0)
            this->m_Area.toY = 0;
        else if (this->m_Area.toY > this->maxSizeWorldGrid.y)
            this->m_Area.toY = this->maxSizeWorldGrid.y;
    }

    sf::FloatRect renrect(
        this->m_Area.fromX * this->m_dnoice.gridSize, this->m_Area.fromY * this->m_dnoice.gridSize,
        this->m_Area.toX * this->m_dnoice.gridSize, this->m_Area.toY * this->m_dnoice.gridSize);

    for (int x = this->m_Area.fromX; x < this->m_Area.toX; x++)
        for (int y = this->m_Area.fromY; y < this->m_Area.toY; y++)
            this->tilemap[x][y][0]->render(target);

    if (!this->m_TreeArray.empty())
        for (auto it : this->m_TreeArray)
            if (renrect.contains(it.getPosition()))
                target->draw(it);

    target->draw(this->bariere_box);
}