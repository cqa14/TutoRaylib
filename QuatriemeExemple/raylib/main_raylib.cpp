#include "raylib_render.h"
#include "contenu.h"
#include <vector>

int main()
{
    RaylibRender ecran;
    std::vector<Contenu> liste_contenus = {
        Contenu(),
        Contenu({-1,1,1}, VERT),
        Contenu({-1,0,1}, ROUGE),
    };

    while (ecran.actif()) {
        for (auto const& contenu : liste_contenus) {
            contenu.dessine_sur(ecran);
        }
    }
}