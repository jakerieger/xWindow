// Author: Jake Rieger
// Created: 12/5/2024.
//

#include "Platform/X11Window.hpp"

namespace x {
    struct X11Window::Impl {
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

    X11Window::X11Window(const str& title, int width, int height)
        : INativeWindow(title, width, height), _impl(std::make_unique<Impl>()) {}

    X11Window::~X11Window() {
        _impl.reset();
    }

    void X11Window::show() {
        _impl->show();
    }

    void X11Window::hide() {
        _impl->hide();
    }

    void X11Window::minimize() {}

    void X11Window::toggleMaximize() {
        if (_maximized) _impl->restore();
        else _impl->maximize();
        _maximized = !_maximized;
    }

    void X11Window::close() {
        _impl->close();
    }

    void X11Window::blitImage(const vector<u8>& data) {
        _impl->blitImage(data);
    }

    void X11Window::dispatchMessages() {
        _impl->dispatchMessages();
    }
}  // namespace x