#ifndef GUI_SIMPLE_SLIDER_HPP
#define GUI_SIMPLE_SLIDER_HPP

#include "../../header.h"

namespace gui {
template <typename T>
class Slider {
private:
    sf::RectangleShape _counterBox;
    sf::RectangleShape _sliderBox;
    sf::RectangleShape _sliderFillBox;
    sf::CircleShape _sliderCircle;

    sf::Text _text;
    sf::Font& _font;
    T _value;
    T _min;
    T _max;
    T _step;

public:
    Slider(sf::Vector2f position, sf::Vector2f size, sf::Font& font, T base_value, T min_val, T max_val, T step)
        : _font(font)
        , _value(base_value)
        , _min(min_val)
        , _max(max_val)
        , _step(step)
    {

        _counterBox.setPosition(position);
        _counterBox.setSize(size);
        _counterBox.setFillColor(sf::Color(50, 50, 50, 200));

        _sliderBox.setPosition(position.x, position.y + size.y / 3.f);
        _sliderBox.setSize(sf::Vector2f(size.x, size.y / 3.f));
        _sliderBox.setFillColor(sf::Color(100, 100, 100, 200));

        float ratio = static_cast<float>(_value - _min) / (_max - _min);
        _sliderFillBox.setPosition(position.x, position.y + size.y / 3.f);
        _sliderFillBox.setSize(sf::Vector2f(size.x * ratio, size.y / 3.f));
        _sliderFillBox.setFillColor(sf::Color(200, 200, 200, 200));

        _sliderCircle.setPosition(position.x + size.x * ratio - size.y / 6.f, position.y + size.y / 3.f);
        _sliderCircle.setRadius(size.y / 6.f);
        _sliderCircle.setFillColor(sf::Color::White);
        _sliderCircle.setOutlineThickness(1.f);
        _sliderCircle.setOutlineColor(sf::Color::Black);

        _text.setFont(_font);
        _text.setCharacterSize(static_cast<unsigned int>(size.y / 2.f));
        _text.setPosition(position);
        _text.setFillColor(sf::Color::White);
    }

    // destructor
    ~Slider() { }

    T getValue() const { return _value; }

    // update slider (cricles) position and value using mouse position
    // if mouse is on slider, slider is litle bit bigger and litle bit red
    void update(const sf::Vector2f& mouse_pos_view)
    {
        if (_sliderCircle.getGlobalBounds().contains(mouse_pos_view)) {
            _sliderCircle.setFillColor(sf::Color::Red);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // Обновляем позицию слайдера в соответствии с положением мыши
                float new_x = mouse_pos_view.x - _sliderCircle.getRadius();
                new_x = std::max(new_x, _sliderBox.getPosition().x);
                new_x = std::min(new_x, _sliderBox.getPosition().x + _sliderBox.getSize().x - 2 * _sliderCircle.getRadius());
                _sliderCircle.setPosition(new_x, _sliderCircle.getPosition().y);

                // Обновляем значение слайдера
                float ratio = (new_x - _sliderBox.getPosition().x) / (_sliderBox.getSize().x - 2 * _sliderCircle.getRadius());
                _value = _min + ratio * (_max - _min);

                // Обновляем заполненность слайдера
                _sliderFillBox.setSize({ ratio * _sliderBox.getSize().x, _sliderFillBox.getSize().y });
            }
        } else if (_sliderBox.getGlobalBounds().contains(mouse_pos_view) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // Обновляем позицию слайдера в соответствии с положением мыши
            float new_x = mouse_pos_view.x - _sliderCircle.getRadius();
            new_x = std::max(new_x, _sliderBox.getPosition().x);
            new_x = std::min(new_x, _sliderBox.getPosition().x + _sliderBox.getSize().x - 2 * _sliderCircle.getRadius());
            _sliderCircle.setPosition(new_x, _sliderCircle.getPosition().y);

            // Обновляем значение слайдера
            float ratio = (new_x - _sliderBox.getPosition().x) / (_sliderBox.getSize().x - 2 * _sliderCircle.getRadius());
            _value = _min + ratio * (_max - _min);

            // Обновляем заполненность слайдера
            _sliderFillBox.setSize({ ratio * _sliderBox.getSize().x, _sliderFillBox.getSize().y });
        } else {
            _sliderCircle.setFillColor(sf::Color::White);
        }
    }
    // render slider
    void render(sf::RenderTarget& target)
    {
        target.draw(_counterBox);
        target.draw(_sliderBox);
        target.draw(_sliderFillBox);
        target.draw(_sliderCircle);
        target.draw(_text);
    }
}; // namespace gui

typedef Slider<int> SliderInt;
typedef Slider<unsigned int> SliderUInt;
typedef Slider<float> SliderFloat;

};
#endif // !GUI_SIMPLE_SLIDER_HPP