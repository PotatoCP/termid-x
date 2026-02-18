#pragma once

#include <unordered_map>
#include <unordered_set>

#include "utils.h"

namespace TermidEngine {

    class Account {
    public:
        Account(TermidType::UserId _user_id, TermidType::UserName _username, TermidType::Currency _initial_balance):
            owned_entities(),
            open_orders_id(),
            user_id(_user_id),
            username(_username),
            cash_balance(_initial_balance)
        {}

        Account(TermidType::UserId _user_id, TermidType::UserName _username):
            owned_entities(),
            open_orders_id(),
            user_id(_user_id),
            username(_username),
            cash_balance(0)
        {}

        void insert_order_id(TermidType::OrderId order_id);
        void remove_order_id(TermidType::OrderId order_id);
        void bought_entity(TermidType::TickerSymbol symbol, TermidType::Currency price, TermidType::Quantity quantity);
        void sold_entity(TermidType::TickerSymbol symbol, TermidType::Currency price, TermidType::Quantity quantity);

    private:
        std::unordered_map<TermidType::TickerSymbol, TermidType::Quantity> owned_entities;
        std::unordered_set<TermidType::OrderId> open_orders_id;

        TermidType::UserId user_id;
        TermidType::UserName username;
        TermidType::Currency cash_balance;
    };

}
