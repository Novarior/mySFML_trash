#define JSON_ImplicitConversions 0

#include "Core.h"

std::map<int, std::shared_ptr<Item>> ItemRegistry::items = {};           // инициализация реестра предметов
unsigned int Entity::count_entitys = 0;                                  // Инициализация статичного счетчика сущностей
unsigned BrickBlock::currentFrame = 0;                                   // Инициализация статичного счетчика для смены текстуры
unsigned int FPS::mFrame = 0;                                            // Инициализация статичного счетчика кадра
unsigned int FPS::mFps = 0;                                              // Инициализация статичного счетчика кадров
sf::Clock FPS::mClock = sf::Clock();                                     // инициализаия часов для подсчета фпс
std::unordered_map<std::string, sf::Texture> TextureManager::m_textures; // Инициализация статического контейнера

int main()
{
    Logger myLogger;

    Logger::logStatic("\n=====================\n=====================\n=====================", "main.cpp");
    Core mc;

    mc.run();

    TextureManager::m_textures.clear();
    return 0;
}