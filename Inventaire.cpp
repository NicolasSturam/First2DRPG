#include <iostream>
#include "Inventaire.h"

Inventaire::Inventaire(){
    this->entete = NULL;
    this->compteur = 0;
}

Inventaire :: ~Inventaire(){
    NoeudI* del = entete;
    while (entete){
        entete = entete -> suivant;
        delete del;
        del = entete;
    }
}

//On cree un nouveau noeud pour un objet qui n'existe pas encore dans la liste
NoeudI* Inventaire :: creerNoeud(Objet* objet){
    NoeudI* temp = new NoeudI;
    temp -> objet = objet;
    temp -> suivant = NULL;
    temp -> quantite = 1;

    return temp;
}

int Inventaire :: taille() const{
    return compteur;
}

//L'objet est ajoute. S'il est deja present, la quantite est augmentee de 1
// et l'objet passe en argument est detruit
void Inventaire :: ajouter(Objet* objet){
    //On parcout la liste pour regarder si l'objet existe deja
    NoeudI* courant = entete;
    for(int i=0; i < this->compteur; i++){
        if(objet->getName() == courant->objet->getName()){
            courant->quantite++;
            return;
        }
        courant = entete->suivant;
    }
    //Si l'objet n'a pas ete trouve, on va l'ajouter en debut de liste
    NoeudI* nouveau = creerNoeud(objet);
    nouveau -> suivant = entete;
    entete = nouveau;
    compteur++;
    return;
}

//Reduit la quantite de l'objet de 1
//Si elle atteint 0, l'objet est detruit et retire de la liste
void Inventaire:: supprimer(string name){
    //On parcout la liste pour trouver l'objet
    NoeudI* courant = entete;
    NoeudI* previous = NULL;
    for(int i=0; i < this->compteur; i++){
        if(name == courant->objet->getName()){
            courant->quantite--;
            if(courant->quantite == 0){
                delete courant->objet;
                if(i==0){ //debut de liste
                    this->entete = courant->suivant;
                }
                else if(i==compteur-1){//en fin de liste
                    previous->suivant = NULL;
                }
                else{ //en milieu de liste
                    previous->suivant = courant->suivant;
                }
                delete courant;
                compteur--;
            }
            return;
        }
        previous = courant;
        courant = courant->suivant;
    }
    return ; //Si on a atteint le bout de la liste sans trouver l'objet
}

void Inventaire :: afficher() const{
    if(this-> compteur==0){
        cout << "Aucun objet dans l'inventaire.\n" << endl;
        return;
    }
    NoeudI* courant = entete;
    while(courant != NULL){
        printf("%s x%d \n", courant->objet->getName().c_str(), courant->quantite);
        courant = courant -> suivant;
    }
}

Objet* Inventaire :: recuperer(string name) const{
    NoeudI* courant = entete;
    for(int i=0;i < this->compteur; i++){
        if(courant->objet->getName() == name){
            return courant->objet;
        }
    }
    return NULL; //L'objet n'a pas ete trouve dans la liste
}

int Inventaire::getQuantite(string name)const{
    NoeudI* courant = this->entete;
    for(int i=0;i < this->compteur; i++){
        if(courant->objet->getName() == name){
            return courant->quantite;
        }
        else{
            courant = courant->suivant;
        }
    }
    return 0; //l'objet n'a pas ete trouve dans la liste;
}
