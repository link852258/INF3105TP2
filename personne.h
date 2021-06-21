/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Été 2021 / TP2
 *  http://ericbeaudry.uqam.ca/INF3105/tp2/         
 */

#if !defined(__PERSONNE_H__)
#define __PERSONNE_H__

#include <iostream>
#include "heure.h"
#include "pointst.h"
#include "tableau.h"

class Personne{
  public:
	// À compléter.
	
	// La suite n'est pas nécessairement la bonne façon de procéder.
	PointST o, d;
	std::string nom;
  std::string liste;
  int nbPassagers;
  char pretVoiture;
  Tableau<Heure> tabHeures;
  private:
	// À compléter.

  friend std::istream& operator >> (std::istream&, Personne&);
  friend std::ostream& operator << (std::ostream&, const Personne&);
};

#endif

