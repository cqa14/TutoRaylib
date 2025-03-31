#pragma once

#include "support_a_dessin.h"

class RaylibRender : public SupportADessin {
public:
    RaylibRender();

    virtual ~RaylibRender() = default;

    virtual void dessine(Contenu const& a_dessiner) override;
};
