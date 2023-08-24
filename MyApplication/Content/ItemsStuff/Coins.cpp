#include "Coins.hpp"

Coins::Coins(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f image_size, sf::Font& font, unsigned int character_size)
    : m_font(font)
{
    this->m_coin_shape.m_GoldShape.setPosition(sf::Vector2f(pos.x + size.y / 4, pos.y + (size.y / 4)));
    this->m_coin_shape.m_GoldShape.setTextureRect(sf::IntRect(0, 0, size.x, size.x));

    this->m_coin_shape.m_SilverShape.setPosition(sf::Vector2f(pos.x + (size.x / 4), pos.y + (size.y / 4)));
    this->m_coin_shape.m_SilverShape.setTextureRect(sf::IntRect(0, 0, size.x, size.x));

    this->m_coin_shape.m_CopperShape.setPosition(sf::Vector2f(pos.x + (size.x / 4) * 2, pos.y + (size.y / 4)));
    this->m_coin_shape.m_CopperShape.setTextureRect(sf::IntRect(0, 0, size.x, size.x));

    this->m_coin_texture.m_GoldTexture.loadFromFile(myConst::item_img_gold_nugget);
    this->m_coin_shape.m_GoldShape.setTexture(this->m_coin_texture.m_GoldTexture);
    this->m_coin_texture.m_SilverTexture.loadFromFile(myConst::item_img_silver_nuggen);
    this->m_coin_shape.m_SilverShape.setTexture(this->m_coin_texture.m_SilverTexture);
    this->m_coin_shape.m_CopperShape.setTexture(this->m_coin_texture.m_SilverTexture);
    this->m_coin_shape.m_CopperShape.setColor(sf::Color(184, 115, 51, 255));

    // init text layout "gold coin"
    {
        sf::Color goldColor(255, 215, 0, 255);
        this->m_coin_text.m_Text_gold.setFillColor(goldColor);
        this->m_coin_text.m_Text_gold.setOutlineColor(sf::Color::Black);
        this->m_coin_text.m_Text_gold.setOutlineThickness(2.0f);
        this->m_coin_text.m_Text_gold.setFont(this->m_font);
        this->m_coin_text.m_Text_gold.setCharacterSize(character_size);
        this->m_coin_text.m_Text_gold.setPosition(sf::Vector2f(
            this->m_coin_shape.m_GoldShape.getPosition().x + this->m_coin_text.m_Text_silver.getCharacterSize(),
            this->m_coin_shape.m_GoldShape.getPosition().y));
    }
    // init text layout "silver coin"
    {
        sf::Color silverColor(192, 192, 192, 255);
        this->m_coin_text.m_Text_silver.setFillColor(silverColor);
        this->m_coin_text.m_Text_silver.setOutlineColor(sf::Color::Black);
        this->m_coin_text.m_Text_silver.setOutlineThickness(2.0f);
        this->m_coin_text.m_Text_silver.setFont(this->m_font);
        this->m_coin_text.m_Text_silver.setCharacterSize(character_size);
        this->m_coin_text.m_Text_silver.setPosition(sf::Vector2f(
            this->m_coin_shape.m_SilverShape.getPosition().x + this->m_coin_text.m_Text_silver.getCharacterSize(),
            this->m_coin_shape.m_SilverShape.getPosition().y));
    }
    // init text layout "copper coin"
    {
        sf::Color copperColor(184, 115, 51, 255);
        this->m_coin_text.m_Text_copper.setFillColor(copperColor);
        this->m_coin_text.m_Text_copper.setOutlineColor(sf::Color::Black);
        this->m_coin_text.m_Text_copper.setOutlineThickness(2.0f);
        this->m_coin_text.m_Text_copper.setFont(this->m_font);
        this->m_coin_text.m_Text_copper.setCharacterSize(character_size);
        this->m_coin_text.m_Text_copper.setPosition(sf::Vector2f(
            this->m_coin_shape.m_CopperShape.getPosition().x + this->m_coin_text.m_Text_silver.getCharacterSize(),
            this->m_coin_shape.m_CopperShape.getPosition().y));
    }
}

Coins::~Coins() { }

void Coins::set_GoldCoinCouns(const int value)
{
    this->m_coin_count.goldCount = value;
}
void Coins::set_SilverCoinCouns(const int value)
{
    this->m_coin_count.silverCount = value;
}
void Coins::set_CopperCoinCouns(const int value)
{
    this->m_coin_count.copperCount = value;
}

void Coins::add_GoldCoinCound(const int value)
{
    this->m_coin_count.goldCount += value;
}
void Coins::add_SilverCoinCound(const int value)
{
    this->m_coin_count.copperCount += value;
}
void Coins::add_CopperCoinCound(const int value)
{
    this->m_coin_count.silverCount += value;
}

// acsess

const int Coins::get_GoldCointCount()
{
    return this->m_coin_count.goldCount;
}

const int Coins::get_SilverCointCount()
{
    return this->m_coin_count.silverCount;
}

const int Coins::get_CopperCointCount()
{
    return this->m_coin_count.copperCount;
}

void Coins::getText()
{
    this->m_StringStream << this->m_coin_count.goldCount;
    this->m_coin_text.m_Text_gold.setString(this->m_StringStream.str());
    this->m_StringStream.str("");

    this->m_StringStream << this->m_coin_count.silverCount;
    this->m_coin_text.m_Text_silver.setString(this->m_StringStream.str());
    this->m_StringStream.str("");

    this->m_StringStream << this->m_coin_count.copperCount;
    this->m_coin_text.m_Text_copper.setString(this->m_StringStream.str());
    this->m_StringStream.str("");
}

void Coins::updateCoins()
{
    // check if the copper count is greater or equal than 100 then add 1 to silver and minus 100 from copper
    if (this->m_coin_count.copperCount >= 100) {
        this->m_coin_count.silverCount += 1;
        this->m_coin_count.copperCount -= 100;
    }
    // check if the silver count is greater or equal than 100 then add 1 to gold and minus 100 from silver
    if (this->m_coin_count.silverCount >= 100) {
        this->m_coin_count.goldCount += 1;
        this->m_coin_count.silverCount -= 100;
    }
}