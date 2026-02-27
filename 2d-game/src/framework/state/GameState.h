#pragma once

/// @brief
class GameState
{
public:
    virtual ~GameState() {};

    /// @brief Runs when the state is loaded by the game.
    virtual void OnLoad() {};

    /// @brief Runs before the game switches from this state to a new one.
    virtual void onExit() {};

    /// @brief Handles all game logic for the state.
    /// @param dt Time since the last update, in seconds.
    virtual void Update(float dt) {};

    /// @brief Handles all rendering to the screen for the state.
    virtual void Render() {};

    /// @brief Handles the logic for when a key is pressed.
    /// @param key The ID of the key, as defined by Raylib.
    virtual void OnKeyPressed(int key) {};
};