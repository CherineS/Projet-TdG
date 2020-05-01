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
    m_Ci=0;
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

double Arrondir(double valeur)
{
    int entier = (int)((0.0005 + valeur) * 1000.0);
    double result = (double)entier / 1000.0;

    return result;
}


void Sommet::Dessiner(Svgfile& index, bool oriente, std::vector<Arete>& aretes, bool CVP, bool CD, bool CP, bool CI)
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
        if(m_Cvp >= 0)
            index.addText(m_x*100-16, m_y*100+33, Arrondir(m_Cvp),"green");
        if(m_Cvp < 0)
            index.addText(m_x*100-16, m_y*100+33, "nan","green");

        index.addLine(30, 50, 50, 50, "green");
        index.addText(65, 55, "Indice de centralite par Vecteur Propre", "green");
    }

    if(CP == true)
    {
        if(m_Cp >= 0)
            index.addText(m_x*100-16, m_y*100+51, Arrondir(m_Cp),"blue");
        if(m_Cp < 0)
            index.addText(m_x*100-16, m_y*100+51, "inf","blue");

        index.addLine(30+300+235, 30, 50+300+235, 30, "blue");
        index.addText(65+300-40, 35, "Indice de centralite de Proximite", "blue");
    }

    if(CI == true)
    {
        if(m_Ci >= 0)
            index.addText(m_x*100-16, m_y*100+69, Arrondir(m_Ci),"red");
        if(m_Ci < 0)
            index.addText(m_x*100-16, m_y*100+69, "inf","red");

        index.addLine(30+300+235, 50, 50+300+235, 50, "red");
        index.addText(65+300-40, 55, "Indice de centralite d'Intermediarite", "red");
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
    m_PccPrecedents.clear();
    for(size_t i=0 ; i < m_Pcc.size() ; i++)
    {
        m_Pcc[i].clear();
    }
    m_Pcc.clear();
}

