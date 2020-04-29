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
        double m_Cd;
        double m_Cvp;
        double m_Cp;

        bool m_marque;
        double m_distance;
        Sommet* m_precedent;

        std::vector<Sommet*> m_successeurs;

    public :
        Sommet(int indice, char nom, int x, int y);
        void Dessiner(Svgfile& index, bool oriente, std::vector<Arete>& aretes, bool CVP, bool CD, bool CP);
        void AddSuccesseur(Sommet* s);
        void Successeur(int id1, int id2, std::vector<Sommet>& sommets, bool oriente);
        void Afficher();
        void Centralite_Degre(int m_ordre);
        void Somme_Indices();
        void Recalcul_Indices(double lambda, double Csi);
        double Csi();

        int get_indice();
        Sommet* Get_precedent();
        bool RechercheSommet(int ind);
        void Fini(int distance, Sommet* precedent);
        void Marquage();
        bool Marque();
        void Dijkstra(std::vector<double>&distances, std::vector<Sommet*>&sommetprec, std::vector<Sommet*>&sommets, double distance, std::vector<Arete>aretes, Sommet* s, bool oriente);
        void Reset_Dijkstra();
        bool TestNombreSuccesseurs();

        void AddCp(double Cp, int n);

};


#endif // SOMMET_H_INCLUDED
