#pragma once
#include <pch.h>

class player : public gameobject{
public:
    player(){
        this->bounds.VERTEX =
            { 
                vec2(-1, -1), // bottom left
                vec2(-1, 1), // top left
                vec2(1, 1), // top right
                vec2(1, -1), // bottom right
            };

        this->bounds.EDGES =
            { 
                {0, 1}, 
                {1, 2}, 
                {2, 3}, 
                {3, 0}
            };
    }

    bound get_collider(){
        return bound(); // todo
    }
};