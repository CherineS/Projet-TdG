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

void Graph::Dessiner(Svgfile& index, bool CVP , bool CD)
{
        index.addGrid(100, 1, "grey");
        for(size_t i=0 ; i < m_sommets.size() ; i++)
        {
            m_sommets[i].Dessiner(index, m_oriente, m_aretes, CVP, CD);
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

void Graph::Centralite_Intermediarite()
{
}

void Graph::Recherche_Connexite()
{
    int nbConnex=0, compteur=1, compteur2=0, prochain=0;
    std::vector<int> ListeConnex;

    do{
        compteur=1;

        ListeConnex.push_back(prochain);

        for(size_t i=0;i<2;++i) ///Le refaire plusieurs fois pour être sûr..
        {
            for(size_t j=0;j<m_aretes.size();++j)  ///Recherche si le sommet a deja ete parcouru
            {
                m_aretes[j].ParcoursConnex(ListeConnex,compteur,prochain);
            }
        }

        nbConnex++;

        ///Affichage
        std::cout << std::endl << "Composante connexe " << nbConnex << " : ";
        for(size_t i=compteur2;i<ListeConnex.size();++i)
            std::cout << m_sommets[ListeConnex[i]].getNom() << " ";
        std::cout << std::endl;

        compteur2+=compteur;
    }while(compteur2<m_ordre);

}
