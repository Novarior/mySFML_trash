#include "block.hpp"

BrickBlock::BrickBlock(sf::Vector2f size, sf::Vector2f position,sf::Color color,bool collision)
{
    this->shape.setSize(size);
    this->shape.setPosition(position);
    this->shape.setFillColor(color);

    this->collision=collision;
    if(this->collision)
    {
        this->hitbox.setSize(size);
        this->hitbox.setPosition(position);
        this->hitbox.setFillColor(sf::Color::Transparent);
        this->hitbox.setOutlineColor(sf::Color::Red);
        this->hitbox.setOutlineThickness(0);
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
    return this->shape;
}

void BrickBlock::render(sf::RenderTarget* target)
{
    target->draw(this->shape);

    if(this->collision)
    target->draw(this->hitbox);
}