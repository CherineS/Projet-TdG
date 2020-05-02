#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <vector>
#include "Arete.h"

class Graph
{
    private :
        bool m_pondere;
        bool m_oriente;
        int m_ordre, m_taille;
        std::vector<Arete> m_aretes;
        std::vector<Sommet> m_sommets;
        std::vector<std::vector<double>> m_distances;

    public :
        Graph(bool oriente, int ordre, int taille);
        void AddOriente_Ordre_Taille(bool oriente, int ordre, int taille);
        void AddSommet(int indice, char nom, double x, double y);
        void AddArete(int indice, int id1, int id2);
        void Dessiner(bool& CVP, bool& CD, bool& CP, bool& CI, bool& N_CD, bool& N_CP, bool& N_CI, std::vector<std::vector<double>> IndicesPrec, std::vector<std::vector<double>> NIndicesPrec, bool DIFF);
        void Successeurs();
        void Afficher();
        void Chargement(std::string nomF);
        void Chargement_Ponderation(std::string nomF);
        void Centralite_Degre();
        void Centralite_Vecteur_Propre();
        void Recherche_Connexite();
        void SupprimerArete();

        void Dijkstra(int s_depart);
        void AfficherParcoursDijkstra(int s_arrivee, double& d);
        void Reset_Dijkstra();
        Sommet* RechercheSommet(int num);

        void Auto_Dijkstra();

        void AfficherPcc(Sommet* s_depart);
        void Test(Sommet* s_depart);
        void CalculPcci(Sommet* s_arrive);

        void Normaliser();

        void Calcul();
        void Memoire(std::string& fichier, int& num);
        void Memoire_Ponderation(std::string& fichier, int num);
        void Menu1(std::string& fichierG, bool& CVP, bool& CD, bool& CP, bool& CI, bool& NCD, bool& NCP, bool& NCI, std::vector<std::vector<double>> IndicesPrec, std::vector<std::vector<double>> NIndicesPrec, bool& DIFF);
        void Menu2(std::string fichierG, bool& CVP, bool& CD, bool& CP, bool& CI, bool& NCD, bool& NCP, bool& NCI, std::vector<std::vector<double>> IndicesPrec, std::vector<std::vector<double>> NIndicesPrec, bool& DIFF);
        void Menu3(bool& CVP, bool& CD, bool& CP, bool& CI, bool& NCD, bool& NCP, bool& NCI, std::vector<std::vector<double>> IndicesPrec, std::vector<std::vector<double>> NIndicesPrec, bool& DIFF);
        void AfficherTout();
        void Sauvegarder(int mode);
        void Sauvegarder_Ponderation(int mode);

        void SaveComparaison();
        void ChargerComparaison(std::vector<std::vector<double>>& IndicesPrec, std::vector<std::vector<double>>& NIndicesPrec);
};

#endif // GRAPH_H_INCLUDED
