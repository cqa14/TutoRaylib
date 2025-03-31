#include <iostream>
#include "raylib_render.h"
#include "contenu.h"
using namespace std;

int main()
{
    /* Nous voulons un support à dessin :                          *
     * ici un TextViewer qui écrit sur cout                        */
    RaylibRender ecran;

    // Nous voulons un contenu à dessiner
    Contenu c;

    // Nous dessinons notre contenu  sur notre support à dessin précédent
    c.dessine_sur(ecran);

    return 0;
}