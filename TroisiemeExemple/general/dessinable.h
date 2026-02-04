#pragma once

class SupportADessin;

class Dessinable {
public:
    /*
     * Cette classe n'a pour but que de servir de généralisation
     * pour les classes qui peuvent être dessinées, fournissant
     * la méthode dessine_sur() devant être implémentée dans
     * toutes les classes qui en héritent.
     */
    virtual void dessine_sur(SupportADessin&) const = 0;

    virtual ~Dessinable() = default;
    Dessinable(Dessinable const&) = default;
    Dessinable& operator=(Dessinable const&) = default;
    Dessinable(Dessinable&&) = default;
    Dessinable& operator=(Dessinable&&) = default;

    Dessinable() = default;
};
