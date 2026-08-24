#pragma once

#include "support_a_dessin.h"
#include "contenu.h"
#include <raylib.h>
class RaylibRender final : public SupportADessin {
public:
    RaylibRender();
    ~RaylibRender() override;

    bool should_close() const;
    void begin_frame();
    void end_frame();

    void dessine(Contenu const& a_dessiner) override;
private:
    Camera3D camera;

    // Ces variables sont utilisées pour les états des événements que l'on va implémenter.
    bool deplacement = false;
    bool pointeur = false;
};
