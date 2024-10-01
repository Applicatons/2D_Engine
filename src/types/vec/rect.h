#pragma once
#include <pch.h>


class rect : public vec4 {
public:
    float w, h = 0;
    
    rect() : vec4() {}
    rect(float x, float y, float w, float h) : w(w), h(h), vec4(x, y, w, h) {}

    operator SDL_Rect () const {
        return {(int)x, (int)y, (int)w, (int)h};
    }

    void apply_scale(float scale){
        this->w *= scale;
        this->h *= scale;
    }

    void mirror(int axis){
        if (axis){
            this->w = -w;
        }else{
            this->h = -h;
        }
    }

    bool is_inside( vec2 position )
    {
        if ( this->x > position.x || this->y > position.y ) return false;
		if ( this->x + this->w < position.x || this->y + this->h < position.y ) return false;
		return true;
    }

    operator vec2 () const {
        return {this->x, this->y};
    }

    void operator-=(const vec2& r) {
        x -= r.x;
        y -= r.y;
    }

    void operator+=(const vec2& r) {
        x += r.x;
        y += r.y;
    }
};