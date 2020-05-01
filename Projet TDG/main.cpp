#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <time.h>
#include "svgfile.h"
#include "Arete.h"
#include "Sommet.h"
#include "Graph.h"

bool OuvertureFichier(std::string fichiern)
{
    bool ouverture = false;
    std::ifstream fichier(fichiern);
    if(fichier)
        ouverture = true;
    return ouverture;
}

void Update_Univers(std::vector<Graph>&Univers)
{
    if(Univers.size() > 0)
        Univers.pop_back();
    Graph G(1, 5, 4);
    Univers.push_back(G);
}

int main()
{
    std::vector<Graph>Univers;
    int choix_m=0;
    bool CVP=false, CD=false, CP=false, CI=false, NCD=false, NCP=false, NCI=false;
    std::string fichier;
    srand(time(NULL));

    do{
   std::cout <<  "                              ------------------ MENU ------------------" << std::endl
              << "                              1-          Charger un Graphe           -1" << std::endl
              << "                              2-     Charger systeme de ponderation   -2" << std::endl
              << "                              3-     Calculer indices de centralite   -3" << std::endl
              << "                              4-        Tester la vulnerabilite       -4" << std::endl
              << "                              5-     Affichage Console des Indices    -5" << std::endl
              << "                              0-               Arreter                -0" << std::endl << std::endl
              << "                                               -> ";
    do{
    std::cin >> choix_m;
    }
    while (choix_m != 0 && choix_m != 1 && choix_m != 2 && choix_m != 3 && choix_m != 4 && choix_m!= 5);

    switch(choix_m)
    {
    case 1 :
        {
        Update_Univers(Univers);
        Univers[0].Menu1(fichier, CVP, CD, CP, CI, NCD, NCP, NCI);
        Univers[0].Sauvegarder(1);
        Univers[0].Sauvegarder_Ponderation(1);
        }
        break;
    case 2 :
        {
        Update_Univers(Univers);
        if(Univers.size()>0)
            Univers[0].Menu2(fichier, CVP, CD, CP, CI, NCD, NCP, NCI);
        }
        break;
    case 3 :
        {
        if(Univers.size()>0)
           Univers[0].Menu3(CVP, CD, CP, CI, NCD, NCP, NCI);
        }
        break;
    case 4 :
        {
            if(Univers.size()>0)
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
                    Univers[0].Dessiner(CVP, CD, CP, CI, NCD, NCP, NCI);
                }
                else Univers[0].Recherche_Connexite();
            }
        }
        break;
    case 5 :
        if(Univers.size()>0)
           Univers[0].AfficherTout();
        break;
    }
    }while(choix_m != 0);


    int Fini=0;
    std::cout << "FINI  =  ";
    std::cin >> Fini;

    return 0;
}


