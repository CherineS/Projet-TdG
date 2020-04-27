#include <iostream>
#include <vector>
#include <fstream>
#include "svgfile.h"

class Sommet
{
    private :
        int m_indice;
        int m_x, m_y;
        bool m_marque;
        std::vector<Sommet*> m_successeurs;

    public :
        Sommet(int indice, int x, int y);
        void Dessiner(Svgfile& index);
        void AddSuccesseur(Sommet* s);
        void Successeur(int id1, int id2, std::vector<Sommet>& sommets);

};

Sommet::Sommet(int indice, int x, int y)
{
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

    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        index.addLine(m_x,m_y, m_successeurs[i]->m_x, m_successeurs[i]->m_y, "black");
    }
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

/*void Arete::Dessiner(Svgfile& index)
{
    index.addLine();
}*/



class Graph
{
    private :
        bool m_oriente;
        int m_ordre, m_taille;
        std::vector<Arete> m_aretes;
        std::vector<Sommet> m_sommets;

    public :
        Graph(bool oriente, int ordre, int taille);
        void AddSommet(int indice, int x, int y);
        void AddArete(int indice, int id1, int id2);
        void Dessiner();
        void Successeurs();
};

Graph::Graph(bool oriente, int ordre, int taille)
{
    m_oriente = oriente;
    m_ordre = ordre;
    m_taille = taille;
}

void Graph::AddSommet(int indice, int x, int y)
{
    Sommet s(indice, x, y);
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
        //index.addTriangle(1*10, 1*10, 4*10, 1*10, 1*10, 4*10, "green");*

        for(size_t i=0 ; i < m_sommets.size() ; i++)
        {
            m_sommets[i].Dessiner(index);
        }

}

int main()
{
    Graph G(0, 3, 2);
    G.AddSommet(0, 1, 1);
    G.Dessiner();





    return 0;
}
