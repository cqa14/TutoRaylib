#pragma once

#include "dessinable.h"
#include "support_a_dessin.h"

class Contenu : public Dessinable {
public:
  virtual ~Contenu() = default;
  Contenu(Contenu const&)            = default;
  Contenu& operator=(Contenu const&) = default;
  Contenu(Contenu&&)                 = default;
  Contenu& operator=(Contenu&&)      = default;

  Contenu() = default;

  virtual void dessine_sur(SupportADessin& support) override
  { support.dessine(*this); }
};
