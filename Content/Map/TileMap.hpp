#ifndef CPP_MAP_TILEMAP_HPP
#define CPP_MAP_TILEMAP_HPP
#include "block.hpp"
#include "../../math/ProcessGenerationNoice.hpp"

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
    std::vector<std::vector<BrickBlock* > > tilemap;
    std::map<std::string, sf::Texture> m_TexturesList;

    void Clear();
    void loadTextuteMap();

    public:
    TileMap(noiceData datanoice, ProcessGenerationNoice* noice);
    virtual ~TileMap();

    const sf::Vector2u getMapSizeOnTiles();
    const sf::Vector2f getMapSizeOnFloat();

    renderArea getRenderArea();


    void render(sf::RenderTarget* target, const sf::Vector2i& gridPosition, const bool debug);
};
#endif