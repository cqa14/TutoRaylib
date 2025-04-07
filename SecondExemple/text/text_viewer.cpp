#include <iostream>
#include "text_viewer.h"
#include "contenu.h"

void TextViewer::dessine(Contenu const&)
{
    /*
     * On dessine un contenu.
     * Ici, on n'utilise pas le contenu, mais on pourrait tout à fait
     * (ce serait même l'utilisation normale).
     */
    flot <<
        "+------+.   " << std::endl <<
        "|`.    | `. " << std::endl <<
        "|  `+--+---+" << std::endl <<
        "|   |  |   |" << std::endl <<
        "+---+--+.  |" << std::endl <<
        " `. |    `.|" << std::endl <<
        "   `+------+" << std::endl;
    // Dessin de https://www.asciiart.eu/art-and-design/geometries
}
