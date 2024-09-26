#include <pch.h>

class gameobject{
public:
    gameobject() {}

    virtual void update(std::unordered_map<int, object_texture*> &textures){
        animation* running_anim = &idle_anim;

        if (object_state & Objects::MOVING)
            running_anim = &move_anim;

        if (running_anim->cat >= running_anim->rtps){
            running_anim->cat = 1;
            running_anim->run(texture, object_state, textures);

            return;
        }

        running_anim->cat++;
    }

    virtual void force_update(std::unordered_map<int, object_texture*> &textures){
        animation* running_anim = &idle_anim;

        if (object_state & Objects::MOVING)
            running_anim = &move_anim;

        running_anim->run(this->texture, this->object_state, textures);
    }

    virtual bound get_collider(){
        return this->bounds;
    }

    virtual object_texture* get_renderable(){
        return &this->texture;
    }

    void implode(){
        this->texture.implode();
        delete this;
    }

    animation idle_anim;
    animation move_anim;

    int object_state = Objects::MOVING | Objects::LEFT;

    object_texture texture;
    bound bounds;
};