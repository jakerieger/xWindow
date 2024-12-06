// Author: Jake Rieger
// Created: 12/5/24.
//

#include "Platform/WaylandWindow.hpp"

#include "Panic.hpp"
#include "Platform/xdg-shell-client-protocol.h"

#include <wayland-client.h>
#include <wayland-client-protocol.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

static int create_shm_file(size_t size) {
    char name[] = "/x-shm-XXXXXX";
    int fd      = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
    shm_unlink(name);  // Unlink it immediately so it will be deleted when closed
    if (fd < 0) return -1;
    if (ftruncate(fd, size) < 0) {
        close(fd);
        return -1;
    }
    return fd;
}

namespace x {
    wl_display* display       = nullptr;
    wl_compositor* compositor = nullptr;
    wl_surface* surface       = nullptr;
    xdg_wm_base* wmBase       = nullptr;
    xdg_surface* xdgSurface   = nullptr;
    xdg_toplevel* xdgTopLevel = nullptr;

    wl_shm_pool* shmPool;
    wl_buffer* buffer;

    static void create_shm_buffer(int width, int height) {
        int stride = width * 4;  // 4 bytes per pixel (RGBA)
        int size   = stride * height;

        int fd = create_shm_file(size);
        if (fd < 0) { Panic("Failed to create SHM file."); }

        void* data = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (data == MAP_FAILED) {
            close(fd);
            Panic("Failed to mmap SHM.");
        }

        memset(data, 0xFF, size);  // Fill with white for visibility

        shmPool = wl_shm_create_pool(wl_display_get_shm(display), fd, size);
        buffer =
          wl_shm_pool_create_buffer(shmPool, 0, width, height, stride, WL_SHM_FORMAT_XRGB8888);
        wl_surface_attach(surface, buffer, 0, 0);
        wl_surface_damage(surface, 0, 0, width, height);
    }

    // Event listener for xdg_wm_base "ping" event (to keep the client alive)
    static void xdg_wm_base_ping(void* data, struct xdg_wm_base* wm_base, uint32_t serial) {
        xdg_wm_base_pong(wm_base, serial);
    }

    static constexpr xdg_wm_base_listener wm_base_listener = {
      .ping = xdg_wm_base_ping,
    };

    static void registry_global(void* data,
                                struct wl_registry* registry,
                                uint32_t name,
                                const char* interface,
                                uint32_t version) {
        if (strcmp(interface, wl_compositor_interface.name) == 0) {
            compositor =
              CAST<wl_compositor*>(wl_registry_bind(registry, name, &wl_compositor_interface, 1));
        } else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
            wmBase =
              CAST<xdg_wm_base*>(wl_registry_bind(registry, name, &xdg_wm_base_interface, 1));
            xdg_wm_base_add_listener(wmBase, &wm_base_listener, nullptr);
        }
    }

    static void registry_global_remove(void* data, struct wl_registry* registry, uint32_t name) {
        // No-op
    }

    static constexpr wl_registry_listener registry_listener = {
      .global        = registry_global,
      .global_remove = registry_global_remove,
    };

    // Handle the configure event from the compositor
    static void
    xdg_surface_configure(void* data, struct xdg_surface* xdg_surface, uint32_t serial) {
        // Acknowledge the configure event with the serial number
        xdg_surface_ack_configure(xdg_surface, serial);

        // Commit any pending surface changes
        wl_surface_commit(x::surface);
    }

    static constexpr xdg_surface_listener xdg_surface_listener = {
      .configure = xdg_surface_configure,
    };

    struct WaylandWindow::Impl {
        Impl(const str& title, int width, int height) {
            // Step 1: Connect to Wayland Display Server
            display = wl_display_connect(nullptr);
            if (!display) { Panic("Failed to connect to Wayland display."); }

            // Step 2: Get Registry and Bind Global Interfaces
            struct wl_registry* registry = wl_display_get_registry(display);
            wl_registry_add_listener(registry, &registry_listener, nullptr);
            wl_display_roundtrip(display);

            if (!compositor || !wmBase) { Panic("Failed to create compositor or WM base."); }

            // Step 3: Create a Surface and Toplevel Window
            surface = wl_compositor_create_surface(compositor);
            if (!surface) { Panic("Failed to create compositor surface."); }

            xdgSurface = xdg_wm_base_get_xdg_surface(wmBase, surface);
            if (!xdgSurface) { Panic("Failed to get xdg surface."); }
            xdg_surface_add_listener(xdgSurface, &xdg_surface_listener, nullptr);

            xdgTopLevel = xdg_surface_get_toplevel(xdgSurface);
            xdg_toplevel_set_app_id(xdgTopLevel, "simple-wayland-window");
            xdg_toplevel_set_title(xdgTopLevel, "Hello, Wayland!");
            xdg_toplevel_set_min_size(xdgTopLevel, width, height);
        }

        ~Impl() {
            // Cleanup Wayland resources
            // Step 6: Cleanup
            wl_display_disconnect(display);
        }

        void show() {
            // Implementation for showing the window
            // Step 4: Show the Window and Commit Changes
            wl_surface_commit(surface);
            wl_display_roundtrip(display);
        }

        void hide() {}

        void minimize() {}

        void restore() {}

        void maximize() {}

        void close() {}

        int dispatch() {
            while (wl_display_dispatch_pending(display) != -1) {
                wl_display_flush(display);  // Ensure all commands are sent to the compositor
            }
            return wl_display_dispatch(display);
        }
    };

    WaylandWindow::WaylandWindow(const str& title, const int width, const int height)
        : INativeWindow(title, width, height), _impl(std::make_unique<Impl>(title, width, height)) {
    }

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
        const auto result = _impl->dispatch();
        if (result == -1) setShouldExit(true);
    }
}  // namespace x