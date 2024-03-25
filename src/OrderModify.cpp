#pragma once

#include "EnumsAndTypes.h"
#include "Order.h" // Include the Order header if not already included elsewhere
#include <memory>  // For std::make_shared

class OrderModify {
public:
    OrderModify(OrderID orderId, Side side, Price price, Quantity quantity) // Correct parameter names
        : orderId_{ orderId }
        , price_{ price }
        , side_{ side }
        , quantity_{ quantity }
    { }

    OrderID getOrderId() const {
        return orderId_;
    }

    Price getPrice() const {
        return price_;
    }

    Side getSide() const {
        return side_;
    }

    Quantity getQuantity() const {
        return quantity_;
    }

    std::shared_ptr<Order> toOrderPointer(OrderType type) const { // Correct function name and return type
        return std::make_shared<Order>(type, getOrderId(), getSide(), getPrice(), getQuantity());
    }

private:
    OrderID orderId_; // Ensure these types are correctly defined in EnumsAndTypes.h or globally
    Price price_;
    Side side_;
    Quantity quantity_;
};
