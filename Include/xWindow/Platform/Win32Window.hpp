// Author: Jake Rieger
// Created: 12/5/2024.
//

#pragma once

#include "NativeWindow.hpp"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>
#include <windowsx.h>

namespace x {
    class Win32Window final : public INativeWindow {
    public:
        Win32Window(const str& title, int width, int height);

        ~Win32Window() override;
        void show() override;
        void hide() override;
        void minimize() override;
        void toggleMaximize() override;
        void close() override;
        void blitImage(const vector<u8>& data) override;
        void dispatchMessages() override;
        void* getNativeWindowHandle() override;
        bool shouldExit() override;
        void setShouldExit(bool exit) override;

    private:
        HWND _hwnd;
        LPCSTR _className;
        LPCSTR _title;
        MSG _msg;
        int _width, _height;
        bool _shouldExit = false;
        bool _maximized  = false;

        ATOM registerClass(HINSTANCE hInstance) const;
        void initInstance(HINSTANCE hInstance);
    };
}  // namespace x