#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <vector>
#include "Sommet.h"

class Arete
{
    private :
        int m_indice;
        int m_id1, m_id2;
        double m_poids;

    public :
        Arete(int indice, int id1, int id2);
        void Successeurs(std::vector<Sommet>& m_sommets, bool oriente);
        void Poids(double poids, int indice);
        void DessinerPoids(Svgfile& index, int indice1, int x1, int y1, int indice2, int x2, int y2);
        void Afficher();
};

#endif // ARETE_H_INCLUDED
