#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "ui_engine/order_book.hpp"

namespace TermidUI {

ftxui::Element OrderBook::render() {
    using namespace ftxui;
    
    // Create bid rows (sorted descending - highest price first)
    std::vector<Element> bid_rows;
    auto sorted_bids = bids_;
    std::sort(sorted_bids.rbegin(), sorted_bids.rend(), 
              [](const OrderLevel& a, const OrderLevel& b) { return a.price < b.price; });

    // Column widths (characters) for price and size columns
    const int kColWidth = 12;

    // Header with fixed-width columns
    {
        std::ostringstream hp, hs;
        hp << std::left << std::setw(kColWidth) << "BID PRICE";
        hs << std::left << std::setw(kColWidth) << "SIZE";
        bid_rows.push_back(
            hbox({ text(hp.str()) | color(Color::Cyan) | bold, separator(), text(hs.str()) | color(Color::Cyan) | bold }) | center
        );
    }

    for (const auto& bid : sorted_bids) {
        std::ostringstream price_str, size_str;
        price_str << std::right << std::setw(kColWidth) << std::fixed << std::setprecision(2) << bid.price;
        size_str << std::right << std::setw(kColWidth) << std::fixed << std::setprecision(2) << bid.size;

        bid_rows.push_back(
            hbox({ text(price_str.str()) | color(Color::Green), separator(), text(size_str.str()) | color(Color::Yellow) })
        );
    }

    // Create ask rows (sorted ascending - lowest price first)
    std::vector<Element> ask_rows;
    auto sorted_asks = asks_;
    std::sort(sorted_asks.begin(), sorted_asks.end(),
              [](const OrderLevel& a, const OrderLevel& b) { return a.price < b.price; });

    // Header for asks
    {
        std::ostringstream hp, hs;
        hp << std::left << std::setw(kColWidth) << "ASK PRICE";
        hs << std::left << std::setw(kColWidth) << "SIZE";
        ask_rows.push_back(
            hbox({ text(hp.str()) | color(Color::Cyan) | bold, separator(), text(hs.str()) | color(Color::Cyan) | bold }) | center
        );
    }

    for (const auto& ask : sorted_asks) {
        std::ostringstream price_str, size_str;
        price_str << std::right << std::setw(kColWidth) << std::fixed << std::setprecision(2) << ask.price;
        size_str << std::right << std::setw(kColWidth) << std::fixed << std::setprecision(2) << ask.size;

        ask_rows.push_back(
            hbox({ text(price_str.str()) | color(Color::Red), separator(), text(size_str.str()) | color(Color::Yellow) })
        );
    }
    
    // Pad rows to same height
    size_t max_rows = std::max(bid_rows.size(), ask_rows.size());
    while (bid_rows.size() < max_rows) {
        bid_rows.push_back(hbox({text("") | flex, separator(), text("") | flex}));
    }
    while (ask_rows.size() < max_rows) {
        ask_rows.push_back(hbox({text("") | flex, separator(), text("") | flex}));
    }
    
    // Combine left and right sides
    std::vector<Element> combined_rows;
    for (size_t i = 0; i < bid_rows.size(); ++i) {
        combined_rows.push_back(
            hbox({
                bid_rows[i],
                separator(),
                ask_rows[i]
            })
        );
    }
    
    return vbox(combined_rows) | border | flex;
}

ftxui::Component OrderBook::create_component() {
    return ftxui::Renderer([this] { return render(); });
}

}
