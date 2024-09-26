#include <pch.h>

class gameobject{
public:
    gameobject() {}

    void implode(){
        this->texture.implode();
        delete this;
    }

    object_texture texture;
    bound bounds;
};