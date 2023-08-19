#ifndef PLAYER_H
#define PLAYER_H
#include "entity.hpp"
class Player : public Entity {
private:
public:
    Player(sf::Vector2f pos);
    virtual ~Player();

    void e_update(const float& delta_time);
    void e_render(sf::RenderTarget& target, const bool show_hitbox = false);
};
#endif