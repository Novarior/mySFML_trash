#ifndef CPP_STATE_NOICE_VIEW_HPP
#define CPP_STATE_NOICE_VIEW_HPP

#include "../../GUI/GUISYS.hpp"
#include "../../math/ProcessGenerationNoice.hpp"
#include "../../math/pNoice.hpp"
#include "../../math/simplex.hpp"

enum noiceType {
    PERLIN_NOICE = 0,
    PERLIN_NOICE_V2 = 1,
    SIMPLEX_NOICE = 2
};

enum colorMode {
    FULL_COLOR = 0,
    NOICE_COLOR = 1,
    BIOME_COLOR = 2
};

class NoiceViewer {
private:
    std::array<std::string, 3> noiceModels = {
        "Perlin Noice",
        "Perlin Noice V2",
        "Simplex Noice"
    };

    std::array<std::string, 3> colorModes = {
        "Full Color",
        "Noice Color",
        "Biome Color"
    };

    // Variables
    struct {
        int deep_ocean = 0;
        int ocean = 0;
        int seasand = 0;
        int beath = 0;
        int sand = 0;
        int grass = 0;
        int dirt = 0;
        int rock = 0;
        int other = 0;
        int mountain = 0;
        int snow = 0;
        int forest = 0;
    } m_BlocksCounter;
    // Noice data colector
    mmath::noiceData& m_noice_data;

    // models Noice generators
    ProcessGenerationNoice* m_prn_noice;
    PerlinNoise* m_perlin_noice;
    SimplexNoise* m_simplex_noice;

    // image and texture
    sf::Image noiceImage;
    sf::Texture noiceTexture;
    sf::RectangleShape noiceShape;

    short int current_Noice_Model;
    short int current_Color_Mode;

    void updateNoiceModels();

    void initvariables();

    // dynamin 2d array
    std::vector<std::vector<double>> noiceMap;

public:
    NoiceViewer(mmath::noiceData& noicedata);
    ~NoiceViewer();
    mmath::noiceData& getNoiceData() { return this->m_noice_data; }

    void swithNoiceModel();
    void swithColorMode();

    const std::string getNoiceModelName();
    const std::string getColorModeName();

    int getNoiceModel() { return this->current_Noice_Model; }
    int getColorMode() { return this->current_Color_Mode; }

    void generateNoice();
    void setNoiceData(mmath::noiceData& noicedata) { this->m_noice_data = noicedata; }

    void update(const float& dt);
    void render(sf::RenderTarget& target);
};
#endif // CPP_STATE_NOICE_VIEW_HPP