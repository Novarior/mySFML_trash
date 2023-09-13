#include "Coins.hpp"

// inline functions
/////////////////////////////////////////////////////////////////
/// @brief Plus operator for Coins
/// @return Coins
template <typename T>
inline Coins operator+(const Coins& left, const Coins& right)
{
    return Coins(left.goldCount + right.goldCount,
        left.silverCount + right.silverCount,
        left.copperCount + right.copperCount);
}

/////////////////////////////////////////////////////////////////
/// @brief Plus equal operator for Coins
/// @return Coins
template <typename T>
inline Coins operator+=(const Coins& left, const Coins& right)
{
    return Coins(left.goldCount += right.goldCount,
        left.silverCount += right.silverCount,
        left.copperCount += right.copperCount);
}

/////////////////////////////////////////////////////////////////
/// @brief Minus operator for Coins
/// @return Coins
template <typename T>
inline Coins operator-(const Coins& left, const Coins& right)
{
    return Coins(left.goldCount - right.goldCount,
        left.silverCount - right.silverCount,
        left.copperCount - right.copperCount);
}

/////////////////////////////////////////////////////////////////
/// @brief Minus equal operator for Coins
/// @return Coins
template <typename T>
inline Coins operator-=(const Coins& left, const Coins& right)
{
    return Coins(left.goldCount -= right.goldCount,
        left.silverCount -= right.silverCount,
        left.copperCount -= right.copperCount);
}

/////////////////////////////////////////////////////////////////
/// @brief Equal operator for Coins
/// @return bool
template <typename T>
inline bool operator==(const Coins& left, const Coins& right)
{
    return (left.goldCount == right.goldCount && left.silverCount == right.silverCount && left.copperCount == right.copperCount);
}
/////////////////////////////////////////////////////////////////
/// @brief Not equal operator for Coins
/// @return bool
template <typename T>
inline bool operator!=(const Coins& left, const Coins& right)
{
    return (left.copperCount != rightm_coin_count.copperCount) || (left.silverCount != right.silverCount) || (left.goldCount != right.goldCount);
}