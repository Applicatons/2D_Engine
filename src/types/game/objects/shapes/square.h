#pragma once
#include <pch.h>

class square : public gameobject{
public:
    square(){
        this->Bounds.VERTEX =
            { 
                vec2(-1, -1), // bottom left
                vec2(-1, 1), // top left
                vec2(1, 1), // top right
                vec2(1, -1), // bottom right
            };

        this->Bounds.EDGES =
            { 
                {0, 1}, 
                {1, 2}, 
                {2, 3}, 
                {3, 0}
            };
    }
};