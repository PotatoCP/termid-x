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
        std::normal_distribution price_generator{400.0, 10.0};

        auto random_price = [&price_generator, &gen]{ return std::lround(price_generator(gen)); };

        for(int i = 0; i < 200; ++i) {
            int ask_or_bid = gen() % 2;
            int quantity = gen() % 1000 + 1;
            int price = random_price();
            if(ask_or_bid == 0) {
                std::cout << "Bidding: " << quantity << " units at $" << price << "\n";
                market_engine.place_bid(1, "TUNA", quantity, price);
            } else {
                std::cout << "Asking: " << quantity << " units at $" << price << "\n";
                market_engine.place_ask(2, "TUNA", quantity, price);
            }
            std::cout << "Price of TUNA: " << market_engine.get_entity_price("TUNA") << "\n";
        }

        std::cout << "Final Price of TUNA: " << market_engine.get_entity_price("TUNA") << "\n";

    });
    engine_thread.join();


    return 0;
}
