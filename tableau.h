/* Squelette pour classe générique Tableau<T>.
 * Lab3 -- Tableau dynamique générique
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * http://ericbeaudry.uqam.ca/INF3105/lab3/
 */

#if !defined(_TABLEAU___H_)
#define _TABLEAU___H_

#include <assert.h>

template <class T>
class Tableau{

  public:
    Tableau(int capacite_initiale=4);
    Tableau(const Tableau<T>&);
    ~Tableau();

    // Ajouter un element à la fin
    void           ajouter(const T& element);
    // Vider le tableau
    void           vider();
    // Retourne le nombre d'éléments dans le tableau
    int            taille() const;

    // Insère element à position index. Les éléments à partir de index sont décalés d'une position.
    void           inserer(const T& element, int index=0);

    // Enlève l'element à position index. Les éléments après index sont décalés d'une position.
    void           enlever(int index=0);

    // Enlève le dernier éléments.
    void           enlever_dernier();

    // Cherche et retourne la position de l'élément. Si non trouvé, retourne -1.
    int            chercher(const T& element);

    const T&       operator[] (int index) const;
    T&             operator[] (int index);

    bool           operator == (const Tableau<T>& autre) const;
    Tableau<T>&    operator = (const Tableau<T>& autre);

    Tableau<T>&    operator += (const Tableau<T>& autre);
    Tableau<T>     operator + (const Tableau<T>& autre) const;
    void           trier();

  private:
    T*             elements;
    int            nbElements;
    int            capacite;
};


// ---------- Définitions -------------


template <class T>
Tableau<T>::Tableau(int capacite_)
{
    capacite = capacite_;
    nbElements = 0;
    elements = new T[capacite];
}

template <class T>
Tableau<T>::Tableau(const Tableau& autre)
{
    nbElements = autre.nbElements;
    capacite = autre.capacite;
    elements = new T[capacite];
    for(int i = 0; i < nbElements; i++){
        elements[i] = autre.elements[i];
    }
}

template <class T>
Tableau<T>::~Tableau()
{
    delete[] elements;
    elements = nullptr;
}

template <class T>
int Tableau<T>::taille() const
{
    return nbElements;
}

template <class T>
void Tableau<T>::ajouter(const T& item)
{
    if(nbElements >= capacite){
        capacite *= 2;
        T* temp = new T[capacite];
        for(int i = 0; i < nbElements; i++){
            temp[i] = elements[i];
        }
        delete[] elements;
        elements = temp;
    }
    elements[nbElements++] = item;
}

template <class T>
void Tableau<T>::inserer(const T& element, int index)
{
    if(nbElements >= capacite){
        capacite *= 2;
        T* temp = new T[capacite];
        for(int i = 0; i < nbElements; i++){
            temp[i] = elements[i];
        }
        delete[] elements;
        elements = temp;
    }
    nbElements++;
    for(int i = nbElements; i > index; i--){
        elements[i] = elements[i-1];
    }
    elements[index] = element;
}

template <class T>
void Tableau<T>::enlever(int index)
{
    nbElements--;
    for(int i = 0; i < nbElements; i++){
        if(i >= index){
            elements[i] = elements[i+1];
        }
    }
}

template <class T>
void Tableau<T>::enlever_dernier()
{
    nbElements--;
}

template <class T>
int Tableau<T>::chercher(const T& element)
{
    for(int i = 0; i < nbElements; i++){
        if(elements[i] == element)
            return i;
    }
    return -1;
}

template <class T>
void Tableau<T>::vider()
{
    nbElements = 0;
}

template <class T>
const T& Tableau<T>::operator[] (int index) const
{
    assert(index < nbElements);
    return elements[index];
}

template <class T>
T& Tableau<T>::operator[] (int index)
{
    assert(index < nbElements);
    return elements[index];
}

template <class T>
Tableau<T>& Tableau<T>::operator = (const Tableau<T>& autre)
{
    if(elements != autre.elements){
        nbElements = autre.nbElements;
        capacite = autre.capacite;

        delete[] elements;
        elements = new T[capacite];

        for(int i = 0; i < nbElements; i++){
            elements[i] = autre.elements[i];
        }
    }
    return *this;
}

template <class T>
bool Tableau<T>::operator == (const Tableau<T>& autre) const
{
    if(nbElements != autre.nbElements) return false;
    if(elements == autre.elements) return true;
    for(int i = 0; i < nbElements; i++){
        if(elements[i] != autre.elements[i]) return false;
    }
    return true;
}

template <class T>
Tableau<T>& Tableau<T>::operator += (const Tableau<T>& autre)
{
    int tempNbElements = nbElements + autre.nbElements;
    while(capacite < tempNbElements){
        capacite *= 2;
    }
    T* temp = new T[capacite];
    for(int i = 0; i < nbElements; i++){
        temp[i] = elements[i];
    }
    for(int i = nbElements; i < autre.nbElements + nbElements; i++){
        temp[i] = autre.elements[i - nbElements];
    }
    delete[] elements;
    elements = temp;
    nbElements += autre.nbElements; 

    return *this;
}

template <class T>
Tableau<T> Tableau<T>::operator + (const Tableau<T>& autre) const
{
    Tableau temp;
    for(int i = 0; i < nbElements; i++){
        temp.ajouter(elements[i]);
    }
    for(int i = 0; i < autre.nbElements; i++){
        temp.ajouter(autre.elements[i]);
    }
    return temp;
}

template <class T>
void Tableau<T>::trier ()
{
    T temp;
    int i = 0;
    int j = 0;
    int nbPlusPetit = 0;
    for(i = 0; i < nbElements; i++){
        temp = elements[i];
        nbPlusPetit = i;
        for(j = i; j < nbElements; j++){
            if(temp >= elements[j]){
                temp = elements[j];
                nbPlusPetit = j;
            }
        }
        elements[nbPlusPetit] = elements[i];
        elements[i] = temp;
    }
}

#endif //define _TABLEAU___H_
