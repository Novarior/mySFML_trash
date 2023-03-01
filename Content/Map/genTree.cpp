#include "genTree.hpp"


GenTree::GenTree()
{
    for(int x=0;x<10;x++)
    {
    this->m_shapeSquare;

    switch(this->commands[x])

    case 'a':
        break;
    case 'b':
        break;
    case 'c':
        break;

    }
    this->m_arrayshape.push_back(this->m_shapeSquare);
}
GenTree::~GenTree()
{
}

void GenTree::update()
{
}

void GenTree::render(sf::RenderTarget* target)
{
    for(auto& x:this->m_arrayshape)
        target->draw(x);
}