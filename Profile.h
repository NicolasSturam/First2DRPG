#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <SDL.h>

using namespace std;

#include "Texture.h"
#include "chainList.cpp"
#include "Magie.h"
#include "Technique.h"



//Augmentable en montant de niveau
struct Attributs{
    int force;
    /*
    Force : Représente la musculature et la force physique
    + degats armes bases sur la force
    + multCrit
    + pvMax
    o poids max transportable
    */
    int dext;
    /*
    Dextérité : Représente l'agilité, la précision et les réflexes
    + degats armes bases sur la dex
    + prc
    + crit
    + esq
    + init
    */
    int cons;
    /*
    Constitution : Représente la santé physique
    Augmente modéremment les dégâts physiques
    + pvMax
    + regPv
    + res aux alterations
    + dégâts physiques
    */
    int intel;
    /*
    Intelligence : Représente la finesse d'esprit et la capacité de déduction
    + puissance des sorts basés sur l'intelligence
    + pmMax
    + init
    */
    int sag;
    /*
    Sagesse : Représente les connaissances, la compassion, le jugement, la perception
    + puissance des sorts basés sur la sagesse
    + res aux alterations
    + esq
    */
    int chc;
    /*
    Chance : Représente la chance, a quel point le destin est favorable
    Augmente les chances de réussites d'action diverses
    + prc
    + esq
    + crit
    + reduction des chances de subir des crit
    + chance de loot
    */
//Uniquement augmentable via le stuff
    int deter;
    /*
    Détermination : A augmenter pour un role plus offensif
    + degats (physiques et magiques)
    + prc
    + crit
    */
    int tena;
    /*
    Tenacité : A augmenter pour un role plus defensif
    + résistances
    + pvMax
    + init
    */
    int piete;
    /*
    Piété : A augmenter pour un role de soigneur
    + puissance des soins
    + regPm
    + pmMax
    */
};

struct Stats{
    int pv;
    int pvMax;
    /*
    Augmenté par :
        * Force
        * Constitution
        * Tena
    */
    int regPv;
    /*
    Augmenté par :
        * Constitution
    */
    int pm;
    int pmMax;
    /*
    Augmenté par :
        * Intelligence
        * Piété
    */
    int regPm;
    /*
    Augmenté par :
        * Piété
    */
    int init;
    /*
    Augmenté par :
        * Dextérité
        * Intelligence
        * Tena
    */
    int atq;
     /*
    Augmenté par :
        * Force ou Dextérité
        * Constitution
        * Détermination
    */
    int magieNoire;
     /*
    Augmenté par :
        * Intelligence
        * Détermination
    */
    int magieBlanche;
    /*
    Augmenté par :
        * Sagesse
        * Détermination
        * Piete
    */
    int prc;
    /*
    Augmenté par :
        * Dextérité
        * Chance
        * Détermination
    */
    int esq;
    /*
    Augmenté par :
        * Dextérité
        * Sagesse
        * Chance
    */
    int crit;
    /*
    Augmenté par :
        * Dextérité
        * Chance
        * Détermination
    */
    int multCrit;
    /*
    Augmenté par :
        * Force
    */
};


struct Resistances{
    //resistance : entre 0 - 100
    // > 100, la difference est abosrbee en pv
    //La Tenacite augmente les resistances
    int resTranchant;
    int resPercant;
    int resContondant;
    int resExplosion;

    int resFeu;
    int resGlace;
    int resFoudre;
    int resAir;
    int resEau;
    int resTerre;
    int resLumiere;
    int resTenebres;

    int resAlterations;
    /*
    Augmenté par:
        * Constitution
        * Sagesse
    */
    int resCrit;
    /*
    Augmenté par :
        * Chance
    */
};

enum Sts {PV, PM, INIT, ATQ, MAG, DEF};

enum Animation {IDLE, WAIT, ATTACK, TECHNIQUE, HURT, WALK, PREPARE, DEATH, MAGIE, OBJET, DEFENDRE, AVANCER, RECULER, FUIR};
//WAIT permet d'attendre qu'une action externe se finisse
enum Operation {Add, Substract, Multiply, Divide};

enum TypeTarget {ALLIE, ENNEMI};

