#pragma once

#include <unordered_map>
#include <memory>

#include "utils.h"
#include "order.h"
#include "entity.h"
#include "account.h"

namespace TermidEngine {

    class MarketEngine {
    public:
        MarketEngine() {}

        void place_order(Order order);
        void add_entity(Type::TickerSymbol new_code, Type::Price new_price);
        void add_account(Type::UserId user_id, std::string username);
        
    private:
        std::unordered_map<Type::OrderId, std::unique_ptr<Order>> open_orders;
        std::unordered_map<Type::TickerSymbol, std::unique_ptr<Entity>> entities;
        std::unordered_map<Type::UserId, std::unique_ptr<Account>> accounts;
    };

}
