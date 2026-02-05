#pragma once

#include "utils.h"

namespace TermidEngine {

    enum class OrderType {
        Bid,
        Ask,
    };

    struct Order {
        Type::OrderId order_id;
        Type::UserId user_id;
        Type::TickerSymbol ticker_symbol;
        OrderType type;
        Type::Quantity quantity;
        Type::Currency price;

        Order(
            Type::OrderId _order_id,
            Type::UserId _user_id,
            Type::TickerSymbol _ticker_symbol,
            OrderType _type,
            Type::Quantity _quantity,
            Type::Currency _price
        ):
            order_id(_order_id),
            user_id(_user_id),
            ticker_symbol(_ticker_symbol),
            type(_type),
            quantity(_quantity),
            price(_price)
        {}
    };

}
