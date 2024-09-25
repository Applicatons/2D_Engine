#include <pch.h>
#include "engine/engine.h"

int main( int argc, char* args[] )
{
    engine* pEngine = new engine(rect(100, 100, 1280, 720));
    if (int init = pEngine->init())
        return init;

    square da_square = square();
    if (!pEngine->create_object("da_square", &da_square))
        printf("Square Creation Failed\n");

    while (pEngine->isRunning) {
        pEngine->events();

        pEngine->pDrawing->set_draw_color(0, 100, 100, 100);
        pEngine->pDrawing->render_clear();
        pEngine->pDrawing->set_draw_color(COLOR::BLACK);

        pEngine->camera_render();

        pEngine->pDrawing->render_preset();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    pEngine->quit();
    pEngine->pDrawing->implode();
    return EXIT_SUCCESS;
}
