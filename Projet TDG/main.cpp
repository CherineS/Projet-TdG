#include <iostream>
#include <vector>
#include <fstream>
#include "svgfile.h"

class Sommet
{
    private :
        char m_nom;
        int m_indice;
        int m_x, m_y;
        bool m_marque;
        std::vector<Sommet*> m_successeurs;

    public :
        Sommet(int indice, char nom, int x, int y);
        void Dessiner(Svgfile& index);
        void AddSuccesseur(Sommet* s);
        void Successeur(int id1, int id2, std::vector<Sommet>& sommets);
        void Afficher();

};

Sommet::Sommet(int indice, char nom, int x, int y)
{
    m_nom = nom;
    m_indice = indice;
    m_marque = false;
    m_x = x;
    m_y = y;
}

void Sommet::AddSuccesseur(Sommet* s)
{
    m_successeurs.push_back(s);
}

void Sommet::Successeur(int id1, int id2, std::vector<Sommet>& sommets)
{
    if(id1 == m_indice)
    {
        for(size_t i=0 ; i < sommets.size() ; i++)
        {
            if(id2 == sommets[i].m_indice)
                m_successeurs.push_back(&sommets[i]);
        }
    }
}



void Sommet::Dessiner(Svgfile& index)
{
    index.addDisk(m_x*100, m_y*100, 3, "cyan");
    std::string c(1, m_nom);
    index.addText(m_x*100 - 5, m_y*100 - 10, c,"black");

    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        index.addLine(m_y*100,m_x*100, m_successeurs[i]->m_y*100, m_successeurs[i]->m_x*100, "black");
    }
}

void Sommet::Afficher()
{
    std::cout << m_indice << std::endl;
    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        std::cout << m_successeurs[i]->m_indice << std::endl;
    }
    std::cout << "---------" << std::endl;
}


class Arete
{
    private :
        int m_indice;
        int m_id1, m_id2, m_poid;

    public :
        Arete(int indice, int id1, int id2);
        void Dessiner(Svgfile& index);
        void Successeurs(std::vector<Sommet>& m_sommets);

};

Arete::Arete(int indice, int id1, int id2)
{
    m_indice = indice;
    m_id1 = id1;
    m_id2 = id2;
}

void Arete::Successeurs(std::vector<Sommet>& sommets)
{
    for(size_t i=0 ; i < sommets.size() ; i++)
    {
        sommets[i].Successeur(m_id1, m_id2, sommets);
    }
}



class Graph
{
    private :
        bool m_oriente;
        int m_ordre, m_taille;
        std::vector<Arete> m_aretes;
        std::vector<Sommet> m_sommets;

    public :
        Graph(bool oriente, int ordre, int taille);
        void AddSommet(int indice, char nom, int x, int y);
        void AddArete(int indice, int id1, int id2);
        void Dessiner();
        void Successeurs();
        void Afficher();
};

Graph::Graph(bool oriente, int ordre, int taille)
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
        m_aretes[i].Successeurs(m_sommets);
    }
}

void Graph::Dessiner()
{
        Svgfile index;
        index.addGrid(100, 1, "grey");
        for(size_t i=0 ; i < m_sommets.size() ; i++)
        {
            m_sommets[i].Dessiner(index);
        }
}

void Graph::Afficher()
{
    for(size_t i=0 ; i < m_sommets.size() ; i++)
    {
        m_sommets[i].Afficher();
    }
}

int main()
{
    Graph G(0, 5, 4);
    G.AddSommet(0, 'A', 2, 1);
    G.AddSommet(1, 'B', 1, 2);
    G.AddSommet(2, 'C', 2, 2);
    G.AddSommet(3, 'D', 3, 2);
    G.AddSommet(4, 'E', 2, 3);
    G.AddArete(0, 0, 2);
    G.AddArete(1, 1, 2);
    G.AddArete(2, 2, 3);
    G.AddArete(3, 2, 4);
    G.Successeurs();
    G.Dessiner();
    G.Afficher();



    return 0;
}
