#include "Coins.hpp"

Coins::Coins() {}
Coins::Coins(int gold_coins, int silver_coins, int copper_coins):
    goldCount(gold_coins), silverCount(silver_coins), copperCount(copper_coins) { }
Coins::~Coins() {}

void Coins::set_GoldCoinCouns(const int value)
{
    this->goldCount = value;
}
void Coins::set_SilverCoinCouns(const int value)
{
    this->silverCount = value;
}
void Coins::set_CopperCoinCouns(const int value)
{
    this->copperCount = value;
}

void Coins::add_GoldCoinCound(const int value)
{
    this->goldCount += value;
}
void Coins::add_SilverCoinCound(const int value)
{
    this->silverCount += value;
}
void Coins::add_CopperCoinCound(const int value)
{
    this->copperCount += value;
}

//acsess

const int Coins::get_GoldCointCount()
{
    return this->goldCount;
}

const int Coins::get_SilverCointCount()
{
    return this->silverCount;
}

const int Coins::get_CopperCointCount()
{
    return this->copperCount;
}
