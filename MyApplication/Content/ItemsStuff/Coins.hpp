#ifndef COINS_H
#define COINS_H

class Coins
{
    private:
    int goldCount;
    int silverCount;
    int copperCount;

    public:
    Coins();
    Coins(int gold_coins, int silver_coins, int copper_coins);;
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

};
#endif