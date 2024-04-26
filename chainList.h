#ifndef CHAINLIST_H
#define CHAINLIST_H

#include <iostream>
#include <cassert>

using namespace std;

//Definition du noeud
template <typename T>
struct Noeud{
    T donnees;
    Noeud <T>* suivant;
    //double chained -> add Noeud <T>* previous
};

//Classe Liste
template <typename T>
class Liste{
private:
    Noeud <T>* entete;
    int compteur;
    Noeud <T>* creerNoeud(T valeur);
    Noeud <T>* creerNoeud(T* valeur);

public:
    Liste();
    ~Liste();
    void inserer(int pos, T valeur);
    void inserer(int pos, T* valeur);
    void supprimer(int pos);
    T* getNoeud(int pos) const;
    T getNoeud2(int pos) const;
    void afficher() const;
    int taille() const;
};

#endif // CHAINLIST_H
