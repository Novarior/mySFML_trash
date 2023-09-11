#include "LSystem.hpp"

LSystem::LSystem()
{
}

LSystem::~LSystem()
{
}

void LSystem::generate()
{
    this->line.clear();
    this->data.pos = sf::Vector2f(0, 0);
    this->data.angle = 15;
    this->data.currentAngle = 0;
    this->data.length = 20;
    this->data.steps = 13;
    this->data.alpha = 255;
    this->data.width = 11;
    this->data.chanceSkip = 60;
    this->data.seed = 0;
    this->axiom = "qqqqqs";
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
    sf::Vector2f localoffsetPos = { 2.0f, 2.0f };
    sf::CircleShape bufferShape;
    int chance = rand() % 100;
    for (int i = 0; i < this->sentence.length(); i++) {
        chance = rand() % 100;
        char current = sentence[i];
        // charset s, d, q, [, ], +, -
        if (current == 'd' || current == 'q') { // red segment
            if (chance < this->data.chanceSkip)
                continue;
            // calculate next pos
            nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -this->data.length), this->data.currentAngle);
            // push thre shapes half transparent wite and black
            bufferShape.setRadius(this->data.length);
            bufferShape.setOrigin(sf::Vector2f(this->data.length / 2, 0));
            bufferShape.setPosition(nextPos + data.offsetPos);

            // withe shape
            bufferShape.setFillColor(sf::Color(255, 255, 255, 127));
            bufferShape.setPosition(nextPos + data.offsetPos - localoffsetPos);
            this->line_whiteShadow.push_back(bufferShape);
            // black shape
            bufferShape.setFillColor(sf::Color(0, 0, 0, 127));
            bufferShape.setPosition(nextPos + data.offsetPos + localoffsetPos);
            this->line_blackShadow.push_back(bufferShape);
            // original shape
            bufferShape.setFillColor(sf::Color(80, 35, 25, this->data.alpha / 2));
            bufferShape.setPosition(nextPos + data.offsetPos);
            this->line.push_back(bufferShape);
            // set pos to next pos
            this->data.pos = nextPos;

        } else if (current == 's') { // green segment leafs
            // calculate next pos
            nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -this->data.width), this->data.currentAngle);
            // push shape
            bufferShape.setRadius(this->data.length);
            bufferShape.setOrigin(sf::Vector2f(this->data.length / 2, 0));
            bufferShape.setPosition(this->data.pos + data.offsetPos);
            bufferShape.setRotation(this->data.currentAngle);
            // set random color in green range 100-255
            int randcolor = rand() % 155 + 100;
            bufferShape.setFillColor(sf::Color(0, randcolor, 0));
            this->line.push_back(bufferShape);
            // set pos to next pos
            this->data.pos = nextPos;
        } else if (current == '+') {
            randangle = rand() % 26 - 13;
            this->data.currentAngle += (data.angle + randangle);
        } else if (current == '-') {
            randangle = rand() % 26 - 13;
            this->data.currentAngle -= (data.angle + randangle);
        } else if (current == '[') {
            this->data.length *= 0.80;
            this->data.alpha *= 0.98;
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
    for (auto& shape : this->line_whiteShadow)
        target.draw(shape);
    for (auto& shape : this->line_blackShadow)
        target.draw(shape);
    for (auto& shape : this->line)
        target.draw(shape);
}