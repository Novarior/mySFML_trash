#ifndef GUI_SIMPLE_COMPONENTS_MINIMAP_HPP
#define GUI_SIMPLE_COMPONENTS_MINIMAP_HPP
#include "../GUISYS.hpp"

namespace gui {
class MiniMap {
private:
    sf::Texture m_texture;
    sf::Image m_image;
    sf::RectangleShape m_background;
    sf::RectangleShape m_view;
    sf::RectangleShape m_player;
    sf::IntRect m_worldBounds;

public:
    MiniMap(const sf::Vector2f m_position, const sf::Vector2f m_size, sf::IntRect worldSize);
    ~MiniMap();

    void setTexture(sf::Texture texture) { this->m_texture = texture; }
    void setImage(sf::Image image)
    {
        this->m_image = image;
        this->m_texture.loadFromImage(this->m_image);
        this->m_background.setTexture(&this->m_texture);
    }

    void update(sf::Vector2f playerPos);
    void render(sf::RenderTarget& target);
};
}
#endif // !GUI_COMPONENTS_MINIMAP_HPP