// Author: Jake Rieger
// Created: 12/5/24.
//

#include "Platform/WaylandWindow.hpp"

#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <wayland-egl.h>
#include "Platform/xdg-shell-client-protocol.h"

namespace x {
    struct WaylandWindow::Impl {
        wl_display* display       = nullptr;
        wl_compositor* compositor = nullptr;
        wl_surface* surface       = nullptr;
        xdg_wm_base* wmBase       = nullptr;
        xdg_surface* xdgSurface   = nullptr;
        xdg_toplevel* xdgTopLevel = nullptr;

        Impl(const str& title, int width, int height) {
            // Initialization code for Wayland
            display = wl_display_connect(nullptr);
            // Create surface, etc.
        }

        ~Impl() {
            // Cleanup Wayland resources
            if (surface) wl_surface_destroy(surface);
            if (display) wl_display_disconnect(display);
        }

        void show() {
            // Implementation for showing the window
        }

        void hide() {}

        void minimize() {}

        void restore() {}

        void maximize() {}

        void close() {}

        void dispatch() {}
    };

    WaylandWindow::WaylandWindow(const str& title, const int width, const int height)
        : INativeWindow(title, width, height),
          _impl(std::make_unique<Impl>(title, width, height)) {}

    WaylandWindow::~WaylandWindow() = default;

    void WaylandWindow::show() {
        _impl->show();
    }

    void WaylandWindow::hide() {
        _impl->hide();
    }

    void WaylandWindow::minimize() {
        _impl->minimize();
    }

    void WaylandWindow::toggleMaximize() {
        if (_maximized) _impl->restore();
        else _impl->maximize();
        _maximized = !_maximized;
    }

    void WaylandWindow::close() {
        _impl->close();
    }

    void WaylandWindow::blitImage(const vector<u8>& data) {}

    void WaylandWindow::dispatchMessages() {
        _impl->dispatch();
    }
}  // namespace x