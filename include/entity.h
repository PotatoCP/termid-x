#pragma once

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include "order.h"
#include "utils.h"

namespace TermidEngine {

    class Entity {
    public:
        using OrderBookPair = std::pair<Type::Currency, std::deque<Type::OrderId>>;

        Entity(Type::TickerSymbol new_code, Type::Currency new_price):
            ticker_symbol(new_code),
            last_traded_price(new_price),
            pending_bid(),
            pending_ask() {}

        Type::TickerSymbol getTickerSymbol() const;
        Type::Currency getLastTradedPrice() const;

        void pop_best_bid();
        void pop_best_ask();
        void push_bid(Type::Currency price, Type::OrderId order_id);
        void push_ask(Type::Currency price, Type::OrderId order_id);
        void setLastTradedPrice(Type::Currency new_price);

        std::vector<OrderBookPair>::reverse_iterator get_best_bid();
        std::vector<OrderBookPair>::reverse_iterator get_best_ask();

        bool bid_is_empty() const;
        bool ask_is_empty() const;

    private:

        Type::TickerSymbol ticker_symbol;

        // This will be shown to the user as the current entity price 
        Type::Currency last_traded_price;

        // Using reversed std::vector instead of std::map for the order book
        // Inspired from http://youtube.com/watch?v=sX2nF1fW7kI
        // TLDR: the activities happen mostly at the top of the order book,
        // so using vectors with reverse iterator ensures most activities happen
        // at the end of the vectors.
        std::vector<OrderBookPair> pending_bid;
        std::vector<OrderBookPair> pending_ask;
    };

}
