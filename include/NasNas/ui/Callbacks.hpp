// Created by Modar Nasser on 31/10/2021.

#pragma once

namespace ns::ui {
    enum class MouseCallback {
        onHover,
        onUnhover,
        onFocus,
        onUnfocus,
    };

    enum class ClickCallback {
        onLeftClickPress,
        onLeftClickRelease,
        onRightClickPress,
        onRightClickRelease,
        onMiddleClickPress,
        onMiddleClickRelease,
        onTouchBegan,
        onTouchEnded
    };
}
