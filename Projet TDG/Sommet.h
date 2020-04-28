#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <vector>
#include "svgfile.h"

class Arete;

class Sommet
{
    private :
        char m_nom;
        int m_indice;
        int m_x, m_y;
        double m_Cvp;
        bool m_marque;
        std::vector<Sommet*> m_successeurs;

    public :
        Sommet(int indice, char nom, int x, int y);
        void Dessiner(Svgfile& index, bool oriente, std::vector<Arete>& aretes, bool CVP);
        void AddSuccesseur(Sommet* s);
        void Successeur(int id1, int id2, std::vector<Sommet>& sommets, bool oriente);
        void Afficher();
        void Centralite_Degre(int m_ordre, Svgfile& index, bool CD);
        void Somme_Indices();
        void Recalcul_Indices(double lambda, double Csi);
        double Csi();

};


#endif // SOMMET_H_INCLUDED
