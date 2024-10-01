#pragma once
#include <pch.h>

class engine
{
public:
    bool isRunning = true;
    
    engine(rect win_size) : win_size(win_size) {};

    bool quit();
    bool init();
    
    camera* create_camera();
    camera* get_pCamera();

    gameworld* create_gameworld();
    gameworld* get_pGameworld();

    gameobject* create_object(std::string tag, gameobject* object);

    void generate_world(vec2 starting_pos);
    void set_title(std::string title);
    void events();
    void camera_render();
    void mesure_ticks();
    void regester_keycall(gameobject* object);
    void keycall();

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
    drawing* pDrawing;

    int tps;
    bool should_tick = true;
private:

    //const float FPS_LIMIT = 144.f;
    Uint64 start_tick, real_mesuring_tick;
    int current_tps;

    rect win_size;

    camera* pCamera;
    gameworld* pGameworld;

    std::unordered_map<std::string, gameobject*> key_callback {};
    std::queue<std::pair<int, SDL_KeyboardEvent>> key_queue {};
};