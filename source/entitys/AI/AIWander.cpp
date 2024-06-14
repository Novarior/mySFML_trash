#include "AIWander.hpp"
#include "AIOption.hpp"

AIWander::AIWander(Entity& self, float radius)
    : AIOption(self, self)
    , _radius(radius)
{
    _center = _ai_self.e_getPosition() - sf::Vector2f(std::rand() & 20 - 10, std::rand() & 20 - 10);

    sf::Vector2f toCenter = _center - _ai_self.e_getPosition();
    float angleToCenter = std::atan2(toCenter.y, toCenter.x);

    // Добавьте случайное отклонение в пределах +/- 45 градусов
    float angle = angleToCenter + ((std::rand() % 90) - 45) * M_PI / 180.0f;

    _direction = sf::Vector2f(std::cos(angle), std::sin(angle));
    _distance = std::rand() % static_cast<int>(_radius); // Случайная дистанция в пределах радиуса
}

AIWander::~AIWander() { }

void AIWander::update(const float& delta_time)
{
    this->updateCooldown(delta_time);
    // Если сущность достигла своего цели, выберите новое случайное направление
    if (getCooldown()) {
        sf::Vector2f toCenter = _center - _ai_self.e_getPosition();
        float angleToCenter = std::atan2(toCenter.y, toCenter.x);

        // Добавьте случайное отклонение в пределах +/- 45 градусов
        float angle = angleToCenter + ((std::rand() % 90) - 45) * M_PI / 180.0f;

        _direction = sf::Vector2f(std::cos(angle), std::sin(angle));
        //_distance = std::rand() % static_cast<int>(_radius); // Случайная дистанция в пределах радиуса
    }

#if __MDEBUG__
    _line.clear();

    _line.setPrimitiveType(sf::Lines);
    // Отрисовка линии от сущности к центру
    _line.append(sf::Vertex(_ai_self.e_getPosition(), sf::Color::Red));
    _line.append(sf::Vertex(_ai_self.e_getPosition() + _direction * 20.f, sf::Color::Red));
    // отриовка линии от сущности к направлению
    _line.append(sf::Vertex(_ai_self.e_getPosition(), sf::Color::Green));
    _line.append(sf::Vertex(_center, sf::Color::Green));

#endif

    // Обновите позицию _self в соответствии с _direction и _distance
    _ai_self.e_move(_direction.x, _direction.y, delta_time);
    //_distance -= std::sqrt(_direction.x * _direction.x + _direction.y * _direction.y) * delta_time;
}