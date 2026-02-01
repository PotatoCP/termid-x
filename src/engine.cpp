#include "engine.h"

namespace TermidEngine {

    void MarketEngine::place_bid(
        Type::UserId user_id,
        Type::TickerSymbol symbol,
        Type::Quantity order_quantity,
        Type::Price price
    ) {
        int current_order_id = ++(this->latest_order_id);

        this->open_orders.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(current_order_id),
            std::forward_as_tuple(
                current_order_id,
                user_id,
                symbol,
                OrderType::Bid,
                order_quantity,
                price
            )
        );
        this->accounts[user_id].insert_order_id(current_order_id);
    }

    void MarketEngine::place_bid(
        Type::UserId user_id,
        Type::TickerSymbol symbol,
        Type::Quantity order_quantity,
        Type::Price price
    ) {
        int current_order_id = ++(this->latest_order_id);

        this->open_orders.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(current_order_id),
            std::forward_as_tuple(
                current_order_id,
                user_id,
                symbol,
                OrderType::Ask,
                order_quantity,
                price
            )
        );
        this->accounts[user_id].insert_order_id(current_order_id);
    }

    void MarketEngine::add_entity(Type::TickerSymbol symbol, Type::Price price) {
        this->entities.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(symbol),
            std::forward_as_tuple(symbol, price)
        );
    }

    void MarketEngine::add_account(Type::UserId user_id, std::string username) {
        this->accounts.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(user_id),
            std::forward_as_tuple(user_id, username)
        );
    }

}