#include <iostream>
#include <thread>
#include <random>
#include <chrono>

#include "engine.h"
#include "app.cpp"

void test_engine() {
    TermidEngine::MarketEngine market_engine;

    market_engine.add_entity("TUNA", 400);
    market_engine.add_entity("NATU", 100);

    market_engine.add_account(1, "Naga", 100000);
    market_engine.add_account(2, "Tupai", 200000);

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution tuna_price_generator{400.0, 30.0};
    std::normal_distribution natu_price_generator{100.0, 10.0};

    auto random_tuna_price = [&tuna_price_generator, &gen]{ return std::lround(tuna_price_generator(gen)); };
    auto random_natu_price = [&natu_price_generator, &gen]{ return std::lround(natu_price_generator(gen)); };

    double total_time_ms = 0.0;
    int total_orders = 1'000'000;

    struct OrderTest {
        std::string symbol;
        int user_id;
        int quantity;
        int price;
        bool is_bid;
    };

    std::vector<OrderTest> orders;

    for(int i = 0; i < total_orders; ++i) {
        int random_symbol = gen() % 2;
        int is_bid = gen() % 2;
        int quantity = gen() % 1000 + 1;
        int price = random_symbol == 0 ? random_tuna_price() : random_natu_price();
        orders.push_back({random_symbol == 0 ? "TUNA" : "NATU", is_bid + 1, quantity, price, (is_bid == 1)});
    }

    std::vector<double> order_times;

    for(const auto& order : orders) {
        auto start_time = std::chrono::high_resolution_clock::now();
        if(order.is_bid) {
            market_engine.place_bid(order.user_id, order.symbol, order.quantity, order.price);
        } else {
            market_engine.place_ask(order.user_id, order.symbol, order.quantity, order.price);
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        auto time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        double time_taken_ns = static_cast<double>(time_taken);
        order_times.push_back(time_taken_ns);
        total_time_ms += time_taken_ns;
    }

    std::cout << "Final Price of TUNA: " << market_engine.get_entity_price("TUNA") << "\n";
    std::cout << "Final Price of NATU: " << market_engine.get_entity_price("NATU") << "\n";
    std::cout << "Average time per order: " << total_time_ms / total_orders << " ns\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);

    // std::thread engine_thread(test_engine);
    // engine_thread.join();
    
    std::thread app_thread(spawn_window);
    app_thread.join();


    return 0;
}
