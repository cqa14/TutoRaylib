#include "raylib_render.h"
#include "contenu.h"

int main()
{
    RaylibRender ecran;
    Contenu c;

    while (ecran.actif()) {
        c.dessine_sur(ecran);
    }
}