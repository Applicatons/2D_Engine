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

    bool is_inside( vec2 position )
    {
        if ( this->x > position.x || this->y > position.y ) return false;
		if ( this->x + this->w < position.x || this->y + this->h < position.y ) return false;
		return true;
    }
};