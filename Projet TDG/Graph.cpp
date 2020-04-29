#include <iostream>
#include <vector>
#include "Graph.h"
#include "math.h"

Graph::Graph(bool oriente, int ordre, int taille)
{
    m_oriente = oriente;
    m_ordre = ordre;
    m_taille = taille;
}

void Graph::AddOriente_Ordre_Taille(bool oriente, int ordre, int taille)
{
    m_oriente = oriente;
    m_ordre = ordre;
    m_taille = taille;

    std::vector<double> vec;

    for(int i=0 ; i < m_ordre ; i++)
    {
        vec.push_back(-1);
    }

    for(int i=0 ; i < m_ordre ; i++)
    {
        m_distances.push_back(vec);
    }

}

void Graph::AddSommet(int indice, char nom, int x, int y)
{
    Sommet s(indice, nom, x, y);
    m_sommets.push_back(s);
}

void Graph::AddArete(int indice, int id1, int id2)
{
    Arete a(indice, id1, id2);
    m_aretes.push_back(a);
}

void Graph::Successeurs()
{
    for(size_t i=0 ; i < m_aretes.size() ; i++)
    {
        m_aretes[i].Successeurs(m_sommets, m_oriente);
    }
}

void Graph::Dessiner(bool CVP , bool CD, bool CP)
{
    Svgfile index;
        index.addGrid(100, 1, "grey");
        for(size_t i=0 ; i < m_sommets.size() ; i++)
        {
            m_sommets[i].Dessiner(index, m_oriente, m_aretes, CVP, CD, CP);
        }
}

void Graph::Afficher()
{
    std::cout << "Aretes Liste : " << std::endl;
    for(size_t i=0 ; i < m_aretes.size() ; i++)
    {
        m_aretes[i].Afficher();
    }

    std::cout << "Sommets Liste : " << std::endl;
    for(size_t i=0 ; i < m_sommets.size() ; i++)
    {
        m_sommets[i].Afficher();
    }
}

void Graph::Chargement(std::string nomF)
{
    int oriente, ordre, taille;
    int indice, x, y;
    char nom;
    bool b_oriente;
    std::ifstream fichier(nomF);
    if(fichier)
    {
        fichier >> oriente;
        if(oriente == 0)
            b_oriente = false;
        if(oriente == 1)
            b_oriente = true;

        fichier >> ordre;
        for(int i=0 ; i < ordre ; i++)
        {
            fichier >> indice >> nom >> x >> y;
            //std::cout << "Indice : " << indice << " Nom : " << nom << " x : " << x << " y : " << y << std::endl;
            AddSommet(indice, nom, x, y);
        }
        fichier >> taille;

        int ind, ext1, ext2;
        for(int i=0 ; i < taille ; i++)
        {
            fichier >> ind >> ext1 >> ext2;
            AddArete(ind, ext1, ext2);
        }

        AddOriente_Ordre_Taille( b_oriente, ordre, taille);
    }
    else
        std::cout << "Probleme ouverture fichier" <<std::endl;
}

void Graph::Chargement_Ponderation(std::string nomF)
{
    std::ifstream fichier(nomF);
    if(fichier)
    {
        int taille, indice;
        double poids;
        fichier >> taille;
        for(int i=0 ; i < taille ; i++)
        {
            fichier >> indice >> poids;
            for(size_t j=0 ; j < m_aretes.size() ; j++)
            {
                m_aretes[j].Poids( poids, indice);
            }
        }
    }
    else
        std::cout << "Probleme ouverture fichier" <<std::endl;
}

void Graph::Centralite_Degre()
{
    for(size_t i=0 ; i < m_sommets.size() ; i++ )
    {
        m_sommets[i].Centralite_Degre(m_ordre);
    }
}

void Graph::Centralite_Vecteur_Propre()
{
    double lambda = 0, lambda_prec = 0;

    do{
    lambda_prec=lambda;
    std::vector<double> Vec_Csi;
    lambda = 0;
    for(size_t i=0 ; i < m_sommets.size() ; i++)
    {
        lambda += (m_sommets[i].Csi())*(m_sommets[i].Csi());
        Vec_Csi.push_back(m_sommets[i].Csi());
    }
    lambda = sqrt(lambda);

    for(size_t i=0 ; i < m_sommets.size() ; i++)
    {
        m_sommets[i].Recalcul_Indices(lambda, Vec_Csi[i]);
    }
    }while( (lambda < (lambda_prec-0.01)) || (lambda > (lambda_prec +0.01)) );

    std::cout << "Lambda : " << lambda << std::endl;
}




