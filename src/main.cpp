#include <pch.h>
#include "engine/engine.h"

int main( int argc, char* args[] )
{
    engine* pEngine = new engine(rect(100, 100, 1280, 720));
    if (int init = pEngine->init())
        return init;

    player main_player = player();
    if (!pEngine->create_object("Mainplayer", &main_player))
        printf("Mainplayer Creation Failed\n");

    pEngine->generate_world(main_player.bounds);
    pEngine->get_pCamera()->bounds += {-150, -150};

    while (pEngine->isRunning) {
        pEngine->mesure_ticks();
        pEngine->events();

        pEngine->pDrawing->set_draw_color(0, 100, 100, 100);
        pEngine->pDrawing->render_clear();
        pEngine->pDrawing->set_draw_color(COLOR::BLACK);

        if (pEngine->should_tick){
            pEngine->keycall();
        }

        pEngine->camera_render();
        pEngine->get_pCamera()->bounds.set_pos(pEngine->get_pCamera()->bounds.lerp(main_player.bounds + vec2(-130, -60), 0.1f));

        pEngine->pDrawing->render_fostring(vec2(1, 3), std::string("TPS: ") + std::to_string(pEngine->tps + 1), COLOR::WHITE);
        pEngine->pDrawing->render_preset();
    }
    
    pEngine->quit();
    pEngine->pDrawing->implode();
    pEngine->get_pGameworld()->implode();

    return EXIT_SUCCESS;
}
