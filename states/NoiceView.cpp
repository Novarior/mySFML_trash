#include "NoiceView.hpp"

void NoiceView::initKeybinds(){
    this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
}

void NoiceView::initButton(){
    this->buttons["EXIT_BTN"] = new gui::Button(
        sf::Vector2f(),sf::Vector2f(250,100),
        this->stateData->font, "Exit", 20,
        sf::Color(200,200,200), sf::Color(180,180,180), sf::Color(160,160,180), 
        sf::Color(100,100,100), sf::Color(140,140,140), sf::Color(80,80,90));
}
/*
void NoiceView::createStepByStep(sf::Vector2f pos){
double writebuff=0;
    //generation terraine
    float sx = pos.x,
          sy = pos.y;

    for(int x = pos.x * this->gridSizeX; x < (pos.x + 1) * this->gridSizeX; x++){
        for(int y = pos.y * this->gridSizeY; y < (pos.y + 1) * this->gridSizeY; y++){
            writebuff=myGN->getNoice(x,y);
                writebuff *= 255;
                writebuff = static_cast<int>(writebuff) % 255;
            if(writebuff<0)
                writebuff= writebuff *- 1;    
            
            if(writebuff<55){ //sea
                this->image.setPixel(x,y,sf::Color(0, 10 + writebuff * 0.6, 100 + writebuff*1.9)); }
            else if(writebuff < 66){ //sand
                this->image.setPixel(x,y,sf::Color(150 + writebuff * 1.5, 120 + writebuff * 1.6, 90+writebuff*0.1)); }
            else if(writebuff < 160){ //grass
                this->image.setPixel(x,y,sf::Color(writebuff * 0.1, 50 + writebuff * 1.1, writebuff * 0.08)); }   
            else if(writebuff < 165){ //ground
                this->image.setPixel(x,y,sf::Color(90-writebuff*0.1, 71+writebuff*0.15, 55+writebuff*0.1)); } 
            else if(writebuff < 175){ //cave
                this->image.setPixel(x,y,sf::Color(40+writebuff*0.1, 71-writebuff*0.2, 55-writebuff*0.2)); } 
            else{ //other
                this->image.setPixel(x,y,sf::Color(writebuff,writebuff,writebuff)); }            
    }   }
    this->texture.update(this->image);
    this->shape.setTexture(&this->texture);
}
*/
void NoiceView::createStepByStep(sf::Vector2f pos)
{
    double writebuff = 0;
    float sx = pos.x, sy = pos.y;
    std::ofstream outfile("result.txt"); // открываем файл для записи

    for (int x = pos.x * this->gridSizeX; x < (pos.x + 1) * this->gridSizeX; x++) {
        for (int y = pos.y * this->gridSizeY; y < (pos.y + 1) * this->gridSizeY; y++) {
            writebuff = myGN->getNoice(x, y);
            writebuff *= 255;
            writebuff = static_cast<int>(writebuff) % 255;
            if (writebuff < 0)
                writebuff = writebuff * -1;

            if (writebuff < 55) { //sea
                this->image.setPixel(x, y, sf::Color(0, 10 + writebuff * 0.6, 100 + writebuff * 1.9, 255));
                outfile << "sea ";
            } else if (writebuff < 66) { //sand
                this->image.setPixel(x, y, sf::Color(150 + writebuff * 1.5, 120 + writebuff * 1.6, 90 + writebuff * 0.1, 255));
                outfile << "sand ";
            } else if (writebuff < 160) { //grass
                this->image.setPixel(x, y, sf::Color(writebuff * 0.1, 50 + writebuff * 1.1, writebuff * 0.08, 255));
                outfile << "grass ";
            } else if (writebuff < 165) { //ground
                this->image.setPixel(x, y, sf::Color(90 - writebuff * 0.1, 71 + writebuff * 0.15, 55 + writebuff * 0.1, 255));
                outfile << "ground ";
            } else if (writebuff < 175) { //cave
                this->image.setPixel(x, y, sf::Color(40 + writebuff * 0.1, 71 - writebuff * 0.2, 55 - writebuff * 0.2, 255));
                outfile << "cave ";
            } else { //other
                this->image.setPixel(x, y, sf::Color(writebuff, writebuff, writebuff, 255));
                outfile << "other ";
            }

            // записываем координаты пикселя и его цвет в файл
            outfile << "(" << x << ", " << y << "): " << this->image.getPixel(x, y).toInteger() << "\n";
        }
    }

    outfile.close(); // закрываем файл
    this->texture.update(this->image);
    this->shape.setTexture(&this->texture);
}

NoiceView::NoiceView(StateData* statedata):State(statedata){
    this->initKeybinds();

    this->noicedata.gridSize = this->stateData->grid_size;
    this->noicedata.octaves = 8;    
    this->noicedata.seed = 1;
    this->noicedata.frequency = 8;
    this->noicedata.RenderWindow = sf::Vector2f(
        this->stateData->gfxSettings->resolution.width,
        this->stateData->gfxSettings->resolution.height);
    this->noicedata.mapSize = sf::Vector2u(this->noicedata.RenderWindow);
    this->noicedata.persistence = 0.6f;

    this->image.create(this->noicedata.RenderWindow.x,this->noicedata.RenderWindow.y);
    this->shape.setSize(this->noicedata.RenderWindow);
    this->texture.create(this->noicedata.RenderWindow.x,this->noicedata.RenderWindow.y);

    this->myGN = new ProcessGenerationNoice(this->noicedata);
    this->isGeneratorClosed = false;   
    this->tick=0;   
    this->gridSizeX = this->noicedata.RenderWindow.x/10;
    this->gridSizeY = this->noicedata.RenderWindow.y/10;
    this->closeGrid=sf::Vector2f();
}

NoiceView::~NoiceView(){
    delete this->myGN;
}

void NoiceView::updateInput(const float& deltatime){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
        this->endState();
}

void NoiceView::update(const float& deltatime){
    this->updateKeytime(deltatime);
    this->updateInput(deltatime);

    if(!this->isGeneratorClosed){
        if(this->tick==2){
            this->tick=0;

            this->createStepByStep(this->closeGrid);
            if(this->closeGrid.x==9){
                this->closeGrid.x=0;
                this->closeGrid.y+=1;
            }
            else    
                this->closeGrid.x+=1;

            if(this->closeGrid.y==10)
                this->isGeneratorClosed=true;
        }   
    }
    this->tick++;   
}

void NoiceView::render(sf::RenderWindow* target){
    target->draw(this->shape);
}