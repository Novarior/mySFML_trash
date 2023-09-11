#include "TabletTree.hpp"

TabletTree::TabletTree()
{
}

TabletTree::~TabletTree()
{
}

void TabletTree::generateRandomGennetic()
{
    srand(std::time(NULL));
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 8; j++) {
            // random value from -1 to 1
            this->gennetic[i][j] = (float)(rand() % 200 - 100) / 100;
        }
    }
}

sf::Vector2f TabletTree::rotate(float x, float y, float angle)
{
    float rad = angle * M_PI / 180;
    float mx = x * cos(rad) - y * sin(rad);
    float my = x * sin(rad) + y * cos(rad);
    return sf::Vector2f(mx, my);
}

void TabletTree::generate()
{
    // generating tree be like as l-system
    // but we use gennetic algorithm
    // and we use 2 dimensional array of float values between 0 and 1
    // size 17x8

    float radius = 0.f;
    sf::Color color = { 0, 0, 0, 0 };
    sf::Vector2f nextPos = { 0.f, 0.f };
    sf::Vector2f currentPos = { 0.f, 0.f };
    sf::Vector2f localOffsetPosition = { 2.f, 2.f };
    sf::CircleShape bufferShape;
    std::stack<GeneticData> stack;
    GeneticData bufferData;
    float shiftAngle = 0.f;
    int randlen = 0;

    // cycle for levels
    for (int level = 0; level < 8; level++) {
        // cycle for branches
        for (int nb = 0; nb < this->gennetic[14][level]; nb++) {
            randlen = rand() % static_cast<int>(this->gennetic[1][level]);
            // cycle on length of branch
            shiftAngle = this->gennetic[14][level];
            // pop from stack
            if (!stack.empty()) {
                bufferData = stack.top();
                stack.pop();
                currentPos = bufferData.Pos;
                shiftAngle = bufferData.Angle;
                color = bufferData.Color;
            }
            for (int br = 0; br < this->gennetic[0][level] + randlen; br++) {
                // calculate next position using gennetic algorithm
                // use gennetic[4][level] as length of branch from previous branch
                nextPos = currentPos + this->rotate(0, -this->gennetic[2][level] / 2, this->gennetic[8][level] + this->gennetic[9][level] + shiftAngle);
                // use gennetic[2][level] as length of branch (radius)
                // use gennetic[3][level] as length shifting size (current radius + size changing)
                radius = this->gennetic[2][level] + this->gennetic[2][level] + this->gennetic[3][level] * br;
                // use gennetic 6 - 8 for RGB color
                // use gennetic 9 - 11 for RGB color shifting
                color = sf::Color(
                    this->gennetic[6][level] + this->gennetic[9][level] * br, // red
                    this->gennetic[7][level] + this->gennetic[10][level] * br, // green
                    this->gennetic[8][level] + this->gennetic[11][level] * br, // blue
                    255 * 0.75); // alpha

                // create circle shape
                bufferShape.setRadius(radius);
                bufferShape.setOrigin(sf::Vector2f(radius / 2, 0));
                bufferShape.setPosition(nextPos + this->offsetPos);
                // create shadows
                //  withe shape
                bufferShape.setFillColor(sf::Color(255, 255, 255, 127));
                bufferShape.setPosition(nextPos + this->offsetPos - localOffsetPosition);
                this->line_whiteShadow.push_back(bufferShape);
                // black shape
                bufferShape.setFillColor(sf::Color(0, 0, 0, 127));
                bufferShape.setPosition(nextPos + this->offsetPos + localOffsetPosition);
                this->line_blackShadow.push_back(bufferShape);
                // original shape
                bufferShape.setFillColor(color);
                this->line.push_back(bufferShape);
                // set current position to next position
                currentPos = nextPos;
            }

            // push to stack current data
            // write to bufferData
            bufferData.Pos = currentPos;
            bufferData.Angle = this->gennetic[15][level] + this->gennetic[16][level] * nb;
            bufferData.Color = color;
            stack.push(bufferData);
        }
    }
}

void TabletTree::render(sf::RenderTarget& target)
{
    for (auto& i : this->line_whiteShadow) {
        target.draw(i);
    }
    for (auto& i : this->line_blackShadow) {
        target.draw(i);
    }
    for (auto& i : this->line) {
        target.draw(i);
    }
}