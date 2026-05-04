#include "GameEngine.h"

int _frameCount = 0;

namespace GameEngine
{
  /// @brief The raylib texture object that the voxels are drawn to. We draw to
  /// the `_voxels` array first, then apply it to this texture, and finally render
  /// this to the screen so that we can double buffer.
  inline Texture2D _texture = {0};

  /// @brief A list of raylib key IDs that are watched for the `ProcessKeyEvents`
  /// function.
  inline const int KEYS_USED[] = {
      KEY_UP,
      KEY_DOWN,
      KEY_LEFT,
      KEY_RIGHT,
      KEY_ENTER,
      KEY_SPACE,
      KEY_ESCAPE,
  };

  void InitializeRoutes(std::string initialRoute,
                        std::map<std::string, GameState *> routes)
  {
    GameEngine::InitializeGraphics();

    _currentState = initialRoute;

    for (auto const &route : routes)
    {
      _states.insert(std::make_pair(route.first, route.second));
    }
  }

  void Shutdown() { _shuttingDown = true; }

  void Cleanup()
  {
    // 1. Unload the texture from GPU memory
    if (_texture.id != 0)
    {
      UnloadTexture(_texture);
    }

    // 2. Free the CPU pixel buffer
    if (_pixels != nullptr)
    {
      free(_pixels);
      _pixels = nullptr;
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

  void UpdateCurrentState(float dt) { _states[_currentState]->Update(dt); }

  void RenderCurrentState()
  {
    const double renderTime = GetTime() * 1000;
    _states[_currentState]->Render();

    const double textureUploadTime = GetTime() * 1000;
    if (_texture.id == 0)
    {
      Image image = {.data = _pixels,
                     .width = WIDTH_VOXELS * VOXEL_SIZE,
                     .height = HEIGHT_VOXELS * VOXEL_SIZE,
                     .mipmaps = 1,
                     .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
      _texture = LoadTextureFromImage(image);
    }
    else
    {
      UpdateTexture(_texture, _pixels);
    }

    DrawTexture(_texture, 0, 0, GameEngine::Colors::WHITE);

    _frameCount++;
  }

  void SetState(std::string route)
  {
    _states[_currentState]->onExit();
    _currentState = route;
    _states[_currentState]->OnEnter();
  }
} // namespace GameEngine