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
    if(distance == m_distance)
        std::cout << "C'EST CA" << std::endl << "distance = " << distance << std::endl << std::endl;


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
                //std::cout << "INDICE : " << m_indice << "  Indice successeur : " << m_successeurs[i]->get_indice() << std::endl;
                for(size_t j=0 ; j < aretes.size() ; j++)
                {
                    poids2 = aretes[j].Recherche_Poids( m_indice, m_successeurs[i]->m_indice, oriente);
                    if(poids2 != 0)
                        poids=poids2;
                }





                // std::cout << "                      Chemin : " << poids+distance  << std::endl;
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

void Sommet::AddPccPrecedent(Sommet* s)
{
    bool idem = false;
    for(size_t i=0 ; i < m_PccPrecedents.size() ; i++)
    {
        if(m_PccPrecedents[i] == s)
            idem = true;
    }
    if(idem == false)
        m_PccPrecedents.push_back(s);
}

void Sommet::AfficherPcc()
{
    std::cout << "Indice : " << m_nom << " PccPrecedent : " << std::endl;
    for(size_t i=0 ; i < m_PccPrecedents.size() ; i++)
    {
        std::cout << "Indice : " << m_PccPrecedents[i]->m_nom << std::endl;
    }
    std::cout << std::endl;
}
/*
void Sommet::TestRec(Sommet* s_depart, int& n, std::vector<int>& liste, double distance, std::vector<Arete>aretes, bool oriente, double& poids)
{


    //std::cout << "IND : " << m_nom << std::endl;
    /// //
    AfficherPcc();
    /// //
    bool stop = false;
    for(size_t j=0 ; j < liste.size() ; j++)
    {
        if((liste[j] == m_indice))
            stop = true;
    }

    if(stop == false)
    {
    liste.push_back(m_indice);


    if(m_PccPrecedents.size() > 0)
        n   +=  m_PccPrecedents.size()-1;
    for(size_t i=0 ; i < m_PccPrecedents.size() ; i++)
    {
        /// ////
        if(liste.size() > 0)
            if((liste[0] == m_PccPrecedents[i]->m_indice))
                stop = true;
        double poids3=0;
        if((stop == false) && (m_indice != s_depart->m_indice))
        {
            poids3 = RechercheAretePoids(aretes, m_indice, m_PccPrecedents[i]->m_indice, oriente);
            poids+=poids3;
        }
        std::cout << m_nom << " -> " << m_PccPrecedents[i]->m_nom << std::endl;
        std::cout << "Poids " << poids << " = " << poids-poids3 << " + " << poids3 << std::endl << std::endl;
        /// ////
        stop=false;


        if(m_indice != s_depart->m_indice)
            m_PccPrecedents[i]->TestRec(s_depart, n, liste, distance, aretes, oriente, poids);

    }
    /// ////
    if((m_indice != s_depart->m_indice) && (m_PccPrecedents.size() == 0))
    {
        double poids3=0;
        if(m_precedent!=NULL)
        {
            poids3 = RechercheAretePoids(aretes, m_indice, m_precedent->m_indice, oriente);
            poids+=poids3;
        }
        std::cout << m_nom << " -> " << m_precedent->m_nom << std::endl;
        std::cout << "Poids " << poids << " = " << poids-poids3 << " + " << poids3 << std::endl << std::endl;
    }
    /// ////


    if((m_indice != s_depart->m_indice) && (m_PccPrecedents.size() == 0))
        m_precedent->TestRec(s_depart, n, liste, distance, aretes, oriente, poids);


    if(m_indice == s_depart->m_indice && n==0)
        n=1;
    }
}*/


void Sommet::TestRec(Sommet* s_depart, int& n, std::vector<int>& liste, double distance, std::vector<Arete>aretes, bool oriente, double poids, Sommet* arrive, Sommet* prec)
{
    if(poids <= arrive->m_distance)
    {
        poids += RechercheAretePoids(aretes, prec->m_indice, m_indice, oriente);
        if( m_indice != s_depart->m_indice )
            liste.push_back(m_indice);

        for(size_t i=0 ; i < m_PccPrecedents.size() ; i++)
        {
            m_PccPrecedents[i]->TestRec( s_depart, n, liste, distance, aretes, oriente, poids, arrive, this);
        }

        if((m_PccPrecedents.size() == 0) && ((m_indice != s_depart->m_indice)))
        {
            m_precedent->TestRec( s_depart, n, liste, distance, aretes, oriente, poids, arrive, this);
        }
        //std::cout << "POIDS = " << poids << " = " << poids-RechercheAretePoids(aretes, prec->m_indice, m_indice, oriente) << " + " << RechercheAretePoids(aretes, prec->m_indice, m_indice, oriente) << std::endl;
        //std::cout << prec->m_nom << " -> " << m_nom << std::endl;

        if(m_indice == s_depart->m_indice)
            n+=1;
    }
}


void Sommet::CalculPccPrec(Sommet* s_depart, std::vector<Arete>aretes, bool oriente)
{
    int n=0;
    std::vector<int> liste;

    ///std::cout << "SOMMET : " << m_nom << std::endl;
    ///std::cout << "Distance : " << m_distance << std::endl;

    double p=0;

    TestRec(s_depart, n, liste, m_distance, aretes, oriente, p, this, this);

   /* for(size_t i=0 ; i < liste.size() ; i++)
    {
        std::cout << " Sommet " << i << " : ";
        switch(liste[i]){
            case 0 : std::cout << "A"; break;
            case 1 : std::cout << "B"; break;
            case 2 : std::cout << "C"; break;
            case 3 : std::cout << "D"; break;
            case 4 : std::cout << "E"; break;
            case 5 : std::cout << "F"; break;
            case 6 : std::cout << "G"; break;
            case 7 : std::cout << "H"; break;
            case 8 : std::cout << "I"; break;}
            std::cout << std::endl;
    }

    std::cout << " Poid Total : " << p << std::endl;*/


    std::cout << "Il y a " << n << " plus courts chemins entre " << s_depart->m_nom << " et " << m_nom << std::endl;

}

double Sommet::RechercheAretePoids(std::vector<Arete> aretes, int ind1, int ind2, bool oriente)
{
    double poids=0, poids2 =0;
    for(size_t i=0 ; i < aretes.size() ; i++)
        {
            poids2 = aretes[i].Recherche_Poids( ind1, ind2, oriente);
            if(poids2 != 0)
            {
                poids = poids2;
            }
        }
    return poids;
}

bool Sommet::TestListe(std::vector<int> liste)
{
    bool stop=false;
    for(size_t j=0 ; j < liste.size() ; j++)
    {
        if((liste[j] == m_indice))
            stop = true;
    }
    return stop;
}

