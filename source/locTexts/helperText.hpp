#ifndef F01D25E1_1913_4228_8335_54CCC0564D08
#define F01D25E1_1913_4228_8335_54CCC0564D08

// здесь все тектовые наименование (названия) для всех элементов
// также служат для подсказок действий для какихто кнопок

// также учитывается что текстовые наименования могут быть на разных языках
// поэтому важно чтобы они были в отдельном файле
// и было легко их заменить на другой язык

#include "../header.h"

namespace helperText {
enum class Language {
    ENG,
    RUS
};
// стуктура со всякими кнопочками приложения
struct Button {
    static std::string BUTTON_PLAY;
    static std::string BUTTON_OPTIONS;
    static std::string BUTTON_EXIT;
    static std::string BUTTON_BACK;
    static std::string BUTTON_APPLY;
    static std::string BUTTON_CANCEL;
    static std::string BUTTON_SAVE;
    static std::string BUTTON_LOAD;
    static std::string BUTTON_NEW_GAME;
    static std::string BUTTON_CONTINUE;
    static std::string BUTTON_NOICE_EDITOR;

    static void initializeLocalization(Language language)
    {
        std::string filename;
        switch (language) {
        case Language::ENG:
            filename = sAppFunctions::get_resources_dir() + myConst::localisation_EN;
            break;
        case Language::RUS:
            filename = sAppFunctions::get_resources_dir() + myConst::localisation_RU;
            break;
        }

        nlohmann::json json;
        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            std::cerr << "ERROR::GRAPHICSSETTINGS::COULD NOT LOAD TO FILE: " << filename << std::endl;
            return;
        }

        ifs >> json;
        ifs.close();

        BUTTON_PLAY = json["BUTTONS"].value("LOCAL_PLAY", "@Play Text");
        BUTTON_OPTIONS = json["BUTTONS"].value("LOCAL_OPTIONS", "@Options Text");
        BUTTON_EXIT = json["BUTTONS"].value("LOCAL_EXIT", "@Exit Text");
        BUTTON_BACK = json["BUTTONS"].value("LOCAL_BACK", "@Back Text");
        BUTTON_APPLY = json["BUTTONS"].value("LOCAL_APPLY", "@Apply Text");
        BUTTON_CANCEL = json["BUTTONS"].value("LOCAL_CANCEL", "@Cancel Text");
        BUTTON_SAVE = json["BUTTONS"].value("LOCAL_SAVE", "@Save Text");
        BUTTON_LOAD = json["BUTTONS"].value("LOCAL_LOAD", "@Load Text");
        BUTTON_NEW_GAME = json["BUTTONS"].value("LOCAL_NEW_GAME", "@New Game Text");
        BUTTON_CONTINUE = json["BUTTONS"].value("LOCAL_CONTINUE", "@Continue Text");

        // и так далее для остальных строк...
    }
};

struct VolumeTexts {
    static std::string VOL_MASTER;
    static std::string VOL_SFX;
    static std::string VOL_MUSIC;
    static std::string VOL_AMBIENT;
    static std::string VOL_ENTITYSFX;
    static std::string VOL_UI_VOL;
    static std::string VOL_DIALOGUE_VOL;
    static std::string VOL_FOLEYVOL;
    static std::string VOL_WEAPONVOL;
    static std::string VOL_ENVIRONMENTVOL;

