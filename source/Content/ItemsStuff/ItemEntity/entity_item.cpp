#include "entity_item.hpp"

void EntityItem::e_update(const float &delta_time) {}

void EntityItem::e_render(sf::RenderTarget &target, const bool show_hitbox) {
  target.draw(this->m_sprite);
  if (show_hitbox) {
    this->e_hitbox->render(target);
  }
}