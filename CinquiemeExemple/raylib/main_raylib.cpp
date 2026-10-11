#include "raylib_render.h"
#include "contenu.h"

int main()
{
    RaylibRender ecran;
    Contenu c;

    while (ecran.actif()) {
        /*
         * On récupère le temps écoulé depuis la dernière frame
         * et on l'utilise pour faire évoluer le contenu.
         */
        c.evolue(ecran.temps());
        c.dessine_sur(ecran);
    }
}
