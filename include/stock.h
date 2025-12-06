#include <string>
#include "entity.h"

class Stock: public Entity {
    std::string ticker_symbol;
    int share_outstanding;
    
public:
    Stock(std::string new_code, int new_price, int new_share_count):
       Entity(new_code, new_price), share_outstanding(new_share_count) {}

    long long getMarketCapitalization() const;
};