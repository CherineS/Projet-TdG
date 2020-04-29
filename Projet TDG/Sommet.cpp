#include <iostream>
#include <vector>
#include "math.h"
#include "Sommet.h"
#include "Arete.h"
#include <iomanip>

Sommet::Sommet(int indice, char nom, int x, int y)
{
    m_nom = nom;
    m_indice = indice;
    m_marque = false;
    m_x = x;
    m_y = y;
    m_Cvp=1;
    m_Cp=0;
    m_precedent=NULL;
}

void Sommet::AddSuccesseur(Sommet* s)
{
    m_successeurs.push_back(s);
}

void Sommet::Successeur(int id1, int id2, std::vector<Sommet>& sommets, bool oriente)
{
    if(id1 == m_indice)
    {
        for(size_t i=0 ; i < sommets.size() ; i++)
        {
            if(id2 == sommets[i].m_indice)
            {
                m_successeurs.push_back(&sommets[i]);

                if(oriente == false)
                {
                    sommets[i].m_successeurs.push_back(this);
                }
            }
        }
    }
}


void Sommet::Dessiner(Svgfile& index, bool oriente, std::vector<Arete>& aretes, bool CVP, bool CD, bool CP)
{
    std::string couleur;
    if( m_Cd < 0.25)
        couleur = "cyan";
    if( m_Cd >= 0.25 && m_Cd < 0.375)
        couleur = "green";
    if( m_Cd >= 0.375 && m_Cd < 0.5)
        couleur = "blue";
    if( m_Cd >= 0.5 && m_Cd < 0.75)
        couleur = "orange";
    if( m_Cd >= 0.75)
        couleur = "red";
    index.addDisk(m_x*100, m_y*100, 3, couleur);
    std::string c(1, m_nom);
    index.addText(m_x*100 - 5, m_y*100 - 10, c,"black");

    if(CD == true)
    {
    index.addText(m_x*100 - 14, m_y*100 + 16, m_Cd, "yellow");
    index.addText(m_x*100 - 16, m_y*100 + 18, m_Cd, "yellow");
    index.addText(m_x*100 - 15, m_y*100 + 17, m_Cd, "black");


    index.addLine(30, 31, 50, 31, "yellow");
    index.addLine(30, 29, 50, 29, "yellow");
    index.addLine(30, 30, 50, 30, "black");

    index.addText(66, 36, "Indice de centralite par Degre", "yellow");
    index.addText(64, 34, "Indice de centralite par Degre", "yellow");
    index.addText(65, 35, "Indice de centralite par Degre", "black");
    }


    if(CVP == true)
    {
        ///Arrondie de virgule
        double valeur = m_Cvp;
        int entier = (int)((0.0005 + valeur) * 1000.0);
        double result = (double)entier / 1000.0;
        //float x = m_Cvp;
        if(result >= 0)
            index.addText(m_x*100-16, m_y*100+33, result,"green");
        if(result < 0)
            index.addText(m_x*100-16, m_y*100+33, "nan","green");

        index.addLine(30, 50, 50, 50, "green");
        index.addText(65, 55, "Indice de centralite par Vecteur Propre", "green");
    }

    if(CP == true)
    {
        double valeur = m_Cp;
        int entier = (int)((0.0005 + valeur) * 1000.0);
        double result = (double)entier / 1000.0;
        if(result >= 0)
            index.addText(m_x*100-16, m_y*100+51, result,"blue");
        if(result < 0)
            index.addText(m_x*100-16, m_y*100+51, "inf","blue");

        index.addLine(30, 70, 50, 70, "blue");
        index.addText(65, 75, "Indice de centralite de Proximite", "blue");
    }


    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        index.addLine(m_x*100,m_y*100, m_successeurs[i]->m_x*100, m_successeurs[i]->m_y*100, "black");

        for(size_t j=0 ; j < aretes.size() ; j++)
        {
            aretes[j].DessinerPoids(index, m_indice, m_x, m_y, m_successeurs[i]->m_indice, m_successeurs[i]->m_x, m_successeurs[i]->m_y);
        }

        if(oriente == true) ///Dessin des flèches
        {
            int ArrowLength = 12, ArrowWidth = 8;
            int x1=m_x*100, x2=m_successeurs[i]->m_x*100;
            int y1=m_y*100, y2=m_successeurs[i]->m_y*100;
            int AB=sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            int xC=x2+ArrowLength*(x1-x2)/AB,   yC=y2+ArrowLength*(y1-y2)/AB;
            int xD=xC+ArrowWidth*(-(y2-y1))/AB, yD=yC+ArrowWidth*((x2-x1))/AB;
            int xE=xC-ArrowWidth*(-(y2-y1))/AB, yE=yC-ArrowWidth*((x2-x1))/AB;

            index.addTriangle(xD, yD, xE, yE,x2, y2, "lightgrey",1, "black");
        }
    }
}

