#ifndef CPP_MATH_LSYSTEM_HPP
#define CPP_MATH_LSYSTEM_HPP
#include "mymath.hpp"
struct GData {
    unsigned int seed;
    unsigned int steps;
    float angle;
    float currentAngle;
    unsigned chanceSkip;
    float length;
    float width;
    std::uint8_t alpha;
    sf::Vector2f offsetPos;
    sf::Vector2f pos;
};
// l-system tree pifagor
// variables "s" and "d" mean "stop" and "Draw" respectively
// constants: "[" and "]" mean "save position and angle on stack" and "restore position and angle from stack" respectively
// constants: "+" and "-" mean "turn left" and "turn right" respectively
//  axiom: s
// charset: s, d, q, [, ], +, -
// rules:
// d -> d[+d][-d]
// s -> d[+s][-s]s

class LSystem {
private:
    GData data;
    std::string axiom;
    std::string sentence;
    std::map<char, std::string> rules;
    std::stack<GData> stack;
    std::vector<sf::RectangleShape> line;

    void generateSentence();
    void applyRules();

    sf::Vector2f rotate(sf::Vector2f v, float angle);

public:
    LSystem();
    ~LSystem();
    // get all sf::RectangleShape on array
    sf::RectangleShape* internalArray() { return this->line.data(); }
    size_t getSizeArray() { return this->line.size(); }

    void generate();
    void setAxiom(std::string axiom) { this->axiom = axiom; }
    void setRules(std::map<char, std::string> rules) { this->rules = rules; }
    void setRule(char key, std::string value) { this->rules[key] = value; }
    void setAxiom(char axiom) { this->axiom = axiom; }
    void setOffsetPos(sf::Vector2f offsetPos) { this->data.offsetPos = offsetPos; }
    void update(const float& delta_time);
    void render(sf::RenderTarget& target);
};
#endif // CPP_MATH_LSYSTEM_HPP