#include <iostream>
#include <stock.cpp>

int main() {
    std::ios_base::sync_with_stdio(false);

    Stock tuna{"TUNA", 500, 2'000'000'000};

    std::cout << "Total Market Capitalization for "
     << tuna.getTickerSymbol() << ": " << tuna.getMarketCapitalization() << "\n";

    return 0;
}