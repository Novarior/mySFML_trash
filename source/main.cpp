#define JSON_ImplicitConversions 0

#include "Core.h"

// some global variables
// some static variables
unsigned int Entity::count_entitys = 0;
unsigned int Item::count_items = 0;
unsigned BrickBlock::currentFrame = 0;

int main()
{
    Logger myLogger;

    myLogger.log("Start program", "main", true, 0);
    Core mc;
    myLogger.log("Core has been successfully created", "main", true, 0);
    myLogger.log("Start main loop", "main", true, 0);
    mc.run();
    myLogger.log("End main loop", "main", true, 0);

    return 0;
}