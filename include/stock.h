#pragma once

#include <string>
#include "entity.h"

namespace TermidEngine {

    class Stock: public Entity {
        long long share_outstanding;
        
    public:
        Stock(Type::TickerSymbol new_code, Type::Currency new_price, Type::Quantity new_share_count):
        Entity(new_code, new_price), share_outstanding(new_share_count) {}

        long long getMarketCapitalization() const;
    };

}
