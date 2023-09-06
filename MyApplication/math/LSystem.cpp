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
    this->data.angle = 20;
    this->data.currentAngle = 0;
    this->data.length = 10;
    this->data.steps = 13;
    this->data.width = 16;
    this->data.chanceSkip = 40;
    this->data.seed = 0;
    this->data.axiom = 's';
    this->sentence = axiom;
    for (int i = 0; i < this->data.steps; i++) {
        this->generateSentence();
    }
    this->applyRules();
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
    this->sentence = nextSentence;
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
    // add litle random to angles and length
    // rangom angle from 0 to 45
    // random length from 10 to 30
    srand(std::time(NULL));
    this->data.seed++;
    int randangle = 0;
    int randlength = 0;
    sf::Vector2f nextPos;
    sf::RectangleShape bufferShape;

    randangle = rand() % 25;
    for (int i = 0; i < this->sentence.length(); i++) {
        char current = sentence[i];
        // charset s, d, q, [, ], +, -
        if (current == 'd') {
            int chance = rand() % 100;
            if (chance < this->data.chanceSkip) {
                continue;
            }
            // calculate next pos
            nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -(this->data.length + randlength)), this->data.currentAngle);
            // push shape
            bufferShape.setSize(sf::Vector2f(this->data.width, this->data.length + randlength));
            //   bufferShape.setOrigin(sf::Vector2f(this->data.width / 2, 0));
            bufferShape.setPosition(this->data.pos + data.offsetPos);
            bufferShape.setRotation(this->data.currentAngle);
            bufferShape.setFillColor(sf::Color::Red);
            this->line.push_back(bufferShape);
            // set pos to next pos
            this->data.pos = nextPos;
        } else if (current == 's') {
            // add leafs
            // calculate next pos
            nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -(this->data.length + randlength)), this->data.currentAngle);
            // push shape
            bufferShape.setSize(sf::Vector2f(this->data.width * 2, this->data.length + randlength));
            //  bufferShape.setOrigin(sf::Vector2f(this->data.width / 2, 0));
            bufferShape.setPosition(this->data.pos + data.offsetPos);
            bufferShape.setRotation(this->data.currentAngle);
            bufferShape.setFillColor(sf::Color::Green);
            this->line.push_back(bufferShape);
            // set pos to next pos
            this->data.pos = nextPos;
        } else if (current == 'q') {
            int chance = rand() % 100;
            if (chance < this->data.chanceSkip) {
                continue;
            }
            // calculate next pos
            nextPos = this->data.pos + this->rotate(sf::Vector2f(0, (-(this->data.length + randlength))), this->data.currentAngle);
            // push shape
            bufferShape.setSize(sf::Vector2f(this->data.width, this->data.length + randlength));
            bufferShape.setOrigin(sf::Vector2f(this->data.width / 2, 0));
            bufferShape.setPosition(this->data.pos + data.offsetPos);
            bufferShape.setRotation(this->data.currentAngle);
            bufferShape.setFillColor(sf::Color::Blue);
            this->line.push_back(bufferShape);
            // set pos to next pos
            this->data.pos = nextPos;
        } else if (current == '+') {
            randangle = rand() % 30 - 15;
            this->data.currentAngle += (data.angle + randangle);
        } else if (current == '-') {
            randangle = rand() % 30 - 15;
            this->data.currentAngle -= (data.angle + randangle);
        } else if (current == '[') {
            this->data.width *= 0.75;
            this->stack.push(this->data);
        } else if (current == ']') {
            this->data = this->stack.top();
            this->stack.pop();
        }
    }
}

void LSystem::update(const float& delta_time)
{
}

void LSystem::render(sf::RenderTarget& target)
{ // render shapes
    for (auto& shape : this->line)
        target.draw(shape);
}