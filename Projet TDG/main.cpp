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
    Graph G(1, 5, 4);
    int choix;
    std::string fichier;

    std::cout << "--------------- MENU ---------------" << std::endl << "Saisir numero du fichier : ";
    while(choix >4 || choix <1)
        std::cin >> choix;

    switch(choix)
    {
        case 1 : G.Chargement("graphe-topo.txt"); break;
        case 2 : G.Chargement("graphe-topo2.txt"); break;
        case 3 : G.Chargement("graphe-topo3.txt"); break;
        case 4 : G.Chargement("graphe-topo4.txt"); G.Chargement_Ponderation("graphe-topo4-ponderation.txt"); break;
    }

    G.Successeurs();
    G.Dessiner();
    G.Afficher();



    return 0;
}


