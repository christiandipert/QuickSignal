#pragma once

#include "LevelInfo.h"

class OrderbookLevelInfos {
public:
    OrderbookLevelInfos(const LevelInfos& bids, const LevelInfos& asks);

    const LevelInfos& getBids() const;
    const LevelInfos& getAsks() const;

private:
    LevelInfos bids_;
    LevelInfos asks_;
};
