#pragma once
#include <pch.h>

class object_texture{
public:
    object_texture() { }

    object_texture* setup(SDL_Texture* texture) 
    {
        this->tData = texture;
        return this;
    }

    rect* set_pos(vec2 pos){
        this->tRect.x = pos.x;
        this->tRect.y = pos.y;
        return &tRect;
    }

    rect* set_area(vec2 pos){
        this->tRect.w = pos.x;
        this->tRect.h = pos.y;
        return &tRect;
    }

    void implode(){
        SDL_DestroyTexture(this->tData);
        delete this;
    }

    SDL_Texture* tData;
    rect tRect;
private:
};