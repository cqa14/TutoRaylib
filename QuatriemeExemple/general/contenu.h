#pragma once

#include "dessinable.h"
#include "support_a_dessin.h"

enum COULEUR {
    NONE,
    ROUGE,
    VERT,
    BLEU,
};

struct Position {
    double x;
    double y;
    double z;
};

class Contenu final : public Dessinable {
public:
    ~Contenu() override = default;
    Contenu(Contenu const &) = default;
    Contenu &operator=(Contenu const &) = default;
    Contenu(Contenu &&) = default;
    Contenu &operator=(Contenu &&) = default;
    explicit Contenu(const Position &p = {0, 0, 0}, const COULEUR c = NONE) : position(p), color(c) {};

    void dessine_sur(SupportADessin &support) const override { support.dessine(*this); }

    [[nodiscard]] Position get_position() const { return position; }
    [[nodiscard]] COULEUR get_color() const { return color; }
private:
    Position position;
    COULEUR color;
};
