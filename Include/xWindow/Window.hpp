// Author: Jake Rieger
// Created: 12/5/24.
//

#pragma once

#include "NativeWindow.hpp"

namespace x {
    class Window {
    public:
        static Unique<INativeWindow> Create(const str& title, int width = 800, int height = 600);
    };
}  // namespace x
