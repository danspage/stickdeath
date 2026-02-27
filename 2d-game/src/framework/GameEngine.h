#pragma once

#include <string>
#include <map>

#include <raylib.h>

#include "state/GameState.h"

namespace GameEngine
{
    /// @brief The FPS that the game attempts to run at. The key event, update, and render functions for the current game state are looped through this many times per second.
    inline const int TARGET_FPS = 60;

    /// @brief The game's graphics have a pixel art style to them, and this controls how big each pixel is (they are referred to as 'voxels'). The game's window size will adjust accordingly.
    inline const int VOXEL_SIZE = 2;

    /// @brief How many voxels wide the game's screen is.
    inline const int WIDTH_VOXELS = 320;

    /// @brief How many voxels tall the game's screen is.
    inline const int HEIGHT_VOXELS = 240;

    /// @brief The total number of voxels present in the screen.
    inline const int TOTAL_NUM_VOXELS = WIDTH_VOXELS * HEIGHT_VOXELS;

    /// @brief The title of the game's window.
    inline const char *WINDOW_TITLE = "2D Game";

    inline bool _shuttingDown = false;

    /// @brief Initializes the game engine's states, mapping them to names that will be used for navigation within the code.
    /// @param initialRoute The name of the state that will be loaded upon launching the game.
    /// @param routes A map that defines all game states, and the names that will be used to navigate to them within the code.
    void InitializeRoutes(std::string initialRoute, std::map<std::string, GameState *> routes);
    
    /// @brief Shuts down the game and closes the window.
    void Shutdown();

    /// @brief Disposes of memory upon closing the game. This is called once in the app's main class, and should not be called anywhere else.
    void Cleanup();

    inline std::string _currentState;

    inline std::map<std::string, GameState *> _states;

    /// @brief Loops through all keys defined in `KEYS_USED`, and calls the current state's `OnKeyPressed` function accordingy for each key that has just been pressed. Timed in tandem with and before the `Update` and `Render` functions.
    void ProcessKeyEvents();

    /// @brief Handles all game logic for the current state, and is run in tandem with and before the `Render` function.
    /// @param dt Time since the last update, in seconds.
    void UpdateCurrentState(float dt);

    /// @brief Handles all rendering to the screen for the current state. Attemps to run at a constant interval defined by the `TARGET_FPS` variable in the `GameEngine` class.
    void RenderCurrentState();

    /// @brief A list of voxels that gets drawn to the screen. Each voxel takes up 4 chars, representing the R, G, B, and A channels, from 0-255.
    inline unsigned char *_voxels;

    /// @brief The raylib texture object that the voxels are drawn to. We draw to the `_voxels` array first, then apply it to this texture, and finally render this to the screen so that we can double buffer.
    inline Texture2D _texture = {0};

    /// @brief A list of raylib key IDs that are watched for the `ProcessKeyEvents` function.
    inline const int KEYS_USED[] = {
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_ENTER,
        KEY_SPACE,
        KEY_ESCAPE,
    };
}