#ifndef AI_OPTIONS_HPP
#define AI_OPTIONS_HPP
#include "../entity.hpp"

enum class FollowTargetEnum {
    Point, // follow for point
    target, // follow for target

    COUNT
};

// list for current actions
enum class stateTODO {
    Idle, // do nothing
    Wait, // wait before next action
    Moving, // move to target or point
    Patrol, // walk around
    Attack, // attack target

    COUNT
};

class AIOption {
protected:
    Entity& _ai_self;
    Entity& _ai_target;

    FollowTargetEnum _ai_follow_target;
    stateTODO _ai_state;

    sf::CircleShape _ai_rad;
    float _ai_cooldown_attack = 0.f;
    float _ai_cooldown_attack_max = 1.f;

    float _ai_time_for_action;
    float _ai_time_for_action_max = 2.5f;

public:
    AIOption(Entity& self, Entity& target)
        : _ai_self(self)
        , _ai_target(target)
    {
        _ai_rad = sf::CircleShape(25);
        _ai_rad.setOrigin(25, 25);
    }
    virtual ~AIOption() { }

    // attention, this functuions use in update() function for select next action

    inline void updateTimeForAction(const float& delta_time)
    {
        if (_ai_time_for_action < _ai_cooldown_attack_max)
            _ai_time_for_action += 1.f * delta_time;
    }

    // attention, this functuions use in update() function for select next action
    inline const bool getTimeForAction()
    {
        if (_ai_time_for_action >= _ai_cooldown_attack_max) {
            _ai_time_for_action = 0.f;
            return true;
        }
        // time for action is not ready, wait pls
        _ai_state = stateTODO::Wait;
        return false;
    }

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