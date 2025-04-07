#include <iostream>
#include "text_viewer.h"
#include "contenu.h"

int main()
{
  // On crée un support à dessin qui va écrire dans le flot passé en paramètre,
  TextViewer ecran(std::cout);

  /*
   * Comme contenu étend Dessinable, on peut tout de suite le dessiner
   * par l'architecture mise en place.
   */
  Contenu c;
  c.dessine_sur(ecran);

  return 0;
}
