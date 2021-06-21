/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Été 2021 / TP2
 *  http://ericbeaudry.uqam.ca/INF3105/tp2/         
 */
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "personne.h"
#include "tableau.h"
#include "coutTemp.h"

int tp2(std::istream &entree);
void meilleurCout(const Tableau<Personne> &t);
double calculerMeilleurDistance(Personne& p1, const Personne& p2, double meilleurCout);
CoutTemp calculerDistanceNormal(Tableau<Personne>& t);
CoutTemp calculerDistanceNormalAvecPret(Personne& p1, const Personne& p2);
std::string meilleurRecommendation(const Personne& p1, const Personne& p2);
std::string meilleurRecommendationPret(const Personne& p1, const Personne& p2);
Heure calculerTemp(const double& distance);
Heure calculerHeureDepart(const double& distance, const Heure& h1, const Heure& h2);

// argc: nombre d'arguments passés.
// argv: tableau de chaines de carractères.
// exemple: ./tp2 test00.txt
//   ==> argc=2; argv[0]="./tp2"; argv[1]="test00.txt"
int main(int argc, const char **argv)
{
    if (argc > 1)
    {
        std::ifstream fichier_entree(argv[1]);
        if (fichier_entree.fail())
        {
            std::cerr << "Erreur de lecture du fichier '" << argv[1] << "'" << std::endl;
            return 1;
        }
        return tp2(fichier_entree);
    }
    else
    {
        // Pas d'argument requêtes ==> lecture depuis l'entrée standard avec std::cin.
        return tp2(std::cin);
    }
}

int tp2(std::istream &entree_requetes)
{
    //Structure pour stocker les personnes. Il est conseiller d'utiliser un Tableau.
    //Tableau<UneClasse> unevariable;
    Tableau<Personne> t;
    //Lecture
    while (entree_requetes && !entree_requetes.eof())
    {
        Personne p;

        // Lecture d'une personne
        entree_requetes >> p >> std::ws;
        t.ajouter(p);
    }
    meilleurCout(t);

    return 0;
}

double methodeRecursive(int i, const Tableau<Personne>& t, Personne p1, Personne p2, int meilleurCout ){
    meilleurCout = 2 * distance(p1.o, p1.d);
    meilleurRecommandation = "+" + p1.nom + "-" + p1.nom + "\t" + "+" + p1.nom + "-" + p1.nom + "\t";
    p1.liste = meilleurRecommandation;
    for (int j = 0; j < t.taille(); j++)
    {
        if (i != j)
        {
            Personne pAutre = t[j];
            meilleurCout = methodeRecursive(i+1, t, p1, p2, meilleurCout);
        }
    }
    return 2.0;
}

void meilleurCout(const Tableau<Personne> &t)
{
    double meilleurCout = 0;
    std::string meilleurRecommandation = "";
    for (int i = 0; i < t.taille(); i++)
    {
        Personne p1 = t[i];
        meilleurCout = 2 * distance(p1.o, p1.d);
        meilleurRecommandation = "+" + p1.nom + "-" + p1.nom + "\t" + "+" + p1.nom + "-" + p1.nom + "\t";
        p1.liste = meilleurRecommandation;
        for (int j = 0; j < t.taille(); j++)
        {
            if (i != j)
            {
                Personne p2 = t[j];
                meilleurCout = calculerMeilleurDistance(p1, p2, meilleurCout);
            }
        }
        std::cout << p1.nom << ":\t"
                  << p1.liste
                  << std::round(meilleurCout) << 'm'
                  << std::endl;
    }
}

double calculerMeilleurDistance(Personne& p1, const Personne& p2, double meilleurCout){
    CoutTemp ct1 = calculerDistanceNormal(p1, p2);
    if(p1.pretVoiture == 'N'){
        if(ct1.obtenirDistance() < meilleurCout && ct1.obtenirSansRetard()){
            p1.liste = meilleurRecommendation(p1, p2);
            return ct1.obtenirDistance();
        }
        return meilleurCout;
    }
    CoutTemp ct2 = calculerDistanceNormalAvecPret(p1, p2);
    if(meilleurCout < ct1.obtenirDistance() && meilleurCout < ct2.obtenirDistance())
        return meilleurCout;

    if(!ct1.obtenirSansRetard() && !ct2.obtenirSansRetard())
        return meilleurCout;

    if(ct1.obtenirSansRetard() && ct2.obtenirSansRetard()){
        if(ct1.obtenirDistance() < ct2.obtenirDistance()){
            if(ct1.obtenirDistance() < meilleurCout){
                p1.liste = meilleurRecommendation(p1, p2);
                return ct1.obtenirDistance();
            }
        }
        else{
            if(ct2.obtenirDistance() < meilleurCout){
                p1.liste = meilleurRecommendationPret(p1, p2);
                return ct2.obtenirDistance();
            }
        }
        return meilleurCout;
    }
    if(ct1.obtenirSansRetard()){
        if(!(meilleurCout < ct1.obtenirDistance())){
            p1.liste = meilleurRecommendation(p1, p2);
            return ct1.obtenirDistance();
        }
        return meilleurCout;
    }
    else{
        if(!(meilleurCout < ct2.obtenirDistance())){
            p1.liste = meilleurRecommendationPret(p1, p2);
            return ct2.obtenirDistance();
        }
        return meilleurCout;
    }
}

