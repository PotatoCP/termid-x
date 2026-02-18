#pragma once

#include <unordered_map>

#include "utils.h"
#include "order.h"
#include "entity.h"
#include "account.h"
#include "trade.h"

namespace TermidEngine {

    class MarketEngine {
    public:
        MarketEngine(): open_orders(), entities(), accounts(), latest_order_id(0) {}

        Type::OrderId place_bid(
            Type::UserId user_id,
            Type::TickerSymbol symbol,
            Type::Quantity order_quantity,
            Type::Currency price
        );
        Type::OrderId place_ask(
            Type::UserId user_id,
            Type::TickerSymbol symbol,
            Type::Quantity order_quantity,
            Type::Currency price
        );
        void do_transaction(
            Type::UserId buyer_id, 
            Type::UserId seller_id, 
            Type::TickerSymbol entity_symbol, 
            Type::Quantity order_quantity, 
            Type::Currency order_price
        );
        void add_entity(Type::TickerSymbol new_code, Type::Currency new_price);
        void add_account(
            Type::UserId user_id,
            Type::UserName username,
            Type::Currency initial_balance = 0
        );

        Type::Currency get_entity_price(Type::TickerSymbol symbol) const;

    private:
        std::unordered_map<Type::OrderId, Order> open_orders;
        std::unordered_map<Type::TickerSymbol, Entity> entities;
        std::unordered_map<Type::UserId, Account> accounts;
        std::vector<Trade> trade_history;

        Type::OrderId latest_order_id;
    };

}
