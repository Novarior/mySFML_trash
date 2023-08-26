#include "minimap.hpp"

namespace gui {

MiniMap::MiniMap()
{
    this->m_background.setSize(sf::Vector2f(200.f, 200.f));
    this->m_background.setFillColor(sf::Color(0, 0, 0, 150));
    this->m_background.setOutlineThickness(1.f);
    this->m_background.setOutlineColor(sf::Color::White);

    this->m_view.setSize(sf::Vector2f(200.f, 200.f));
    this->m_view.setFillColor(sf::Color(0, 0, 0, 0));
    this->m_view.setOutlineThickness(1.f);
    this->m_view.setOutlineColor(sf::Color::White);

    this->m_player.setSize(sf::Vector2f(5.f, 5.f));
    this->m_player.setFillColor(sf::Color::Red);
}

MiniMap::~MiniMap() { }

void MiniMap::update(sf::Vector2f playerPos)
{
    this->m_player.setPosition(playerPos.x / 10.f, playerPos.y / 10.f);
}

void MiniMap::render(sf::RenderTarget& target)
{
    target.draw(this->m_background);
    target.draw(this->m_view);
    target.draw(this->m_player);
}

} // namespace gui