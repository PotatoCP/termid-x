#include <string>
#include <vector>
#include <queue>

#include "order.h"

class Entity {
    std::string ticker_symbol;

    // This will be shown to the user as the current entity price 
    int last_traded_price;

    // {price, }
    std::vector<std::queue<Order>> pending_bid;
    std::vector<std::queue<Order>> pending_ask;

public:
    Entity(std::string new_code, int new_price):
        ticker_symbol(new_code), last_traded_price(new_price), pending_bid(), pending_ask() {}

    std::string getTickerSymbol() const;

    int getLastTradedPrice() const;
};