//Genere un nombre aleatoire entre 0 et N-1
int randomNumber100();

int calculerDegats();

class Profile : public Texture{

public:
    Profile();   //constructeur par defaut
    Profile(string name, string path, SDL_Renderer* renderer, SDL_Rect rect, bool type = false);
    ~Profile();
    void setArcher(SDL_Rect* collider);
    void setVoleur(SDL_Rect* collider);
    void setSamourai(SDL_Rect* collider);
    void setElementaliste(SDL_Rect* collider);
    void setNinja(SDL_Rect* collider);
    void setChevalier(SDL_Rect* collider);
    void setBretteur(SDL_Rect* collider);

    bool render(SDL_Renderer* renderer, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    bool attaquer(Profile* cible, int* degats, TypeDegat tDegat=TRANCHANT, Element e=NONE);

    bool lancerMagie(Profile* cible, Magie* magie, int* degats);

    void seDefendre();

    //void
    //Accesseurs
    const char* getName();
    string getNameString();
    int getPv();
    int getPvMax();
    int getPm();
    int getPmMax();
    int getInit();
    int getAtq();
    int getMagieNoire();
    int getMagieBlanche();

    int getCrit();

    int getResTranchant();
    int getResPercant();
    int getResContondant();
    int getResExplosif();

    int getResFeu();
    int getResGlace();
    int getResFoudre();
    int getResAir();
    int getResEau();
    int getResTerre();
    int getResLumiere();
    int getResTenebres();

    int getResCrit();

    TypeArme getTypeArme();

    bool getIsTurn() const;
    bool getEnDefense();
    void updateIsTurn(bool value);
    void updateEnDefense(bool value);
    void updateStats(Operation operation, Sts stat, int value);
    void setStats(Sts stat, int value);

    void changeAnimation(Animation anim);
    Animation getAnimType() const;

    void startAnimation();
    void resetAnimation(); //Pour remettre les parametres par defaut
    bool getIsPlayer();
    void setDistant();

    //Variables publiques
    int target[2]; //cible dans la liste (en combat)
    TypeTarget tTarget; //pour savoir dans quelle liste on se trouve
    bool pmEnRecharge;
    bool getIsDead();
    void setIsDead(bool b);
    void setPortrait(string path, SDL_Renderer* renderer );

    Liste<Magie*>* listeMagies;
    //Liste<Technique*>* listeTechniques;

    Etat listeEtats[10];
    int dureeEtats[10];

    int nbrEtats;
    FleauElementaire fleau;
    int fleauDuree;

    Magie* currentMagie;

    bool isTurn;
    bool debutTour;
    //Position du personnage sur la grille de combat
    int ligne;
    int colonne;
    bool distant;
    Texture* getPortrait();

    void calculerStats();
    void initAttributs();
    void initRes();
    void setAttributs();

protected:
    string name;

    Attributs attr;
    Stats stats;

    Resistances res;

    TypeArme typeArme;

    bool enDefense;
    bool isPlayer;
    bool isDead;

    Texture* portrait;

    int idleFrames;
    SDL_Rect* idle;
    //Pour les animations offensives,
    //on ajoute une frame "efficace" ou l'attaque se lance
    int walkFrames;
    int walkEff;
    SDL_Rect* walk;

    int attackFrames;
    int attackEff;
    SDL_Rect* attack;

    int attack1Frames;
    int attack1Eff;
    SDL_Rect* attack1;

    int aoeFrames;
    int aoeEff;
    SDL_Rect* aoe;

    int laserBeamFrames;
    int laserBeamEff;
    SDL_Rect* laserBeam;

    int magieFrames;
    int magieEff;
    SDL_Rect* magie;

    int hurtFrames;
    int hurtEff;
    SDL_Rect* hurt;

    int prepareFrames;
    SDL_Rect* prepare;

    int deathFrames;
    SDL_Rect* death;

    int defendreFrames;
    int defendreEff;
    SDL_Rect* defendre;

    int frame; //frame actuelle
    int coeffFrame;

    Animation anim;
    int* currentFrames;
    SDL_Rect* currentClip;

    bool playAnimation;

};

#endif
