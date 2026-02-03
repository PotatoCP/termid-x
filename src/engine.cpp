#include "engine.h"

namespace TermidEngine {

    void MarketEngine::place_bid(
        Type::UserId user_id,
        Type::TickerSymbol symbol,
        Type::Quantity order_quantity,
        Type::Price price
    ) {
        int current_order_id = ++(this->latest_order_id);

        // Match before pushing the bid
        auto& entity = this->entities.at(symbol);
        while(!entity.ask_is_empty()) {
            auto current_best_ask = entity.get_best_ask();
            Type::Price best_ask_price = current_best_ask->first;

            // If the best ask price is more than the current bid price,
            // we can't match the current order anymore.
            if(best_ask_price > price) {
                break;
            }

            // Iterate the queue of the best ask until either
            // the current bid quantity is empty or the best ask queue is empty.
            auto& order_book_queue = current_best_ask->second;
            while(!order_book_queue.empty()) {
                try {
                    auto& ask_order = this->open_orders.at(order_book_queue.front());

                    if(ask_order.quantity >= order_quantity) {
                        trade_history.emplace_back(
                            user_id,
                            ask_order.user_id,
                            order_quantity,
                            price
                        );

                        // Return since we don't need t push empty empty bid
                        return;
                    } else {
                        // TODO: Transaction happens with ask_order.quantity amount
                    }
    
                    order_book_queue.pop();
                } catch (const std::out_of_range& _oor) {
                    continue;
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