#pragma once

#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "order.h"
#include "utils.h"

namespace TermidEngine {

    class Entity {
    public:
        using OrderBookPair = std::pair<Type::Price, std::queue<Type::OrderId>>;

        Entity(Type::TickerSymbol new_code, Type::Price new_price):
            ticker_symbol(new_code),
            last_traded_price(new_price),
            pending_bid(),
            pending_ask() {}

        Type::TickerSymbol getTickerSymbol() const;
        Type::Price getLastTradedPrice() const;

        void pop_best_bid();
        void pop_best_ask();
        void push_bid(Type::Price price, Type::OrderId order_id);
        void push_ask(Type::Price price, Type::OrderId order_id);

        std::vector<OrderBookPair>::reverse_iterator get_best_bid() const;
        std::vector<OrderBookPair>::reverse_iterator get_best_ask() const;

        bool bid_is_empty() const;
        bool ask_is_empty() const;

    private:

        Type::TickerSymbol ticker_symbol;

        // This will be shown to the user as the current entity price 
        Type::Price last_traded_price;

        // Using reversed std::vector instead of std::map for the order book
        // Inspired from http://youtube.com/watch?v=sX2nF1fW7kI
        std::vector<OrderBookPair> pending_bid;
        std::vector<OrderBookPair> pending_ask;
    };

}
