#include "Order.h"

Order::Order(OrderType orderType, OrderID orderId, Side side, Price price, Quantity quantity)
    : orderType_{ orderType }
    , orderId_{ orderId }
    , side_{ side }
    , price_{ price }
    , initialQuantity_{ quantity }
    , remainingQuantity_{ quantity }
{}

OrderID Order::getOrderID() const {
    return orderId_;
}

Side Order::getSide() const {
    return side_;
}

Price Order::getPrice() const {
    return price_;
}

OrderType Order::getOrderType() const {
    return orderType_;
}

Quantity Order::getInitialQuantity() const {
    return initialQuantity_;
}

Quantity Order::getRemainingQuantity() const {
    return remainingQuantity_;
}

Quantity Order::getFilledQuantity() const {
    return initialQuantity_ - remainingQuantity_;
}

void Order::Fill(Quantity quantity) {
    if (quantity > getRemainingQuantity()) {
        throw std::logic_error("Attempted to fill an order with quantity exceeding remaining quantity.");
    }

    remainingQuantity_ -= quantity;
}
