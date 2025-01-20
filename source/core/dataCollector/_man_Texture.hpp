#ifndef FB27D2D7_15D5_4021_90D0_83477726D619
#define FB27D2D7_15D5_4021_90D0_83477726D619

#include "../header.h"

class TextureManager
{
public:
    // Метод для загрузки текстуры
    static bool loadTexture(const std::string &textureName, const std::string &filePath)
    {
        if (m_textures.find(textureName) != m_textures.end())
        {
            // Если текстура уже загружена, возвращаем true
            Logger::logStatic(textureName + " texture alrady loaded", "TextureManager::loadTexture()", logType::INFO);
            return true;
        }

        sf::Texture texture;
        if (texture.loadFromFile(ApplicationsFunctions::get_resources_dir() + filePath))
        {
            // сохраняем текстуру в контейнер
            m_textures.emplace(textureName, std::move(texture));
            Logger::logStatic(textureName + " success load", "TextureManager::loadTexture()", logType::INFO); // Логируем успешную загрузку
            return true;
        }
        else
        {
            Logger::logStatic(textureName + " failed to load", "TextureManager::loadTexture()", logType::ERROR); // Логируем ошибку
            return false;
        }
    }

    // Метод для получения текстуры по имени
    static sf::Texture &getTexture(const std::string &textureName)
    {
        if (m_textures.find(textureName) != m_textures.end())
        {
            return m_textures[textureName];
        }
        else
        {
            // В случае отсутствия текстуры, логируем ошибку
            Logger::logStatic("Texture not found: " + textureName, "TextureManager::getTexture()", logType::ERROR);
            throw std::runtime_error("Texture not found: " + textureName);
        }
    }

    // Метод для проверки, существует ли текстура
    static bool hasTexture(const std::string &textureName)
    {
        return m_textures.find(textureName) != m_textures.end();
    }

    ~TextureManager()
    {
        m_textures.clear();
    }

    // Контейнер для хранения текстур (теперь это статический контейнер)
    static std::unordered_map<std::string, sf::Texture> m_textures;
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
