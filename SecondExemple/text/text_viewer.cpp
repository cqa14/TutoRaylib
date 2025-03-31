#include <iostream> // pour endl
#include "text_viewer.h"
#include "contenu.h"

void TextViewer::dessine(Contenu const&)
{
  /* Dans ce premier exemple très simple, on n'utilise       *
   * pas l'argument Contenu. Nous ne l'avons donc pas nommé. */

  flot << "un cube" << std::endl;
}
