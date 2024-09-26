#include "camera.h"


vec2 camera::w2s(vec2 world_pos, float scale) {
}

void camera::render(bool is_tick, std::unordered_map<std::string, gameobject*> &objs, std::unordered_map<int, object_texture*> &textures) {
    for (auto& game_pair : objs){
        std::string object_tag = game_pair.first;
        gameobject* object = game_pair.second;

        if (is_tick)
            object->update(textures);
        
        this->pDrawing->render_texture(vec2(100, 100), object->get_renderable());
    }
}

void camera::force_update(std::unordered_map<std::string, gameobject*> &objs, std::unordered_map<int, object_texture*> &textures) {
    for (auto& game_pair : objs){
        gameobject* object = game_pair.second;
        object->force_update(textures);
    }
}