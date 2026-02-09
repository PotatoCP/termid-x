#include <iostream>
#include <thread>
#include <random>

#include "engine.h"

int main() {
    std::ios_base::sync_with_stdio(false);

    std::thread engine_thread([]{
        TermidEngine::MarketEngine market_engine;

        market_engine.add_entity("TUNA", 400);

        std::cout << "Latest Price of TUNA: " << market_engine.get_entity_price("TUNA") << "\n";

        market_engine.add_account(1, "Naga", 100000);
        market_engine.add_account(2, "Tupai", 200000);

        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution price_generator{400.0, 1.0};

        auto random_price = [&price_generator, &gen]{ return std::lround(price_generator(gen)); };

        double total_time_ms = 0.0;
        int total_orders = 100;

        struct OrderTest {
            std::string symbol;
            int user_id;
            int quantity;
            int price;
            bool is_bid;
        };

        std::vector<OrderTest> orders;

        for(int i = 0; i < total_orders; ++i) {
            int ask_or_bid = gen() % 2;
            int quantity = gen() % 1000 + 1;
            int price = random_price();
            orders.push_back({"TUNA", ask_or_bid + 1, quantity, price, ask_or_bid == 0});
        }

        for(const auto& order : orders) {
            auto start_time = std::chrono::high_resolution_clock::now();
            if(order.is_bid) {
                market_engine.place_bid(order.user_id, order.symbol, order.quantity, order.price);
            } else {
                market_engine.place_ask(order.user_id, order.symbol, order.quantity, order.price);
            }
            auto end_time = std::chrono::high_resolution_clock::now();
            total_time_ms += std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
            std::cout << "Placed " << (order.is_bid ? "Bid" : "Ask") << " for " << order.quantity << " of " << order.symbol << " at price " << order.price << " by user " << order.user_id << "\n";
            std::cout << "Current Price of TUNA: " << market_engine.get_entity_price("TUNA") << "\n";
        }

        std::cout << "Final Price of TUNA: " << market_engine.get_entity_price("TUNA") << "\n";
        std::cout << "Average time per order: " << total_time_ms / total_orders << " ns\n";

    });
    engine_thread.join();


    return 0;
}
