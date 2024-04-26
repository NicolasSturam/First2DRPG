#ifndef PNJ_H
#define PNJ_H

#include "Profile.h"
#include "Personnage.h"
#include "chainList.h"
#include "jeu.h"
#include "Joueur.h"


class PNJ {
public:
    PNJ();
    ~PNJ();
    PNJ(string path, SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect collider);

    void initVoleur();
    void createProfile( string name, Stats stats, Resistances res, string path, SDL_Renderer* renderer, SDL_Rect rect );

    bool followPoint(SDL_Rect* rect);
    SDL_Rect creerChemins2(Texture* actuel, SDL_Rect* target, SDL_Rect* murs, int nbrMurs);

    void creerChemins();
    void addToChemin(SDL_Rect* target, SDL_Rect* murs, int nbrMurs);

    void setInBase(bool b);
    //objets
    Personnage* p;
    Liste<Profile*>* profiles;
    //int nbrProfiles;


    //Accesseurs
    Liste<SDL_Rect>* getChemin() const;
    bool isInBase() const;
    void patrouille(Joueur* joueur, SDL_Rect* murs, int nbrMurs);

    //Pointeur de fonction
    //void (PNJ::*iaOutCombat)(Joueur* j);

private:
    Liste<SDL_Rect>* chemin;
    //Deplacement par defaut gauche, droite
    SDL_Rect stepOne;
    SDL_Rect stepTwo;
    SDL_Rect* nextStep;
    SDL_Rect* currentStep;
    SDL_Rect* temp;
    SDL_Rect base;
    bool inBase;
};



#endif // PNJ_H
