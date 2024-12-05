// Author: Jake Rieger
// Created: 12/5/2024.
//

#pragma once

#include "Canvas.hpp"
#include "Platform.hpp"

namespace XVGE {
    class Win32Canvas final : public ICanvas {
    public:
        void Initialize() override {}
        void Destroy() override {}
        void DrawLine() override {}
        void DrawRect() override {}
        void DrawEllipse() override {}
        void DrawPath() override {}
        void DrawText() override {}
        void DrawImage() override {}
    };
}  // namespace XVGE
