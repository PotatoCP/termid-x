#include <iostream>

#include "engine.h"

int main() {
    std::ios_base::sync_with_stdio(false);

    TermidEngine::MarketEngine market_engine;

    market_engine.add_entity("TUNA", 400);

    std::cout << "Latest Price of TUNA: " << market_engine.get_entity_price("TUNA") << "\n";

    market_engine.add_account(1, "Naga", 100000);
    market_engine.add_account(2, "Tupai", 200000);

    market_engine.place_bid(1, "TUNA", 100, 350);
    market_engine.place_ask(2, "TUNA", 50, 410);

    std::cout << "Latest Price of TUNA: " << market_engine.get_entity_price("TUNA") << "\n";

    market_engine.place_bid(1, "TUNA", 100, 420);

    std::cout << "Latest Price of TUNA: " << market_engine.get_entity_price("TUNA") << "\n";

    return 0;
}
