#include "engine.h"

bool engine::quit(){
    TTF_Quit();

    SDL_DestroyRenderer(this->pRenderer);
    SDL_DestroyWindow(this->pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}

bool engine::init(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    this->pWindow = SDL_CreateWindow("SLD test", this->win_size.x, this->win_size.y, this->win_size.w, this->win_size.h, 0);
    if (!this->pWindow) {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    this->pRenderer = SDL_CreateRenderer(this->pWindow, -1, SDL_RENDERER_SOFTWARE);
    if (!this->pRenderer) {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    this->pDrawing = new drawing(this->pRenderer, this->pWindow);
    this->create_camera();
    this->create_gameworld();

    return EXIT_SUCCESS;
}

camera* engine::create_camera(){
    return this->pCamera = new camera(&this->win_size, this->pDrawing);
}

camera* engine::get_pCamera(){
   return this->pCamera;
}

gameworld* engine::create_gameworld(){
    return this->pGameworld = new gameworld(this->pRenderer);
}

gameworld* engine::get_pGameworld(){
   return this->pGameworld;
}

gameobject* engine::create_object(std::string tag, gameobject* object){
    if (this->pGameworld->objects.find(tag) != this->pGameworld->objects.end())
        return nullptr;
    this->pGameworld->objects.emplace(tag, object);
    return this->pGameworld->objects[tag];
}

void engine::set_title(std::string title){
    SDL_SetWindowTitle(this->pWindow, title.c_str());
}

void engine::events(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) {
            case SDL_QUIT:
                this->isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == 79) // r
                    this->pGameworld->objects.begin()->second->object_state = Objects::RIGHT | Objects::MOVING;
                else if (event.key.keysym.scancode == 80) // l
                    this->pGameworld->objects.begin()->second->object_state = Objects::LEFT | Objects::MOVING;
                else if (event.key.keysym.scancode == 81) // d
                    this->pGameworld->objects.begin()->second->object_state = Objects::FRONT | Objects::MOVING;
                else if (event.key.keysym.scancode == 82) // u
                    this->pGameworld->objects.begin()->second->object_state = Objects::BACK | Objects::MOVING;
                break;
            case SDL_KEYUP:
                if (this->pGameworld->objects.begin()->second->object_state & Objects::BACK)
                    this->pGameworld->objects.begin()->second->object_state = Objects::BACK | Objects::STANDING;
                else if (this->pGameworld->objects.begin()->second->object_state & Objects::FRONT)
                    this->pGameworld->objects.begin()->second->object_state = Objects::FRONT | Objects::STANDING;
                else if (this->pGameworld->objects.begin()->second->object_state & Objects::RIGHT)
                    this->pGameworld->objects.begin()->second->object_state = Objects::RIGHT | Objects::STANDING;
                else if (this->pGameworld->objects.begin()->second->object_state & Objects::LEFT)
                    this->pGameworld->objects.begin()->second->object_state = Objects::LEFT | Objects::STANDING;
                break;
            default:
                break;
        }
    }
}

void engine::camera_render(bool force){
    if (force)
        this->pCamera->force_update(this->pGameworld->objects, this->pGameworld->textures);
    else
        this->pCamera->render(this->should_tick, this->pGameworld->objects, this->pGameworld->textures);
}

void engine::mesure_ticks(){
    Uint64 current_tick = SDL_GetTicks64();

    if (should_tick) {
        start_tick = current_tick;
        should_tick = false;
        return;
    }

    if ((1000 / 20) < (current_tick - start_tick)) {
        should_tick = true;
        this->current_tps++;
        start_tick = current_tick;
    }       

    if (current_tick - this->real_mesuring_tick >= 1000) {
        this->tps = this->current_tps;
        this->current_tps = 0;
        this->real_mesuring_tick = current_tick;
    }
}