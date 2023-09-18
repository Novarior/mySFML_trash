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

/////////////////////////////////////////////////////////////////
/// @brief Less than operator for Coins
/// @return bool
template <typename T>
inline bool operator<(const Coins& left, const Coins& right)
{
    return (left.goldCount < right.goldCount) || (left.silverCount < right.silverCount) || (left.copperCount < right.copperCount);
}

/////////////////////////////////////////////////////////////////
/// @brief Greater than operator for Coins
/// @return bool
template <typename T>
inline bool operator>(const Coins& left, const Coins& right)
{
    return (left.goldCount > right.goldCount) || (left.silverCount > right.silverCount) || (left.copperCount > right.copperCount);
}

/////////////////////////////////////////////////////////////////
/// @brief Less than or equal operator for Coins
/// @return bool
template <typename T>
inline bool operator<=(const Coins& left, const Coins& right)
{
    return (left.goldCount <= right.goldCount) || (left.silverCount <= right.silverCount) || (left.copperCount <= right.copperCount);
}

/////////////////////////////////////////////////////////////////
/// @brief Greater than or equal operator for Coins
/// @return bool
template <typename T>
inline bool operator>=(const Coins& left, const Coins& right)
{
    return (left.goldCount >= right.goldCount) || (left.silverCount >= right.silverCount) || (left.copperCount >= right.copperCount);
}

/////////////////////////////////////////////////////////////////
/// @brief Output stream operator for Coins
/// @return std::ostream
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Coins& coin)
{
    os << coin.goldCount << "g " << coin.silverCount << "s " << coin.copperCount << "c";
    return os;
}

/////////////////////////////////////////////////////////////////
/// @brief Input stream operator for Coins
/// @return std::istream
template <typename T>
inline std::istream& operator>>(std::istream& is, Coins& coin)
{
    is >> coin.goldCount >> coin.silverCount >> coin.copperCount;
    return is;
}
