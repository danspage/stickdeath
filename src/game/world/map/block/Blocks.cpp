#include "Blocks.h"

namespace StickDeath
{
    void InitBlockProperties()
    {
        std::ifstream f("assets/data/blockproperties.json");
        if (!f.is_open())
        {
            std::cerr << "Could not open assets/data/blockproperties.json" << std::endl;
            return;
        }

        json data = json::parse(f);

        for (auto &[blockName, blockContent] : data.items())
        {
            if (blockName == "parent_models")
                continue;

            std::cout << "Loading default values for block: " << blockName << std::endl;

            BlockDefinition def;

            if (blockContent.contains("parent"))
            {
                const std::string parentName = blockContent.at("parent").get<std::string>();

                if (!data.contains("parent_models") || !data.at("parent_models").contains(parentName))
                {
                    throw std::runtime_error(std::format("Missing parent model '{}'", parentName));
                }

                const json &parentModel = data.at("parent_models").at(parentName);

                for (const json &rect : parentModel)
                {
                    const float leftPx = rect.at(0).get<float>();
                    const float bottomPx = rect.at(1).get<float>();
                    const float rightPx = rect.at(2).get<float>();
                    const float topPx = rect.at(3).get<float>();

                    def.properties.bounds.push_back({
                        .leftBound = leftPx / 16.0f,
                        .rightBound = rightPx / 16.0f,
                        .bottomBound = bottomPx / 16.0f,
                        .topBound = topPx / 16.0f,
                    });
                }
            }
            else if (blockContent.contains("model"))
            {
                def.properties.bounds.clear();

                const json &model = blockContent.at("model");
                for (const json &rect : model)
                {
                    const float leftPx = rect.at(0).get<float>();
                    const float bottomPx = rect.at(1).get<float>();
                    const float rightPx = rect.at(2).get<float>();
                    const float topPx = rect.at(3).get<float>();

                    def.properties.bounds.push_back({
                        .leftBound = leftPx / 16.0f,
                        .rightBound = rightPx / 16.0f,
                        .bottomBound = bottomPx / 16.0f,
                        .topBound = topPx / 16.0f,
                    });
                }
            }
            else
            {
                throw std::runtime_error(std::format("No model or parent model defined '{}'", blockName));
            }

            for (auto &[propKey, propValue] : blockContent.items())
            {
                if (propKey == "parent" || propKey == "model")
                    continue;

                if (propKey == "texture")
                {
                    def.texturePath = propValue.get<std::string>();
                }
                else if (propKey == "isSolid")
                {
                    def.properties.isSolid = propValue.get<bool>();
                }

                _defaultBlockProperties[blockName] = def;
            }
        }
    }
}