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
            : mIsMinimized(false), mIsMaximized(false), mTitle(title), mWidth(width),
              mHeight(height), mShouldExit(false) {
            mEventDispatcher = std::make_shared<EventDispatcher>();
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
            return mShouldExit;
        }

        friend class Win32Window;
        friend class X11Window;
        friend class WaylandWindow;
        friend class CocoaWindow;

    protected:
        Shared<EventDispatcher> mEventDispatcher;

    private:
        bool mIsMinimized;
        bool mIsMaximized;
        str mTitle;
        i32 mWidth;
        i32 mHeight;
        bool mShouldExit;

        void setShouldExit(const bool shouldExit) {
            mShouldExit = shouldExit;
        }
    };
}  // namespace x