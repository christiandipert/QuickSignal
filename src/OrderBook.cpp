#include <cstdint>
#include <vector>

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

using namespace std;

using Price = int32_t;
using Quantity = uint32_t;
using OrderID = uint64_t;

struct levelInfo {
    Price price_;
    Quantity quantity_;
};

int main() {
    return 0;
}