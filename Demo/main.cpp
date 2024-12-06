// Author: Jake Rieger
// Created: 12/5/24.
//

#include <Events.hpp>
#include <Window.hpp>
#include <iostream>
#include <ostream>

int main() {
    const auto window = x::Window::Create("Hello World", 800, 600);

    window->registerListener<x::ResizeEvent>([&](const x::ResizeEvent& e) {
        std::cout << "ResizeEvent: " << "(" << e.Width << ", " << e.Height << ")" << std::endl;
    });

    window->show();
    while (!window->shouldExit()) {
        window->blitImage(canvasData);
        window->dispatchMessages();
    }

    return 0;
}