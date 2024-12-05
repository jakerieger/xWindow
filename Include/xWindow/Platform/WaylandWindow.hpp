// Author: Jake Rieger
// Created: 12/5/24.
//

#pragma once

#include "NativeWindow.hpp"

namespace x {
    class WaylandWindow final : public INativeWindow {
    public:
        WaylandWindow(const str& title, int width, int height);

        ~WaylandWindow() override;
        void show() override;
        void hide() override;
        void minimize() override;
        void toggleMaximize() override;
        void close() override;
        void blitImage(const vector<u8>& data) override;
        void dispatchMessages() override;
    };
}  // namespace x
