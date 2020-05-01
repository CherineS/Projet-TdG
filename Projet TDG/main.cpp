#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include "svgfile.h"
#include "Arete.h"
#include "Sommet.h"
#include "Graph.h"



int main()
{
    bool  CD = true , CVP = true , CP = true , CI = true;
    bool Norm_CD = true , Norm_CP = true , Norm_CI = true ;

    //int indice_sommet_arrivee = 6 ;
    //int indice_sommet_depart = 0 ;

    Graph G(1, 5, 4);
    int choix;
    std::string fichier;

    std::cout << "--------------- MENU ---------------" << std::endl << "Saisir numero du fichier : ";
    while(choix >4 || choix <1)
        std::cin >> choix;

    switch(choix)
    {
        case 1 : G.Chargement("graphe-topo.txt"); G.Chargement_Ponderation("graphe-topo-ponderation.txt"); break;
        case 2 : G.Chargement("graphe-topo2.txt"); G.Chargement_Ponderation("graphe-topo2-ponderation.txt"); break;
        case 3 : G.Chargement("graphe-topo3.txt"); G.Chargement_Ponderation("graphe-topo3-ponderation.txt"); break;
        case 4 : G.Chargement("graphe-topo4.txt"); G.Chargement_Ponderation("graphe-topo4-ponderation.txt"); break;
    }

    G.Successeurs();
    G.Centralite_Degre();
    G.Centralite_Vecteur_Propre();
    G.Auto_Dijkstra();
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


