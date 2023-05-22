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

//functions for get and set attributes
float Attributes::getHealth() {
    return this->m_attributes.health;
}

void Attributes::setHealth(float health) {
    this->m_attributes.health = health;
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

//add experience to experience
void Attributes::addExperience(int experience) {
    this->m_attributes.experience += experience;
    this->chekForLevel(experience);
}

//get and set experience
int Attributes::getExperience() {
    return this->m_attributes.experience;
}
void Attributes::setExperience(int experience) {
    this->m_attributes.experience = experience;
}

Attributes::Atri* Attributes::getAttributes() {
    return &this->m_attributes;
}

void Attributes::setAttributes(Atri attributes) {
    this->m_attributes = attributes;
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