#pragma once

#include "utils.h"

namespace TermidEngine {
    struct Trade {
        TermidType::UserId buy_order_id;
        TermidType::UserId ask_order_id;
        TermidType::TickerSymbol entity_symbol;
        TermidType::Quantity quantity;
        TermidType::Currency price;

        Trade(
            TermidType::OrderId _buy_id,
            TermidType::OrderId _ask_id,
            TermidType::TickerSymbol _entity_symbol,
            TermidType::Quantity _quantity,
            TermidType::Currency _price
        ):
            buy_order_id(_buy_id),
            ask_order_id(_ask_id),
            entity_symbol(_entity_symbol),
            quantity(_quantity),
            price(_price)
        {}
    };
}
