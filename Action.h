#ifndef ACTION_H
#define ACTION_H

enum TypeArme{
    FORCE, DEXTERITE
};

enum TypeMagie{
    INTELLIGENCE, SAGESSE
};

enum Type { //pour le ciblage
    Offensive, Defensive
};

enum TypeDegat { NEUTRE,
TRANCHANT, PERCANT, CONTONDANT,
EXPLOSIF,
SOIN,
};

enum Element { NONE,
 FEU, GLACE, FOUDRE, AIR, EAU, TERRE,
 LUMIERE, TENEBRES};

enum Etat { AUCUN,
//Negatifs
 POISON, VENIN, SEIGNEMENT, HEMORRAGIE, GLAS, MORT, //perte de PV
 ETOURDISSEMENT, SOMMEIL, PARALYSIE, ATERRE, PETRIFICATION, FOSSILE, STASE,//perte de tours
 ZOMBIE, CONTROLE, METAMORPHOSE, TERREUR, FOLIE, //perte de controle totale du perso
 SILENCE, HANDICAP, COLERE, CECITE, ENTRAVE, //empeche d'utiliser certaines actions
 FAIBLESSE, DEFAILLANCE, FRAGILITE, VULNERABILITE, MALEDICTION, LENTEUR, TRISTESSE, MINI, MALADIE,//diminution de stats
//Positifs
 RECUP, SAIGNEE, AUREOLE, //influe sur la vie
 BRAVOURE, FOI, BARRIERE,  AURA, VOLONTE, VOILE, CELERITE, //augmentation de stat
 ANTIFEU, ANTIGLACE, ANTIFOUDRE, ANTIVENT, ANTIEAU, ANTILUMIERE, ANTITENEBRES, //resistance elementaire
 BOUCLIER, INVISIBLE, LEVITATION, INVINCIBLE, //Protection
 DOUBLE, TRIPLE, QUINTUPLE, //lancement de sort multiple
//Neutre
 ENDOFEU, ENDOGLACE, ENDOFOUDRE, ENDOVENT, ENDOEAU, //attaque a l'arme elementaire
 FURIE, MIROIR //Booste l'attaque mais attaque un ennemi aleatoire uniquement a l'arme
};

enum FleauElementaire { ZERO,
    BRULURE, GELURE, CONGELATION, CHARGE, SUFFOCATION, CHANCELEMENT
};

#endif // ACTION_H
