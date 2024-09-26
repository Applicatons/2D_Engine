#pragma once
#include <pch.h>

class gameworld {
public:
    gameworld(SDL_Renderer* pRenderer){
        std::string path = "../textures";
        for (const auto & entry : std::filesystem::directory_iterator(path)){
            std::string file = utility::split(entry.path(), '/').back();
            std::string ext = utility::split(file, '.').back();
            
            if (ext != "png")
                continue;
            
            SDL_Texture* texture_tile = IMG_LoadTexture(pRenderer, entry.path().c_str());
            for (int y = 0; y < 16; y++)
                for (int x = 0; x < 16; x++)
                    this->textures.emplace((y * 16) + x, this->crop_texture(pRenderer, rect((x * 32), (y * 32), 32.f, 32.f), texture_tile));
        }
    }

    object_texture* get_texture(int idx)
    {
        return this->textures[idx];
    }

    void implode(){
        for (auto& pair : this->textures){
            pair.second->implode();
            delete pair.second;
        }
    }

    std::unordered_map<std::string, gameobject*> objects {};
    std::unordered_map<int, object_texture*> textures {};

private:

    object_texture* crop_texture( SDL_Renderer* pRenderer, rect area, SDL_Texture* source)
    {
        SDL_Texture* result = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, area.w, area.h);          
        SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);

        SDL_Rect rect = {(int)area.x, (int)area.y, (int)area.w, (int)area.h};
        
        SDL_SetRenderTarget(pRenderer, result);
        SDL_RenderCopy(pRenderer, source, &rect, NULL);
        SDL_SetRenderTarget(pRenderer, NULL);  

        object_texture* texture = new object_texture();
        area.apply_scale(1.2f);
        texture->tRect = area;
        texture->setup(result);
        
        return texture;
    }
};