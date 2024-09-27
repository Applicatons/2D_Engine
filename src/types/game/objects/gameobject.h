#include <pch.h>

class gameobject{
public:
    gameobject() { }

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

    virtual void key_input(int key_type, SDL_KeyboardEvent key) { }

    virtual void on_start(std::unordered_map<int, object_texture*> &textures){
        idle_anim.run(this->texture, this->object_state, textures);
    }

    virtual bound get_collider(){
        return this->bounds;
    }

    virtual object_texture* get_renderable(){
        return &this->texture;
    }

    virtual void add_keymap(std::string name, std::vector<int> keys){
        if (this->keymap.find(name) != this->keymap.end()){
            this->keymap[name] = keys;
            return;
        }

        this->keymap.emplace(name, keys);
    }

    virtual bool assert_key(std::string name, int key) {
        if (this->keymap.find(name) == this->keymap.end())
            return false;
        
        std::vector<int> keys = this->keymap[name];

        for (auto& ckey : keys)
            if (ckey == key)
                return true;
                
        return false;
    }

    void implode(){
        this->texture.implode();
        delete this;
    }

    animation idle_anim;
    animation move_anim;

    int object_state = Objects::PLAYER_IDLE_FRONT;

    object_texture texture;
    bound bounds;

    std::string tag;

    std::unordered_map<std::string, std::vector<int>> keymap {};
};