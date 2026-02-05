#pragma once

#include <iostream>
#include "support_a_dessin.h"

class TextViewer final : public SupportADessin {
public:
    /*
     * On crée un support à dessin qui va écrire dans le flot passé en paramètre,
     * par exemple std::cout.
     */
    explicit TextViewer(std::ostream& flot_) : flot(flot_) {}

    ~TextViewer() override = default;
    TextViewer(TextViewer const&) = delete;
    TextViewer& operator=(TextViewer const&) = delete;
    TextViewer(TextViewer&&) = default;
    /*
     * Remarquez que l'on disait qu'un SupportADessin était déplaçable.
     * Néanmoins, on a désactivé le déplacement par opérateur d'affectation
     * dans ce cas.
     * En effet, c'est le comportement par défaut du compilateur qui est ici
     * explicité, car on ne peut pas copier un flot.
     * La construction de TextViewer par déplacement est autorisée (ci-dessus),
     * parce que celle-ci ne fait que copier la référence au flot.
     */
    TextViewer& operator=(TextViewer&&) = delete;

    /*
     * Il faut surcharger la méthode dessine pour dessiner le contenu.
     * Ne pas oublier de le faire pour toutes les méthodes de dessin !
     */
    void dessine(Contenu const& a_dessiner) override;

private:
    std::ostream& flot;
};
