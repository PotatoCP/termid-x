#include "entity.h"

namespace TermidEngine {

    Type::TickerSymbol Entity::getTickerSymbol() const {
        return this->ticker_symbol;
    }

    Type::Currency Entity::getLastTradedPrice() const {
        return this->last_traded_price;
    }

    std::vector<Entity::OrderBookPair>::reverse_iterator Entity::get_best_bid() const {
        return (this->pending_bid).rbegin();
    }

    std::vector<Entity::OrderBookPair>::reverse_iterator Entity::get_best_ask() const {
        return (this->pending_ask).rbegin();
    }

    void Entity::pop_best_bid() {
        this->pending_bid.pop_back();
    }

    void Entity::pop_best_ask() {
        this->pending_ask.pop_back();
    }

    void Entity::push_bid(Type::Currency price, Type::OrderId order_id) {
        auto it = this->pending_bid.rbegin();
        for(; it != this->pending_bid.rend(); it++) {
            if(it->first < price) {
                break;
            }
            if(it->first == price) {
                it->second.push(order_id);
                break;
            }
        }
        std::queue<Type::OrderId> order_id_queue({order_id});
        this->pending_bid.emplace(
            it.base(),
            std::piecewise_construct,
            std::forward_as_tuple(price),
            std::forward_as_tuple(std::move(order_id_queue))
        );
    }
    
    void Entity::push_ask(Type::Currency price, Type::OrderId order_id) {
        auto it = this->pending_ask.rbegin();
        for(; it != this->pending_ask.rend(); it++) {
            if(it->first > price) {
                break;
            }
            if(it->first == price) {
                it->second.push(order_id);
                break;
            }
        }
        std::queue<Type::OrderId> order_id_queue({order_id});
        this->pending_ask.emplace(
            it.base(),
            std::piecewise_construct,
            std::forward_as_tuple(price),
            std::forward_as_tuple(std::move(order_id_queue))
        );
    }

    bool Entity::bid_is_empty() const {
        return this->pending_bid.empty();
    }

    bool Entity::ask_is_empty() const {
        return this->pending_ask.empty();
    }
}
