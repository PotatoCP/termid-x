#include "entity.h"
#include "stock.h"

namespace TermidEngine {

    long long Stock::getMarketCapitalization() const {
        return 1LL * this->getLastTradedPrice() * this->share_outstanding;
    }

}