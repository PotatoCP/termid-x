#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>

#include "utils.h"
#include "engine.h"

namespace TermidEngine {

    class Account {
    public:
        Account(Type::UserId _user_id, std::string _username):
            user_id(_user_id),
            username(_username),
            owned_entities(),
            open_orders_id()
        {}

        void insert_order_id(Type::OrderId order_id);
        void remove_order_id(Type::OrderId order_id);
        void bought_entity(Type::TickerSymbol symbol, Type::Currency price, Type::Quantity quantity);
        void sold_entity(Type::TickerSymbol symbol, Type::Currency price, Type::Quantity quantity);

    private:
        std::unordered_map<Type::TickerSymbol, Type::Quantity> owned_entities;
        std::unordered_set<Type::OrderId> open_orders_id;

        Type::UserId user_id;
        std::string username;
        Type::Currency cash_balance;
    };

}
