#ifndef PLAYER_H
#define PLAYER_H
#include "entity.hpp"
class Player : public Entity {
private:
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    void e_update(const float& delta_time);
    void e_render(sf::RenderTarget& target, const bool show_hitbox = false);
};
#endif