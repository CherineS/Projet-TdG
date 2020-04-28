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
        bool m_marque;
        std::vector<Sommet*> m_successeurs;

    public :
        Sommet(int indice, char nom, int x, int y);
        void Dessiner(Svgfile& index, bool oriente, std::vector<Arete>& aretes);
        void AddSuccesseur(Sommet* s);
        void Successeur(int id1, int id2, std::vector<Sommet>& sommets, bool oriente);
        void Afficher();
};


#endif // SOMMET_H_INCLUDED
