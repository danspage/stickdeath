#pragma once

#include <string>

namespace GameUtil
{
    inline bool begins_with(std::string const &value, std::string const &beginning)
    {
        if (beginning.size() > value.size())
            return false;
        return std::equal(beginning.begin(), beginning.end(), value.begin());
    }

    inline bool ends_with(std::string const &value, std::string const &ending)
    {
        if (ending.size() > value.size())
            return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
}