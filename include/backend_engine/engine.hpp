#pragma once

#include <unordered_map>

#include "utils.hpp"
#include "order.hpp"
#include "entity.hpp"
#include "account.hpp"
#include "trade.hpp"

namespace TermidEngine {

    class MarketEngine {
    public:
        MarketEngine(): open_orders(), entities(), accounts(), latest_order_id(0) {}

        TermidType::OrderId place_bid(
            TermidType::UserId user_id,
            TermidType::TickerSymbol symbol,
            TermidType::Quantity order_quantity,
            TermidType::Currency price
        );
        TermidType::OrderId place_ask(
            TermidType::UserId user_id,
            TermidType::TickerSymbol symbol,
            TermidType::Quantity order_quantity,
            TermidType::Currency price
        );
        void do_transaction(
            TermidType::UserId buyer_id, 
            TermidType::UserId seller_id, 
            TermidType::TickerSymbol entity_symbol, 
            TermidType::Quantity order_quantity, 
            TermidType::Currency order_price
        );
        void add_entity(TermidType::TickerSymbol new_code, TermidType::Currency new_price);
        void add_account(
            TermidType::UserId user_id,
            TermidType::UserName username,
            TermidType::Currency initial_balance = 0
        );

        TermidType::Currency get_entity_price(TermidType::TickerSymbol symbol) const;

    private:
        std::unordered_map<TermidType::OrderId, Order> open_orders;
        std::unordered_map<TermidType::TickerSymbol, Entity> entities;
        std::unordered_map<TermidType::UserId, Account> accounts;
        std::vector<Trade> trade_history;

        TermidType::OrderId latest_order_id;
    };

}
