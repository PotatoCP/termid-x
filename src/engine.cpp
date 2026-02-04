#include <algorithm>

#include "engine.h"

namespace TermidEngine {

    void MarketEngine::do_transaction(
        Type::UserId buyer_id, 
        Type::UserId seller_id, 
        Type::TickerSymbol entity_symbol, 
        Type::Quantity order_quantity, 
        Type::Price order_price
    ) {
        this->trade_history.emplace_back(
            buyer_id,
            seller_id,
            entity_symbol,
            order_quantity,
            order_price
        );

        // TODO: Change account entities ownership
    }

    void MarketEngine::place_bid(
        Type::UserId user_id,
        Type::TickerSymbol symbol,
        Type::Quantity order_quantity,
        Type::Price price
    ) {
        int current_order_id = ++(this->latest_order_id);

        // Match before pushing the bid
        auto entity_it = this->entities.find(symbol);
        if(entity_it == this->entities.end()){
            return;
        }

        auto &entity = entity_it->second;

        while(!entity.ask_is_empty()) {
            auto current_best_ask = entity.get_best_ask();
            Type::Price best_ask_price = current_best_ask->first;

            // If the best ask price is more than the current bid price,
            // we can't match the current order.
            if(best_ask_price > price) {
                break;
            }

            // Iterate the queue of the best ask until either
            // the current bid quantity is empty or the best ask queue is empty.
            auto& order_book_queue = current_best_ask->second;
            while(!order_book_queue.empty()) {
                auto ask_order_it = this->open_orders.find(order_book_queue.front());

                if(ask_order_it == this->open_orders.end()){
                    order_book_queue.pop();
                    continue;
                }

                auto& ask_order = ask_order_it->second;

                Type::Quantity trade_quantity = std::min(order_quantity, ask_order.quantity);

                this->do_transaction(
                    user_id,
                    ask_order.user_id,
                    symbol,
                    trade_quantity,
                    best_ask_price
                );

                ask_order.quantity -= trade_quantity;
                order_quantity -= trade_quantity;

                if(ask_order.quantity == 0) {
                    this->open_orders.erase(order_book_queue.front());
                    order_book_queue.pop();
                } 

                if(order_quantity == 0) {
                    return;
                }
            }

            entity.pop_best_ask();
        }

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

    void MarketEngine::place_ask(
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