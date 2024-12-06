// Author: Jake Rieger
// Created: 12/5/24.
//

#pragma once

#include "EventSystem.hpp"

#include <Types.hpp>

namespace x {
    class INativeWindow {
    public:
        explicit INativeWindow() {
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
        virtual void* getNativeWindowHandle()          = 0;
        virtual bool shouldExit()                      = 0;
        virtual void setShouldExit(bool exit)          = 0;

        template<typename EventType>
        void registerListener(std::function<void(const EventType&)> callback) {
            _eventDispatcher->registerListener(callback);
        }

        EventDispatcher& getEventDispatcher() const {
            return *_eventDispatcher;
        }

        friend class Win32Window;
        friend class X11Window;
        friend class WaylandWindow;
        friend class CocoaWindow;

    protected:
        Shared<EventDispatcher> _eventDispatcher;
    };
}  // namespace x