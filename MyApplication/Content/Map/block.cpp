#include "block.hpp"

BrickBlock::BrickBlock(sf::Vector2f size, sf::Vector2f position, sf::Color color, bool collision,
    sf::Texture& texture, unsigned short type, bool isAnim)
    : m_Texture(texture)
    , m_type(type)
    , m_isAnim(isAnim)
    , m_collision(collision)
    , m_size(size)
{
    this->m_sprite.setPosition(position);
    this->m_sprite.setColor(color);
    this->m_sprite.setTexture(this->m_Texture);
    this->m_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));

    if (isAnim) {
        this->currentFrame = 0;
        this->framesCounter = this->m_sprite.getTexture()->getSize().y / size.y;
    }
}

BrickBlock::~BrickBlock()
{
}

void BrickBlock::updateFrame()
{
    this->currentFrame++;
}

const sf::FloatRect BrickBlock::getGlobalBounds()
{
    return this->m_sprite.getGlobalBounds();
}

const bool BrickBlock::intersects(sf::FloatRect rect)
{
    return this->m_sprite.getGlobalBounds().intersects(rect);
}

void BrickBlock::updateAnimation()
{
    if (this->m_isAnim) {
        if (this->currentFrame >= this->framesCounter)
            this->currentFrame = 0;

        this->m_sprite.setTextureRect(sf::IntRect(0, this->currentFrame * this->m_size.y,
            this->m_size.x, this->m_size.y));
    }
}

void BrickBlock::render(sf::RenderTarget* target)
{
    target->draw(this->m_sprite);
}