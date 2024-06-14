#ifndef myConst_h
#define myConst_h

#define __MDEBUG__ 1

namespace myConst {
// path constants

// data
const char app_name[] = "Ekzeckt";

// config
const char config_game[] = "/config/gamedata.json";
const char config_entitydata[] = "/config/entitysdata.json";
const char config_inventory[] = "/config/inventorydata.json";
const char config_playerdata[] = "/config/playerdata.json";
const char config_window[] = "/config/window.json";
const char config_soundvolume[] = "/config/soundvolume.json";
const char config_keybinds[] = "/config/keybinds.json";
const char config_noicedata[] = "/config/noicedata.json";
// localisation
const char localisation_RU[] = "/localisation/RUS.json";
const char localisation_EN[] = "/localisation/ENG.json";

// fonst
const char data_debugfont_path[] = "/fonts/Muli-Regular.ttf";
const char data_gameproces_font_path[] = "/fonts/Blackwood Castle.ttf";
const char data_gameproces_font_path_2[] = "/fonts/Alamak.ttf";
const char data_gameproces_font_path_3[] = "/fonts/712_serif.ttf";

// GUI textures
const char texture_CellInventory_path[] = "/textures/textures/CellOutLine.png";

// textures
const char texture_GRASS[] = "/textures/Tiles/grass.png";
const char texture_STONE[] = "/textures/Tiles/stone.png";
const char texture_OCEAN[] = "/textures/Tiles/ocean.png";
const char texture_OCEAN_ANIM[] = "/textures/Tiles/water_still.png";
const char texture_SAND[] = "/textures/Tiles/sand.png";
const char texture_DIRT[] = "/textures/Tiles/coarse_dirt.png";

const char f_Trees[] = "/textures/Trees/";

// shaders

const char M_SHADER_01_F[] = "/shaders/bloom.frag";
const char M_SHADER_02_V[] = "/shaders/bloom.vert";

// sprites
const char slime_texture[] = "/textures/Entitys/slime_terratia.png";

// items
const char item_img_gold_nugget[] = "/textures/Images/gold_nugget.png";
const char item_img_copper_nuggen[] = "/textures/Images/copper_nugget.png";
const char item_img_silver_nuggen[] = "/textures/Images/iron_nugget.png";
const char item_img_someore[] = "/textures/Images/some_ore.png";

// backgrounds
const char texture_background_mainmenu_lay_1[] = "/textures/Images/Lay_1.png";
const char texture_background_mainmenu_lay_2[] = "/textures/Images/Lay_2.png";
const char texture_background_mainmenu_lay_3[] = "/textures/Images/Lay_3.png";

// sounds

const char sound_test[] = "/sounds/music/test_01.wav";
};

#endif // myConst_h