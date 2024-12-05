// Author: Jake Rieger
// Created: 12/5/24.
//

#pragma once

#include "EventSystem.hpp"

#include <Types.hpp>

namespace x {
    class INativeWindow {
    public:
        explicit INativeWindow(const str& title, const int width = 800, const int height = 600)
            : _maximized(false), _minimized(false), _title(title), _width(width), _height(height),
              _shouldExit(false) {
            _eventDispatcher = std::make_shared<EventDispatcher>();
        }

        virtual ~INativeWindow() = default;

        virtual void show()                            = 0;
        virtual void hide()                            = 0;
        virtual void minimize()                        = 0;
        virtual void toggleMaximize()                  = 0;
        virtual void close()                           = 0;
        virtual void blitImage(const vector<u8>& data) = 0;
        virtual void dispatchMessages()                = 0;

        [[nodiscard]] bool shouldExit() const {
            return _shouldExit;
        }

        friend class Win32Window;
        friend class X11Window;
        friend class WaylandWindow;
        friend class CocoaWindow;

    protected:
        Shared<EventDispatcher> _eventDispatcher;

    private:
        bool _maximized;
        bool _minimized;
        str _title;
        i32 _width;
        i32 _height;
        bool _shouldExit;

        void setShouldExit(const bool shouldExit) {
            _shouldExit = shouldExit;
        }
    };
}  // namespace x