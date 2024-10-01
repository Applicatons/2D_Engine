#pragma once
#include <pch.h>

class player : public gameobject{
public:
    player(){
        this->bounds.VERTEX =
            { 
                vec2(-1, -1), // bottom left
                vec2(-1, 1), // top left
                vec2(1, 1), // top right
                vec2(1, -1), // bottom right
            };

        this->bounds.EDGES =
            { 
                {0, 1}, 
                {1, 2}, 
                {2, 3}, 
                {3, 0}
            };


        this->add_keymap("forward", {SDL_SCANCODE_UP, SDL_SCANCODE_W});
        this->add_keymap("back",    {SDL_SCANCODE_DOWN, SDL_SCANCODE_S});
        this->add_keymap("right",   {SDL_SCANCODE_RIGHT, SDL_SCANCODE_D});
        this->add_keymap("left",    {SDL_SCANCODE_LEFT, SDL_SCANCODE_A});
    }

    void key_input(int key_type, SDL_KeyboardEvent key) override {
        switch (key_type){
            case SDL_KEYDOWN:
                if (this->assert_key("right", key.keysym.scancode))
                    this->object_state = Objects::RIGHT | Objects::MOVING;
                else if (this->assert_key("left", key.keysym.scancode))
                    this->object_state = Objects::LEFT | Objects::MOVING;
                else if (this->assert_key("back", key.keysym.scancode))
                    this->object_state = Objects::FRONT | Objects::MOVING;
                else if (this->assert_key("forward", key.keysym.scancode))
                    this->object_state = Objects::BACK | Objects::MOVING;
                break;
            case SDL_KEYUP:
                this->object_state = (this->object_state & ~Objects::MOVING) | Objects::STANDING;
            default:
                break;    
        }
    }

    bound get_collider() override {
        return bound(); // todo
    }

    void update(std::unordered_map<int, object_texture*> &textures) override {
        gameobject::update(textures);
        if (this->move_anim.cat == 1)
            this->tick_movement();
    }

    void tick_movement() {
        if (!(this->object_state & Objects::MOVING))
            return;

        if (this->object_state & Objects::FRONT){
            this->bounds.set_rel_pos(vec2(0.f, this->speed));
        }else if (this->object_state & Objects::BACK){
            this->bounds.set_rel_pos(vec2(0.f, -this->speed));
        }else if (this->object_state & Objects::LEFT){
            this->bounds.set_rel_pos(vec2(-this->speed, 0.f));
        }else if (this->object_state & Objects::RIGHT){
            this->bounds.set_rel_pos(vec2(this->speed, 0.f));
        }
    }

private:
    float speed = 3.f;
};