#include <iostream>
#include "text_viewer.h"
#include "contenu.h"

void TextViewer::dessine(Contenu const&)
{
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
