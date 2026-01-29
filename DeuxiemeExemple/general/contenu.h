#pragma once

#include "dessinable.h"
#include "support_a_dessin.h"

/*
 * Classe d'exemple étendant Dessinable.
 *
 * Tout est laissé par défaut, car ce n'est pas le but de cet exemple
 * d'avoir une utilité concrète.
 */

class Contenu final : public Dessinable {
public:
    /*
     * Le reste de la classe peut être quelconque selon les besoins.
     */
    ~Contenu() override = default;
    Contenu(Contenu const &) = default;
    Contenu &operator=(Contenu const &) = default;
    Contenu(Contenu &&) = default;
    Contenu &operator=(Contenu &&) = default;
    Contenu() = default;

    /*
     * Ceci est la méthode devant être ajoutée à toute classe
     * étendant Dessinable, afin de pouvoir être dessinée.
     */
    void dessine_sur(SupportADessin &support) override { support.dessine(*this); }
};
