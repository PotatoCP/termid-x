#include "entity.h"

namespace TermidEngine {

    Type::TickerSymbol Entity::getTickerSymbol() const {
        return this->ticker_symbol;
    }

    Type::Price Entity::getLastTradedPrice() const {
        return this->last_traded_price;
    }

    std::vector<Entity::OrderBookPair>::reverse_iterator Entity::get_best_bid() const {
        return (this->pending_bid).rbegin();
    }

    std::vector<Entity::OrderBookPair>::reverse_iterator Entity::get_best_ask() const {
        return (this->pending_ask).rbegin();
    }

    bool Entity::bid_is_empty() const {
        return this->pending_bid.empty();
    }

    bool Entity::ask_is_empty() const {
        return this->pending_ask.empty();
    }
}
