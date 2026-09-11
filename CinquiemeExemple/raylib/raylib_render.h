#pragma once

#include "support_a_dessin.h"
#include "contenu.h"
#include <raylib.h>

class RaylibRender final : public SupportADessin {
public:
    RaylibRender(Contenu& a_dessiner);
    ~RaylibRender() override;

    void dessine(Contenu const& a_dessiner) override;
private:
    Camera3D camera;
};
