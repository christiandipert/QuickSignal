#pragma once

#include <cstdint>

enum class OrderType {
    Market,
    Limit,
    GoodTillCancel,
    FillAndKill
};

enum class Side {
    Buy,
    Sell
};

using Price = int32_t;
using Quantity = uint32_t;
using OrderID = uint64_t;
