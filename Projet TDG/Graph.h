#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <vector>
#include "Arete.h"

class Graph
{
    private :
        bool m_oriente;
        int m_ordre, m_taille;
        std::vector<Arete> m_aretes;
        std::vector<Sommet> m_sommets;
        std::vector<std::vector<double>> m_distances;

    public :
        Graph(bool oriente, int ordre, int taille);
        void AddOriente_Ordre_Taille(bool oriente, int ordre, int taille);
        void AddSommet(int indice, char nom, int x, int y);
        void AddArete(int indice, int id1, int id2);
        void Dessiner(bool CVP, bool CD, bool CP);
        void Successeurs();
        void Afficher();
        void Chargement(std::string nomF);
        void Chargement_Ponderation(std::string nomF);
        void Centralite_Degre();
        void Centralite_Vecteur_Propre();

        void Dijkstra(int s_depart);
        void AfficherParcoursDijkstra(int s_arrivee, double& d);
        void Reset_Dijkstra();
        Sommet* RechercheSommet(int num);

        void Auto_Dijkstra();

        void AfficherPcc();
        void Test(Sommet* s_depart);
};

#endif // GRAPH_H_INCLUDED
