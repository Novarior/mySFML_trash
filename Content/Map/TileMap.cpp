#include "TileMap.hpp"

void TileMap::Clear(){
     if(!this->tilemap.empty()){
        for(int x = 0; x < this->tilemap.size(); x++){
            for(int y = 0; x < this->tilemap[x].size(); x++){
                delete this->tilemap[x][y];
				this->tilemap[x][y] = NULL;
            }
            this->tilemap[x].clear();
        }
    this->tilemap.clear();
    }
}

void TileMap::loadTextuteMap(){

    if(!this->m_TexturesList["GRASS"].loadFromFile("Content/Textures/Tiles/grass.png"))
         std::cout<<"\nTexture GRASS Dosent LOAD \n";
    if(!this->m_TexturesList["STONE"].loadFromFile("Content/Textures/Tiles/stone.png"))
        std::cout<<"\nTexture STONE Dosent LOAD \n";
    if(!this->m_TexturesList["OCEAN"].loadFromFile("Content/Textures/Tiles/ocean.png"))
        std::cout<<"\nTexture OCEAN Dosent LOAD \n";
    if(!this->m_TexturesList["SAND"].loadFromFile("Content/Textures/Tiles/ocean.png"))
        std::cout<<"\nTexture SAND Dosent LOAD \n";
    if(!this->m_TexturesList["GROUND"].loadFromFile("Content/Textures/Tiles/ocean.png"))
        std::cout<<"\nTexture GROUND Dosent LOAD \n";
}

TileMap::TileMap(noiceData datanoice, ProcessGenerationNoice* noice){
    this->Clear();
    this->loadTextuteMap();
    double writebuff;
    bool collisionBuff;
    this->m_dnoice = datanoice;
    this->maxSizeWorldGrid=this->m_dnoice.mapSize;
    this->maxSizeWorldFloat = sf::Vector2f(
        this->m_dnoice.mapSize.x * datanoice.gridSize,
        this->m_dnoice.mapSize.y * datanoice.gridSize
    );

    this->m_Area.offsetX = (datanoice.RenderWindow.x / datanoice.gridSize / 4) + 2; 
    this->m_Area.offsetY = (datanoice.RenderWindow.y / datanoice.gridSize / 4) + 2; 
    this->m_Area.fromX = 0;
    this->m_Area.fromY = 0;
    this->m_Area.toX = 0;
    this->m_Area.toY = 0;
    

    this->tilemap.resize(this->maxSizeWorldGrid.x,std::vector<BrickBlock*>());

    sf::Color buff;
    for(int x=0; x<this->m_dnoice.mapSize.x; x++)
        for(int y=0; y<this->m_dnoice.mapSize.y; y++){
            writebuff=noice->getNoice(x,y);
                writebuff *= 255;
                writebuff = static_cast<int>(writebuff) % 255;
            if(writebuff<0)
                writebuff= writebuff *- 1;   
            if(writebuff<0x3f)
                collisionBuff = false;
            
            if(writebuff<55)
            { //sea
                buff = sf::Color(0, 10 + writebuff * 1.6, 100 + writebuff*1.9, 255); 
                this->tilemap[x].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize,this->m_dnoice.gridSize),
                    sf::Vector2f(x*this->m_dnoice.gridSize, y*this->m_dnoice.gridSize),buff,
                    collisionBuff, this->m_TexturesList["OCEAN"]));
            }
            else if(writebuff < 66)
            { //sand
                buff = sf::Color(150 + writebuff * 1.5, 120 + writebuff * 1.6, 90+writebuff*0.1, 255);
                this->tilemap[x].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize,this->m_dnoice.gridSize),
                    sf::Vector2f(x*this->m_dnoice.gridSize, y*this->m_dnoice.gridSize),buff,
                    collisionBuff, this->m_TexturesList["SAND"]));
            }
            else if(writebuff < 160)
            { //grass
                buff = sf::Color(writebuff * 0.1, 50 + writebuff * 1.1, writebuff * 0.08, 255); 
                this->tilemap[x].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize,this->m_dnoice.gridSize),
                    sf::Vector2f(x*this->m_dnoice.gridSize, y*this->m_dnoice.gridSize),buff,
                    collisionBuff, this->m_TexturesList["GRASS"]));
                    }   
            else if(writebuff < 165)
            { //ground
                buff = sf::Color(90-writebuff*0.1, 71+writebuff*0.15, 55+writebuff*0.1, 255);
                this->tilemap[x].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize,this->m_dnoice.gridSize),
                    sf::Vector2f(x*this->m_dnoice.gridSize, y*this->m_dnoice.gridSize),buff,
                    collisionBuff, this->m_TexturesList["GROUND"]));
            } 
            else if(writebuff < 175)
            { //cave
                buff = sf::Color(40+writebuff*0.1, 71-writebuff*0.2, 55-writebuff*0.2, 255);
                this->tilemap[x].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize,this->m_dnoice.gridSize),
                    sf::Vector2f(x*this->m_dnoice.gridSize, y*this->m_dnoice.gridSize),buff,
                    collisionBuff, this->m_TexturesList["STONE"]));
            } 
            else
            { //other
                buff = sf::Color(writebuff,writebuff,writebuff,255);
                this->tilemap[x].push_back(new BrickBlock(
                    sf::Vector2f(this->m_dnoice.gridSize,this->m_dnoice.gridSize),
                    sf::Vector2f(x*this->m_dnoice.gridSize, y*this->m_dnoice.gridSize),buff,
                    collisionBuff, this->m_TexturesList["GRASS"]));
            }         

                    
        }
}

TileMap::~TileMap(){
    this->Clear();
}

renderArea TileMap::getRenderArea(){
    return this->m_Area;
}

const sf::Vector2u TileMap::getMapSizeOnTiles(){
    return this->maxSizeWorldGrid;
}

const sf::Vector2f TileMap::getMapSizeOnFloat(){
    return this->maxSizeWorldFloat;
}

void TileMap::render(sf::RenderTarget* target, const sf::Vector2i& gridPosition, const bool debug){
	this->m_Area.fromX = gridPosition.x - this->m_Area.offsetX;
	if (this->m_Area.fromX < 0)
		this->m_Area.fromX = 0;
	else if (this->m_Area.fromX > this->maxSizeWorldGrid.x)
		this->m_Area.fromX = this->maxSizeWorldGrid.x;

	this->m_Area.toX = gridPosition.x + this->m_Area.offsetX;
	if (this->m_Area.toX < 0)
		this->m_Area.toX = 0;
	else if (this->m_Area.toX > this->maxSizeWorldGrid.x)
		this->m_Area.toX = this->maxSizeWorldGrid.x;

	this->m_Area.fromY = gridPosition.y - this->m_Area.offsetY;
	if (this->m_Area.fromY < 0)
		this->m_Area.fromY = 0;
	else if (this->m_Area.fromY > this->maxSizeWorldGrid.y)
		this->m_Area.fromY = this->maxSizeWorldGrid.y;

	this->m_Area.toY = gridPosition.y + this->m_Area.offsetY;
	if (this->m_Area.toY < 0)
		this->m_Area.toY = 0;
	else if (this->m_Area.toY > this->maxSizeWorldGrid.y)
		this->m_Area.toY = this->maxSizeWorldGrid.y;

    for (int x = this->m_Area.fromX; x < this->m_Area.toX; x++)
		for (int y = this->m_Area.fromY; y < this->m_Area.toY; y++)
            this->tilemap[x][y]->render(target);
}