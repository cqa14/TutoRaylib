#pragma once

#include "support_a_dessin.h"
#include "contenu.h"
#include <raylib.h>

class RaylibRender final : public SupportADessin {
public:
    RaylibRender();
    ~RaylibRender() override;

    void dessine(Contenu const& a_dessiner) override;

    bool actif();  // l'écran est-il toujours actif ?

    double temps() const; // temps écoulé depuis la dernière frame

private:
    Camera3D camera;

    void begin_frame();
    void end_frame();
};
