#pragma once
#include <pch.h>

class bound : public rect {
public:
    float scale = 10.f;

    bound() : rect() {}
    bound(float x, float y, float w, float h) : rect(x, y, w, h) {}

    void set_pos(vec2 pos){
        this->x = pos.x;
        this->y = pos.y;
    }

    std::vector<vec2> VERTEX {};
    std::vector<std::pair<int, int>> EDGES {};
};