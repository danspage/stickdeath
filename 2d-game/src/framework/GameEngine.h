#pragma once

#include <string>
#include <map>

#include <raylib.h>

#include "state/GameState.h"

namespace GameEngine
{
    inline const int TARGET_FPS = 60;

    inline const int VOXEL_SIZE = 2;
    inline const int WIDTH_VOXELS = 320;
    inline const int HEIGHT_VOXELS = 240;
    inline const int TOTAL_NUM_VOXELS = WIDTH_VOXELS * HEIGHT_VOXELS;

    inline const char *WINDOW_TITLE = "2D Game";

    inline bool _shuttingDown = false;

    void Initialize(std::string initialRoute, std::map<std::string, GameState*> routes);
    void Shutdown();
    void Cleanup();

    inline std::string _currentState;

    inline std::map<std::string, GameState*> _states;

    void ProcessKeyEvents();
    void UpdateCurrentState(float dt);
    void RenderCurrentState();

    // Used for rendering pixels
    inline unsigned char *_pixels;
    inline Texture2D _texture = {0};

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