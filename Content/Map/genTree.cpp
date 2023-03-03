#include "genTree.hpp"

void GenTree::clear()
{
    this->m_arrayshape.clear();
}

GenTree::GenTree()
{

}

GenTree::~GenTree()
{
    this->clear();
}

void GenTree::generateTree()
{
    // реализация Lсистемы дерева ну или его подобия
    /*
            const   LWORD
                    1       Draw line on step size
                    2       Draw line with a chance
                    c       Draw leaf on 1 step and back
                    [       Push back state "drawer" position, angle
                    ]       Pop back state "drawer" position, angle
                    r       Draw rigth
                    l       Draw left
                    s       stepleght \2


    */
    this->clear();
    float stepleght = 15;
    float wigth = 15;
    float angle = 25;
    float currentAngle = 0;
    int octaves = 5;
    int recurs = 0;
    sf::Vector2f nextPosition(1000, 1000);
    sf::RectangleShape mShape;
    std::string word = "22221c";
    int wordsize = word.size();
    struct statedrawer
    {
        float angle;
        sf::Vector2f pos;
        float stepLeght;
    } dstate;
    statedrawer dstateBack;
    std::vector<statedrawer> state;

    for (int i = 0;i < octaves;i++)
    {
        for (int x = 0;x < wordsize;x++)
        {
            if (word[x] == '1')
                word += "21";
            if (word[x] == 'c')
                word += "1[sl221c][sr221c]";
        }
        wordsize = word.size();
        std::cout << '\n' << wordsize;
    }
    mShape.setOutlineThickness(-1);
    mShape.setOutlineColor(sf::Color::Red);
    for (int x = 0;x < word.size();x++)
    {
        switch (word[x])
        {
            case '1':
                mShape.setSize(sf::Vector2f(wigth, stepleght));
                mShape.setPosition(nextPosition);
                mShape.setFillColor(sf::Color::Cyan);
                mShape.setRotation(currentAngle);
                nextPosition = sf::Vector2f(mShape.getPosition().x - mShape.getGlobalBounds().width * sin(currentAngle), mShape.getPosition().y - stepleght * cos(currentAngle));
                this->m_arrayshape.push_back(mShape);
                dstateBack.angle = currentAngle;
                dstateBack.pos = nextPosition;
                dstateBack.stepLeght = stepleght;

                break;
            case '2':
                if (1 + rand() % 10 > 4)
                {
                    mShape.setSize(sf::Vector2f(wigth, stepleght));
                    mShape.setPosition(nextPosition);
                    mShape.setFillColor(sf::Color::White);
                    mShape.setRotation(currentAngle);
                    nextPosition = sf::Vector2f(mShape.getPosition().x - mShape.getGlobalBounds().width * sin(currentAngle), mShape.getPosition().y - stepleght * cos(currentAngle));
                    this->m_arrayshape.push_back(mShape);
                }
                break;
            case 'c':
                mShape.setSize(sf::Vector2f(wigth, stepleght));
                mShape.setPosition(nextPosition);
                mShape.setFillColor(sf::Color::Green);
                mShape.setRotation(currentAngle);
                nextPosition = sf::Vector2f(mShape.getPosition().x - mShape.getGlobalBounds().width * sin(currentAngle), mShape.getPosition().y - stepleght * cos(currentAngle));
                this->m_arrayshape.push_back(mShape);

                currentAngle = dstateBack.angle;
                nextPosition = dstateBack.pos;
                stepleght = dstateBack.stepLeght;
                break;
            case 'r':
                currentAngle += angle * randZeroToOne() + 0.5;
                break;
            case 'l':
                currentAngle -= angle * randZeroToOne() + 0.5;
                break;
            case '[':
                dstate.angle = currentAngle;
                dstate.pos = nextPosition;
                dstate.stepLeght = stepleght;
                state.push_back(dstate);
                break;
            case ']':
                currentAngle = state.back().angle;
                nextPosition = state.back().pos;
                stepleght = state.back().stepLeght;
                state.pop_back();
                break;
            case 's':
                stepleght *= 0.75f;
                break;
            default:
                break;
        }
    }

}



/**
 * @brief
 *
 */
void GenTree::update()
{
}

void GenTree::render(sf::RenderTarget* target)
{
    if (!this->m_arrayshape.empty())
        for (auto& x : this->m_arrayshape)
            target->draw(x);
}