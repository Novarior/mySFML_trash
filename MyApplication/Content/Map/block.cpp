#include "block.hpp"

BrickBlock::BrickBlock(sf::Vector2f size, sf::Vector2f position, sf::Color color, bool collision,
    sf::Texture& texture, unsigned short type)
    : m_Texture(texture)
    , m_type(type)
{
    this->m_Shape.setSize(size);
    this->m_Shape.setPosition(position);
    this->m_Shape.setFillColor(color);
    this->m_Shape.setTexture(&this->m_Texture);

    this->m_collision = collision;

    if (this->m_collision) {
        this->m_Hitbox.setSize(size);
        this->m_Hitbox.setPosition(position);
        this->m_Hitbox.setFillColor(sf::Color::Transparent);
        this->m_Hitbox.setOutlineColor(sf::Color::Red);
        this->m_Hitbox.setOutlineThickness(-1);
    }
}

BrickBlock::~BrickBlock()
{
}

const bool& BrickBlock::getCollision()
{
    if (this->m_collision)
        this->m_Hitbox.setOutlineColor(sf::Color::Green);

    return this->m_collision;
}

const sf::FloatRect BrickBlock::getGlobalBounds()
{
    return this->m_Shape.getGlobalBounds();
}

sf::RectangleShape& BrickBlock::getRectangleShape()
{
    return this->m_Shape;
}

const bool BrickBlock::intersects(sf::FloatRect rect)
{
    return this->m_Shape.getGlobalBounds().intersects(rect);
}

void BrickBlock::update()
{
}

void BrickBlock::render(sf::RenderTarget* target, const bool draw_collision)
{
    target->draw(this->m_Shape);

    if (this->m_collision && draw_collision)
        target->draw(this->m_Hitbox);
}