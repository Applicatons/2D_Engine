#pragma once
#include <pch.h>

class camera : public gameobject {
public:
    camera(rect* pWinSize, drawing* pDrawing) : pWinSize(pWinSize), pDrawing(pDrawing) {}
    
    vec2 w2s(vec2 world_pos, float scale = 1.0f);
    void render(bool is_tick, std::unordered_map<std::string, gameobject*> &objs, std::unordered_map<int, object_texture*> &textures);
    void force_update(std::unordered_map<std::string, gameobject*> &objs, std::unordered_map<int, object_texture*> &textures);
private:
    float fov = 90.f;
    rect* pWinSize;
    drawing* pDrawing;
};