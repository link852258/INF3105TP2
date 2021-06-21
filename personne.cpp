/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Été 2021 / TP2
 *  http://ericbeaudry.uqam.ca/INF3105/tp2/         
 */
#include <cassert>
#include "personne.h"

std::istream& operator >> (std::istream& is, Personne& p){
    // À compléter.
    std::string s;
    char c;
    // lire nom, nombre de passagers, l'acceptation de prêter le véhicule
    is >> p.nom >> p.nbPassagers >> c;
    p.pretVoiture = c;
    // lire l'origine (résidence) et la destination (travail / étude)
    is >> p.o >> s >> p.d;
    assert(s == "-->"); // robustesse
    Heure h;
    // lire les contraintes de temps (4 heures)
    for(int i = 0; i < 4; i++){
        is >> h;
        h.secondes = 0;
        p.tabHeures.ajouter(h);
    }

    // lire le point-virgule de fin de ligne
    is >> c;
    assert(c== ';'); // robustesse
    return is;
}

std::ostream& operator << (std::ostream& os, const Personne& p){
     // À compléter si vous en avez besoin.
    return os;
}

