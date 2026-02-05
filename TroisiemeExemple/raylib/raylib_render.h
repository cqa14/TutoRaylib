#pragma once

#include "support_a_dessin.h"
#include "contenu.h"
#include <raylib.h>
#include <vector>

class RaylibRender final : public SupportADessin {
public:
    RaylibRender();
    ~RaylibRender() override;

    void run();

    void dessine(Contenu const& a_dessiner) override;
private:
    Camera3D camera;

    /*
     * Pour simplifier le code, on utilise une liste de Contenu.
     *
     * Note : pour un comportement polymorphique, il est tout à fait possible
     * d'adapter le code pour utiliser une liste de pointeurs sur Contenu.
     */
    std::vector<Contenu> liste_contenus = {
        Contenu(),
        Contenu({-1,1,1}, VERT),
        Contenu({-1,0,1}, ROUGE),
    };
};
