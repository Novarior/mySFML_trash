#include "attributes.hpp"

Attributes::Attributes() {
    this->m_attributes.health = 100;
    this->m_attributes.max_health = 100;
    this->m_attributes.regen = 1;

    this->m_attributes.experience_for_level = 100;
    this->m_attributes.experience = 0;
    this->m_attributes.level = 1;

    this->m_attributes.some_points = 0;
}
Attributes:: ~Attributes() {}

//functions for save and load attributes
std::string Attributes::saveAttributesAsString() {
    std::stringstream ss;
    ss << this->m_attributes.health << " " << this->m_attributes.max_health << " " << this->m_attributes.regen << " "
        << this->m_attributes.experience_for_level << " " << this->m_attributes.experience << " "
        << this->m_attributes.level << " " << this->m_attributes.some_points;

    return ss.str();
}

void Attributes::loadAttributesFromString(const std::string attributes_string) {
    std::stringstream ss(attributes_string);
    ss >> this->m_attributes.health >> this->m_attributes.max_health >> this->m_attributes.regen
        >> this->m_attributes.experience_for_level >> this->m_attributes.experience
        >> this->m_attributes.level >> this->m_attributes.some_points;
}

//chek if experience_for_level bigger than experience, if true level up and set experience to 0, after level up set experience_for_level to 1.5 * experience_for_level
void Attributes::chekForLevel(int experience) {
    if (this->m_attributes.experience >= this->m_attributes.experience_for_level) {
        this->m_attributes.level++;
        this->m_attributes.some_points += 5;
        this->m_attributes.experience = 0;
        this->m_attributes.experience_for_level = 100 + ((this->m_attributes.level - 1) * 65);
        //calculate new max health using max health and level and some_points
        this->m_attributes.max_health = 200 + std::floor(5 * (this->m_attributes.level - 1)) + (this->m_attributes.level * this->m_attributes.some_points + 10) * 18;

        //set health to max health
        this->m_attributes.health = this->m_attributes.max_health;
        //calculate new regen using max health and level
        this->m_attributes.regen = 1 + (this->m_attributes.level * 0.8 - 5) * 0.2;
    }
}

void Attributes::update(const float& delta_time) {
    //renerate health per second if health is not full
    if (this->m_attributes.health < this->m_attributes.max_health) {
        this->m_attributes.health += this->m_attributes.regen * delta_time;
        //chek if health is full
        if (this->m_attributes.health > this->m_attributes.max_health) {
            this->m_attributes.health = this->m_attributes.max_health;
        }
    }
};