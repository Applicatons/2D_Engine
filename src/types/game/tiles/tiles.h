#pragma once
#include <pch.h>

// big tile
class tile {
public:
    tile(vec2 position) 
    {
        size_data.set_pos(position);
        for (int i = 0; i < 9; i++)
            sub_tiles[i] = this->generate_tile(i);
    }

    itile* generate_tile(int index){
        itile* tile = new itile(this, index);
        return tile;
    }

private:
    itile* sub_tiles[9]; 
    //{1, 2, 3}  {0, 1, 2}
    //{4, 5, 6}  {3, 4, 5}
    //{7, 8, 9}  {6, 7, 8}
    bound size_data {0, 0, 3, 3};
};