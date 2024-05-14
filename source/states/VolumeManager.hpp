#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP
#include "../header.h"

enum class SoundCategory {
    vol_MASTER,
    vol_SFX, // Звуковые эффекты
    vol_MUSIC, // Музыка
    vol_AMBIENT, // Фоновые звуки
    vol_ENTITY, // Звуки, связанные с другими сущностями в игре
    vol_UI, // Звуки пользовательского интерфейса
    vol_DIALOGUE, // Диалоги или голосовые звуки
    vol_FOLEY, // Звуки движения персонажей или предметов
    vol_WEAPON, // Звуки оружия
    vol_ENVIRONMENT, // Звуки окружающей среды
    vol_COUNT
};

class VolumeManager {
private:
    // Громкости
    std::map<SoundCategory, float> categoryVolumes = {
        { SoundCategory::vol_MASTER, 100.f },
        { SoundCategory::vol_SFX, 100.f },
        { SoundCategory::vol_MUSIC, 100.f },
        { SoundCategory::vol_AMBIENT, 100.f },
        { SoundCategory::vol_ENTITY, 100.f },
        { SoundCategory::vol_UI, 100.f },
        { SoundCategory::vol_DIALOGUE, 100.f },
        { SoundCategory::vol_FOLEY, 100.f },
        { SoundCategory::vol_WEAPON, 100.f },
        { SoundCategory::vol_ENVIRONMENT, 100.f }
    };

public:
    VolumeManager() { }
    // set value Volume by category
    void setCategoryVolume(SoundCategory category, float volume) { categoryVolumes[category] = volume; }

    // get value Volume by category
    float getCategoryVolume(SoundCategory category) const
    {
        auto it = categoryVolumes.find(category);
        return it != categoryVolumes.end() ? it->second : 100.f;
    }

    // get all categories for next save to file
    const std::map<SoundCategory, float> getCategoryVolumes() const { return categoryVolumes; }
    // get size of map categoryVolumes
    const size_t getCategoryVolumesSize() const { return categoryVolumes.size() - 1; }
};

#endif // !AUDIO_MANAGER_HPP