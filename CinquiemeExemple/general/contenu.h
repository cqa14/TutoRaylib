#pragma once

#include "dessinable.h"
#include "support_a_dessin.h"

/*
 * On lui ajoute un angle pour pouvoir le faire pivoter
 */

class Contenu final : public Dessinable {
public:
    ~Contenu() override = default;
    Contenu(Contenu const &) = default;
    Contenu &operator=(Contenu const &) = default;
    Contenu(Contenu &&) = default;
    Contenu &operator=(Contenu &&) = default;
    Contenu() = default;

    void dessine_sur(SupportADessin &support) override { support.dessine(*this); }

    // On ajoute un getter pour pouvoir utiliser l'angle
    [[nodiscard]] double get_angle() const { return angle; }

    // Et une méthode pour faire le faire évoluer
    void evolue(const double dt) {
        angle += 10*dt;
    }
private:
    double angle = 0;
};
