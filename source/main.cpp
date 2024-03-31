
#define JSON_ImplicitConversions 0

#include "Core.h"

std::map<int, std::shared_ptr<Item>> ItemRegistry::items = {};
unsigned int Entity::count_entitys = 0;
unsigned BrickBlock::currentFrame = 0;
unsigned int FPS::mFrame = 0;
unsigned int FPS::mFps = 0;
sf::Clock FPS::mClock = sf::Clock();

int main()
{
    Logger myLogger;

    Logger::log("\n=====================\n=====================\n=====================", "main.cpp");
    Core mc;

    mc.run();

    return 0;
}