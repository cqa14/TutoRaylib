#include <iostream>
#include "text_viewer.h"
#include "contenu.h"

int main()
{
  TextViewer ecran(std::cout);
  Contenu c;
  c.dessine_sur(ecran);

  return 0;
}
