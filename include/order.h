#include <string>

enum class OrderType {
    buy,
    sell,
};

struct Order {
    int order_id;
    int user_id;
    std::string ticker_symbol;
    OrderType type;
    long long order_quantity;
    int entity_price;

    Order(
        int _order_id,
        int _user_id,
        std::string _ticker_symbol,
        long long _order_quantity,
        int _entity_price
    ):
        order_id(_order_id),
        user_id(_user_id),
        ticker_symbol(_ticker_symbol),
        order_quantity(_order_quantity),
        entity_price(_entity_price)
    {}
};