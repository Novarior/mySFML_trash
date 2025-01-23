#ifndef myConst_h
#define myConst_h

#define __MDEBUG__ 1

namespace myConst {
// path constants

// data
const char app_name[] = "Ekzeckt";

namespace config { // config
    const char config_entitydata[] = "/config/entitysdata.json";
    const char config_inventory[] = "/config/inventorydata.json";
    const char config_playerdata[] = "/config/playerdata.json";
    const char config_window[] = "/config/window.json";
    const char config_noicedata[] = "/config/noicedata.json";
};

namespace localisation { // localisation
    const char localisation_RU[] = "/localisation/RUS.json";
    const char localisation_EN[] = "/localisation/ENG.json";
};

namespace fonts { // fonts
    const char data_debugfont_path[] = "/fonts/Muli-Regular.ttf";
    const char data_gameproces_font_path[] = "/fonts/Blackwood Castle.ttf";
    const char data_gameproces_font_path_2[] = "/fonts/Alamak.ttf";
    const char data_gameproces_font_path_3[] = "/fonts/712_serif.ttf";
};

namespace gui { // GUI textures
    const char texture_CellInventory_path[] = "/textures/textures/CellOutLine.png";

    const char texture_background_mainmenu_lay_1[] = "/textures/gui/Lay_1.png";
    const char texture_background_mainmenu_lay_2[] = "/textures/gui/Lay_2.png";
    const char texture_background_mainmenu_lay_3[] = "/textures/gui/Lay_3.png";
};

namespace textures { // textures
    const char texture_DEEP_OCEAN[] = "/textures/tiles/deep_ocean.png";
    const char texture_OCEAN[] = "/textures/tiles/ocean.png";
    const char texture_SAND[] = "/textures/tiles/sand.png";
    const char texture_GRASS[] = "/textures/tiles/grass.png";
    const char texture_DIRT[] = "/textures/tiles/dirt.png";
    const char texture_STONE[] = "/textures/tiles/stone.png";
    const char texture_SNOW[] = "/textures/tiles/snow.png";

    const char texture_NULL[] = "/textures/gui/nulltexture.png";

    const char folder_Trees[] = "/textures/Trees/";
};

namespace shders { // shaders
    const char M_SHADER_01_F[] = "/shaders/bloom.frag";
    const char M_SHADER_02_V[] = "/shaders/bloom.vert";
};

namespace sprites { // sprites
    const char texture_SLIME[] = "/sprites/Slime_01.png";
    const char texture_PLAYER[] = "/sprites/Slime_01.png";
};

namespace items { // items
    namespace coins
    {
        const char item_img_copper_nuggen[] = "/textures/items/coins/copper_nugget.png";
        const char item_img_silver_nuggen[] = "/textures/items/coins/iron_nugget.png";
        const char item_img_gold_nugget[] = "/textures/items/coins/gold_nugget.png";
    };
    namespace poison
    {
        const char item_img_poison_small_regeneration[] = "/textures/items/poison/Potion_1_Original.png";
    }
    const char item_img_stone[] = "/textures/items/stone_01.png";
};

namespace backgrounds { // backgrounds
   
};

namespace sounds { // sounds
    const char music_menu[] = "/sounds/music/music_01.wav";
    const char selbtn_menu[] = "/sounds/sfx/selbtn_01.wav";
    const char press_newg[] = "/sounds/sfx/press_ng_01.wav";
    const char press_btn[] = "/sounds/sfx/press_btn_01.wav";
};
};

#endif // myConst_h