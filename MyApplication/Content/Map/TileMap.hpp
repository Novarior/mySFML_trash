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
    sf::Vector2u maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldFloat;
    noiceData m_dnoice;
    ProcessGenerationNoice mGen_noice;
    std::vector<std::vector<std::vector<BrickBlock*>>> tilemap;
    std::vector<sf::Vector2f> m_listGrassBlocks;
    std::map<std::string, sf::Texture> m_TexturesList;
    sf::RectangleShape bariere_box;
    sf::FloatRect checkreck;
    std::vector<sf::Texture> listTrees;
    std::vector<sf::RectangleShape> trees;

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

    const sf::Vector2u getMapSizeOnTiles();
    const sf::Vector2f getMapSizeOnFloat();

    void updateWorldBoundsCollision(Entity* entity);
    void updateTileCollision(Entity* entity, const float& delta_time);
    void updateAnimationTiles(const float& delta_time);
    void updateRenderArea(const sf::Vector2i& playerPosition_grid);
    void update(Entity* entity, const float& delta_time);

    // get array with grassblock
    std::vector<sf::Vector2f> getSpawnPosArray();

    sf::FloatRect getGlobalBounds(const unsigned int x, const unsigned int Y) const;
    bool getCollision(const unsigned int x, const unsigned int y) const;

    rectangleWithOffset getRenderArea();
    void render(sf::RenderTarget* target);
};
#endif