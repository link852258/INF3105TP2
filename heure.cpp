/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Été 2021 / TP2
 *  http://ericbeaudry.uqam.ca/INF3105/tp2/         
 */
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include "heure.h"

Heure &Heure::operator=(const Heure &h)
{
    this->heures = h.heures;
    this->minutes = h.minutes;
    this->secondes = h.secondes;
    return *this;
}

bool Heure::operator<(const Heure &h) const
{
    if (this->heures < h.heures)
    {
        return true;
    }
    else if (this->heures == h.heures)
    {
        if (this->minutes < h.minutes)
        {
            return true;
        }
        else if (this->minutes == h.minutes)
        {
            if (this->secondes < h.secondes)
            {
                return true;
            }
        }
    }
    return false;
}

Heure Heure::operator+(const Heure &h) const
{
    Heure hr;
    hr.heures = 0;
    hr.minutes = 0;
    hr.secondes = 0;

    if ((this->secondes + h.secondes) >= 60)
    {
        hr.minutes += 1;
        hr.secondes = this->secondes + h.secondes - 60;
    }
    else{
        hr.secondes = this->secondes + h.secondes;
    }

    if ((this->minutes + h.minutes + hr.minutes) >= 60)
    {
        hr.heures = this->heures + h.heures + 1;
        hr.minutes += this->minutes + h.minutes - 60;
    }
    else
    {
        hr.heures = this->heures + h.heures;
        hr.minutes += this->minutes + h.minutes;
    }

    return hr;
}

bool Heure::operator<=(const Heure &h) const
{
    if (this->heures < h.heures)
    {
        return true;
    }
    if (this->heures == h.heures)
    {
        if (this->minutes <= h.minutes)
            return true;
    }
    return false;
}

std::istream &operator>>(std::istream &is, Heure &heure)
{
    // À compléter.
    char h;
    is >> heure.heures >> h >> heure.minutes;
    if (!is)
        return is;
    assert(h == 'h' || h == 'H'); // pour robustesse: valider le caractère 'h'
    return is;
}

std::ostream &operator<<(std::ostream &os, const Heure &h)
{
    // À compléter.
    char chaine[40];
    sprintf(chaine, "%02dh%02d", h.heures, h.minutes);
    os << chaine;
    return os;
}
