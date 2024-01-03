#ifndef AI_OPTIONS_HPP
#define AI_OPTIONS_HPP
#include "../entity.hpp"

enum class FollowTargetEnum { NONE,
    T_PLAYER,
    T_ENTITY,
    T_POINT };

class AIOption {
protected:
    Entity& _ai_entity;
    Entity& _ai_self;
    sf::CircleShape _ai_rad;
    float _ai_cooldown_attack = 0.f;
    float _ai_cooldown_attack_max = 1.f;

public:
    AIOption(Entity& self, Entity& entity)
        : _ai_self(self)
        , _ai_entity(entity)
    {
        _ai_rad = sf::CircleShape(25);
        _ai_rad.setOrigin(25, 25);
    }
    virtual ~AIOption() { }
    inline void updateCooldown(const float& delta_time)
    {
        if (_ai_cooldown_attack < _ai_cooldown_attack_max)
            _ai_cooldown_attack += 1.f * delta_time;
    }
    inline const bool getCooldown()
    {
        if (_ai_cooldown_attack >= _ai_cooldown_attack_max) {
            _ai_cooldown_attack = 0.f;
            return true;
        }
        return false;
    }
    virtual void update(const float& delta_time) = 0;
};
#endif