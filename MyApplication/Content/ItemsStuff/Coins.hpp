#ifndef ITEMSTUFF_COINS_H
#define ITEMSTUFF_COINS_H
#include "../../header.h"

class Coins: public sf::Drawable
{
    private:
    int goldCount;
    int silverCount;
    int copperCount;

    sf::Font& m_font;
    sf::Text m_Text_gold;
    sf::Text m_Text_silver;
    sf::Text m_Text_copper;
    std::stringstream m_StringStream;

    sf::RectangleShape m_back;
    sf::RectangleShape m_GoldShape;
    sf::RectangleShape m_SilverShape;
    sf::RectangleShape m_CopperShape;

    sf::Texture m_TextureGold;
    sf::Texture m_TextureCopper;
    sf::Texture m_TextureSilver;


    inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_GoldShape);
        target.draw(m_SilverShape);
        target.draw(m_CopperShape);
        target.draw(m_Text_gold);
        target.draw(m_Text_silver);
        target.draw(m_Text_copper);
    }

    public:
    /// @brief 
    /// @param pos position this coin box
    /// @param size size this coin box
    /// @param image_size size of icon coins
    /// @param font font for text
    /// @param character_size size letter
    Coins(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f image_size, sf::Font& font, unsigned int character_size);
    virtual ~Coins();

    void set_GoldCoinCouns(const int value);
    void set_SilverCoinCouns(const int value);
    void set_CopperCoinCouns(const int value);

    void add_GoldCoinCound(const int value);
    void add_SilverCoinCound(const int value);
    void add_CopperCoinCound(const int value);

    //Acsess
    const int get_GoldCointCount();
    const int get_SilverCointCount();
    const int get_CopperCointCount();

    void getText();

};
#endif