CoutTemp calculerDistanceNormal(Tableau<Personne>& t){
    Heure h;
    double distanceTotale = 0.0;
    double distanceCourante = 0.0;
    //aller
    h = calculerHeureDepart(distanceCourante, t, 0);
    distanceCourante = distance(p2.o, p2.d);
    distanceTotale += distanceCourante;
    h = h + calculerTemp(distanceCourante);
    if(p2.tabHeures[1] < h)
        return CoutTemp(distanceTotale, false);
    distanceCourante = distance(p2.d, p1.d);
    distanceTotale += distanceCourante;
    h = h + calculerTemp(distanceCourante);
    if(p1.tabHeures[1] < h)
        return CoutTemp(distanceTotale, false);
    
    //retour
    distanceCourante = distance(p1.d, p2.d);
    distanceTotale += distanceCourante;
    h = calculerHeureDepart(distanceCourante, p1.tabHeures[2], p2.tabHeures[2]);
    distanceCourante = distance(p2.d, p2.o);
    distanceTotale += distanceCourante;
    h = h + calculerTemp(distanceCourante);
    if(p2.tabHeures[3] < h)
        return CoutTemp(distanceTotale, false);
    distanceCourante = distance(p2.o, p1.o);
    distanceTotale += distanceCourante;
    h = h + calculerTemp(distanceCourante);
    if(p1.tabHeures[3] < h)
        return CoutTemp(distanceTotale, false);
    distanceTotale = distanceTotale - 2 * distance(p2.o, p2.d);
    return CoutTemp(distanceTotale, true);
}

CoutTemp calculerDistanceNormalAvecPret(Personne& p1, const Personne& p2){
    Heure h;
    double distanceTotale = 0.0;
    double distanceCourante = 0.0;
    //aller
    distanceCourante = distance(p1.o, p2.o);
    distanceTotale = distanceCourante;
    h = calculerHeureDepart(distanceCourante, p1.tabHeures[0], p2.tabHeures[0]);
    distanceCourante = distance(p2.o, p1.d);
    distanceTotale += distanceCourante;
    h = h + calculerTemp(distanceCourante);
    if(p1.tabHeures[1] < h)
        return CoutTemp(distanceTotale, false);
    distanceCourante = distance(p1.d, p2.d);
    distanceTotale += distanceCourante;
    h = h + calculerTemp(distanceCourante);
    if(p2.tabHeures[1] < h)
        return CoutTemp(distanceTotale, false);
    
    //retour
    distanceCourante = distance(p2.d, p1.d);
    distanceTotale += distanceCourante;
    h = calculerHeureDepart(distanceCourante, p2.tabHeures[2], p1.tabHeures[2]);
    distanceCourante = distance(p1.d, p2.o);
    distanceTotale += distanceCourante;
    h = h + calculerTemp(distanceCourante);
    if(p2.tabHeures[3] < h)
        return CoutTemp(distanceTotale, false);
    distanceCourante = distance(p2.o, p1.o);
    distanceTotale += distanceCourante;
    h = h + calculerTemp(distanceCourante);
    if(p1.tabHeures[3] < h)
        return CoutTemp(distanceTotale, false);
    distanceTotale = distanceTotale - 2 * distance(p2.o, p2.d);
    return CoutTemp(distanceTotale, true);
}

std::string meilleurRecommendation(const Personne& p1, const Personne& p2){
    std::string meilleurRecommandation = "";
    meilleurRecommandation = "+" + p1.nom;
    meilleurRecommandation += "+" + p2.nom;
    meilleurRecommandation += "-" + p2.nom;
    meilleurRecommandation += "-" + p1.nom + "\t";
    meilleurRecommandation += "+" + p1.nom;
    meilleurRecommandation += "+" + p2.nom;
    meilleurRecommandation += "-" + p2.nom;
    meilleurRecommandation += "-" + p1.nom + "\t";
    return meilleurRecommandation;
}

std::string meilleurRecommendationPret(const Personne& p1, const Personne& p2){
    std::string meilleurRecommandation = "";
    meilleurRecommandation = "+" + p1.nom;
    meilleurRecommandation += "+" + p2.nom;
    meilleurRecommandation += "-" + p1.nom;
    meilleurRecommandation += "-" + p2.nom + "\t";
    meilleurRecommandation += "+" + p2.nom;
    meilleurRecommandation += "+" + p1.nom;
    meilleurRecommandation += "-" + p2.nom;
    meilleurRecommandation += "-" + p1.nom + "\t";
    return meilleurRecommandation;
}

Heure calculerHeureDepart(double& distanceTotale, const Tableau<Personne>& t, int moment){
    double distanceCourante = 0.0;
    Heure heureCourante = t[0].tabHeures[moment];
    for(int i = 0; i < t.taille() - 1; i++){
        distanceCourante = distance(t[i].o, t[i+1].o);
        distanceTotale += distanceCourante;
        Heure h = calculerTemp(distanceCourante);
        if(t[i + 1].tabHeures[moment] < (heureCourante + h)){
            heureCourante = t[i].tabHeures[moment] + h;
        }
        else{
            heureCourante = t[i + 1].tabHeures[moment];
        }
    }
    return heureCourante;
}

Heure calculerTemp(const double& distance){
    Heure h;
    double tempEnSec = distance / 10;
    double minute = double(int(tempEnSec) % 3600) / 60;
    h.heures = tempEnSec / 3600;
    h.minutes = std::floor(double(int(tempEnSec) % 3600) / 60);
    h.secondes = std::ceil((minute - h.minutes)*60);
    return h;
}