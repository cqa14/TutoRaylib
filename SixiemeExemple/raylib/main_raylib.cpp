#include "raylib_render.h"
#include "contenu.h"


int main()
{
    RaylibRender ecran;
    Contenu c;

    while (not ecran.should_close()) {
        ecran.begin_frame();
        c.dessine_sur(ecran);
        ecran.end_frame();
    }
}