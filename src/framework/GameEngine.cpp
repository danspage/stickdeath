#include "GameEngine.h"

#include "state/GameState.h"

#include <SDL2/SDL.h>

int _frameCount = 0;

namespace GameEngine
{
  SDL_Texture *_texture = nullptr;
  SDL_Renderer *_renderer = nullptr;
  int _fps = 0;
  Uint64 _lastFpsCounter = 0;

  void SetRenderer(SDL_Renderer *renderer)
  {
    _renderer = renderer;
    _lastFpsCounter = 0;
  }

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
    if (_texture != nullptr)
    {
      SDL_DestroyTexture(_texture);
    }

    if (_pixels != nullptr)
    {
      free(_pixels);
      _pixels = nullptr;
    }
  }

  int GetFPS()
  {
    return _fps;
  }

  void ProcessKeyEvents()
  {
    static bool prevDown[SDL_NUM_SCANCODES] = {};
    const Uint8 *keyboard = SDL_GetKeyboardState(nullptr);

    for (SDL_Scancode key : KEYS_USED)
    {
      bool down = keyboard[key] != 0;

      if (down && !prevDown[key])
        _states[_currentState]->OnKeyPressed(key);
      else if (!down && prevDown[key])
        _states[_currentState]->OnKeyReleased(key);
      
      if (down)
        _states[_currentState]->OnKeyHeld(key);

      prevDown[key] = down;
    }
  }

  void UpdateCurrentState(float dt) { _states[_currentState]->Update(dt); }

  void RenderCurrentState()
  {
    _states[_currentState]->Render();
    if (_renderer == nullptr)
      return;

    if (_texture == nullptr)
      _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, WIDTH_PIXELS, HEIGHT_PIXELS);

    SDL_SetTextureScaleMode(_texture, SDL_ScaleModeNearest);

    SDL_UpdateTexture(_texture, nullptr, _pixels, WIDTH_PIXELS * sizeof(uint32_t));

    SDL_RenderClear(_renderer);
    SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);

    _frameCount++;

    // Calculate FPS
    const Uint64 now = SDL_GetPerformanceCounter();
    if (_lastFpsCounter == 0)
    {
      _lastFpsCounter = now;
    }

    const double elapsedSeconds = static_cast<double>(now - _lastFpsCounter) /
                                  static_cast<double>(SDL_GetPerformanceFrequency());

    if (elapsedSeconds >= 1.0)
    {
      _fps = static_cast<int>(_frameCount / elapsedSeconds);
      _frameCount = 0;
      _lastFpsCounter = now;
    }
  }

  void SetState(std::string route)
  {
    _states[_currentState]->onExit();
    _currentState = route;
    _states[_currentState]->OnEnter();
  }
}