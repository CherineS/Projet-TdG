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


void Sommet::Dessiner(Svgfile& index, bool oriente, std::vector<Arete>& aretes, bool CVP, bool CD)
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


    index.addLine(30, 51, 50, 51, "yellow");
    index.addLine(30, 49, 50, 49, "yellow");
    index.addLine(30, 50, 50, 50, "black");

    index.addText(65, 55, "Indice de centralite par degre", "black");
    }


    if(CVP == true)
    {
        ///Arrondie de virgule
        double valeur = m_Cvp;
        int entier = (int)((0.0005 + valeur) * 1000.0);
        double result = (double)entier / 1000.0;
        //float x = m_Cvp;
        index.addText(m_x*100-16, m_y*100+33, result,"green");

        index.addLine(30, 70, 50, 70, "green");
        index.addText(65, 75, "Indice de centralite par Vecteur Propre", "green");
    }


    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        index.addLine(m_x*100,m_y*100, m_successeurs[i]->m_x*100, m_successeurs[i]->m_y*100, "black");

        for(size_t j=0 ; j < aretes.size() ; j++)
        {
            aretes[j].DessinerPoids(index, m_indice, m_x, m_y, m_successeurs[i]->m_indice, m_successeurs[i]->m_x, m_successeurs[i]->m_y);
        }

        if(oriente == true) ///Dessin des fl�ches
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
    std::cout << "Successeurs : " << std::endl;
    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        std::cout << m_successeurs[i]->m_indice << std::endl;
    }
    std::cout << "---------" << std::endl;
}

int Sommet::getIndice()
{
    return m_indice;
}

char Sommet::getNom()
{
    return m_nom;
}

bool Sommet::getMarquage()
{
    return m_marque;
}

void Sommet::setMarquage(bool marque)
{
    m_marque=marque;
}

void Sommet::ResetMarquage()
{
    for(size_t i=0 ; i < m_successeurs.size() ; i++)
    {
        m_successeurs[i]->m_marque=false;
    }
}

void Sommet::BFSrecursif(std::vector<int> &Queue, int compteur)
{
    std::vector<int> temp;

    bool present=0;

    for(size_t i=0;i<m_successeurs.size();++i)
    {
        for(size_t j=0;j<Queue.size();++j)
        {
            present=0;
            if(m_successeurs[i]->getMarquage()==true)   ///Si le sommet est marque (parcouru) on ne l'ajoute pas
            {
                present=1;
                break; ///Pas besoin d'aller plus loin
            }
        }
        if(present!=1)
        {
            Queue.push_back(m_successeurs[i]->getIndice());
            m_successeurs[i]->setMarquage(true);
            //std::cout << "\ns pushed back " << m_successeurs[i]->getIndice();
            temp.push_back(i);
        }
    }

    if(present!=1)
    {
        ++compteur;
        for(size_t j=0;j<temp.size();++j)
        {
            m_successeurs[temp[j]]->BFSrecursif(Queue, compteur);
        }
    }
}
