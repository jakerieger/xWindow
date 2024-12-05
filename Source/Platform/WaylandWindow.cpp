// Author: Jake Rieger
// Created: 12/5/24.
//

#include "Platform/WaylandWindow.hpp"

#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <wayland-egl.h>
#include "Platform/xdg-shell-client-protocol.h"

namespace x {
    struct WaylandWindow::WaylandWindowImpl {
        wl_display* display       = nullptr;
        wl_compositor* compositor = nullptr;
        wl_surface* surface       = nullptr;
        xdg_wm_base* wmBase       = nullptr;
        xdg_surface* xdgSurface   = nullptr;
        xdg_toplevel* xdgTopLevel = nullptr;

        WaylandWindowImpl(const str& title, int width, int height) {
            // Initialization code for Wayland
            display = wl_display_connect(nullptr);
            // Create surface, etc.
        }

        ~WaylandWindowImpl() {
            // Cleanup Wayland resources
            if (surface) wl_surface_destroy(surface);
            if (display) wl_display_disconnect(display);
        }

        void show() {
            // Implementation for showing the window
        }
    };

    WaylandWindow::WaylandWindow(const str& title, const int width, const int height)
        : INativeWindow(title, width, height),
          _impl(std::make_unique<WaylandWindowImpl>(title, width, height)) {}

    WaylandWindow::~WaylandWindow() = default;

    void WaylandWindow::show() {
        _impl->show();
    }

    void WaylandWindow::hide() {}

    void WaylandWindow::minimize() {}

    void WaylandWindow::toggleMaximize() {}

    void WaylandWindow::close() {}

    void WaylandWindow::blitImage(const vector<u8>& data) {}

    void WaylandWindow::dispatchMessages() {}
}  // namespace x