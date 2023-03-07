#include "TileMap.hpp"

void TileMap::Clear() {
    if (!this->tilemap.empty()) {
        for (int x = 0; x < this->tilemap.size(); x++) {
            for (int y = 0; y < this->tilemap[x].size(); y++) {
                for (int z = 0; z < this->tilemap[x][y].size(); z++)
                {
                    delete this->tilemap[x][y][z];
                    this->tilemap[x][y][z] = NULL;
                }
                this->tilemap[x][y].clear();
            }
            this->tilemap.clear();
        }
    }
}

void TileMap::loadTextuteMap() {

    if (!this->m_TexturesList["GRASS"].loadFromFile(texture_DIRT));
    if (!this->m_TexturesList["STONE"].loadFromFile(texture_STONE));
    if (!this->m_TexturesList["OCEAN"].loadFromFile(texture_OCEAN));
    if (!this->m_TexturesList["SAND"].loadFromFile(texture_SAND));
    if (!this->m_TexturesList["DIRT"].loadFromFile(texture_DIRT));
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

TileMap::TileMap(noiceData datanoice, ProcessGenerationNoice* noice) {
    this->Clear();
    this->loadTextuteMap();

    double writebuff;
    bool collisionBuff;
    this->m_dnoice = datanoice;
    this->maxSizeWorldGrid = this->m_dnoice.mapSize;
    this->maxSizeWorldFloat = sf::Vector2f(this->m_dnoice.mapSize.x * datanoice.gridSize, this->m_dnoice.mapSize.y * datanoice.gridSize);

    this->m_Area.offsetX = (datanoice.RenderWindow.x / datanoice.gridSize / 4) + 4;
    this->m_Area.offsetY = (datanoice.RenderWindow.y / datanoice.gridSize / 4) + 4;
    this->m_Area.fromX = 0;
    this->m_Area.fromY = 0;
    this->m_Area.toX = 0;
    this->m_Area.toY = 0;

    sf::Color buff;
    if (this->m_TreeTexture.loadFromFile(texture_TREE))
    {
        this->m_TreeSprite.setTexture(this->m_TreeTexture);
        this->m_TreeTexture.setSmooth(true);
    }

    this->tilemap.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<BrickBlock*>>());

    for (int x = 0; x < this->m_dnoice.mapSize.x; x++) {
        this->tilemap[x].resize(this->maxSizeWorldGrid.y, std::vector<BrickBlock*>());
        for (int y = 0; y < this->m_dnoice.mapSize.y; y++) {
            writebuff = noice->getNoice(x, y);
            writebuff *= 255;
            writebuff = static_cast<int>(writebuff) % 255;
            if (writebuff < 0)
                writebuff = writebuff * -1;


            if (writebuff < 55)
            { //Ocean
                buff = sf::Color(0, 10 + writebuff * 1.6, 100 + writebuff * 1.9, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    true, this->m_TexturesList["OCEAN"], BLOCK_OCEAN));
            }
            else if (writebuff < 66)
            { //sand
                buff = sf::Color(140 + writebuff * 1.5, 120 + writebuff * 1.4, 80 + writebuff * 0.1, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    false, this->m_TexturesList["SAND"], BLOCK_SAND));
            }
            else if (writebuff < 160)
            { //grass
                buff = sf::Color(writebuff * 0.1, 50 + writebuff * 1.1, writebuff * 0.08, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    false, this->m_TexturesList["GRASS"], BLOCK_GRASS));

                if (rand() % 100 < 8)
                    this->pushTree(x, y, this->m_dnoice.seed);
            }
            else if (writebuff < 165)
            { //dirt
                buff = sf::Color(90 - writebuff * 0.1, 71 + writebuff * 0.15, 55 + writebuff * 0.1, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    false, this->m_TexturesList["DIRT"], BLOCK_DIRT));
            }
            else if (writebuff < 175)
            { //stone
                buff = sf::Color(40 + writebuff * 0.1, 71 - writebuff * 0.2, 55 - writebuff * 0.2, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    false, this->m_TexturesList["STONE"], BLOCK_STONE));
            }
            else
            { //other
                buff = sf::Color(writebuff, writebuff, writebuff, 255);
                this->tilemap[x][y].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize, this->m_dnoice.gridSize),
                    sf::Vector2f(x * this->m_dnoice.gridSize, y * this->m_dnoice.gridSize), buff,
                    true, this->m_TexturesList["GRASS"], NULL));
            }
        }
    }
}

TileMap::~TileMap() {
    this->Clear();
    this->m_TreeArray.clear();
}

renderArea TileMap::getRenderArea() {
    return this->m_Area;
}

const sf::Vector2u TileMap::getMapSizeOnTiles() {
    return this->maxSizeWorldGrid;
}

const sf::Vector2f TileMap::getMapSizeOnFloat() {
    return this->maxSizeWorldFloat;
}

const bool TileMap::getCollision(const unsigned int x, const unsigned int y) const
{
    return this->tilemap[x][y][0]->getCollision();
}

sf::FloatRect TileMap::getGlobalBounds(const unsigned int x, const unsigned int y) const
{
    return this->tilemap[x][y][0]->getGlobalBounds();
}

void TileMap::render(sf::RenderTarget* target, const sf::Vector2i& gridPosition, const bool debug) {
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
}