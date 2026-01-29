#pragma once

#include "support_a_dessin.h"
#include "contenu.h"
#include <raylib.h>

class RaylibRender final : public SupportADessin {
public:
    /*
     * On va utiliser les constructeurs et destructeurs afin de ne pas oublier
     * l'initialisation et la fermeture de la fenêtre.
     */
    RaylibRender();
    ~RaylibRender() override;

    void run();

    void dessine(Contenu const& a_dessiner) override;
private:
    /*
     * Afin de faire un dessin 3D, il faut une caméra.
     */
    Camera3D camera = { 0 };

    /*
     * On enregistrera dans cette architecture le contenu à dessiner
     * immédiatement dans la classe de rendu.
     * D'un point de vue concret, on préfèrera en général
     * utiliser des pointeurs vers les objets dessinables afin d'éviter
     * de faire des copies de gros objets.
     */
    Contenu c;
};
