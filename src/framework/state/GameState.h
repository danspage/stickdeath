#pragma once

#include "../io/Key.h"

namespace GameEngine
{
    class GameState
    {
    public:
        virtual ~GameState() {};

        /// @brief Runs when the state is loaded by the game.
        virtual void OnEnter() {};

        /// @brief Runs before the game switches from this state to a new one.
        virtual void onExit() {};

        /// @brief Handles all game logic for the state.
        /// @param dt Time since the last update, in seconds.
        virtual void Update(float dt) {};

        /// @brief Handles all rendering to the screen for the state.
        virtual void Render() {};

        /// @brief Handles the logic for when a key is pressed.
        /// @param key Which key was pressed.
        virtual void OnKeyPressed(GameEngine::Key key) {};

        /// @brief Handles the logic for when a key is held.
        /// @param key Which key is being held.
        virtual void OnKeyHeld(GameEngine::Key key) {};
    };
}