// Author: Jake Rieger
// Created: 12/5/24.
//

#include "Window.hpp"

#if defined(_WS_WINDOWS)
    #include "Platform/Win32Window.hpp"
using WindowType = x::Win32Window;
#elif defined(_WS_WAYLAND)
    #include "Platform/WaylandWindow.hpp"
using WindowType = x::WaylandWindow;
#elif defined(_WS_X11)

#elif defined(_WS_APPLE)
#else
    #error "Unsupported platform"
#endif

namespace x {
    Unique<INativeWindow> Window::Create(const str& title, const int width, const int height) {
        return std::make_unique<WindowType>(title, width, height);
    }
}  // namespace x