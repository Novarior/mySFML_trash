#ifndef GUI_PROGRESSBAR_HPP
#define GUI_PROGRESSBAR_HPP
#include "../../header.h"

namespace gui {
class ProgressBar {
private:
    std::string barString;
    sf::Text text;
    float maxWidth;
    sf::RectangleShape back;
    sf::RectangleShape inner;

public:
    ProgressBar(sf::Vector2f pos, sf::Vector2f size,
        sf::Color inner_color, unsigned character_size,
        sf::Vector2f resolution, sf::Font& font);
    ~ProgressBar();

    // Accessors

    // Modifiers

    // Functions
    void update(const int current_value, const int max_value);
    void render(sf::RenderTarget& target);
};
} // namespace gui
#endif // !GUI_PROGRESSBAR_HPP