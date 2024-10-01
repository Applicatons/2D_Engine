#include "camera.h"


vec2 camera::w2s(vec2 world_pos) {
    // Translate world position to camera space
    float screen_x = (world_pos.x - this->bounds.x) * this->scale;
    float screen_y = (world_pos.y - this->bounds.y) * this->scale;

    return vec2(screen_x, screen_y);
}

bool camera::is_within_view(vec2 world_pos) {
    // Define the camera's visible bounds in world space
    float left_bound = this->bounds.x - (this->pWinSize->w / this->scale);
    float right_bound = this->bounds.x + (this->pWinSize->w / this->scale);
    float top_bound = this->bounds.y - (this->pWinSize->h / this->scale) / 2;
    float bottom_bound = this->bounds.y + (this->pWinSize->h / this->scale) * 2;

    // Check if the world position is within these bounds
    return (world_pos.x >= left_bound && world_pos.x <= right_bound &&
                world_pos.y >= top_bound && world_pos.y <= bottom_bound);
}

void camera::render(bool is_tick, gameworld* pGameworld) {
    static std::vector<std::pair<vec2, int>> picks {};
    picks.clear();
    for (tile* t : pGameworld->world_tiles){
        vec2 pos = t->get_pos();
        if (!this->is_within_view(pos))
            continue;
            
        vec2 ipos_rel = vec2(pos.x, pos.y  - t->get_height() + itile::SIZE);

        std::vector<itile*> itiles = t->get_tiles();
        this->pDrawing->set_draw_color(COLOR::BLACK);

        for (itile* it : itiles){
            vec2 ipos = ipos_rel + it->get_relative_pos();
            this->pDrawing->render_texture(this->w2s(ipos), it->get_rendereable(), vec2(itile::SIZE, itile::SIZE) * this->scale);
            
            
            /*this->pDrawing->render_line(this->w2s(vec2(ipos.x, ipos.y)), this->w2s(vec2(ipos.x + itile::SIZE, ipos.y)));
            this->pDrawing->render_line(this->w2s(vec2(ipos.x + itile::SIZE, ipos.y)), this->w2s(vec2(ipos.x + itile::SIZE, ipos.y - itile::SIZE)));
            this->pDrawing->render_line(this->w2s(vec2(ipos.x + itile::SIZE, ipos.y - itile::SIZE)), this->w2s(vec2(ipos.x, ipos.y - itile::SIZE)));
            this->pDrawing->render_line(this->w2s(vec2(ipos.x, ipos.y - itile::SIZE)), this->w2s(vec2(ipos.x, ipos.y)));*/
        }  

        //this->pDrawing->set_draw_color(COLOR::BLACK);
        //this->pDrawing->render_line(this->w2s(vec2(pos.x, pos.y)), this->w2s(vec2(pos.x + t->get_width(), pos.y)));
        //this->pDrawing->render_line(this->w2s(vec2(pos.x + t->get_width(), pos.y)), this->w2s(vec2(pos.x + t->get_width(), pos.y - t->get_height())));
        //this->pDrawing->render_line(this->w2s(vec2(pos.x + t->get_width(), pos.y - t->get_height())), this->w2s(vec2(pos.x, pos.y - t->get_height())));
        //this->pDrawing->render_line(this->w2s(vec2(pos.x, pos.y - t->get_height())), this->w2s(vec2(pos.x, pos.y)));
    }


    for (auto& game_pair : pGameworld->objects){
        std::string object_tag = game_pair.first;
        gameobject* object = game_pair.second;

        if (is_tick)
            object->update(pGameworld->textures);
        
        this->pDrawing->render_texture(this->w2s(object->bounds), object->get_renderable());
    }
}

void camera::lerp_camera(vec2 pos){
    this->bounds.set_pos(this->bounds.lerp(pos + vec2(-(this->pWinSize->w / this->scale) / 2, -(this->pWinSize->h / this->scale) / 2), 0.1f));
}