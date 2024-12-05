// Author: Jake Rieger
// Created: 12/5/2024.
//

#include "Platform/Win32Window.hpp"

namespace x {
    struct Win32Window::Impl {
        Impl() {}
        ~Impl() {}

        void hide() {}
        void show() {}
        void minimize() {}
        void maximize() {}
        void restore() {}
        void blitImage(const vector<u8>& data) {}
        void dispatchMessages() {}
        void close() {}
    };

    Win32Window::Win32Window(const str& title, int width, int height)
        : INativeWindow(title, width, height), _impl(std::make_unique<Impl>()) {}

    Win32Window::~Win32Window() {
        _impl.reset();
    }

    void Win32Window::show() {
        _impl->show();
    }

    void Win32Window::hide() {
        _impl->hide();
    }

    void Win32Window::minimize() {}

    void Win32Window::toggleMaximize() {
        if (_maximized) _impl->restore();
        else _impl->maximize();
        _maximized = !_maximized;
    }

    void Win32Window::close() {
        _impl->close();
    }

    void Win32Window::blitImage(const vector<u8>& data) {
        _impl->blitImage(data);
    }

    void Win32Window::dispatchMessages() {
        _impl->dispatchMessages();
    }
}  // namespace x