void Graph::Dijkstra(int s_depart)
{
    Sommet* s = RechercheSommet(s_depart);
    s->Marquage();
    double distance = 0;
    bool impossible = s->TestNombreSuccesseurs();;
    std::vector<double>distances;
    std::vector<Sommet*>sommetprec;
    std::vector<Sommet*>sommets;

    for(int i=0 ; i < m_ordre ; i++)
    {
        s->Dijkstra(distances, sommetprec, sommets, distance, m_aretes, s, m_oriente);
        int minn=10000000;
        int s_position=0;
        for(size_t k=0 ; k < distances.size() ; k++)
        {
            if(minn > distances[k] && sommets[k]->Marque()==false)
            {
                minn=distances[k];
                s_position=k;
            }
        }
        if(impossible == true)
            s->Fini(0, NULL);
        if(impossible == false)
            s=sommets[s_position];
        /*if(s->Marque() == false)
            s->Marquage();*/
        //std::cout << "MARQUAGE : " << s->get_indice() << std::endl;
        //std::cout <<  std::endl;
        if(impossible == false && s->Marque() == false)
        {
            s->Fini(distances[s_position], sommetprec[s_position]);
            std::cout << "MARQUAGE : " << s->get_indice() << std::endl;
            std::cout <<  std::endl;
        }
        if(s->Marque() == false)
            s->Marquage();
        if(impossible == false)
            distance = distances[s_position];
        if(distances.size()>0)
        {
            distances.erase(distances.begin()+s_position);
            sommetprec.erase(sommetprec.begin()+s_position);
            sommets.erase(sommets.begin()+s_position);
        }
    }
}

Sommet* Graph::RechercheSommet(int num)
{
    Sommet* sommet;
    for(size_t i=0 ; i < m_sommets.size() ; i++)
    {
        if(m_sommets[i].RechercheSommet(num) == true)
            sommet=&m_sommets[i];
    }
    return sommet;
}


void Graph::AfficherParcoursDijkstra(int s_arrivee, double& d)
{
    Sommet* s;
    std::vector<double>longueur;
    s=RechercheSommet(s_arrivee);
    if(s->Get_precedent()!=NULL)
        std::cout << s->get_indice();
    double poids=0;
    double poids2=0;
    while(s->Get_precedent()!=NULL)
    {
        //longueur.push_back(RechercheArete(s->get_indice(), s->Get_precedent()->get_indice())->Get_poids());
        ///longueur.push_back(RechercheArete(s->Get_precedent()->get_indice(), s->get_indice())->Get_poids());
        for(size_t i=0 ; i < m_aretes.size() ; i++)
        {
            poids2 = m_aretes[i].Recherche_Poids( s->Get_precedent()->get_indice(), s->get_indice(), m_oriente);
            if(poids2 != 0)
                poids = poids2;
        }
        longueur.push_back(poids);


        std::cout << " <-- " << s->Get_precedent()->get_indice();
        s=s->Get_precedent();
    }
    if(longueur.size() == 0)
    {
        std::cout << "Impossible" << std::endl;
    }
    else{
        std::cout << " : longueur " << longueur[0] ;
        double somme=longueur[0];
        for(size_t i=1 ; i < longueur.size() ; i++)
        {
            std::cout << " + " << longueur[i];
            somme+=longueur[i];
        }
        std::cout << " = " << somme <<std::endl;
        d=somme;
    }
}

void Graph::Reset_Dijkstra()
{
    for(size_t i = 0 ; i < m_sommets.size() ; i++)
    {
        m_sommets[i].Reset_Dijkstra();
    }
}



void Graph::Auto_Dijkstra()
{
    double distance=0;
    double Cp=0;
    double sommeTotale=0;


    for(size_t i = 0 ; i < m_sommets.size() ; i++)
    {
        Reset_Dijkstra();
        Dijkstra(m_sommets[i].get_indice());
        for(size_t j = 0 ; j < m_sommets.size() ; j++)
        {
            distance=0;
            AfficherParcoursDijkstra(m_sommets[j].get_indice(), distance);

            //std::cout << "Distance = " << distance << std::endl;
            m_distances[i][j]=distance;
            sommeTotale+=distance;
            Cp+=distance;
        }
        std::cout << std::endl;
        Cp=1/Cp;
        m_sommets[i].AddCp(Cp, m_ordre);
        Cp=0;
    }
    std::cout << "Distance TOTAL = " << sommeTotale << std::endl;
}

