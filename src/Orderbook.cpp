#include "SmartPointers.h"
#include <map>
#include <unordered_map>
#include <algorithm> // For std::min
#include "TradeInfo.h"
#include "Trade.cpp"

class Orderbook {
private:
    struct OrderEntry {
        OrderPointer order_{nullptr};
        OrderPointers::iterator location_;
    };

    std::map<Price, OrderPointers, std::greater<Price>> bids_;
    std::map<Price, OrderPointers, std::less<Price>> asks_;
    std::unordered_map<OrderID, OrderEntry> orders_;

public:
    bool canMatch(Side side, Price price) const {
        if (side == Side::Buy) {
            if (asks_.empty()) {
                return false;
            }
            // Changed from structured binding to iterator to avoid compile error in const context
            auto bestAskIt = asks_.begin();
            return price >= bestAskIt->first;
        } else {
            if (bids_.empty()) {
                return false;
            }
            auto bestBidIt = bids_.begin();
            return price <= bestBidIt->first;
        }
    }

    Trades matchOrders() {
        Trades trades;

        while (true) {
            if (bids_.empty() || asks_.empty()) {
                break;
            }

            auto bidIt = bids_.begin();
            auto askIt = asks_.begin();

            if (bidIt->first < askIt->first) { break; }

            while (!bidIt->second.empty() && !askIt->second.empty()) {
                auto& bid = bidIt->second.front();
                auto& ask = askIt->second.front();

                Quantity quantity = std::min(bid->getRemainingQuantity(), ask->getRemainingQuantity());

                bid->Fill(quantity);
                ask->Fill(quantity);

                if (bid->getRemainingQuantity() == 0) {
                    bidIt->second.pop_front();
                    orders_.erase(bid->getOrderID());
                }

                if (ask->getRemainingQuantity() == 0) {
                    askIt->second.pop_front();
                    orders_.erase(ask->getOrderID());
                }

                if (bidIt->second.empty()) {
                    bids_.erase(bidIt++);
                }

                if (askIt->second.empty()) {
                    asks_.erase(askIt++);
                }

                // Assuming TradeInfo has a constructor that takes these parameters
                trades.push_back( Trade {
                    TradeInfo{bid->getOrderID(), bid->getPrice(), quantity},
                    TradeInfo{ask->getOrderID(), ask->getPrice(), quantity}
                });
            }
        }

        if (!bids_.empty()) {
            auto& [_, bids] = *bids_.begin();
            auto& order = bids.front();
            if (order->getOrderType() == OrderType::FillAndKill) {
                CancelOrder(order->getOrderID);
            }
        }

        if (!asks_.empty()) {
            auto& [_, asks] = *asks_.begin();
            auto& order = asks.front();
            if (order->getOrderType() == OrderType::FillAndKill) {
                CancelOrder(order->getOrderID());
            }
        }

        return trades;
    }

    public:
        Trades addOrder(OrderPointer order) {
            if (orders_.contains(order->getOrderID())) {
                return { };
            }
            if (order->getOrderType() == OrderType::FillAndKill && !canMatch(order->getSide(), order->getPrice())) {
                return { };
            }

            OrderPointers::iterator iterator;

            if (order->getSide() == Side::Buy) {
                auto& orders = bids_[order->getPrice()];
                orders.push_back(order);
                iterator = std::next(orders.begin(), orders.size() - 1);
            } else {
                auto& orders = asks_[order->getPrice()];
                orders.push_back(order);
                iterator = std::next(orders.begin(), orders.size() - 1);
            }

            orders_.insert({order->getOrderID(), OrderEntry{order, iterator}});
            return matchOrders();
        }
};