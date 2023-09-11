#ifndef CPP_MATH_TABLET_TREE_HPP
#define CPP_MATH_TABLET_TREE_HPP

#include "mymath.hpp"
struct GeneticData {
    sf::Vector2f Pos;
    float Angle;
    sf::Color Color;
};

class TabletTree {
private:
    float gennetic[20][8] {
        { 5, 5, 5, 5, 5, 5, 3, 2 }, //  0- size of branch
        { 2, 2, 2, 2, 2, 2, 2, 2 }, //  1 - size shifting
        { 15, 14, 12, 12, 12, 10, 8, 7 }, //  2 - length of branch
        { -0.1, -0.1f, -0.1f, -0.1f,
            -0.1f, -0.1f, -0.1f, -0.1f }, //  3 - lenght changes
        { 0, 0, 0, 0, 0, 0, 0, 0 }, //  4 - lenght from previous branch
        { 0, 0, 0, 0, 0, 0, 0, 0 }, //  5 - lenght from level
        { 10, 20, 12, 12, 24, 22, 14, 53 }, //  6 - Red color
        { 13, 31, 13, 19, 14, 71, 16, 1 }, //  7 - Green color
        { 15, 51, 41, 71, 61, 16, 71, 1 }, //  8 - Blue color
        { 2, 1, 3, 5, 5, 2, 5, 1 }, //  9 - Shift Red color on step
        { 2, 1, 3, 5, 5, 2, 5, 1 }, //  10 - Shift Green color on step
        { 5, 2, 3, 7, 5, 3, 5, 1 }, //  11 - Shift Blue color on step
        { 0, 0, 0, 0, 0, 0, 0, 0 }, //  12 - color from previous
        { 0, 0, 0, 0, 0, 0, 0, 0 }, //  13 - color shifting
        { 0, 2, 2, 2, 2, 2, 2, 2 }, //  14 - number of branches
        { 0, 15, 15, 15, 15, 15, 15, 0 }, //  15 - angle on two branches
        { 0, 0, 0, 0, 0, 0, 0, 0 }, //  16 - angle shifting
        { 0, 0, 0, 0, 0, 0, 0, 0 }, //  17 - trun
        { 0, 0, 0, 0, 0, 0, 0, 0 }, //  18 - random trun
        { 0, 0, 0, 0, 0, 0, 0, 0 } //   19 - down-up
    };
    std::vector<sf::CircleShape> line;
    std::vector<sf::CircleShape> line_whiteShadow;
    std::vector<sf::CircleShape> line_blackShadow;

    sf::Vector2f offsetPos;

    sf::Vector2f rotate(float x, float y, float angle);

public:
    TabletTree();
    virtual ~TabletTree();

    void generateRandomGennetic();
    void generate();
    void setOffsetPos(sf::Vector2f offsetPos) { this->offsetPos = offsetPos; }
    size_t getSizeTree() { return this->line.size() + this->line_blackShadow.size() + this->line_whiteShadow.size(); }

    void render(sf::RenderTarget& target);
};
#endif // !CPP_MATH_TABLET_TREE_HPP
