#include "Tiles.h"

namespace StickDeath
{
    void InitTileProperties()
    {
        std::ifstream propsFile("assets/data/tileproperties.json");
        if (!propsFile.is_open())
        {
            std::cerr << "Could not open assets/data/tileproperties.json" << std::endl;
            return;
        }

        json tilePropsData = json::parse(propsFile);

        for (auto &[tileName, tileContent] : tilePropsData.items())
        {
            // Skip parent models data, it does not represent actual tiles
            if (tileName == "parent_models")
                continue;

            std::cout << "Loading default values for tile: " << tileName << std::endl;

            TileProperties props;
            
            props.id = tileName;

            // If the tile has a parent, use the parent's model as the default bounds for this tile. This allows multiple tiles to share the same model without having to duplicate it in the JSON file.
            if (tileContent.contains("parent"))
            {
                const std::string parentName = tileContent.at("parent").get<std::string>();

                if (!tilePropsData.contains("parent_models") || !tilePropsData.at("parent_models").contains(parentName))
                {
                    throw std::runtime_error(std::format("Missing parent model '{}'", parentName));
                }

                const json &parentModel = tilePropsData.at("parent_models").at(parentName);

                for (const json &rect : parentModel)
                {
                    const float leftPx = rect.at(0).get<float>();
                    const float bottomPx = rect.at(1).get<float>();
                    const float rightPx = rect.at(2).get<float>();
                    const float topPx = rect.at(3).get<float>();

                    props.bounds.push_back({
                        .leftBound = leftPx / 16.0f,
                        .rightBound = rightPx / 16.0f,
                        .topBound = topPx / 16.0f,
                        .bottomBound = bottomPx / 16.0f,
                    });
                }
            }
            else if (tileContent.contains("model"))
            {
                // If the tile does not have a parent, it must define its own model, otherwise we don't know what bounds it has and can't do collision detection for it. We clear the default bounds just in case the tile inherits from a parent but also defines its own model, in which case we want to use the model defined in the tile itself and not the one from the parent.

                props.bounds.clear();

                const json &model = tileContent.at("model");
                for (const json &rect : model)
                {
                    const float leftPx = rect.at(0).get<float>();
                    const float bottomPx = rect.at(1).get<float>();
                    const float rightPx = rect.at(2).get<float>();
                    const float topPx = rect.at(3).get<float>();

                    props.bounds.push_back({
                        .leftBound = leftPx / 16.0f,
                        .rightBound = rightPx / 16.0f,
                        .topBound = topPx / 16.0f,
                        .bottomBound = bottomPx / 16.0f,
                    });
                }
            }
            else
            {
                throw std::runtime_error(std::format("No model or parent model defined '{}'", tileName));
            }

            for (auto &[propKey, propValue] : tileContent.items())
            {
                // Skip any model related properties, we have already processed them and they are not relevant for the tile definition itself
                if (propKey == "parent" || propKey == "model")
                    continue;

                if (propKey == "texture")
                {
                    std::ifstream animFile("assets/images/" + propValue.get<std::string>() + ".sdanim");
                    if (animFile.is_open())
                    {
                        json data = json::parse(animFile);

                        // Get the list of textures for this animation
                        const json &textures = data.at("textures");
                        for (const json &texture : textures)
                        {
                            props.texturePaths.push_back(texture.get<std::string>());
                        }

                        float intervalSecs = 0.1f; // Default to 0.1 seconds if not specified in the animation file

                        // If the animation has an interval defined, set up the animation data for this tile
                        if (data.contains("interval_seconds"))
                        {
                            intervalSecs = data.at("interval_seconds").get<float>();
                        }

                        props.animated = true;
                        _animationStates.insert_or_assign(tileName, TileAnimationState{GameEngine::Util::Timer(intervalSecs, true), 0});
                    }
                    else
                    {
                        // If the texture property is not an animation, just treat it as a single texture path
                        props.texturePaths.push_back(propValue.get<std::string>());
                    }
                }
                else if (propKey == "isSolid")
                {
                    props.isSolid = propValue.get<bool>();
                }
            }
            
            _defaultTileProperties[tileName] = props;
        }
    }

    void UpdateTileAnimations(float dt)
    {
        for (auto &[tileName, animState] : _animationStates)
        {
            int frameNum = animState.animTimer.UpdateAndGetTicks(dt);
            if (frameNum > 0)
            {
                animState.currentFrame = (animState.currentFrame + frameNum) % _defaultTileProperties[tileName].texturePaths.size();
            }
        }
    }
}