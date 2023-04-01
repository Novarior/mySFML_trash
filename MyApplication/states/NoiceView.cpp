#include "NoiceView.hpp"

void NoiceView::initKeybinds() {
    this->Ikeybinds["CLOSE"] = this->IsupportedKeys->at("Escape");
}

void NoiceView::initButton() {
    this->buttons["EXIT_BTN"] = new gui::Button(
        sf::Vector2f(), sf::Vector2f(250, 100),
        this->IstateData->font, "Exit", 20,
        sf::Color(200, 200, 200), sf::Color(180, 180, 180), sf::Color(160, 160, 180),
        sf::Color(100, 100, 100), sf::Color(140, 140, 140), sf::Color(80, 80, 90));
}


void NoiceView::createStepByStep(sf::Vector2f pos)
{
    double writebuff = 0;
    double min = 10, max = 0;

    for (int x = pos.x * this->gridSizeX; x < (pos.x + 1) * this->gridSizeX; x++) {
        for (int y = pos.y * this->gridSizeY; y < (pos.y + 1) * this->gridSizeY; y++) {
            writebuff = myGN->getNoice(x, y);
            if (writebuff < min)
                min = writebuff;
            if (writebuff > max)
                max = writebuff;
            writebuff *= 255;
            writebuff = static_cast<int>(writebuff) % 255;
            if (writebuff < 0)
                writebuff = writebuff * -1;

            if (writebuff < 55) { //sea
                this->image.setPixel(x, y, sf::Color(0, 10 + writebuff * 0.6, 100 + writebuff * 1.9, 255));
                this->m_BlocksCounter.ocean++;
            }
            else if (writebuff < 66) { //sand
                this->image.setPixel(x, y, sf::Color(150 + writebuff * 1.5, 120 + writebuff * 1.6, 90 + writebuff * 0.1, 255));
                this->m_BlocksCounter.sand++;
            }
            else if (writebuff < 160) { //grass
                this->image.setPixel(x, y, sf::Color(writebuff * 0.1, 50 + writebuff * 1.1, writebuff * 0.08, 255));
                this->m_BlocksCounter.grass++;
            }
            else if (writebuff < 165) { //ground
                this->image.setPixel(x, y, sf::Color(90 - writebuff * 0.1, 71 + writebuff * 0.15, 55 + writebuff * 0.1, 255));
                this->m_BlocksCounter.dirt++;
            }
            else if (writebuff < 175) { //cave
                this->image.setPixel(x, y, sf::Color(40 + writebuff * 0.1, 71 - writebuff * 0.2, 55 - writebuff * 0.2, 255));
                this->m_BlocksCounter.rock++;
            }
            else { //other
                this->image.setPixel(x, y, sf::Color(writebuff, writebuff, writebuff, 255));
                this->m_BlocksCounter.other++;
            }
        }
    }
    this->texture.update(this->image);
    this->shape.setTexture(&this->texture);
    std::cout << "\n\t\tS2S:\tpos: " << pos.x << " x " << pos.y << "\t\tMinMax: " << min << " x " << max;
}

NoiceView::NoiceView(StateData* statedata):State(statedata) {
    this->initKeybinds();

    this->noicedata.gridSize = this->IstateData->grid_size;
    this->noicedata.octaves = 8;
    this->noicedata.seed = 1;
    this->noicedata.frequency = 8;
    this->noicedata.RenderWindow = sf::Vector2f(
        this->IstateData->gfxSettings->resolution.width,
        this->IstateData->gfxSettings->resolution.height);
    this->noicedata.mapSize = sf::Vector2u(this->noicedata.RenderWindow);
    this->noicedata.persistence = 0.6f;

    this->image.create(this->noicedata.RenderWindow.x, this->noicedata.RenderWindow.y);
    this->shape.setSize(this->noicedata.RenderWindow);
    this->texture.create(this->noicedata.RenderWindow.x, this->noicedata.RenderWindow.y);
    this->myGN = new ProcessGenerationNoice(this->noicedata);
    this->isGeneratorClosed = false;
    this->tick = 0;
    this->gridSizeX = this->noicedata.RenderWindow.x / 10;
    this->gridSizeY = this->noicedata.RenderWindow.y / 10;
    this->closeGrid = sf::Vector2f();
}

NoiceView::~NoiceView() {
    delete this->myGN;
}

void NoiceView::updateInput(const float& delta_time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->Ikeybinds.at("CLOSE"))) && this->getKeytime())
        this->endState();
}

void NoiceView::update(const float& delta_time) {
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);


    if (!this->isGeneratorClosed) {
        if (this->tick == 2) {
            this->tick = 0;

            this->createStepByStep(this->closeGrid);
            if (this->closeGrid.x == 9) {
                this->closeGrid.x = 0;
                this->closeGrid.y += 1;
            }
            else
                this->closeGrid.x += 1;

            if (this->closeGrid.y == 10)
                this->isGeneratorClosed = true;
        }
    }
    if (this->debugMode) {//update debug information
        double fps = 1.0f / delta_time;
        this->dString_Stream
            << "FPS:\t" << fps << "\n"
            << "Block counter:"
            << "\n\tgrass: " << this->m_BlocksCounter.grass
            << "\n\tdirt: " << this->m_BlocksCounter.dirt
            << "\n\tmud: " << this->m_BlocksCounter.mud
            << "\n\tocean: " << this->m_BlocksCounter.ocean
            << "\n\trock: " << this->m_BlocksCounter.rock
            << "\n\tsand: " << this->m_BlocksCounter.sand
            << "\n\tother " << this->m_BlocksCounter.other
            << "Pause:\t" << this->Ipaused;

        this->dText.setString(this->dString_Stream.str());
        this->dString_Stream.str("");
    }
    this->tick++;
}

void NoiceView::render(sf::RenderWindow* target) {
    target->draw(this->shape);

    if (this->debugMode)
        target->draw(this->dText);
}