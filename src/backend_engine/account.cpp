#include "backend_engine/account.h"

namespace TermidEngine {

    void Account::insert_order_id(TermidType::OrderId order_id) {
        this->open_orders_id.insert(order_id);
    }

    void Account::remove_order_id(TermidType::OrderId order_id) {
        this->open_orders_id.erase(order_id);
    }

    void Account::bought_entity(TermidType::TickerSymbol symbol, TermidType::Currency price, TermidType::Quantity quantity) {
        this->owned_entities[symbol] += quantity;
        this->cash_balance -= price * quantity;
    }

    void Account::sold_entity(TermidType::TickerSymbol symbol, TermidType::Currency price, TermidType::Quantity quantity) {
        this->owned_entities[symbol] -= quantity;
        this->cash_balance += price * quantity;
    }

}