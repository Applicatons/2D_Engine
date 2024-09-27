#pragma once
#include <pch.h>

// oh yeah big brain time
class tile;

// user interactable tile
class itile {
public:
    itile() : parent(nullptr) {}
    itile(tile* parent, int index, std::unordered_map<int, object_texture*> &textures) : parent(parent), index(index) 
    {
        texture = *textures[Objects::GROUND_1];
    }

    int tile_has_object(int seed){
        auto pos = this->get_relative_pos();

        if(utility::get_random(seed + (int)(pos.x * pos.y) / 2, 2))
            return utility::get_random(seed + pos.x * pos.y, 6);
        
        return -1;
    }

    tile* get_parent() {
        return this->parent;
    }

    int get_index(){
        return this->index;
    }

    vec2 get_relative_pos(){
        return vec2((this->index % 4) * SIZE, (((int)(this->index / 4)) % 4) * SIZE);
    }

    object_texture* get_rendereable(){
        return &this->texture;
    }

    void implode(){
        this->texture.implode();
        delete this;
    }

    static const int SIZE = 20;
private:
    tile* parent;
    int index;
    object_texture texture;
    int seed;
};