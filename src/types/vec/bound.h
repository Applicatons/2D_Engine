#pragma once
#include <pch.h>

class bound : public rect {
public:
    float scale = 10.f;

    bound() : rect() {}
    bound(float x, float y, float w, float h) : rect(x, y, w, h) {}

    std::vector<vec2> VERTEX {};
    std::vector<std::pair<int, int>> EDGES {};
};