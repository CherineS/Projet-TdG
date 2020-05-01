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
        double m_N_Cd;
        double m_Cd;
        double m_Cvp;
        double m_N_Cp;
        double m_Cp;
        double m_N_Ci;
        double m_Ci;

        bool m_marque;
        double m_distance;
        Sommet* m_precedent;
        std::vector<Sommet*> m_PccPrecedents;
        std::vector<std::vector<int>> m_Pcc;

        std::vector<Sommet*> m_successeurs;

    public :
        Sommet(int indice, char nom, int x, int y);
        void Dessiner(Svgfile& index, bool oriente, std::vector<Arete>& aretes, bool CVP, bool CD, bool CP, bool CI, bool pondere, bool N_CD, bool N_CP, bool N_CI);
        void AddSuccesseur(Sommet* s);
        void Successeur(int id1, int id2, std::vector<Sommet>& sommets, bool oriente);
        void Afficher();
        void Centralite_Degre(int m_ordre);
        void Somme_Indices();
        void Recalcul_Indices(double lambda, double Csi);
        double Csi();
        char getNom();

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

        void AddPccPrecedent(Sommet* s);
        void CalculPccPrec(Sommet* s_depart, std::vector<Arete>aretes, bool oriente);
        void TestRec(Sommet* s_depart, int& n, std::vector<int>& liste, double distance, std::vector<Arete>aretes, bool oriente, double poids, Sommet* arrive, Sommet* prec, double& poidsprec, std::vector<int>& liste2, bool& test);
        double RechercheAretePoids(std::vector<Arete> aretes, int ind1, int ind2, bool oriente);
        bool TestListe(std::vector<int> liste);
        void ClearListe2(std::vector<int>& liste2, double poids, Sommet* s_depart, Sommet* s_arrive, bool oriente, std::vector<Arete> aretes, double poidsprec);

        void AjouterPcc(std::vector<int> liste, int n);
        void AfficherPcc(Sommet* s_depart);
        void CalculPcci(Sommet* si, Sommet* s_arrive, bool oriente);
        void Normaliser(int n);
        void AfficherTout();
};


#endif // SOMMET_H_INCLUDED
