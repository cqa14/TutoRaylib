#pragma once

#include <iostream>
#include "support_a_dessin.h"

class TextViewer final : public SupportADessin {
public:
    explicit TextViewer(std::ostream& flot) : flot(flot) {}

    ~TextViewer() override = default;
    TextViewer(TextViewer const&) = delete;
    TextViewer& operator=(TextViewer const&) = delete;
    TextViewer(TextViewer&&) = default;

    void dessine(Contenu const& a_dessiner) override;

private:
    std::ostream& flot;
};
