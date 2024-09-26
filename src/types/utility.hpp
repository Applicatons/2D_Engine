#pragma once
#include <pch.h>

namespace utility{
    inline std::vector<std::string> split(const std::string& s, char seperator)
    {
        std::vector<std::string> output;
        std::string::size_type prev_pos = 0, pos = 0;

        while((pos = s.find(seperator, pos)) != std::string::npos)
        {
            std::string substring( s.substr(prev_pos, pos-prev_pos) );
            output.push_back(substring);
            prev_pos = ++pos;
        }

        output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word
        return output;
    }
}

namespace COLOR{
    inline color4 WHITE = color4(255, 255, 255);
    inline color4 BLACK = color4(0, 0, 0);
}

namespace tex{
    enum textures_index : int32_t {
        PLAYER_BACK = 0,
        PLAYER_FRONT,
        PLAYER_RIGHT,
        PLAYER_LEFT,
    };

    enum texture_animations : int32_t {
        PLAYER_IDLE = 0,
    };

    inline std::unordered_map<int, std::vector<int>> ANIMATIONS {};
}

