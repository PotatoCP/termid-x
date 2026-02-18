#include <algorithm>

#include "backend_engine/engine.h"

namespace TermidEngine {

    // Buyer and seller must be guaranteed to exist before calling this function
    void MarketEngine::do_transaction(
        Type::UserId buyer_id,
        Type::UserId seller_id,
        Type::TickerSymbol entity_symbol,
        Type::Quantity order_quantity,
        Type::Currency order_price
    ) {
        this->trade_history.emplace_back(
            buyer_id,
            seller_id,
            entity_symbol,
            order_quantity,
            order_price
        );
        this->accounts.at(buyer_id).bought_entity(entity_symbol, order_price, order_quantity);
        this->accounts.at(seller_id).sold_entity(entity_symbol, order_price, order_quantity);
        this->entities.at(entity_symbol).setLastTradedPrice(order_price);
    }

    Type::OrderId MarketEngine::place_bid(
        Type::UserId user_id,
        Type::TickerSymbol symbol,
        Type::Quantity order_quantity,
        Type::Currency price
    ) {
        auto entity_it = this->entities.find(symbol);
        if(entity_it == this->entities.end()){
            // If the entity doesn't exist, we can't place the order.
            return 0;
        }

        auto account_it= this->accounts.find(user_id);
        if(account_it == this->accounts.end()){
            // Account must exist to place an order.
            return 0;
        }

        auto &entity = entity_it->second;

        // Match before pushing the bid
        while(!entity.ask_is_empty()) {
            auto current_best_ask = entity.get_best_ask();
            Type::Currency best_ask_price = current_best_ask->first;

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
                    order_book_queue.pop_front();
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
                    this->accounts.at(ask_order.user_id).remove_order_id(order_book_queue.front());
                    this->open_orders.erase(order_book_queue.front());
                    order_book_queue.pop_front();
                } 

                // If the current order quantity is zero, we don't need to store the order.
                if(order_quantity == 0) {
                    return 0;
                }
            }

            entity.pop_best_ask();
        }

        Type::OrderId current_order_id = ++(this->latest_order_id);
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
        entity.push_bid(price, current_order_id);
        account_it->second.insert_order_id(current_order_id);
        return current_order_id;
    }

    Type::OrderId MarketEngine::place_ask(
        Type::UserId user_id,
        Type::TickerSymbol symbol,
        Type::Quantity order_quantity,
        Type::Currency price
    ) {
        auto entity_it = this->entities.find(symbol);
        if(entity_it == this->entities.end()){
            // If the entity doesn't exist, we can't place the order.
            return 0;
        }

        auto account_it= this->accounts.find(user_id);
        if(account_it == this->accounts.end()){
            // Account must exist to place an order.
            return 0;
        }

        auto &entity = entity_it->second;

        // Match before pushing the ask
        while(!entity.bid_is_empty()) {
            auto current_best_bid = entity.get_best_bid();
            Type::Currency best_bid_price = current_best_bid->first;

            // If the best bid price is less than the current ask price,
            // we can't match the current order.
            if(best_bid_price < price) {
                break;
            }

            // Iterate the queue of the best bid until either
            // the current ask quantity is empty or the best bid queue is empty.
            auto& order_book_queue = current_best_bid->second;
            while(!order_book_queue.empty()) {
                auto bid_order_it = this->open_orders.find(order_book_queue.front());

                if(bid_order_it == this->open_orders.end()){
                    order_book_queue.pop_front();
                    continue;
                }

                auto& bid_order = bid_order_it->second;

                Type::Quantity trade_quantity = std::min(order_quantity, bid_order.quantity);

                this->do_transaction(
                    bid_order.user_id,
                    user_id,
                    symbol,
                    trade_quantity,
                    best_bid_price
                );

                bid_order.quantity -= trade_quantity;
                order_quantity -= trade_quantity;

                if(bid_order.quantity == 0) {
                    this->accounts.at(bid_order.user_id).remove_order_id(order_book_queue.front());
                    this->open_orders.erase(order_book_queue.front());
                    order_book_queue.pop_front();
                } 

                // If the current order quantity is zero, we don't need to store the order.
                if(order_quantity == 0) {
                    return 0;
                }
            }

            entity.pop_best_bid();
        }

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
        entity.push_ask(price, current_order_id);
        account_it->second.insert_order_id(current_order_id);
        return current_order_id;
    }

    void MarketEngine::add_entity(Type::TickerSymbol symbol, Type::Currency price) {
        this->entities.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(symbol),
            std::forward_as_tuple(symbol, price)
        );
    }

    void MarketEngine::add_account(
        Type::UserId user_id,
        Type::UserName username,
        Type::Currency initial_balance
    ) {
        this->accounts.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(user_id),
            std::forward_as_tuple(user_id, username, initial_balance)
        );
    }

    Type::Currency MarketEngine::get_entity_price(Type::TickerSymbol symbol) const {
        auto entity_it = this->entities.find(symbol);
        if(entity_it == this->entities.end()){
            // If the entity doesn't exist, return -1 as the price.
            return -1;
        }

        return entity_it->second.getLastTradedPrice();
    }

}