void Sommet::Centralite_Degre(int n)
{
    double ordre = m_successeurs.size();
    ordre = ordre / (n-1) ;
    m_Cd = ordre;
}

void Sommet::Somme_Indices()
{
    m_Cvp=0;
    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        m_Cvp += m_successeurs[i]->m_Cvp ;
    }
}
void Sommet::Recalcul_Indices(double lambda, double Csi)
{
    m_Cvp = (Csi)/ lambda ;
}

double Sommet::Csi()
{
    double Csi=0;

    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        Csi += m_successeurs[i]->m_Cvp;
    }

    return Csi;
}



void Sommet::Afficher()
{
    std::cout << m_indice << std::endl;
    std::cout << "Cvp : " << m_Cvp << std::endl;
    std::cout << "Cp : " << m_Cp << std::endl;
    std::cout << "Successeurs : " << std::endl;
    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        std::cout << m_successeurs[i]->m_indice << std::endl;
    }
    std::cout << "---------" << std::endl;
}

void Sommet::Marquage()
{
    m_marque=true;
}

bool Sommet::RechercheSommet(int ind)
{
    bool resultat=false;
    if(ind == m_indice)
        resultat = true;

    return resultat;
}

bool Sommet::Marque()
{
    bool resultat = false;
    if(m_marque == true)
        resultat = true;
    return resultat;
}

void Sommet::Fini(int distance, Sommet* precedent)
{
    m_precedent = precedent;
    m_distance = distance;
}

int Sommet::get_indice()
{
    return m_indice;
}

Sommet* Sommet::Get_precedent()
{
    return m_precedent;
}

void Sommet::Dijkstra( std::vector<double>&distances, std::vector<Sommet*>&sommetprec, std::vector<Sommet*>&sommets, double distance, std::vector<Arete>aretes, Sommet* s, bool oriente)
{
    double poids=0, poids2=0;
    for(size_t i=0 ; i < m_successeurs.size() ; i++)
        {
            if(m_successeurs[i]->Marque() == false)
            {
                for(size_t j=0 ; j < aretes.size() ; j++)
                {
                    poids2 = aretes[j].Recherche_Poids( m_indice, m_successeurs[i]->m_indice, oriente);
                    if(poids2 != 0)
                        poids=poids2;
                }
                distances.push_back( poids + distance);
                sommetprec.push_back(s);
                sommets.push_back(m_successeurs[i]);
            }
        }
}

void Sommet::Reset_Dijkstra()
{
    m_marque = false;
    m_distance = 0;
    m_precedent = NULL;
}

void Sommet::AddCp(double Cp, int n)
{
    m_Cp = Cp;
    m_Cp= m_Cp*(n-1);
}

bool Sommet::TestNombreSuccesseurs()
{
    bool impossible = false;
    if(m_successeurs.size() == 0)
        impossible = true;

    return impossible;
}
