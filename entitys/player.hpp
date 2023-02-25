#ifndef CPP_PLAYERCLASS_HPP
#define CPP_PLAYERCLASS_HPP
#include "entity.hpp"

class Player: public Entity
{
    private:

    public:
        Player();
        virtual ~Player();

        void e_update(const float& deltatime);
        void e_render(sf::RenderTarget* target);

};

#endif CPP_PLAYERCLASS_HPP