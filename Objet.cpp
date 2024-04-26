#include "Objet.h"

//Constructeur par defaut
Objet::Objet(){
    this->name = "Rien";
    this->valeur = 0;
    this->bonus = true;
    this->stat = PV;
}

Objet::Objet(string name, int valeur, bool bonus, Sts stat){
    this->name = name;
    this->valeur = valeur;
    this->bonus = bonus;
    this->stat = stat;
}

Objet :: ~Objet(){
}

string Objet::getName() const{
    return this->name;
}

int Objet::getValeur() const{
    return this->valeur;
}

bool Objet::getBonus() const{
    return this->bonus;
}

Sts Objet::getStat() const{
    return this->stat;
}
