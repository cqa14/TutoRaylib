#pragma once

#include "dessinable.h"
#include "support_a_dessin.h"

class Contenu final : public Dessinable {
public:
    ~Contenu() override = default;
    Contenu(Contenu const &) = default;
    Contenu &operator=(Contenu const &) = default;
    Contenu(Contenu &&) = default;
    Contenu &operator=(Contenu &&) = default;
    Contenu() = default;

    void dessine_sur(SupportADessin &support) const override { support.dessine(*this); }
};
