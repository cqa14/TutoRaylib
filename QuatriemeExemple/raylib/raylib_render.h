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

    // Ces variables sont utilisées pour les états des événements que l'on va implémenter.
    bool deplacement = false;
    bool pointeur = false;

    std::vector<Contenu> liste_contenus = {
        Contenu(),
        Contenu({-1,1,1}, VERT),
        Contenu({-1,0,1}, ROUGE),
    };
};
