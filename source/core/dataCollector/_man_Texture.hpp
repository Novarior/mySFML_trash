#ifndef FB27D2D7_15D5_4021_90D0_83477726D619
#define FB27D2D7_15D5_4021_90D0_83477726D619
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

class TextureManager {
public:
    // Метод для загрузки текстуры
    bool loadTexture(const std::string& textureName, const std::string& filePath)
    {
        if (textures.find(textureName) != textures.end()) {
            // Если текстура уже загружена, возвращаем true
            logger.logTextureLoad(textureName, true);
            return true;
        }

        sf::Texture texture;
        if (texture.loadFromFile(filePath)) {
            //сохраняем текстуру в контейнер
            textures[textureName] = texture;
            logger.logTextureLoad(textureName, true); // Логируем успешную загрузку
            return true;
        } else {
            logger.logTextureLoad(textureName, false); // Логируем ошибку
            return false;
        }
    }

    // Метод для получения текстуры по имени
    sf::Texture& getTexture(const std::string& textureName)
    {
        if (textures.find(textureName) != textures.end()) {
            return textures[textureName];
        } else {
            // В случае отсутствия текстуры, логируем ошибку
            logger.logError("Texture not found: " + textureName);
            throw std::runtime_error("Texture not found: " + textureName);
        }
    }

    // Метод для проверки, существует ли текстура
    bool hasTexture(const std::string& textureName)
    {
        return m_textures.find(textureName) != m_textures.end();
    }

private:
    // Контейнер для хранения текстур
    std::unordered_map<std::string, sf::Texture> m_textures;
};
#include "Logger.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class TextureManager {
private:
    std::unordered_map<std::string, sf::Texture> textures;
    Logger logger; // Экземпляр логгера для записи событий

public:
    // Загрузка текстуры по имени
  
 
};
// int main()
// {
//     TextureManager textureManager;

//     // Загружаем текстуру
//     textureManager.loadTexture("player", "path_to_player_texture.png");
//     textureManager.loadTexture("enemy", "path_to_enemy_texture.png");

//     // Получаем и используем текстуру для спрайта
//     if (textureManager.hasTexture("player")) {
//         sf::Sprite playerSprite;
//         playerSprite.setTexture(textureManager.getTexture("player"));
//         // Теперь можно использовать playerSprite
//     }

//     return 0;
// }

#endif /* FB27D2D7_15D5_4021_90D0_83477726D619 */
