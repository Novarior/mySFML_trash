#include "slime.hpp"

Slime::Slime(float spawn_pos_x, float spawn_pos_y, Entity& targer_follow)
    : Entity(entityEnum::entityBehaviorClass::ENEMY,
        entityEnum::entityMovementState::IDLE,
        entityEnum::entityState::DISABLED,
        entityEnum::entityDirection::VOID)
{
    this->m_texture.loadFromFile(std::string(sAppFunctions::get_resources_dir() + myConst::slime_texture));
    this->m_sprite.setTexture(this->m_texture);
    this->m_sprite.setScale(0.02f, 0.02f);
    this->createHitboxComponent(this->m_sprite, 0.f, 0.f, 32.f, 32.f);
    this->createMovementComponent(3.f, 1.4f, 5.f);
    this->createAttributesComponent();

    this->e_setPosition(spawn_pos_x, spawn_pos_y);
    this->ai_component = std::make_unique<AIComponent>(*this, targer_follow);
    this->ai_component.get()->create_follow(150);
    this->ai_component.get()->create_attack();
}

Slime::~Slime() { }

void Slime::e_update(const float& delta_time)
{
    this->ai_component->update(delta_time);

    this->e_movement->update(delta_time);
    this->e_attributes->update(delta_time);
    this->e_hitbox->update();
}

void Slime::e_render(sf::RenderTarget& target, const bool show_hitbox)
{
    target.draw(this->m_sprite);

    if (show_hitbox)
        this->e_hitbox->render(target);
}
