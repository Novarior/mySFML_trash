#ifndef CPP_MAP_TILEMAP_HPP
#define CPP_MAP_TILEMAP_HPP
#include "block.hpp"

#include "../../entitys/entity.hpp"
#include "../../math/ProcessGenerationNoice.hpp"

class Entity;

struct rectangleWithOffset {
    int fromX;
    int fromY;
    int toX;
    int toY;

    int offsetX;
    int offsetY;
};

class TileMap {
private:
    rectangleWithOffset m_renderArea;
    rectangleWithOffset m_colisionArea;

    sf::Vector2i worldSizeGrid;
    sf::Vector2f worldSizeFloat;
    noiceData m_dnoice;
    ProcessGenerationNoice mGen_noice;
    std::vector<std::vector<std::vector<BrickBlock*>>> tilemap;
    std::vector<sf::Vector2f> m_listGrassBlocks;
    std::map<std::string, sf::Texture> m_TexturesList;
    sf::RectangleShape bariere_box;
    sf::FloatRect checkreck;
    std::vector<sf::Texture> listTrees;
    std::vector<sf::RectangleShape> trees;
    sf::Image minimapImage;

    float keyTime;
    float keyTimeMax;
    void updateKeyTime(const float& delta_time);
    const bool getKeyTime();

    void Clear();
    void loadTextuteMap();
    void generateMap();

    void pushTree(int x, int y);
    void initTrees();

public:
    TileMap(noiceData datanoice, ProcessGenerationNoice* noice);
    virtual ~TileMap();

    inline const sf::Image& getMinimapImage() { return this->minimapImage; }
    inline const sf::Vector2i& getMapSizeOnTiles() { return this->worldSizeGrid; }
    inline const sf::Vector2f& getMapSizeOnFloat() { return this->worldSizeFloat; }
    inline const rectangleWithOffset& getRenderArea() { return this->m_renderArea; }

    void updateWorldBoundsCollision(Entity* entity);
    void updateTileCollision(Entity* entity, const float& delta_time);
    void updateAnimationTiles(const float& delta_time);
    void updateRenderArea(const sf::Vector2i& playerPosition_grid);
    void update(Entity* entity, const float& delta_time);

    // get array with grassblock
    std::vector<sf::Vector2f>& getSpawnPosArray() { return this->m_listGrassBlocks; }

    sf::FloatRect getGlobalBounds(const unsigned int x, const unsigned int Y) const;
    bool getCollision(const unsigned int x, const unsigned int y) const;

    void render(sf::RenderTarget* target);
};
#endif