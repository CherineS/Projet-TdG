#include <iostream>
#include <vector>
#include "Arete.h"

Arete::Arete(int indice, int id1, int id2)
{
    m_indice = indice;
    m_id1 = id1;
    m_id2 = id2;
}

void Arete::Successeurs(std::vector<Sommet>& sommets, bool oriente)
{
    for(size_t i=0 ; i < sommets.size() ; i++)
    {
        sommets[i].Successeur(m_id1, m_id2, sommets, oriente);
    }
}

void Arete::Poids(double poids, int indice)
{
    if(indice == m_indice)
        m_poids = poids;
}

void Arete::DessinerPoids(Svgfile& index, int indice1, int x1, int y1, int indice2, int x2, int y2)
{
    x1=x1*100; y1=y1*100; x2=x2*100; y2=y2*100;
    if((m_id1 == indice1) && (m_id2==indice2))
    {
        //index.addDisk( x1+(x2-x1)/2, y1+(y2-y1)/2, 10,"white");
        //index.addText( x1+(x2-x1)/2 -4, y1+(y2-y1)/2 +4, m_poids, "grey");
        index.addText( x1+(x2-x1)/2 -4, y1+(y2-y1)/2 -8, m_poids, "black");
    }

}

void Arete::Afficher()
{
    std::cout << "indice : " << m_indice << " id1 : " << m_id1 << " id2 : " << m_id2 << " Poids : " << m_poids << std::endl;
}

double Arete::Recherche_Poids(double ind1, double ind2, bool oriente)
{
    double poids=0;
    if(oriente == true)
        if((m_id1 == ind1) && (m_id2 == ind2))
            poids = m_poids;
    if(oriente == false)
    {
        if(((m_id1 == ind1) && (m_id2 == ind2)) || ((m_id1 == ind2) && (m_id2 == ind1)))
        {
            poids = m_poids;
        }

    }

    return poids;
}

