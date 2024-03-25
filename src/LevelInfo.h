#pragma once

#include <vector>
#include "EnumsAndTypes.h"

struct LevelInfo {
    Price price_;
    Quantity quantity_;
};

using LevelInfos = std::vector<LevelInfo>;
