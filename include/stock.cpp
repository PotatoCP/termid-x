#include "stock.h"

long long Stock::getMarketCapitalization() const {
    return 1LL * this->getLastTradedPrice() * this->share_outstanding;
}
