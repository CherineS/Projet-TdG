#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <time.h>
#include "svgfile.h"
#include "Arete.h"
#include "Sommet.h"
#include "Graph.h"

void Update_Univers(std::vector<Graph>&Univers)
{
    if(Univers.size() > 0)
        Univers.pop_back();
    Graph G(1, 5, 4);
    Univers.push_back(G);
}

int main()
{
    bool  CD = true , CVP = true , CP = true , CI = true;
    bool Norm_CD = true , Norm_CP = true , Norm_CI = true ;

    //int indice_sommet_arrivee = 6 ;
    //int indice_sommet_depart = 0 ;
    std::vector<Graph>Univers;
    Graph G(1, 5, 4);
    int choix_m=0;
    std::string fichier;
    srand(time(NULL));

    do{
   std::cout <<  "--------------- MENU ---------------" << std::endl
              << "            0 : Arreter             " << std::endl
              << "       1 : Charger un Graphe        " << std::endl
              << " 2 : Charger systeme de ponderation " << std::endl
              << " 3 : Calculer indices de centralite " << std::endl
              << "     4 : Tester la vulnerabilite    " << std::endl
              << "             Choix : " ;
    do{
    std::cin >> choix_m;
    }
    while (choix_m != 0 && choix_m != 1 && choix_m != 2 && choix_m != 3 && choix_m != 4);

    switch(choix_m)
    {
    case 1 :
        {
        Update_Univers(Univers);
        Univers[0].Menu1(fichier);
        }
        break;
    case 2 :
        break;
    case 3 :
        break;
    case 4 :
        {
        std::cout << "\n      1 : Supprimer une arete\n    2 : Afficher les connexites\n\t     Choix : ";
        do
        std::cin >> choix_m;
        while (choix_m != 1 && choix_m != 2);

        if(choix_m==1)
        {
            Univers[0].Sauvegarder(0);
            Univers[0].Sauvegarder_Ponderation(0);
            Univers[0].SupprimerArete();
            Univers[0].Sauvegarder(1);
            Univers[0].Sauvegarder_Ponderation(1);
            Update_Univers(Univers);
            Univers[0].Chargement("GrapheActuel.txt");
            Univers[0].Chargement_Ponderation("PonderationActuelle.txt");
            Univers[0].Calcul();
            Univers[0].Dessiner(true, true, true, true);
        }
        else Univers[0].Recherche_Connexite();
        }

        break;
    }
    }while(choix_m != 0);





   /* std::cout << "--------------- MENU ---------------" << std::endl << "Saisir numero du fichier : ";
    do{
        std::cin >> choix;
    }while(choix >4 || choix <1);

    std::cout << "Saisir numero du fichier : ";
    while(choixF >4 || choixF <1)
        std::cin >> choixF;

    switch(choixF)
    {
        case 1 : G.Chargement("graphe-topo.txt");  G.Chargement_Ponderation("graphe-topo-ponderation.txt"); break;
        case 2 : G.Chargement("graphe-topo2.txt"); G.Chargement_Ponderation("graphe-topo2-ponderation.txt"); break;
        case 3 : G.Chargement("graphe-topo3.txt"); G.Chargement_Ponderation("graphe-topo3-ponderation.txt"); break;
        case 4 : G.Chargement("graphe-topo4.txt"); G.Chargement_Ponderation("graphe-topo4-ponderation.txt"); break;
    }*/

    /*G.Successeurs();
    G.Centralite_Degre();
    G.Centralite_Vecteur_Propre();
    G.Auto_Dijkstra();*/
    G.Normaliser( Norm_CD, true, Norm_CP, Norm_CI);
    G.Dessiner(CVP, CD, CP, CI);
    //G.Afficher();

    //G.AfficherPcc();

    /*int continuer=1;
    do{
        std::cout << "Saisir Indice sommet Depart Dijkstra : ";
        std::cin >> indice_sommet_depart;
        std::cout << "Saisir Indice sommet Arrivee Dijkstra : ";
        std::cin >> indice_sommet_arrivee;
        std::cout << std::endl << std::endl;

        G.Reset_Dijkstra();
        double d=0;
        G.Dijkstra(indice_sommet_depart);
        G.AfficherParcoursDijkstra(indice_sommet_arrivee, d);

        std::cout << std::endl << std::endl;
        std::cout << "      Continuer ?    " << std::endl << " 0 : Non || Oui : 1 " << std::endl << "         ";
        std::cin >> continuer;

    }while(continuer != 0);*/
    int Fini=0;
    std::cout << "FINI  =  ";
    std::cin >> Fini;

    return 0;
}


