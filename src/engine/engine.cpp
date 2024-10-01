#include "engine.h"

bool engine::quit(){
    TTF_Quit();

    SDL_DestroyRenderer(this->pRenderer);
    SDL_DestroyWindow(this->pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}

bool engine::init(){
    srand (time(NULL));

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
    
    object->tag = tag;
    
    this->pGameworld->objects.emplace(tag, object);
    this->regester_keycall(object);

    object->on_start(this->pGameworld->textures);
    return this->pGameworld->objects[tag];
}

void engine::generate_world(vec2 starting_pos){
    this->pGameworld->generate_world(starting_pos);
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
            case SDL_MOUSEWHEEL:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYUP:
            case SDL_KEYDOWN:
                this->key_queue.push(std::pair(event.type, event.key));
            default:
                break;
        }
    }
}

void engine::camera_render(){
    this->pCamera->render(this->should_tick, this->pGameworld);
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

void engine::regester_keycall(gameobject* object){
    
    if (this->key_callback.find(object->tag) != this->key_callback.end()){
        this->key_callback[object->tag] = object;
        return;
    }
    
    this->key_callback.emplace(object->tag, object);
    printf("%s Key Callback Registerd\n", object->tag.c_str());
}

void engine::keycall(){
    while (!this->key_queue.empty()) {
        for (auto& key_pair : this->key_callback)
            key_pair.second->key_input(this->key_queue.front().first, this->key_queue.front().second);
        
        this->key_queue.pop();
    }
}