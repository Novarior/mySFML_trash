#include "LSystem.hpp"

LSystem::LSystem()
{
}

LSystem::~LSystem()
{
}

void LSystem::generate()
{
    this->data.pos = sf::Vector2f(0, 0);
    this->data.angle = 90;
    this->data.length = 10;
    this->data.steps = 5;
    this->data.seed = 0;
    this->data.axiom = 's';
    this->sentence = axiom;
    for (int i = 0; i < this->data.steps; i++) {
        this->generateSentence();
        this->applyRules();
    }
}

void LSystem::generateSentence()
{
    std::string nextSentence;
    for (int i = 0; i < this->sentence.length(); i++) {
        char current = this->sentence[i];
        if (this->rules.find(current) != this->rules.end()) {
            nextSentence += this->rules[current];
        } else {
            nextSentence += current;
        }
    }
    sentence = nextSentence;
}

sf::Vector2f LSystem::rotate(sf::Vector2f v, float angle)
{
    float rad = angle * M_PI / 180;
    float x = v.x * cos(rad) - v.y * sin(rad);
    float y = v.x * sin(rad) + v.y * cos(rad);
    return sf::Vector2f(x, y);
}

void LSystem::applyRules()
{
    for (int i = 0; i < this->sentence.length(); i++) {
        char current = sentence[i];
        if (current == 'd') {
            sf::Vector2f nextPos = data.pos + this->rotate(sf::Vector2f(0, -this->data.length), this->data.angle);
            this->line.push_back(sf::Vertex(this->data.pos, sf::Color::White));
            this->line.push_back(sf::Vertex(nextPos, sf::Color::White));
            this->data.pos = nextPos;
        } else if (current == '+') {
            this->data.angle += data.angle;
        } else if (current == '-') {
            this->data.angle -= data.angle;
        } else if (current == '[') {
            this->stack.push(this->data);
        } else if (current == ']') {
            this->data = this->stack.top();
            this->stack.pop();
        }
    }
}

void LSystem::turtle(sf::RenderWindow& window)
{
    for (int i = 0; i < line.size(); i += 2) {
        window.draw(&line[i], 2, sf::Lines);
    }
}

void LSystem::setAxiom(std::string axiom)
{
    this->axiom = axiom;
}

void LSystem::setRules(std::map<char, std::string> rules)
{
    this->rules = rules;
}

void LSystem::setRule(char key, std::string value)
{
    rules[key] = value;
}

void LSystem::setAxiom(char axiom)
{
    this->axiom = axiom;
}
