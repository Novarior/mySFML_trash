#include "MainMenu.hpp"

void MainMenu::initRenderDefines(){
    this->renderTexture.create(
		this->stateData->sWindow->getSize().x,
		this->stateData->sWindow->getSize().y);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, 
			this->stateData->sWindow->getSize().x,
			this->stateData->sWindow->getSize().y));
}

void MainMenu::initKeybinds(){   
    this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
}

void MainMenu::initView(){
    this->view.setSize(sf::Vector2f(
			static_cast<float>(this->stateData->sWindow->getSize().x ),
			static_cast<float>(this->stateData->sWindow->getSize().y)));

	this->view.setCenter(sf::Vector2f(
			static_cast<float>(this->stateData->sWindow->getSize().x / 2),
			static_cast<float>(this->stateData->sWindow->getSize().y / 2)));
}

void MainMenu::initBackground(){
    this->background.setSize(sf::Vector2f(this->stateData->sWindow->getSize()));
    this->background.setFillColor(sf::Color(0,0,30));
    this->background.setPosition(sf::Vector2f());
}

void MainMenu::initButtons(){
    int offsetX=this->stateData->sWindow->getSize().x;
    int offsetY=this->stateData->sWindow->getSize().y;

    this->buttons["EXIT_BTN"] = new gui::Button(
        sf::Vector2f(offsetX-275,offsetY-125),sf::Vector2f(250,100),
        this->stateData->font, "Exit", 20,
        sf::Color(200,200,200), sf::Color(180,180,180), sf::Color(160,160,180), 
        sf::Color(100,100,100), sf::Color(140,140,140), sf::Color(80,80,90));

    this->buttons["SOME_BTN"] = new gui::Button(
        sf::Vector2f(offsetX-275,offsetY-225),sf::Vector2f(250,100),
        this->stateData->font, "Play", 20,
        sf::Color(200,200,200), sf::Color(180,180,180), sf::Color(160,160,180),
        sf::Color(100,100,100), sf::Color(140,140,140), sf::Color(80,80,90));

    this->buttons["PERLIN"] = new gui::Button(
        sf::Vector2f(offsetX-275,offsetY-325),sf::Vector2f(250,100),
        this->stateData->font, "Noice", 20,
        sf::Color(200,200,200), sf::Color(180,180,180), sf::Color(160,160,180),
        sf::Color(100,100,100), sf::Color(140,140,140), sf::Color(80,80,90));
}

void MainMenu::initBlocks(){
    BlocksGenData bgd;
    bgd.amplifire = 500;
    bgd.countPhantomBlocks = 255;
    bgd.offset=sf::Vector2f(
        this->stateData->sWindow->getSize().x/2,
        this->stateData->sWindow->getSize().y/2);
    bgd.windowSize=this->stateData->sWindow->getSize();
    bgd.pos = sf::Vector2f();
    bgd.frequency = 2.5f;

    this->rotationCyrcleShape = new RotarionCircle(bgd);
    sf::CircleShape shape;
    shape.setFillColor(sf::Color::White);
    shape.setRadius(20.f);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(0.f);
    this->rotationCyrcleShape->setShape(shape);
}

void MainMenu::initStartProcces(){
    this->fadeShape.setFillColor(sf::Color(0,0,0,0));
    this->fadeShape.setSize(sf::Vector2f(this->stateData->sWindow->getSize()));
}

bool MainMenu::isStarted(){
    return false;
}

void MainMenu::updateStartProcces(){
    sf::Color buff = this->fadeShape.getFillColor();

    if(buff.a<255)
        buff.a+=1; 
    else{
       this->states->push(new Process(this->stateData));

        this->isstatred=false;
        this->resetView();

       buff=sf::Color(0,0,0,0); 
    }
    this->fadeShape.setFillColor(buff);

    sf::Vector2f vSize=this->view.getSize();
    vSize-=sf::Vector2f(1,1);
    this->view.setSize(vSize);
}

void MainMenu::resetView(){
    this->view.setSize(sf::Vector2f(
			static_cast<float>(this->stateData->sWindow->getSize().x ),
			static_cast<float>(this->stateData->sWindow->getSize().y)));

	this->view.setCenter(sf::Vector2f(
			static_cast<float>(this->stateData->sWindow->getSize().x / 2),
			static_cast<float>(this->stateData->sWindow->getSize().y / 2)));
}

MainMenu::MainMenu(StateData* statedata):State(statedata){
    this->initRenderDefines();
    this->initKeybinds(); 
    this->initView();
    this->initBackground();
    this->initButtons();
    this->initBlocks();
    this->initStartProcces();
}

MainMenu::~MainMenu(){
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
    	delete it->second;
	
    this->buttons.clear();
    delete this->rotationCyrcleShape;
}

void MainMenu::update(const float& deltatime){   
    this->updateKeytime(deltatime);

    if(!this->isstatred){
        this->updateMousePositions(&this->view);
        this->updateInput(deltatime);
        this->updateButtons();
    }
    else
        this->updateStartProcces();
    
    this->rotationCyrcleShape->update(deltatime);

    if(this->debugMode)
    {
        this->string_Stream << "FPS:\t" << 1/deltatime << "\n";
        this->dText.setString(this->string_Stream.str());
        this->string_Stream.str("");
    }
}

void MainMenu::updateInput(const float& deltatime){ }

void MainMenu::updateButtons(){
    for(auto& it:this->buttons)
       it.second->update(this->mousePosWindow);

    if(this->buttons["EXIT_BTN"]->isPressed()&&this->getKeytime())
        this->endState();
    
    if(this->buttons["SOME_BTN"]->isPressed()&&this->getKeytime())
        this->isstatred=true;

    if(this->buttons["PERLIN"]->isPressed() && this->getKeytime())
        this->states->push(new NoiceView(this->stateData));
        
}

void MainMenu::render(sf::RenderWindow* target){
    if(!target)
        target=this->window;
    this->renderTexture.clear();
    this->renderTexture.setView(this->view);

    renderTexture.draw(this->background);

    this->rotationCyrcleShape->render(&renderTexture);

    for(auto&it:this->buttons)
        it.second->render(&renderTexture);

    this->renderTexture.setView(this->renderTexture.getDefaultView());

    if(this->isstatred)
        renderTexture.draw(this->fadeShape);

    if(this->debugMode)
        this->renderTexture.draw(this->dText); 

    this->renderTexture.display();
    target->draw(this->renderSprite);    
}