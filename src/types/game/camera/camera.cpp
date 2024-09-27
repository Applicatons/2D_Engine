#include "camera.h"


vec2 camera::w2s(vec2 world_pos) {
    // Translate world position to camera space
    float screen_x = (world_pos.x - this->bounds.x) * this->scale;
    float screen_y = (world_pos.y - this->bounds.y) * this->scale;

    return vec2(screen_x, screen_y);
}

bool camera::is_within_view(vec2 world_pos) {
    // Define the camera's visible bounds in world space
    float left_bound = this->bounds.x;
    float right_bound = this->bounds.x + 260;
    float top_bound = this->bounds.y;
    float bottom_bound = this->bounds.y + 260;

    // Check if the world position is within these bounds
    return (world_pos.x >= left_bound && world_pos.x <= right_bound &&
            world_pos.y >= top_bound && world_pos.y <= bottom_bound);
}

void camera::render(bool is_tick, gameworld* pGameworld) {
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
            int pick = it->tile_has_object(pGameworld->get_seed()) + 1;
            if (pick){
                this->pDrawing->render_texture(this->w2s(ipos + vec2(5, 2)), pGameworld->get_texture(15 + pick), vec2(itile::SIZE, itile::SIZE) * this->scale);
            }
            
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