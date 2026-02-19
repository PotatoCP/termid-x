#include "backend_engine/entity.hpp"

namespace TermidEngine {

    TermidType::TickerSymbol Entity::getTickerSymbol() const {
        return this->ticker_symbol;
    }

    TermidType::Currency Entity::getLastTradedPrice() const {
        return this->last_traded_price;
    }

    std::vector<Entity::OrderBookPair>::reverse_iterator Entity::get_best_bid() {
        return this->pending_bid.rbegin();
    }

    std::vector<Entity::OrderBookPair>::reverse_iterator Entity::get_best_ask() {
        return this->pending_ask.rbegin();
    }

    void Entity::pop_best_bid() {
        this->pending_bid.pop_back();
    }

    void Entity::pop_best_ask() {
        this->pending_ask.pop_back();
    }

    void Entity::push_bid(TermidType::Currency price, TermidType::OrderId order_id) {
        auto it = this->pending_bid.rbegin();
        for(; it != this->pending_bid.rend(); ++it) {
            if(it->first < price) {
                break;
            }
            if(it->first == price) {
                it->second.push_back(order_id);
                return;
            }
        }
        std::deque<TermidType::OrderId> order_id_queue({order_id});
        this->pending_bid.emplace(
            it.base(),
            std::piecewise_construct,
            std::forward_as_tuple(price),
            std::forward_as_tuple(std::move(order_id_queue))
        );
    }
    
    void Entity::push_ask(TermidType::Currency price, TermidType::OrderId order_id) {
        auto it = this->pending_ask.rbegin();
        for(; it != this->pending_ask.rend(); ++it) {
            if(it->first > price) {
                break;
            }
            if(it->first == price) {
                it->second.push_back(order_id);
                return;
            }
        }
        std::deque<TermidType::OrderId> order_id_queue({order_id});
        this->pending_ask.emplace(
            it.base(),
            std::piecewise_construct,
            std::forward_as_tuple(price),
            std::forward_as_tuple(std::move(order_id_queue))
        );
    }

    void Entity::setLastTradedPrice(TermidType::Currency new_price) {
        this->last_traded_price = new_price;
    }

    bool Entity::bid_is_empty() const {
        return this->pending_bid.empty();
    }

    bool Entity::ask_is_empty() const {
        return this->pending_ask.empty();
    }
}
