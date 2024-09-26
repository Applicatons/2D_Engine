#pragma once
#include <pch.h>

class animation {
public:
    animation(int rtps = 8) : rtps(rtps) {}

    void run(object_texture &texture, int object_state, std::unordered_map<int, object_texture*> &textures){
        std::vector<int> animation = Objects::ANIMATIONS[object_state];

        if (animation.empty())
            return;

        if (textures.find(animation[itr]) == textures.end())
            return;

        texture = *textures[animation[itr]];
        itr++;


        if (animation.size()-1 < itr)
            itr = 0;
        
    }

    int itr = 0;
    int rtps;    // 1 iteration per ticks per second interval
    int cat = 1; // current animation tick
};