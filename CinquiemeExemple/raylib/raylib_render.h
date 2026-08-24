#pragma once

#include "support_a_dessin.h"
#include "contenu.h"
#include <raylib.h>

class RaylibRender final : public SupportADessin {
public:
    RaylibRender();
    ~RaylibRender() override;

    bool should_close() const;
    [[nodiscard]] double frame_time() const;
    void begin_frame();
    void end_frame();

    void dessine(Contenu const& a_dessiner) override;
private:
    Camera3D camera;
};
