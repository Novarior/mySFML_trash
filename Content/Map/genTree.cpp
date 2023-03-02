#include "genTree.hpp"

/**
 * @brief Construct a new Gen Tree:: Gen Tree object
 * 
 */
GenTree::GenTree()
{

}


void GenTree::generateTree()
{
// реализация Lсистемы дерева ну или его подобия
/*
        const   LWORD
                1       Draw line on step size
                2       Draw line with a chance
                0       Draw leaf on 1 step and back
                [       Push back state "drawer" position, angle
                ]       Pop back state "drawer" position, angle
                r       Draw rigth
                l       Draw left



*/
    float stepleght = 16;
    float wigth = 5;   
    float angle = 25;
    int octaves = 5;
    float currentang =0;
    sf::Vector2f position;

    std::string word = "22220";
    int wordsize = word.size();
    struct statedrawer 
    {
    float angle;
    sf::Vector2f pos;
    } dstate;
    std::stack<statedrawer> state;

    for(int i=0;i<octaves;i++)
        for(int x=0;x<wordsize;x++)
        {
            if(word[x]=='1')
                word += "21";
            if(word[x]=='0')
                word += "1[l20]r20";
        }
    
    std::cout << "\n\tTreeWord:" << word;

    for(int x=0;x<word.size();x++)
    {
    this->m_shapeSquare;

        switch(word[x])
        {
            case '1':
                break;
            case '2':
                if(rand)
                break;
            case '0':
                break;
            case 'r':
                break;
            case 'l':
                break;
            case '[':
                dstate.angle = currentang;
                dstate.pos = position;
                state.push(dstate);
                break;
            case ']':
                currentang = state.top().angle;
                position = state.top().pos;
                state.pop();
                break;
            default:
                break;
        }
    }

}
/**
 * @brief Destroy the Gen Tree:: Gen Tree object
 * 
 */
GenTree::~GenTree()
{
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
    for(auto& x:this->m_arrayshape)
        target->draw(x);
}