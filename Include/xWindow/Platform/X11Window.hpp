// Author: Jake Rieger
// Created: 12/5/2024.
//

#pragma once

#include "NativeWindow.hpp"

namespace x {
    class X11Window final : public INativeWindow {
    public:
        X11Window(const str& title, int width, int height);

        ~X11Window() override;
        void show() override;
        void hide() override;
        void minimize() override;
        void toggleMaximize() override;
        void close() override;
        void blitImage(const vector<u8>& data) override;
        void dispatchMessages() override;

    private:
        struct Impl;
        Unique<Impl> _impl;
    };
}  // namespace x