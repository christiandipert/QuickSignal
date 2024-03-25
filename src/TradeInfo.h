#pragma once

#include "EnumsAndTypes.h"
#include <vector>

struct TradeInfo {
    OrderID orderId_;
    Price price_;
    Quantity quantity_;
};

using Trades = std::vector<Trade>;