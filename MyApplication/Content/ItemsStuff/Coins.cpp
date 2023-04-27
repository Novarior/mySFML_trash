#include "Coins.hpp"

Coins::Coins(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f image_size, sf::Font& font, unsigned int character_size):m_font(font) {

    this->m_coin_shape.m_back.setSize(size);
    this->m_coin_shape.m_back.setPosition(pos);

    this->m_coin_shape.m_GoldShape.setSize(image_size);
    this->m_coin_shape.m_GoldShape.setPosition(pos);

    this->m_coin_shape.m_SilverShape.setPosition(sf::Vector2f(this->m_coin_shape.m_GoldShape.getSize().x * 2 + pos.x, pos.y));
    this->m_coin_shape.m_SilverShape.setSize(image_size);

    this->m_coin_shape.m_CopperShape.setPosition(sf::Vector2f(this->m_coin_shape.m_SilverShape.getSize().x * 2 + this->m_coin_shape.m_SilverShape.getPosition().x, pos.y));
    this->m_coin_shape.m_CopperShape.setSize(image_size);

    this->m_coin_texture.m_TextureGold.loadFromFile(item_img_gold_nugget);
    this->m_coin_texture.m_TextureCopper.loadFromFile(item_img_copper_nuggen);
    this->m_coin_texture.m_TextureSilver.loadFromFile(item_img_silver_nuggen);
    this->m_coin_shape.m_GoldShape.setTexture(&this->m_coin_texture.m_TextureGold);
    this->m_coin_shape.m_SilverShape.setTexture(&this->m_coin_texture.m_TextureSilver);
    this->m_coin_shape.m_CopperShape.setTexture(&this->m_coin_texture.m_TextureCopper);

    this->m_coin_text.m_Text_gold.setFillColor(sf::Color::White);
    this->m_coin_text.m_Text_gold.setOutlineColor(sf::Color::Black);
    this->m_coin_text.m_Text_gold.setOutlineThickness(2.0f);
    this->m_coin_text.m_Text_gold.setFont(this->m_font);
    this->m_coin_text.m_Text_gold.setCharacterSize(character_size);
    this->m_coin_text.m_Text_gold.setPosition(sf::Vector2f(
        this->m_coin_shape.m_GoldShape.getPosition().x + this->m_coin_shape.m_GoldShape.getSize().x,
        this->m_coin_shape.m_GoldShape.getPosition().y + this->m_coin_shape.m_GoldShape.getSize().y / 4));

    this->m_coin_text.m_Text_silver.setFillColor(sf::Color::White);
    this->m_coin_text.m_Text_silver.setOutlineColor(sf::Color::Black);
    this->m_coin_text.m_Text_silver.setOutlineThickness(2.0f);
    this->m_coin_text.m_Text_silver.setFont(this->m_font);
    this->m_coin_text.m_Text_silver.setCharacterSize(character_size);
    this->m_coin_text.m_Text_silver.setPosition(sf::Vector2f(
        this->m_coin_shape.m_SilverShape.getPosition().x + this->m_coin_shape.m_SilverShape.getSize().x,
        this->m_coin_shape.m_SilverShape.getPosition().y + this->m_coin_shape.m_SilverShape.getSize().y / 4));

    this->m_coin_text.m_Text_copper.setFillColor(sf::Color::White);
    this->m_coin_text.m_Text_copper.setOutlineColor(sf::Color::Black);
    this->m_coin_text.m_Text_copper.setOutlineThickness(2.0f);
    this->m_coin_text.m_Text_copper.setFont(this->m_font);
    this->m_coin_text.m_Text_copper.setCharacterSize(character_size);
    this->m_coin_text.m_Text_copper.setPosition(sf::Vector2f(
        this->m_coin_shape.m_CopperShape.getPosition().x + this->m_coin_shape.m_CopperShape.getSize().x,
        this->m_coin_shape.m_CopperShape.getPosition().y + this->m_coin_shape.m_CopperShape.getSize().y / 4));

}

Coins::~Coins() {}

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

//acsess

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