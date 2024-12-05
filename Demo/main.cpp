// Author: Jake Rieger
// Created: 12/5/24.
//

#include <Window.hpp>

int main() {
    const auto window = x::Window::Create("Hello World", 800, 600);
    window->show();
    while (!window->shouldExit()) {
        window->dispatchMessages();
    }
    window->close();

    return 0;
}