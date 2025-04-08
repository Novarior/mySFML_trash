#include "systemFunctionUNIX.hpp"
#define JSON_ImplicitConversions 0

#include "Core.h"

// инициализация реестра предметов
std::map<int, std::shared_ptr<Item>> ItemRegistry::items = {};
// Инициализация статичного счетчика сущностей
unsigned int Entity::count_entitys = 0;
// Инициализация статичного счетчика для смены текстуры
unsigned BrickBlock::currentFrame = 0;
// Инициализация статичного счетчика кадра
unsigned int FPS::mFrame = 0;
// Инициализация статичного счетчика кадров
unsigned int FPS::mFps = 0;
// инициализаия часов для подсчета фпс
sf::Clock FPS::mClock = sf::Clock();
// Инициализация статического контейнера
std::unordered_map<std::string, sf::Texture> TextureManager::m_textures;

int main() {
  ApplicationsFunctions::createAppDirectories();

  Logger::logStatic(
      "\n=====================\n=====================\n=====================",
      "main.cpp");
  Core mc;

  mc.run();

  TextureManager::m_textures.clear();
  return 0;
}