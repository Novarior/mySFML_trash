#include "NoiceViewer.hpp"

void NoiceViewer::initvariables()
{
    this->noiceImage.create(this->m_noice_data.RenderWindowX, this->m_noice_data.RenderWindowY);
    this->noiceTexture.create(this->m_noice_data.RenderWindowX, this->m_noice_data.RenderWindowY);
    this->noiceShape.setSize(sf::Vector2f(this->m_noice_data.RenderWindowX, this->m_noice_data.RenderWindowY));
}

NoiceViewer::NoiceViewer(mmath::noiceData& m_data)
    : m_noice_data(m_data)
{
    // logger
    Logger::log("NoiceViewer constructor", "NoiceViewer", true);

    this->m_prn_noice = new ProcessGenerationNoice(this->m_noice_data);
    this->m_perlin_noice = new PerlinNoise();
    this->m_simplex_noice = new SimplexNoise();
    this->current_Noice_Model = PERLIN_NOICE;
    this->current_Color_Mode = FULL_COLOR;

    // resize vector to map size
    this->noiceMap.resize(this->m_noice_data.mapSizeX);
    for (int i = 0; i < this->m_noice_data.mapSizeX; i++)
        this->noiceMap[i].resize(this->m_noice_data.mapSizeY);

    this->initvariables();

    Logger::log("NoiceViewer constructor end", "NoiceViewer", true);
}

NoiceViewer::~NoiceViewer()
{
    Logger::log("NoiceViewer destructor", "NoiceViewer", true);

    delete this->m_prn_noice;
    delete this->m_perlin_noice;
    delete this->m_simplex_noice;
}

void NoiceViewer::updateNoiceModels()
{
    this->m_prn_noice->setNoiceData(this->m_noice_data);
}

void NoiceViewer::generateNoice()
{
    double h_buffer = 0.f;

    // clean noice map before generate
    this->noiceMap.clear();

    this->noiceMap.resize(this->m_noice_data.mapSizeX);
    for (int i = 0; i < this->m_noice_data.mapSizeX; i++)
        this->noiceMap[i].resize(this->m_noice_data.mapSizeY);

    for (int x = 0; x < this->m_noice_data.mapSizeX; x++)
        for (int y = 0; y < this->m_noice_data.mapSizeY; y++)
            switch (noiceType(current_Noice_Model)) {
            case PERLIN_NOICE:
                h_buffer = this->m_perlin_noice->Noise(x, y);
                this->noiceMap[x][y] = h_buffer;
                break;
            case PERLIN_NOICE_V2:
                h_buffer = this->m_prn_noice->getNoice(x, y);
                this->noiceMap[x][y] = h_buffer;
                break;
            case SIMPLEX_NOICE:
                h_buffer = this->m_simplex_noice->noise(x / this->m_noice_data.amplifire / 10.f, y / this->m_noice_data.amplifire / 10.f);
                this->noiceMap[x][y] = h_buffer;
                break;
            default:
                break;
            }

    // fill image using vector array
    double vec_buffer = 0.f;
    for (int x = 0; x < this->m_noice_data.mapSizeX; x++)
        for (int y = 0; y < this->m_noice_data.mapSizeY; y++) {
            vec_buffer = this->noiceMap[x][y];

            switch (colorMode(current_Color_Mode)) {
            case FULL_COLOR: {
                if (vec_buffer < 45) { // deep ocean
                    this->noiceImage.setPixel(x, y, sf::Color(0, 10 + vec_buffer * 0.6, 100 + vec_buffer * 1.5, 255));
                    this->m_BlocksCounter.deep_ocean++;
                } else if (vec_buffer < 66) { // ocean
                    this->noiceImage.setPixel(x, y, sf::Color(0, 20 + vec_buffer * 0.7, 100 + vec_buffer * 1.7, 255));
                    this->m_BlocksCounter.ocean++;
                } else if (vec_buffer < 70) { //  sand
                    this->noiceImage.setPixel(x, y, sf::Color(150 + vec_buffer * 1.5, 120 + vec_buffer * 1.6, 90 + vec_buffer * 0.1, 255));
                    this->m_BlocksCounter.sand++;
                } else if (vec_buffer < 74) { // sea sand
                    this->noiceImage.setPixel(x, y, sf::Color(150 + vec_buffer * 1.5, 140 + vec_buffer * 1.6, 120 + vec_buffer * 0.1, 255));
                    this->m_BlocksCounter.seasand++;
                } else if (vec_buffer < 120) { // grass
                    this->noiceImage.setPixel(x, y, sf::Color(vec_buffer * 0.1, 50 + vec_buffer * 1.1, vec_buffer * 0.08, 255));
                    this->m_BlocksCounter.grass++;
                } else if (vec_buffer < 165) { // ground
                    this->noiceImage.setPixel(x, y, sf::Color(90 - vec_buffer * 0.1, 71 + vec_buffer * 0.15, 55 + vec_buffer * 0.1, 255));
                    this->m_BlocksCounter.dirt++;
                } else if (vec_buffer < 175) { // cave
                    this->noiceImage.setPixel(x, y, sf::Color(40 + vec_buffer * 0.1, 71 - vec_buffer * 0.2, 55 - vec_buffer * 0.2, 255));
                    this->m_BlocksCounter.rock++;
                } else if (vec_buffer < 180) { // mountain
                    this->noiceImage.setPixel(x, y, sf::Color(120 - vec_buffer * 0.2, 100 + vec_buffer * 0.2, 120 - vec_buffer * 0.2, 255));
                    this->m_BlocksCounter.mountain++;
                } else if (vec_buffer < 200) { // snow
                    this->noiceImage.setPixel(x, y, sf::Color(255 - vec_buffer * 0.4, 255 - vec_buffer * 0.4, 255 - vec_buffer * 0.4, 255));
                    this->m_BlocksCounter.snow++;
                }
                break;
            }
            case NOICE_COLOR:
                this->noiceImage.setPixel(x, y, sf::Color(vec_buffer, vec_buffer, vec_buffer, 255));
                break;
            case BIOME_COLOR:
                break;
            default:
                break;
            }
        }

    // access finale image
    this->noiceTexture.update(this->noiceImage);
    this->noiceShape.setTexture(&this->noiceTexture);
}

void NoiceViewer::swithNoiceModel()
{
    // switch noice model to next
    // if current model is last, switch to first
    if (this->current_Noice_Model == SIMPLEX_NOICE)
        this->current_Noice_Model = PERLIN_NOICE;
    else
        this->current_Noice_Model++;
}
const std::string NoiceViewer::getNoiceModelName()
{
    return this->noiceModels[this->current_Noice_Model];
}

void NoiceViewer::swithColorMode()
{
    // switch color mode to next
    // if current mode is last, switch to first
    if (this->current_Color_Mode == BIOME_COLOR)
        this->current_Color_Mode = FULL_COLOR;
    else
        this->current_Color_Mode++;
}
const std::string NoiceViewer::getColorModeName()
{
    return this->colorModes[this->current_Color_Mode];
}

void NoiceViewer::update(const float& dt)
{
}

void NoiceViewer::render(sf::RenderTarget& target)
{
    target.draw(this->noiceShape);
}
