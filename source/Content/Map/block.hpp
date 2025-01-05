#ifndef CPP_CONTENT_BLOCKS_HPP
#define CPP_CONTENT_BLOCKS_HPP
#include "../../core/header.h"

enum BLOCKTYPE { NAN_DEF = 0,
    BLOCK_GRASS,
    BLOCK_SAND,
    BLOCK_OCEAN,
    BLOCK_OCEAN_ANIM,
    BLOCK_STONE,
    BLOCK_DIRT,
    BLOCK_MUD };

class BrickBlock {
private:
    sf::Sprite m_sprite;
    sf::Texture& m_Texture;
    bool m_collision;
    bool m_isAnim;
    const unsigned short m_type;
    static unsigned currentFrame;
    unsigned framesCounter;
    bool isSetTree;
    sf::Vector2f m_size;

public:
    BrickBlock(sf::Vector2f size, sf::Vector2f position, sf::Color color, bool collosion, sf::Texture& texture, unsigned short type, bool isAnim = false, bool isSetTree = false);
    virtual ~BrickBlock();

    const sf::FloatRect getGlobalBounds();
    const bool intersects(sf::IntRect rect);
    inline const bool& getCollision() { return this->m_collision; }
    void updateFrame();
    sf::Color getBlockColor() { return this->m_sprite.getColor(); }

    void updateAnimation();
    void render(sf::RenderTarget* target);
};

#endif