#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP
#include "../../header.h"
struct Atri
{
    float health;
    float max_health;
    float regen;

    int experience_for_level;
    int experience;
    int level;

    int some_points;

};

class Attributes
{
    private:
    Atri m_attributes;

    public:
    Attributes();
    virtual ~Attributes();

    //functions for save and load attributes
    std::string saveAttributesAsString();
    void loadAttributesFromString(const std::string attributes_string);

    //functions for get and set attributes
    float getMaxHealth() { return this->m_attributes.max_health; }
    void setMaxHealth(float health) { this->m_attributes.max_health = health; }
    float getCurrentHealth() { return this->m_attributes.health; }
    void setCurrentHealth(float health) { this->m_attributes.health = health; }


    //chek if experience_for_level 
    void chekForLevel(int experience);
    void addExperience(int experience) { this->m_attributes.experience += experience; }

    //get and set experience
    int getExperience() { return this->m_attributes.experience; }
    void setExperience(int experience) { this->m_attributes.experience = experience; }

    Atri* getAttributes() { return &this->m_attributes; }
    void setAttributes(Atri attributes) { this->m_attributes = attributes; }

    void update(const float& delta_time);
};
#endif // ATTRIBUTES_HPP