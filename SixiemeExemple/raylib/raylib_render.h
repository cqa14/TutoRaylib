#pragma once

#include "support_a_dessin.h"
#include "contenu.h"
#include <raylib.h>

class RaylibRender final : public SupportADessin {
public:
    RaylibRender();
    ~RaylibRender() override;

    bool actif();

    void dessine(Contenu const& a_dessiner) override;
private:
    Camera3D camera;
    void begin_frame();
    void end_frame();

    // On stocke les modèles que l'on voudra dessiner
    Model myModel{};
};
