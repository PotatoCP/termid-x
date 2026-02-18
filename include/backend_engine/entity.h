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
        using OrderBookPair = std::pair<TermidType::Currency, std::deque<TermidType::OrderId>>;

        Entity(TermidType::TickerSymbol new_code, TermidType::Currency new_price):
            ticker_symbol(new_code),
            last_traded_price(new_price),
            pending_bid(),
            pending_ask() {}

        TermidType::TickerSymbol getTickerSymbol() const;
        TermidType::Currency getLastTradedPrice() const;

        void pop_best_bid();
        void pop_best_ask();
        void push_bid(TermidType::Currency price, TermidType::OrderId order_id);
        void push_ask(TermidType::Currency price, TermidType::OrderId order_id);
        void setLastTradedPrice(TermidType::Currency new_price);

        std::vector<OrderBookPair>::reverse_iterator get_best_bid();
        std::vector<OrderBookPair>::reverse_iterator get_best_ask();

        bool bid_is_empty() const;
        bool ask_is_empty() const;

    private:

        TermidType::TickerSymbol ticker_symbol;

        // This will be shown to the user as the current entity price 
        TermidType::Currency last_traded_price;

        // Using reversed std::vector instead of std::map for the order book
        // Inspired from http://youtube.com/watch?v=sX2nF1fW7kI
        // TLDR: the activities happen mostly at the top of the order book,
        // so using vectors with reverse iterator ensures most activities happen
        // at the end of the vectors.
        std::vector<OrderBookPair> pending_bid;
        std::vector<OrderBookPair> pending_ask;
    };

}
