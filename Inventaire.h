#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include "Objet.h"

struct NoeudI{
    int quantite;
    Objet* objet;
    NoeudI* suivant;
    //double chained -> add Noeud <T>* previous
};

class Inventaire{
private:
    NoeudI* entete;
    int compteur; //indique le nombre de type d'objet (!= de la somme des quantites)
    NoeudI* creerNoeud(Objet* objet);

public:
    Inventaire();
    ~Inventaire();
    Objet* recuperer(string name) const; //recupe l'addresse de l'objet
    void ajouter(Objet* objet); //ajoute un objet a la liste
    void supprimer(string name); //retire un objet de la liste
    void afficher() const;
    int taille() const;
    int getQuantite(string name) const;
};

#endif // INVENTAIRE_H