void Sommet::AddCp(double Cp, int n)
{
    m_Cp = Cp;
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

void Sommet::ClearListe2(std::vector<int>& liste2, double poids, Sommet* s_depart, Sommet* s_arrive, bool oriente, std::vector<Arete> aretes, double poidsprec)
{
    if(poids == 0 )
    {
        poidsprec = 0;
        liste2.clear();
    }

    double manquant = 0;
    if(liste2.size() > 0 )
        manquant = RechercheAretePoids(aretes, s_depart->m_indice, liste2[liste2.size()-1], oriente);
    poidsprec += manquant;

    if(liste2.size() >= 1)
    {
        poidsprec -= RechercheAretePoids(aretes, s_depart->m_indice, liste2[liste2.size()-1], oriente);
    }
    while(poidsprec != poids)
    {
        if(liste2.size() == 1)
        {
            poidsprec -= RechercheAretePoids(aretes, liste2[liste2.size()-1], s_arrive->m_indice, oriente);
            liste2.pop_back();
        }
        if(liste2.size() >= 2)
        {
            poidsprec -= RechercheAretePoids(aretes, liste2[liste2.size()-1], liste2[liste2.size()-2], oriente);
            liste2.pop_back();
        }
    }
}



void Sommet::TestRec(Sommet* s_depart, int& n, std::vector<int>& liste, double distance, std::vector<Arete>aretes, bool oriente, double poids, Sommet* arrive, Sommet* prec, double& poidsprec, std::vector<int>& liste2, bool& test)
{
    if(poids <= arrive->m_distance)
    {

        if(poids <= poidsprec)
        {
            if(test == true)
            {
                ClearListe2(liste2, poids, s_depart, arrive, oriente, aretes, poidsprec);
            }
            else{
                ClearListe2(liste2, poids, s_depart, arrive, oriente, aretes, poidsprec);
            }
            test=false;
        }

        poidsprec = poids;

        ///poids += RechercheAretePoids(aretes, prec->m_indice, m_indice, oriente);
        poids += RechercheAretePoids(aretes, m_indice, prec->m_indice, oriente);
        if( m_indice != s_depart->m_indice )
        {
            liste.push_back(m_indice);

            if(m_indice != arrive->m_indice)
                liste2.push_back(m_indice);

        }

        for(size_t i=0 ; i < m_PccPrecedents.size() ; i++)
        {
            m_PccPrecedents[i]->TestRec( s_depart, n, liste, distance, aretes, oriente, poids, arrive, this, poidsprec, liste2, test);
        }

        if((m_PccPrecedents.size() == 0) && ((m_indice != s_depart->m_indice)))
        {
            m_precedent->TestRec( s_depart, n, liste, distance, aretes, oriente, poids, arrive, this, poidsprec, liste2, test);
        }

        if(m_indice == s_depart->m_indice)
            n+=1;

        /// ////
        if(poids == arrive->m_distance && m_indice == s_depart->m_indice)
        {
            ///AfficherListe(liste2); /// OMG CA MARCHE
            arrive->AjouterPcc(liste2, n);
        }
        /// ////

    }
    else{
        test = true;
    }
}


void Sommet::CalculPccPrec(Sommet* s_depart, std::vector<Arete>aretes, bool oriente)
{
    int n=0;
    std::vector<int> liste, liste2;
    double p=0;
    bool test=false;

    if(m_distance > 0)
        TestRec(s_depart, n, liste, m_distance, aretes, oriente, p, this, this, p, liste2, test);

    ///std::cout << "Il y a " << n << " plus courts chemins entre " << s_depart->m_nom << " et " << m_nom << std::endl;
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

void Sommet::AjouterPcc(std::vector<int> liste, int n)
{
    //AfficherListe(liste);
    m_Pcc.push_back(liste);
}

void AfficherListe(std::vector<int> liste2)
{
    for(size_t i=0 ; i < liste2.size() ; i++)
    {
        std::cout << "Parcours : ";
        switch(liste2[i]){
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
    //if(liste2.size() > 0)
    //std::cout << "STOP" << std::endl;
}

void Sommet::AfficherPcc(Sommet* s_depart)
{
    std::cout << "Il y a " << m_Pcc.size() << " plus court(s) chemin(s) entre " << s_depart->m_nom << " et " << m_nom <<std::endl;
    if(m_Pcc.size() > 0)
        std::cout << "Passant(s) par : " << std::endl;
    for(size_t i=0 ; i < m_Pcc.size() ; i++)
    {
        std::cout << "Chemin " << i+1 << " : " <<std::endl;
        AfficherListe(m_Pcc[i]);
    }
    std::cout << "--------------------------------------------------" << std::endl;
}

void Sommet::CalculPcci(Sommet* si, Sommet* s_depart, bool oriente)
{
    double pcci = 0;
    for(size_t i=0 ; i < m_Pcc.size() ; i++)
    {
        for(size_t j=0 ; j < m_Pcc[i].size() ; j++)
        {
            if(s_depart->m_indice < m_indice || oriente == true)
                if(si->m_indice == m_Pcc[i][j])
                    pcci += 1;
        }
    }
    if(m_Pcc.size()>0)
        pcci = pcci / m_Pcc.size();
    si->m_Ci += pcci;
    std::cout << "Le Sommet " << si->m_nom << " apparait " << pcci << " fois entre " << s_depart->m_nom << " et " << m_nom << std::endl;
}

void Sommet::Normaliser(bool Norm_Cd, bool Norm_Cvp, bool Norm_Cp, bool Norm_Ci, int n)
{
    if(Norm_Cd == true)
    {
        m_Cd = m_Cd / (n-1) ;
    }
    if(Norm_Cvp == true)
    {

    }
    if(Norm_Cp == true)
    {
        m_Cp = m_Cp*(n-1) ;
    }
    if(Norm_Ci == true)
    {
        m_Ci = 2 * m_Ci / ((n*n) - (3*n) + 2) ;
    }
}

