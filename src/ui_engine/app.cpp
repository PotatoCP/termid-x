#pragma once

#include "ftxui/component/component.hpp"          // for ScreenInteractive, Component
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive, Component

void spawn_window() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    int value = 0;

    auto status_line = ftxui::Renderer([&] {
        ++value;
        return ftxui::text("status line, counter: " + std::to_string(value)) | ftxui::center;
    });

    auto canvas = ftxui::text("Canvas") | ftxui::center | ftxui::border | ftxui::flex;

    auto layout = ftxui::Container::Vertical(
        {ftxui::Renderer([&] { return canvas; }), ftxui::Renderer([] { return ftxui::separator(); }), status_line});

    screen.Loop(layout);
}