#pragma once

#include <stdexcept>
#include <memory>
#include "EnumsAndTypes.h"

class Order {
    public:
        Order(OrderType orderType, OrderID orderId, Side side, Price price, Quantity quantity);

        OrderID getOrderID() const;
        Side getSide() const;
        Price getPrice() const;
        OrderType getOrderType() const;
        Quantity getInitialQuantity() const;
        Quantity getRemainingQuantity() const;
        Quantity getFilledQuantity() const;
        void Fill(Quantity quantity);

    private:
        OrderType orderType_;
        OrderID orderId_;
        Side side_;
        Price price_;
        Quantity initialQuantity_;
        Quantity remainingQuantity_;
    };
