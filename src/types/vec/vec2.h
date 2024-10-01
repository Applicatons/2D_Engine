#pragma once

#include <cmath>

class vec2 {
public:
    float x, y;

    vec2() : x(0), y(0) { }
    vec2(float x, float y) : x(x), y(y) { }

    bool is_valid(){
        return !(this->x == 0 && this->y == 0);
    }

    vec2 operator+(const vec2 &r) const {
        return vec2(this->x + r.x, this->y + r.y);
    }

    vec2 operator-(const vec2 &r) const {
        return vec2(this->x - r.x, this->y - r.y);
    }

    vec2 operator-() const {
        return vec2(-this->x, -this->y);
    }

    vec2 operator/(const vec2 &r) const {
        return vec2(this->x / r.x, this->y / r.y);
    }

    vec2 operator*(const vec2 &r) const {
        return vec2(this->x * r.x, this->y * r.y);
    }

    vec2 operator*(const float &r) const {
        return vec2(this->x * r, this->y * r);
    }

    float dot(const vec2 &r) const {
        return this->x * r.x + this->y * r.y;
    }

    float length() const {
        return std::sqrt(this->x * this->x + this->y * this->y);
    }

    float distance(const vec2 &r) const {
        float dx = this->x - r.x;
        float dy = this->y - r.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    vec2 normalize() const {
        float len = length();
        if (len > 0) {
            return vec2(this->x / len, this->y / len);
        }
        return *this;
    }

    void rotate(float angle) {
        float rad = angle * (M_PI / 180.0f); // Convert degrees to radians
        float cos_theta = std::cos(rad);
        float sin_theta = std::sin(rad);

        this->x = x * cos_theta - y * sin_theta;
        this->y = x * sin_theta + y * cos_theta;
    }

    std::string to_string(){
        const int SIZE = 10;
        char bufferx[SIZE];
        char buffery[SIZE];
        std::snprintf(bufferx, SIZE, "%.1f", this->x);
        std::snprintf(buffery, SIZE, "%.1f", this->y);

        return "(" + std::string(bufferx) + ", " + std::string(buffery) + ")";
    }
};