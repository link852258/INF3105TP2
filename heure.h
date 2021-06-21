/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Été 2021 / TP2
 *  http://ericbeaudry.uqam.ca/INF3105/tp2/         
 */
#if !defined(__HEURE_H__)
#define __HEURE_H__

#include <iostream>

class Heure{
  public:
	// À compléter.

    Heure&    operator =(const Heure& h);
    bool      operator <(const Heure& h) const;
    bool      operator <=(const Heure& h) const;
    Heure     operator +(const Heure& h)const;
    int       minutes;
    int       heures;
    int       secondes = 0;
  private:
	// À compléter.
  friend std::istream& operator >> (std::istream&, Heure&);
  friend std::ostream& operator << (std::ostream&, const Heure&);
};

#endif

