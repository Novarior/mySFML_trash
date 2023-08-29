#define JSON_ImplicitConversions 0
#include "Core.h"

unsigned int Entity::count_entitys = 0;
unsigned int Item::count_items = 0;
unsigned BrickBlock::currentFrame = 0;

int main()
{
    Core mc;
    mc.run();

    return 0;
}