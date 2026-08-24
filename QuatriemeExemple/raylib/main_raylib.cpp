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

    while (not ecran.should_close()) {
        ecran.begin_frame();
        for (auto const& contenu : liste_contenus) {
            contenu.dessine_sur(ecran);
        }
        ecran.end_frame();
    }
}