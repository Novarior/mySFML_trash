#ifndef CPP_TEST_CLASS_HPP
#define CPP_TEST_CLASS_HPP
#include "../AI/AIFollow.hpp"
#include "../entity.hpp"

class TestEntity:public Entity
{
    private:
    AIFollow* m_AIFollow;

    void initMovament();

    public:
    TestEntity(sf::Vector2f spawn_pos, Entity& player);
    virtual ~TestEntity();

    void e_update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
    void e_render(sf::RenderTarget& target, const bool show_hitbox = false);
};
#endif