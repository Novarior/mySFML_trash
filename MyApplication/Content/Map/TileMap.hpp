#ifndef CPP_MAP_TILEMAP_HPP
#define CPP_MAP_TILEMAP_HPP
#include "TreeList.h"
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
    std::vector<std::vector<std::vector<BrickBlock*>>> tilemap;
    std::map<std::string, sf::Texture> m_TexturesList;
    std::vector<sf::Sprite> m_TreeArray;
    sf::Texture m_TreeTexture;
    sf::Sprite m_TreeSprite;
    sf::RectangleShape bariere_box;
    sf::FloatRect checkreck;

    float keyTime;
    float keyTimeMax;
    void updateKeyTime(const float& delta_time);
    const bool getKeyTime();

    void Clear();
    void loadTextuteMap();
    void pushTree(int x, int y, int seed);

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

    sf::FloatRect getGlobalBounds(const unsigned int x, const unsigned int Y) const;
    bool getCollision(const unsigned int x, const unsigned int y) const;

    rectangleWithOffset getRenderArea();
    void render(sf::RenderTarget* target);
};
#endif