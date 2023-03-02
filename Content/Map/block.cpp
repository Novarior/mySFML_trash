#include "block.hpp"

BrickBlock::BrickBlock(sf::Vector2f size, sf::Vector2f position, sf::Color color, bool collision, sf::Texture& texture):m_Texture(texture)
{
    this->m_Shape.setSize(size);
    this->m_Shape.setPosition(position);
    this->m_Shape.setFillColor(color);
    this->m_Shape.setTexture(&this->m_Texture);

    this->collision = collision;

    if (this->collision)
    {
        this->m_Hitbox.setSize(size);
        this->m_Hitbox.setPosition(position);
        this->m_Hitbox.setFillColor(sf::Color::Transparent);
        this->m_Hitbox.setOutlineColor(sf::Color::Red);
        this->m_Hitbox.setOutlineThickness(0);
    }
}

BrickBlock::~BrickBlock()
{

}

const bool& BrickBlock::getCollision()
{
    return this->collision;
}

sf::RectangleShape& BrickBlock::getRectangleShape()
{
    return this->m_Shape;
}

void BrickBlock::render(sf::RenderTarget* target)
{
    target->draw(this->m_Shape);

    if (this->collision)
        target->draw(this->m_Hitbox);
}