#pragma once

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include <vector>

#include "ui_engine/order_book.hpp"

void spawn_window() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    
    // Create order book instance
    auto order_book = std::make_shared<TermidUI::OrderBook>();
    
    // Sample bid data (open bids to buy)
    std::vector<TermidUI::OrderLevel> bids = {
        {98.50, 1000},
        {98.25, 1500},
        {98.00, 2000},
        {97.75, 1200},
        {97.50, 900},
        {97.25, 1100},
        {97.00, 800},
    };
    
    // Sample ask data (open asks to sell)
    std::vector<TermidUI::OrderLevel> asks = {
        {99.75, 1100},
        {100.00, 950},
        {100.25, 1300},
        {100.50, 1800},
        {100.75, 1600},
        {101.00, 1400},
        {101.25, 1050},
    };
    
    order_book->set_bids(bids);
    order_book->set_asks(asks);
    
    // Create the title
    auto title = ftxui::Renderer([] {
        return ftxui::text("ORDER BOOK") | ftxui::center | ftxui::bold | ftxui::color(ftxui::Color::Cyan);
    });
    
    // Create status line
    int tick = 0;
    auto status_line = ftxui::Renderer([&] {
        return ftxui::text("Press Ctrl+C to exit | Update: " + std::to_string(tick++)) 
            | ftxui::center | ftxui::dim;
    });
    
    // Create the main layout
    auto layout = ftxui::Container::Vertical({
        title,
        ftxui::Renderer([] { return ftxui::separator(); }),
        order_book->create_component(),
        ftxui::Renderer([] { return ftxui::separator(); }),
        status_line
    });

    screen.Loop(layout);
}