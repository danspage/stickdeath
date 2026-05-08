#pragma once

namespace GameEngine
{
    /// @brief A list of keys that are watched for the `ProcessKeyEvents`
    /// function.
    enum class Key
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ENTER,
        SPACE,
        ESCAPE
    };

    const Key ALL_KEYS[] = {
        Key::UP,
        Key::DOWN,
        Key::LEFT,
        Key::RIGHT,
        Key::ENTER,
        Key::SPACE,
        Key::ESCAPE,
    };
}