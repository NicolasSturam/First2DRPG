#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include <SDL.h>

using namespace std;

#include "Personnage.h"
#include "Profile.h"
#include "Inventaire.h"
#include "Objet.h"
#include "chainList.h"

class Joueur{

public:
    Joueur();   //constructeur par defaut
    Joueur(string name, string path, SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect collider);
    //Joueur(string name, Stats* stats, std::string path, SDL_Surface* screenSurface, SDL_Rect* postion, Inventaire* inventaire);
    ~Joueur();

    void createProfile( string name, Stats stats, string path, SDL_Renderer* renderer, SDL_Rect rect );
    //Takes key presses and adjusts the velocity
    void handleEvent( SDL_Event* e);

    bool useObjet(string name);

    void setHUDCombat(SDL_Renderer* renderer, TTF_Font* font, SDL_Color* color);

    void afficherHUD(SDL_Renderer* renderer, SDL_Color* color, TTF_Font* font);

    //Accesseurs
    Objet* getObjet(string name) const;
    Inventaire* getInventaire() const;

    Personnage* p;
    Liste<Profile*>* profiles;
    //int nbrProfiles;

    //HUD en combat
    SDL_Rect hudRect[5];
    SDL_Rect hudRect2[5];
    SDL_Rect hpRect[5];
    SDL_Rect mpRect[5];

    SDL_Rect clipBarreNoire;
    SDL_Rect clipHpBarre;
    SDL_Rect clipMpBarre;
    SDL_Rect clipMpBarre2;

    Texture* hud;
    Texture* nomJoueur[5];
    Texture* hpJoueur[5];
    Texture* mpJoueur[5];

    int currentHPJoueur[5];
    int currentMPJoueur[5];

private:
    string name;
    Inventaire* inventaire;


};

#endif // JOUEUR_H
