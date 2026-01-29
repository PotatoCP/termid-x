#pragma once

#include "utils.h"

namespace TermidEngine {

    enum class OrderType {
        Buy,
        Sell,
    };

    struct Order {
        Type::OrderId order_id;
        Type::UserId user_id;
        Type::TickerSymbol ticker_symbol;
        OrderType type;
        Type::Quantity order_quantity;
        Type::Price entity_price;

        Order(
            Type::OrderId _order_id,
            Type::UserId _user_id,
            Type::TickerSymbol _ticker_symbol,
            Type::Quantity _order_quantity,
            Type::Price _entity_price
        ):
            order_id(_order_id),
            user_id(_user_id),
            ticker_symbol(_ticker_symbol),
            order_quantity(_order_quantity),
            entity_price(_entity_price)
        {}
    };

}
