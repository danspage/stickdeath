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

            std::cout << "Loading default values for block: " << blockName << std::endl;

            _defaultBlockProperties[blockName] = {};

            for (auto &[propKey, propValue] : blockContent.items())
            {
                std::string valueAsString = propValue.is_string()
                                                ? propValue.get<std::string>()
                                                : propValue.dump();
                _defaultBlockProperties[blockName][propKey] = valueAsString;
            }
        }
    }
}