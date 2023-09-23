#ifndef AI_OPTIONS_HPP
#define AI_OPTIONS_HPP
#include "../entity.hpp"

enum FollowTargetEnum { NONE,
    T_PLAYER,
    T_ENTITY,
    T_POINT };

class AIOption {
protected:
    Entity& entity;
    Entity& self;
    sf::CircleShape rad;
    float m_cooldown_attack = 0.f;
    float m_cooldown_attack_max = 1.f;

public:
    AIOption(Entity& self, Entity& entity)
        : self(self)
        , entity(entity)
    {
        rad = sf::CircleShape(25);
        rad.setOrigin(25, 25);
    }
    virtual ~AIOption() { }
    inline void updateCooldown(const float& delta_time)
    {
        if (this->m_cooldown_attack < this->m_cooldown_attack_max)
            this->m_cooldown_attack += 1.f * delta_time;
    }
    inline const bool getCooldown()
    {
        if (this->m_cooldown_attack >= this->m_cooldown_attack_max) {
            this->m_cooldown_attack = 0.f;
            return true;
        }
        return false;
    }
    virtual void update(const float& delta_time) = 0;
};
#endif