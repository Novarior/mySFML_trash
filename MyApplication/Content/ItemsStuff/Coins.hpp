#ifndef ITEMSTUFF_COINS_H
#define ITEMSTUFF_COINS_H
#include "../../header.h"

class Coins : public sf::Drawable {
private:
    sf::Font& m_font;
    std::stringstream m_StringStream;

    struct CoinCount {
        int goldCount = 0;
        int silverCount = 0;
        int copperCount = 0;
    } m_coin_count;

    struct CoinText {
        sf::Text m_Text_gold;
        sf::Text m_Text_silver;
        sf::Text m_Text_copper;
    } m_coin_text;

    struct CoinShape {
        sf::Sprite m_GoldShape;
        sf::Sprite m_SilverShape;
        sf::Sprite m_CopperShape;
    } m_coin_shape;

    struct CoinTexture {
        sf::Texture m_GoldTexture;
        sf::Texture m_SilverTexture;
        sf::Texture m_CopperTexture;
    } m_coin_texture;

    inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Draw Texture shapes with image
        target.draw(m_coin_shape.m_GoldShape);
        target.draw(m_coin_shape.m_SilverShape);
        target.draw(m_coin_shape.m_CopperShape);

        target.draw(m_coin_text.m_Text_gold);
        target.draw(m_coin_text.m_Text_silver);
        target.draw(m_coin_text.m_Text_copper);
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

    // Acsess
    const int get_GoldCointCount();
    const int get_SilverCointCount();
    const int get_CopperCointCount();

    // Update coins
    void updateCoins();

    void getText();
};
#endif