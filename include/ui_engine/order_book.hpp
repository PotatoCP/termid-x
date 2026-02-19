#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include <vector>
#include <string>

namespace TermidUI {

struct OrderLevel {
    double price;
    double size;
};

class OrderBook {
public:
    OrderBook() = default;
    
    // Set bid orders (price, size) - typically shown left side
    void set_bids(const std::vector<OrderLevel>& bids) {
        bids_ = bids;
    }
    
    // Set ask orders (price, size) - typically shown right side
    void set_asks(const std::vector<OrderLevel>& asks) {
        asks_ = asks;
    }
    
    // Create the FTXUI component for rendering the order book
    ftxui::Component create_component();
    
    // Create just the visual element (can be used with Renderer)
    ftxui::Element render();

private:
    std::vector<OrderLevel> bids_;
    std::vector<OrderLevel> asks_;
};

} // namespace ui_engine
