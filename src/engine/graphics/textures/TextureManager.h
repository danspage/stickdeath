#pragma once

#include <string>
#include <vector>

#include "../GameImage.h"
#include "AnimationPlayer.h"

namespace GameEngine::TextureManager
{
    /**
     * @brief Registers a static texture so that it can be used within the game.
     * @param path The filepath of the image, relative to `assets/images`.
     */
    void RegisterStaticTexture(const std::string &refPath, const std::string &imagePath);

    /**
     * @brief Registers an animated texture so that it can be used within the game.
     * @param reference The filepath of the animated texture's json properties, relative
     * to `assets/images`.
     */
    void RegisterAnimatedTexture(const std::string &refPath, const std::string &jsonPath);

    /**
     * @brief Returns a texture in the form of a GameImage. If the texture is animated,
     * and `global_loop` is set to true in the animation JSON, it will return the current
     * frame of the animation loop as synced up to the game's clock. If `global_loop` is
     * set to false, it will throw an exception since GetTextureAnimationFrames should be
     * used for manual animations along with an AnimationPlayer.
     *
     * @param texture The reference name of the texture.
     */
    const GameEngine::GameImage &GetTexture(const std::string &texture);

    // TODO: MUST THROW EXCEPTIONS FOR NON-EXISTENT TEXTURES AND TEXTURES THAT ARE STATIC
    // FUTURE WORK
    /// @brief Creates an animation player for the specified texture.
    const AnimationPlayer &CreateAnimationPlayer(const std::string &texture);

    /**
     * @brief Returns the TextureAsset object for the specified texture.
     *
     * @param texture The reference name of the texture.
     */
    const TextureAsset &GetTextureAsset(const std::string &texture);

    /**
     * @brief Updates the globally looping animations.
     * 
     * @param dt The amount of time passed since the previous update.
     */
    void UpdateGlobalAnimations(float dt);
}