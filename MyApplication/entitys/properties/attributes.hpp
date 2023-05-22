#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP
#include "../../header.h"

class Attributes
{
    private:
    struct Atri
    {
        float health;
        float max_health;
        float regen;

        int experience_for_level;
        int experience;
        int level;

        int some_points;

    } m_attributes;

    public:
    Attributes();
    virtual ~Attributes();

    //functions for get and set attributes
    float getHealth();
    void setHealth(float health);

    //chek if experience_for_level bigger than experience, if true level up and set experience to 0, after level up set experience_for_level to 1.5 * experience_for_level
    void chekForLevel(int experience);

    //add experience to experience
    void addExperience(int experience);

    //get and set experience
    int getExperience();
    void setExperience(int experience);

    Atri* getAttributes();
    void setAttributes(Atri attributes);

    void update(const float& delta_time);
};
#endif // ATTRIBUTES_HPP