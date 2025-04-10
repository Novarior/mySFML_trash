#ifndef ENTITY_ITEM_HPP
#define ENTITY_ITEM_HPP

#include "../../../entitys/entity.hpp"
#include "../Item.hpp"

class EntityItem : public Entity {
private:
  // my item

public:
  EntityItem(std::shared_ptr<Item> _item)
      : Entity(entityEnum::entityBehaviorClass::ebc_ENTITY_ITEM,
               entityEnum::entityMovementState::ems_IDLE,
               entityEnum::entityState::es_DISABLED,
               entityEnum::entityDirection::ed_VOID) {
    // set position of item
    this->e_updateTexture(TextureManager::getTexture("items_stone"));
    this->m_sprite.setTexture(this->m_texture);

    e_setPosition(0.f, 0.f);
    // set item to entity
    this->createItemComponent(_item);
  }
  ~EntityItem() = default;

  // function for interact with item
  void e_interact(Entity &_eTarget) {
    // print to console that you interact with this entity
    std::cout << "You interact with " << e_item->getName() << std::endl;
    std::cout << e_item->getName() << " Disappeared in world" << std::endl;
    // add to inventory
    _eTarget.e_getInventory().addItem(std::move(e_item));
    // remove from world, die like a entity
    this->e_die();
  }

  // function for render & update item
  void e_update(const float &delta_time);
  void e_render(sf::RenderTarget &target, const bool show_hitbox = false);
};

#endif /* ENTITY_ITEM */
