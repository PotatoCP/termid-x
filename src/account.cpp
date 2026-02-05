#include "account.h"

namespace TermidEngine {

    void Account::insert_order_id(Type::OrderId order_id) {
        this->open_orders_id.insert(order_id);
    }

    void Account::remove_order_id(Type::OrderId order_id) {
        this->open_orders_id.erase(order_id);
    }

    void Account::bought_entity(Type::TickerSymbol symbol, Type::Currency price, Type::Quantity quantity) {
        this->owned_entities[symbol] += quantity;
        this->cash_balance -= price * quantity;
    }

    void Account::sold_entity(Type::TickerSymbol symbol, Type::Currency price, Type::Quantity quantity) {
        this->owned_entities[symbol] -= quantity;
        this->cash_balance += price * quantity;
    }

}