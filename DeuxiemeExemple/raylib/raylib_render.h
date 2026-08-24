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

    bool should_close() const;
    void begin_frame();
    void end_frame();

    void dessine(Contenu const& a_dessiner) override;
private:
    /*
     * Afin de faire un dessin 3D, il faut une caméra.
     */
    Camera3D camera;

};
