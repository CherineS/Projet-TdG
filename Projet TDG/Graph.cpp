#include <iostream>
#include <vector>
#include "Graph.h"

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

void Graph::Dessiner(Svgfile& index)
{
        index.addGrid(100, 1, "grey");
        for(size_t i=0 ; i < m_sommets.size() ; i++)
        {
            m_sommets[i].Dessiner(index, m_oriente, m_aretes);
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

void Graph::Centralite_Degre(Svgfile& index)
{
    for(size_t i=0 ; i < m_sommets.size() ; i++ )
    {
        m_sommets[i].Centralite_Degre(m_ordre, index);
    }
}

