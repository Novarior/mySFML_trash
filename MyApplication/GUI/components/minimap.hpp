#ifndef GUI_COMPONENTS_MINIMAP_HPP
#define GUI_COMPONENTS_MINIMAP_HPP
#include "../GUISYS.hpp"

namespace gui {
class MiniMap {
private:
    sf::Texture m_texture;
    sf::Image m_image;
    sf::RectangleShape m_background;
    sf::RectangleShape m_view;
    sf::RectangleShape m_player;

public:
    MiniMap();
    ~MiniMap();

    void setTexture(sf::Texture texture) { this->m_texture = texture; }
    void setImage(sf::Image image) { this->m_image = image; }

    void update(sf::Vector2f playerPos);
    void render(sf::RenderTarget& target);
};
}
#endif // !GUI_COMPONENTS_MINIMAP_HPP