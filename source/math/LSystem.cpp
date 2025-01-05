#include "LSystem.hpp"

LSystem::LSystem()
{
}

LSystem::~LSystem()
{
    // очистка стека
    while (!this->stack.empty())
        this->stack.pop();

    // очистка вектора
    this->line.clear();

    // очистка правил
    this->rules.clear();

    // очистка строки
    this->sentence.clear();
}

void LSystem::generate()
{
    this->line.clear();
    this->data.pos = sf::Vector2f(0, 0);
    this->data.angle = 15;
    this->data.currentAngle = 0;
    this->data.length = 20;
    this->data.steps = 10;
    this->data.alpha = 255;
    this->data.width = 11;
    this->data.chanceSkip = 50;
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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);
    std::uniform_int_distribution<> dis_angle(0, 25);
    std::uniform_int_distribution<> dis_color(80, 255);

    sf::Vector2f nextPos;
    sf::RectangleShape bufferShape;
    float half_length = this->data.length / 2;

    for (char current : this->sentence) {
        int chance = dis(gen);
        if (current == 'd' || current == 'q') {
            if (chance < this->data.chanceSkip)
                continue;
            nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -this->data.width), this->data.currentAngle + dis_angle(gen));
            bufferShape.setSize(sf::Vector2f(this->data.length, this->data.width));
            bufferShape.setOrigin(sf::Vector2f(half_length, 0));
            bufferShape.setPosition(nextPos + data.offsetPos);
            bufferShape.setRotation(this->data.currentAngle + dis_angle(gen));
            bufferShape.setFillColor(sf::Color(80, 35, 25, this->data.alpha));
            this->line.push_back(bufferShape);
            this->data.pos = nextPos;

        } else
            switch (current) {
            case 's': { // green segment leafs
                // calculate next pos
                nextPos = this->data.pos + this->rotate(sf::Vector2f(0, -this->data.width), this->data.currentAngle + dis_angle(gen));
                // push shape
                bufferShape.setSize(sf::Vector2f(this->data.length + dis_angle(gen) % 3 + 1, this->data.width - 2));
                bufferShape.setOrigin(sf::Vector2f(half_length, 0));
                bufferShape.setPosition(this->data.pos + data.offsetPos);
                bufferShape.setRotation(this->data.currentAngle + dis_angle(gen));
                // set random color in green range 80-255
                int randcolor = dis_color(gen);
                bufferShape.setFillColor(sf::Color(0, randcolor, 0));
                this->line.push_back(bufferShape);
                // set pos to next pos
                this->data.pos = nextPos;
                break;
            }
            case '+': // rotate right
                this->data.currentAngle += (data.angle + dis_angle(gen));
                break;
            case '-':
                this->data.currentAngle -= (data.angle + dis_angle(gen));
                break;
            case '[':
                this->data.length *= 0.80;
                this->data.alpha *= 0.98;
                this->stack.push(this->data);
                break;
            case ']':
                this->data = this->stack.top();
                this->stack.pop();
                break;
            };
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