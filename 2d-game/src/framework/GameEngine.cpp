#include "GameEngine.h"

namespace GameEngine
{
    void InitializeRoutes(std::string initialRoute, std::map<std::string, GameState *> routes)
    {
        GameEngine::InitializeGraphics();

        _currentState = initialRoute;

        for (auto const &route : routes)
        {
            _states.insert(std::make_pair(route.first, route.second));
        }
    }

    void Shutdown()
    {
        _shuttingDown = true;
    }

    void Cleanup()
    {
        // 1. Unload the texture from GPU memory
        if (_texture.id != 0)
        {
            UnloadTexture(_texture);
        }

        // 2. Free the CPU pixel buffer
        if (_voxels != nullptr)
        {
            free(_voxels);
            _voxels = nullptr;
        }
    }

    void ProcessKeyEvents()
    {
        for (int key : KEYS_USED)
        {
            if (IsKeyPressed(key))
            {
                _states[_currentState]->OnKeyPressed(key);
            }
        }
    }

    void UpdateCurrentState(float dt)
    {
        _states[_currentState]->Update(dt);
    }

    void RenderCurrentState()
    {
        _states[_currentState]->Render();

        if (_texture.id == 0)
        {
            Image image = {
                .data = _voxels,
                .width = WIDTH_VOXELS * VOXEL_SIZE,
                .height = HEIGHT_VOXELS * VOXEL_SIZE,
                .mipmaps = 1,
                .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
            _texture = LoadTextureFromImage(image);
        }
        else
        {
            UpdateTexture(_texture, _voxels);
        }

        DrawTexture(_texture, 0, 0, WHITE);
    }
}