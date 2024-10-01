#pragma once
#include <pch.h>

class camera : public gameobject {
public:
    camera(rect* pWinSize, drawing* pDrawing) : pWinSize(pWinSize), pDrawing(pDrawing) {}
    
    vec2 w2s(vec2 world_pos);
    bool is_within_view(vec2 world_pos);
    void render(bool is_tick, gameworld* pGameworld);
    void lerp_camera(vec2 position);
private:
    float scale = 5.f;
    float fov = 52.f;
    rect* pWinSize;
    drawing* pDrawing;
};