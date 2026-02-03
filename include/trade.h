#pragma once

#include "utils.h"

namespace TermidEngine {
    struct Trade {
        Type::UserId buy_order_id;
        Type::UserId ask_order_id;
        Type::Quantity quantity;
        Type::Price price;

        Trade(
            Type::OrderId _buy_id,
            Type::OrderId _ask_id,
            Type::Quantity _quantity,
            Type::Price _price
        ):
            buy_order_id(_buy_id),
            ask_order_id(_ask_id),
            quantity(_quantity),
            price(_price) {}
    };
}
