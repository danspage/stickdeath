#pragma once

#include <string>

namespace GameEngine::Util
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

    inline auto split(std::string_view str, std::string_view delim)
    {
        std::vector<std::string_view> tokens;
        size_t start = 0, end = 0;
        while ((end = str.find(delim, start)) != std::string_view::npos)
        {
            if (end != start)
                tokens.push_back(str.substr(start, end - start));
            start = end + delim.length();
        }
        if (start < str.length())
            tokens.push_back(str.substr(start));
        return tokens;
    }

    inline std::string trim(std::string_view str)
    {
        const std::string_view whitespace = " \t\r\n";
        const auto start = str.find_first_not_of(whitespace);
        if (start == std::string_view::npos)
            return {}; // Entirely whitespace
        const auto end = str.find_last_not_of(whitespace);
        return std::string(str.substr(start, end - start + 1));
    }
}