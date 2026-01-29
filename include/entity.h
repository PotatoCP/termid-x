#pragma once

#include <string>
#include <map>
#include <queue>
#include <unordered_set>
#include "order.h"
#include "utils.h"

namespace TermidEngine {

    class Entity {
    public:
        Entity(Type::TickerSymbol new_code, Type::Price new_price):
            ticker_symbol(new_code),
            last_traded_price(new_price),
            deleted_order_id(),
            pending_bid(),
            pending_ask() {}

        Type::TickerSymbol getTickerSymbol() const;

        int getLastTradedPrice() const;

        void delete_order(Type::OrderId id);
        void pop_bid(Type::Price price);
        void pop_ask(Type::Price price);
        void push_bid(Type::Price price, Type::OrderId order_id);
        void push_ask(Type::Price price, Type::OrderId order_id);

    private:
        Type::TickerSymbol ticker_symbol;

        // This will be shown to the user as the current entity price 
        Type::Price last_traded_price;

        // If the order id exist in this set, ignore the bid/ask
        std::unordered_set<Type::OrderId> deleted_order_id;

        std::map<Type::Price, std::queue<Type::OrderId>, std::greater<Type::Price>> pending_bid;
        std::map<Type::Price, std::queue<Type::OrderId>, std::less<Type::Price>> pending_ask;
    };

}
