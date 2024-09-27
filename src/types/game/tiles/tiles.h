#pragma once
#include <pch.h>

// big tile
class tile {
public:
    tile(vec2 position, std::unordered_map<int, object_texture*> &textures) 
    {
        size_data.set_pos(position);
        for (int i = 0; i < SIZE * SIZE; i++)
            sub_tiles[i] = this->generate_tile(i, textures);
    }

    itile* generate_tile(int index, std::unordered_map<int, object_texture*> &textures){
        itile* tile = new itile(this, index, textures);
        return tile;
    }

    int get_width(){
        return this->size_data.w;
    }

    int get_height(){
        return this->size_data.h;
    }

    vec2 get_pos(){
        return {this->size_data.x, this->size_data.y};
    }

    std::vector<itile*> get_tiles (){
        return this->sub_tiles;
    }
    
    void implode(){
        for (auto& tile : this->sub_tiles)
        {
            tile->implode();
            delete tile;
        }
    }

    static const int SIZE = 4;
private:
    std::vector<itile*> sub_tiles = std::vector<itile*>(SIZE * SIZE); 
    bound size_data {0, 0, SIZE * itile::SIZE, SIZE * itile::SIZE};
};