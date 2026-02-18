#pragma once

#include "utils.h"

namespace TermidEngine {
    struct Trade {
        Type::UserId buy_order_id;
        Type::UserId ask_order_id;
        Type::TickerSymbol entity_symbol;
        Type::Quantity quantity;
        Type::Currency price;

        Trade(
            Type::OrderId _buy_id,
            Type::OrderId _ask_id,
            Type::TickerSymbol _entity_symbol,
            Type::Quantity _quantity,
            Type::Currency _price
        ):
            buy_order_id(_buy_id),
            ask_order_id(_ask_id),
            entity_symbol(_entity_symbol),
            quantity(_quantity),
            price(_price)
        {}
    };
}
