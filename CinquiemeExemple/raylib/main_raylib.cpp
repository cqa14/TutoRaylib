#include "raylib_render.h"
#include "contenu.h"

int main()
{
    RaylibRender ecran;
    Contenu c;

    while (not ecran.should_close()) {
        /*
         * On récupère le temps écoulé depuis la dernière frame
         * et on l'utilise pour faire évoluer le contenu.
         */
        const auto dt = ecran.frame_time();
        c.evolue(dt);

        ecran.begin_frame();
        c.dessine_sur(ecran);
        ecran.end_frame();
    }
}