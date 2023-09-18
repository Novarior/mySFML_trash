#ifndef ITEMSTUFF_COINS_H
#define ITEMSTUFF_COINS_H
#include "../../header.h"

class Coins {
private:
    int m_gold;
    int m_silver;
    int m_copper;

public:
    /// @brief template constructor for Coins
    /// @param m_gold - gold coins
    /// @param m_silver - silver coins
    /// @param m_copper - copper coins
    Coins(const int gold = 0, const int silver = 0, const int copper = 0)
    {
        this->m_gold = gold;
        this->m_silver = silver;
        this->m_copper = copper;
    }
    virtual ~Coins() { }

    void set_GoldCoinCouns(const int value) { this->m_gold = value; }
    void set_SilverCoinCouns(const int value) { this->m_silver = value; }
    void set_CopperCoinCouns(const int value) { this->m_copper = value; }

    void add_GoldCoinCound(const int value) { this->m_gold += value; }
    void add_SilverCoinCound(const int value) { this->m_silver += value; }
    void add_CopperCoinCound(const int value) { this->m_copper += value; }

    // Acsess
    inline const int get_GoldCointCount() { return this->m_gold; }
    inline const int get_SilverCointCount() { return this->m_silver; }
    inline const int get_CopperCointCount() { return this->m_copper; }

    // Update coins
    void updateCoins()
    {
        // if copper coins bigger that 100
        if (this->m_copper >= 100) {
            this->m_silver += this->m_copper / 100;
            this->m_copper = this->m_copper % 100;
        }
        // else copper coins smaller that 0
        else if (this->m_copper < 0 && this->m_copper > -100) {
            this->m_silver -= 1;
            this->m_copper = 100 + this->m_copper;
        }

        // if silver coins bigger that 100
        if (this->m_silver >= 100) {
            this->m_gold += this->m_silver / 100;
            this->m_silver = this->m_silver % 100;
        }
        // else silver coins smaller that 0
        // and if silver coins quantity bigger that 0
        else if (this->m_silver < 0 && this->m_silver > -100) {
            this->m_gold -= 1;
            this->m_silver = 100 + this->m_silver;
        }
    }
};
#endif