    static void initializeLocalization(Language language)
    {
        std::string filename;
        switch (language) {
        case Language::ENG:
            filename = sAppFunctions::get_resources_dir() + myConst::localisation_EN;
            break;
        case Language::RUS:
            filename = sAppFunctions::get_resources_dir() + myConst::localisation_RU;
            break;
        }

        std::ifstream file(filename);
        nlohmann::json json;
        file >> json;

        VOL_MASTER = json["AUDIO_OPTIONS"].value("LOCAL_MASTER", "@Master Volume");
        VOL_SFX = json["AUDIO_OPTIONS"].value("LOCAL_SFX", "@SFX Volume");
        VOL_MUSIC = json["AUDIO_OPTIONS"].value("LOCAL_MUSIC", "@Music Volume");
        VOL_AMBIENT = json["AUDIO_OPTIONS"].value("LOCAL_AMBIENT", "@Ambient Volume");
        VOL_ENTITYSFX = json["AUDIO_OPTIONS"].value("LOCAL_ENTITYSFX", "@Entity SFX Volume");
        VOL_UI_VOL = json["AUDIO_OPTIONS"].value("LOCAL_UI_VOL", "@UI Volume");
        VOL_DIALOGUE_VOL = json["AUDIO_OPTIONS"].value("LOCAL_DIALOGUE_VOL", "@Dialogue Volume");
        VOL_FOLEYVOL = json["AUDIO_OPTIONS"].value("LOCAL_FOLEYVOL", "@Foley Volume");
        VOL_WEAPONVOL = json["AUDIO_OPTIONS"].value("LOCAL_WEAPONVOL", "@Weapon Volume");
        VOL_ENVIRONMENTVOL = json["AUDIO_OPTIONS"].value("LOCAL_ENVIRONMENTVOL", "@Environment Volume");
    }
};

struct SettingsTexts {
    static std::string TEXT_RESOLUTION;
    static std::string TEXT_FULLSCREEN;
    static std::string TEXT_VSYNC;
    static std::string TEXT_CONTROLS;
    static std::string TEXT_AUDIO;
    static std::string TEXT_ANTIALIASING;
    static std::string TEXT_FRAMERATE_LIMIT;
    static std::string TEXT_GRAPHICS;
    static std::string TEXT_GAMEPLAY;
    static std::string TEXT_LANGUAGE;
    static std::string TEXT_CREDITS;
    static std::string TEXT_SAVE;
    static std::string TEXT_LOAD;
    static std::string TEXT_EXIT;

    static void initializeLocalization(Language language)
    {
        std::string filename;
        switch (language) {
        case Language::ENG:
            filename = sAppFunctions::get_resources_dir() + myConst::localisation_EN;
            break;
        case Language::RUS:
            filename = sAppFunctions::get_resources_dir() + myConst::localisation_RU;
            break;
        }

        std::ifstream file(filename);
        nlohmann::json json;
        file >> json;

        TEXT_RESOLUTION = json["SETTING_OPTIONS"].value("LOCAL_RESOLUTION", "@Resolution Text");
        TEXT_FULLSCREEN = json["SETTING_OPTIONS"].value("LOCAL_FULLSCREEN", "@Fullscreen Text");
        TEXT_VSYNC = json["SETTING_OPTIONS"].value("LOCAL_VSYNC", "@VSync Text");
        TEXT_CONTROLS = json["SETTING_OPTIONS"].value("LOCAL_CONTROLS", "@Controls Text");
        TEXT_AUDIO = json["SETTING_OPTIONS"].value("LOCAL_AUDIO", "@Audio Text");
        TEXT_ANTIALIASING = json["SETTING_OPTIONS"].value("LOCAL_ANTIALIASING", "@Antialiasing Text");
        TEXT_FRAMERATE_LIMIT = json["SETTING_OPTIONS"].value("LOCAL_FRAMERATE_LIMIT", "@Framerate Limit Text");
        TEXT_GRAPHICS = json["SETTING_OPTIONS"].value("LOCAL_GRAPHICS", "@Graphics Text");
        TEXT_GAMEPLAY = json["SETTING_OPTIONS"].value("LOCAL_GAMEPLAY", "@Gameplay Text");
        TEXT_LANGUAGE = json["SETTING_OPTIONS"].value("LOCAL_LANGUAGE", "@Language Text");
        TEXT_CREDITS = json["SETTING_OPTIONS"].value("LOCAL_CREDITS", "@Credits Text");
        TEXT_SAVE = json["SETTING_OPTIONS"].value("LOCAL_SAVE", "@Save Text");
        TEXT_LOAD = json["SETTING_OPTIONS"].value("LOCAL_LOAD", "@Load Text");
        TEXT_EXIT = json["SETTING_OPTIONS"].value("LOCAL_EXIT", "@Exit Text");

        // и так далее для остальных строк...
    }
};
}; // namespace helperText
#endif /* F01D25E1_1913_4228_8335_54CCC0564D08 */
