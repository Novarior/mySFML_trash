#ifndef CPP_MAP_TILEMAP_HPP
#define CPP_MAP_TILEMAP_HPP
#include "block.hpp"
#include "TreeList.h"
#include "../../math/ProcessGenerationNoice.hpp"
#include "texture list.h"

/** */
const struct renderArea
{
    int fromX;
    int fromY;
    int toX;
    int toY;

    int offsetX;
    int offsetY;
};

class TileMap
{
    private:
    renderArea m_Area;
    sf::Vector2u maxSizeWorldGrid;
    sf::Vector2f maxSizeWorldFloat;
    noiceData m_dnoice;
    std::vector<std::vector<std::vector<BrickBlock* >  > > tilemap;
    std::map<std::string, sf::Texture> m_TexturesList;
    std::vector<sf::Sprite> m_TreeArray;
    sf::Texture m_TreeTexture;
    sf::Sprite m_TreeSprite;

    void Clear();
    void loadTextuteMap();
    void pushTree(int x, int y, int seed);

    public:
    TileMap(noiceData datanoice, ProcessGenerationNoice* noice);
    virtual ~TileMap();

    const sf::Vector2u getMapSizeOnTiles();
    const sf::Vector2f getMapSizeOnFloat();

    sf::FloatRect getGlobalBounds(const unsigned int x, const unsigned int Y) const;
    const bool getCollision(const unsigned int x, const unsigned int y) const;

    renderArea getRenderArea();

    void render(sf::RenderTarget* target, const sf::Vector2i& gridPosition, const bool debug);
};
#endif