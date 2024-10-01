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

    void set_rel_pos(vec2 pos){
        this->x += pos.x;
        this->y += pos.y;
    }

    vec2 lerp(vec2 b, float t){
        float _t = utility::clamp(t, 1, -1);
        return vec2(this->x + _t * (b.x - this->x), this->y + _t * (b.y - this->y));
    }

    void rotate(float angle) {
        float rad = angle * (M_PI / 180.0f); // Convert degrees to radians
        float cos_theta = std::cos(rad);
        float sin_theta = std::sin(rad);

        this->x = x * cos_theta - y * sin_theta;
        this->x = x * sin_theta + y * cos_theta;
    }

    vec2 operator+(const vec2 &r) const {
        return vec2(this->x + r.x, this->y + r.y);
    }

    operator vec2(){
        return {this->x, this->y};
    }

    std::vector<vec2> VERTEX {};
    std::vector<std::pair<int, int>> EDGES {};
};