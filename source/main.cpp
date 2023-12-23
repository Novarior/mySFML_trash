#define JSON_ImplicitConversions 0

#include "Core.h"

std::map<int, std::shared_ptr<Item>> ItemRegistry::items = {};
unsigned int Entity::count_entitys = 0;
unsigned BrickBlock::currentFrame = 0;
Node* Node::_currentDraggingNode = nullptr;

int main()
{
    Logger myLogger;

    myLogger.log("Start program", "main");
    Core mc;
    myLogger.log("Core has been successfully created", "main");
    myLogger.log("Start main loop", "main");
    mc.run();
    myLogger.log("End main loop", "main");

    return 0;
}