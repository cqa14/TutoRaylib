#include "raylib_render.h"

int main()
{
    /*
     * Le dessin étant fait dans la méthode run de la classe RaylibRender,
     * il suffit d'instancier un objet de cette classe puis d'appeler cette
     * méthode pour lancer la boucle de dessin.
     */
    RaylibRender ecran;
    ecran.run();
}