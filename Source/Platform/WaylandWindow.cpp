// Author: Jake Rieger
// Created: 12/5/24.
//

#include "Platform/WaylandWindow.hpp"

namespace x {
    WaylandWindow::WaylandWindow(const str& title, const int width, const int height)
        : INativeWindow(title, width, height) {}

    WaylandWindow::~WaylandWindow() {}

    void WaylandWindow::show() {}

    void WaylandWindow::hide() {}

    void WaylandWindow::minimize() {}

    void WaylandWindow::toggleMaximize() {}

    void WaylandWindow::close() {}

    void WaylandWindow::blitImage(const vector<u8>& data) {}

    void WaylandWindow::dispatchMessages() {}
}  // namespace x