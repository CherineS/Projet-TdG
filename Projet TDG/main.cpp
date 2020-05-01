#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <time.h>
#include "svgfile.h"
#include "Arete.h"
#include "Sommet.h"
#include "Graph.h"



int main()
{
    Svgfile index;
    bool  CD = true;
    bool CVP = true;
    Graph G(1, 5, 4);
    int choix=2, choixF=0;
    srand(time(NULL));

    std::cout << "--------------- MENU ---------------" << std::endl;

    std::cout << "Saisir numero du fichier : ";
    while(choixF >4 || choixF <1)
        std::cin >> choixF;

    switch(choixF)
    {
        case 1 : G.Chargement("graphe-topo.txt"); break;
        case 2 : G.Chargement("graphe-topo2.txt"); break;
        case 3 : G.Chargement("graphe-topo3.txt"); break;
        case 4 : G.Chargement("graphe-topo4.txt"); G.Chargement_Ponderation("graphe-topo4-ponderation.txt"); break;
    }

    while(choix!=3)
    {
        G.Successeurs();
        G.Centralite_Degre();
        G.Centralite_Vecteur_Propre();
        G.Dessiner(index, CVP, CD);
        G.Afficher();
        G.Recherche_Connexite();

        choix=0;

        std::cout << "\n\n--------------- MENU ---------------" << std::endl;
        std::cout << "\n\n1. Supprimer une arete\n2. Changer de fichier\n3. Quitter\n\nChoix : ";
        while(choix >3 || choix <1)
                std::cin >> choix;

        if(choix==1)
            G.SupprimerArete();
    }

    return 0;
}


