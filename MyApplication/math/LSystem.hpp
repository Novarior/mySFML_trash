#ifndef CPP_MATH_LSYSTEM_HPP
#define CPP_MATH_LSYSTEM_HPP
#include "mymath.hpp"
struct GData {
    unsigned int seed;
    unsigned int steps;
    unsigned int angle;
    unsigned int length;
    char axiom;
    sf::Vector2f pos;
};
// l-system tree pifagor
// variables "s" and "d" mean "stop" and "Draw" respectively
// constants: "+" and "-" mean "turn left by angle" and "turn right by angle" respectively
// constatns: "[" and "]" mean "save position and angle on stack" and "restore position and angle from stack" respectively
// axiom: s

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
    std::vector<sf::Vertex> line;

    void generateSentence();
    void applyRules();
    void turtle(sf::RenderWindow& window);
    sf::Vector2f rotate(sf::Vector2f v, float angle);

public:
    LSystem();
    ~LSystem();

    void generate();
    void setAxiom(std::string axiom);
    void setRules(std::map<char, std::string> rules);
    void setRule(char key, std::string value);
    void setAxiom(char axiom);
};
#endif // CPP_MATH_LSYSTEM_HPP