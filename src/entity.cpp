#include "entity.h"

namespace TermidEngine {

    std::string Entity::getTickerSymbol() const {
        return this->ticker_symbol;
    }

    int Entity::getLastTradedPrice() const {
        return this->last_traded_price;
    }

}