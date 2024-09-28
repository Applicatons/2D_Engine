#pragma once
#include <pch.h>

namespace utility{
    inline std::unordered_map<int, int> random_cache {};

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

    inline int get_random(int seed, int max){
        if (utility::random_cache.find(seed) != utility::random_cache.end())
            return utility::random_cache[seed];
        
        srand(seed);
        int pick = rand() % max;
        srand(time(NULL));

        utility::random_cache.emplace(seed, pick);
        return pick;
    }

    inline int get_random(int max){
        return rand() % max;
    }
    
    inline float clamp(float val, float max, float min){
        if (val > max)
            return max;
        if (val < min)
            return min;

        return val;
    }
}

namespace COLOR{
    inline color4 WHITE = color4(255, 255, 255);
    inline color4 BLACK = color4(0, 0, 0);
}

#define FLAG(x) (1 << (x))

namespace Objects{
    enum textures_index : int32_t {
        PLAYER_BACK,
        PLAYER_FRONT,
        PLAYER_RIGHT,
        PLAYER_LEFT,
        PLAYER_LEFT_BOB,
        PLAYER_BACK_BOB,
        PLAYER_FRONT_BOB,
        PLAYER_RIGHT_BOB,
        PLAYER_BACK_R1,
        PLAYER_BACK_R2,
        PLAYER_FRONT_R1,
        PLAYER_FRONT_R2,
        PLAYER_RIGHT_R1,
        PLAYER_LEFT_R1,
        GROUND_1,
        ROCK_LRG,
        ROCK_MID,
        ROCK_SM,
        STICK_MID,
        STICK_LOG,
        STICK_SM
    };

    enum object_actions : int32_t {
        PLAYER_IDLE_BACK = FLAG(3) | FLAG(0),
        PLAYER_IDLE_FRONT = FLAG(2) | FLAG(0),
        PLAYER_IDLE_RIGHT = FLAG(4) | FLAG(0),
        PLAYER_IDLE_LEFT = FLAG(5) | FLAG(0),
        PLAYER_BACK_RUN = FLAG(3) | FLAG(1),
        PLAYER_FRONT_RUN = FLAG(2) | FLAG(1),
        PLAYER_RIGHT_RUN = FLAG(4) | FLAG(1),
        PLAYER_LEFT_RUN = FLAG(5) | FLAG(1),
    };

    enum object_state : int32_t {
        STANDING = FLAG(0),
        MOVING = FLAG(1),
    };
    
    enum object_direction : int32_t {
        FRONT = FLAG(2),
        BACK = FLAG(3),
        RIGHT = FLAG(4),
        LEFT = FLAG(5),
    };


    inline std::unordered_map<int, std::vector<int>> ANIMATIONS { {PLAYER_IDLE_BACK,  {PLAYER_BACK,  PLAYER_BACK_BOB }},   
                                                                  {PLAYER_IDLE_FRONT, {PLAYER_FRONT, PLAYER_FRONT_BOB}},   
                                                                  {PLAYER_IDLE_RIGHT, {PLAYER_RIGHT, PLAYER_RIGHT_BOB}},
                                                                  {PLAYER_IDLE_LEFT, {PLAYER_LEFT,  PLAYER_LEFT_BOB }},
                                                                  {PLAYER_BACK_RUN,  {PLAYER_BACK_R1,  PLAYER_BACK_R2 }},
                                                                  {PLAYER_FRONT_RUN, {PLAYER_FRONT_R1, PLAYER_FRONT_R2 }},
                                                                  {PLAYER_RIGHT_RUN, {PLAYER_RIGHT, PLAYER_RIGHT_R1 }},
                                                                  {PLAYER_LEFT_RUN,  {PLAYER_LEFT, PLAYER_LEFT_R1 }} }; 
}

