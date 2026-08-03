#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "graphics/GameImage.h"
#include "graphics/Graphics.h"

struct SDL_Renderer;

namespace GameEngine
{
    class GameState;

    /// @brief The target update rate of the game, in Hz. This is used to calculate
    /// the fixed time step for the game loop, which is used to ensure that the game runs at a consistent speed regardless of the performance of the machine it's
    /// running on.
    inline const int TARGET_UPDATE_HZ = 60;

    /// @brief The game's graphics have a pixel art style to them, and this controls
    /// how big each pixel is (they are referred to as 'voxels'). The game's window
    /// size will adjust accordingly.
    inline const int VOXEL_SIZE = 2;

    /// @brief How many voxels wide the game's screen is.
    inline const int WIDTH_VOXELS = 320;

    /// @brief How many voxels tall the game's screen is.
    inline const int HEIGHT_VOXELS = 240;

    /// @brief How many pixels (NOT voxels) wide the game's screen is.
    inline const int WIDTH_PIXELS = WIDTH_VOXELS * VOXEL_SIZE;

    /// @brief How many pixels (NOT voxels) tall the game's screen is.
    inline const int HEIGHT_PIXELS = HEIGHT_VOXELS * VOXEL_SIZE;

    /// @brief The total number of voxels present in the screen.
    inline const int TOTAL_NUM_VOXELS = WIDTH_VOXELS * HEIGHT_VOXELS;

    /// @brief The total number of pixels (NOT voxels) present on the screen.
    inline const int TOTAL_NUM_PIXELS = TOTAL_NUM_VOXELS * VOXEL_SIZE * VOXEL_SIZE;
    /// @brief The title of the game's window.
    inline const char *WINDOW_TITLE = "2D Game";

    inline bool _shuttingDown = false;

    inline const SDL_Scancode KEYS_USED[] = {
        SDL_SCANCODE_UP,
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_ESCAPE,
        SDL_SCANCODE_RETURN,
        SDL_SCANCODE_SPACE,
        SDL_SCANCODE_E,
    };

    /// @brief Sets the SDL_Renderer that the game engine will use to render to the screen. This should only be called once, in the app's main class, and should not be called anywhere else.
    void SetRenderer(SDL_Renderer *renderer);

    /// @brief Initializes the game engine's states, mapping them to names that will
    /// be used for navigation within the code.
    /// @param initialRoute The name of the state that will be loaded upon launching
    /// the game.
    /// @param routes A map that defines all game states, and the names that will be
    /// used to navigate to them within the code.
    void InitializeRoutes(std::string initialRoute,
                          const std::map<std::string, GameState *> &routes);

    /// @brief Shuts down the game and closes the window.
    void Shutdown();

    /// @brief Disposes of memory upon closing the game. This is called once in the
    /// app's main class, and should not be called anywhere else.
    void Cleanup();

    inline std::string _currentState;

    inline std::map<std::string, GameState *> _states;

    /// @brief Gets the current FPS of the game.
    int GetFPS();

    /// @brief Loops through all keys defined in `KEYS_USED`, and calls the current
    /// state's `OnKeyPressed` function accordingy for each key that has just been
    /// pressed. Timed in tandem with and before the `Update` and `Render`
    /// functions.
    void ProcessKeyEvents();

    void Update(float dt);

    /// @brief Handles all rendering to the screen for the current state. Attemps to
    /// run at a constant interval defined by the `TARGET_FPS` variable in the
    /// `GameEngine` class.
    void RenderCurrentState();

    /// @brief Exits the current state and loads the specified state.
    void SetState(std::string route);

    /// @brief A list of voxels that gets drawn to the screen. Each voxel takes up 4
    /// chars, representing the R, G, B, and A channels, from 0-255.
    inline uint32_t *_pixels;
}