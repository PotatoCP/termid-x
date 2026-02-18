#pragma once

#include "utils.h"

namespace TermidEngine {

    enum class OrderTermidType {
        Bid,
        Ask,
    };

    struct Order {
        TermidType::OrderId order_id;
        TermidType::UserId user_id;
        TermidType::TickerSymbol ticker_symbol;
        OrderTermidType TermidType;
        TermidType::Quantity quantity;
        TermidType::Currency price;

        Order(
            TermidType::OrderId _order_id,
            TermidType::UserId _user_id,
            TermidType::TickerSymbol _ticker_symbol,
            OrderTermidType _TermidType,
            TermidType::Quantity _quantity,
            TermidType::Currency _price
        ):
            order_id(_order_id),
            user_id(_user_id),
            ticker_symbol(_ticker_symbol),
            TermidType(_TermidType),
            quantity(_quantity),
            price(_price)
        {}
    };

}
