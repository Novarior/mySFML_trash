#include "test.hpp"

void TestEntity::initMovament() {

}

TestEntity::TestEntity(sf::Vector2f spawn_pos, Entity& player) {
    this->m_AIFollow = new AIFollow(*this, player);
}

TestEntity::~TestEntity() {
    delete this->m_AIFollow;
}

void TestEntity::e_update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view) {}
void TestEntity::e_render(sf::RenderTarget& target, const bool show_hitbox) {}