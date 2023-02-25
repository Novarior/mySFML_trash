#include "entity.hpp"

void Entity::initHitboxAndSprite()
{
    this->e_hitbox = NULL;
}
void Entity::initMovement()
{
    this->e_movement = NULL;
}
void Entity::initSomeinit()
{
    this->isAlive = true;
    this->isFall = false;
    this->isDuck = false;
    this->isJump = false;
    this->isCollision = false;
    this->mState = IDLE;
}

void Entity::initHitbox()
{
}


Entity::Entity()
{
    this->initHitboxAndSprite();
    this->initHitbox();
    this->initMovement();
    this->initSomeinit();
}
Entity::~Entity()
{
}

HitboxCounter* Entity::getHitbox()
{
    return this->e_hitbox;
}

Movement* Entity::getMovement()
{
    return this->e_movement;
}

void Entity::e_move(sf::Vector2f directionalmove,const float& deltaTime)
{
    this->e_movement->move(directionalmove,deltaTime);

        this->mState = IDLE;
    if(this->e_movement->getVelocity().x!=0 || this->e_movement->getVelocity().y!=0)
    {
        this->mState = WALK;
    }
}
void Entity::e_updateAnimation(std::string keyNameAnimation, const float& deltaTime)
{
    if(this->isDuck)
    {
        this->sprite.setScale(sf::Vector2f(1.f,0.5f));
    }
    else
    {
        this->sprite.setScale(sf::Vector2f(1.f,1.f));
    }
}
void Entity::e_updateHitbox(sf::IntRect rectEntity, sf::IntRect rectCollision)
{
    this->e_hitbox->update();
}

sf::Vector2f Entity::e_getPosition()
{
    return this->sprite.getPosition();
}
sf::Vector2i Entity::e_getGridPosition(unsigned int grisSize)
{
    return sf::Vector2i(this->sprite.getPosition().x / grisSize,this->sprite.getPosition().y / grisSize);
}
sf::Vector2f Entity::e_getVelocity()
{
    return this->e_movement->getVelocity();
}
void Entity::e_updateCollison(TileMap* map, const float& deltatime)
{
    this->e_movement->updateCollison(map, deltatime);
}

void Entity::e_jump(const float& deltatime)
{
    this->e_movement->jump(deltatime);
}