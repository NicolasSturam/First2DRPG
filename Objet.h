#ifndef OBJET_H
#define OBJET_H

#include "Profile.h"

class Objet{
public:
    Objet();
    Objet(string name, int valeur, bool bonus, Sts stat);
    ~Objet();
    string getName() const;
    int getValeur() const;
    bool getBonus() const;
    Sts getStat() const;
private:
    string name;
    int valeur; //puissance de l'objet
    bool bonus; //true = effet positif, false = effet negatif
    Sts stat; //statistique affectee. Ex: PV pour potion
};

#endif // OBJET_H
