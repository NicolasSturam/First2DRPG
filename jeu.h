#ifndef JEU_H
#define JEU_H

#include <stdio.h>
#include <SDL.h>
#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <SDL_ttf.h>

using namespace std;

#include "chainlist.cpp"
#include "Profile.h"
#include "Timer.h"
#include "Joueur.h"
#include "Projectile.h"
#include "Technique.h"

struct Point{
    int x;
    int y;
};

struct Ennemi{
    Profile* e_profile;
    bool** e_statsConnues;
};

struct Grille{
    int w; //parametre pour regler l'angle des colonnes entre elles
    int h; //hauteur entre les lignes
    int l; //largeur entre les colonnes

    Point tab[5][3];

};

struct DonneesCombat{
    int tour; //numero du tour en cour
    int currentEntite;
    int degats; //pour afficher les degats
    int decallageDegats;

    bool victoire;
    bool defaite;
    bool fuite;

    bool afficherDegats;

    Timer timerFin;
    Timer degatsTimer;

    SDL_Rect degatsRect;

    Texture* degatsText;
    int nbrJoueurs;
    int nbrEnnemi;
    int nbrJoueursDead;
    int joueursDead[3];
    int nbrEnnemiDead;
    int ennemisDead[3];

    int increment; // pour les deplacements
    Magie* currentMagie;

    Texture* compteur;
};

//Genere un indice dans le tableau en fonction de la cle entree en parametre
int hachage(string cle, int tailleTableau);

template <typename T>
void ajouterAuTableau(T* tab[], int tailleTableau, T* element){
    int indice = hachage(element->getName(), tailleTableau);
    tab[indice] = element;
}

//Separer dans les differents niveaux ?
//Cree le joueur
Joueur* creerJoueur(SDL_Renderer* renderer, Grille* grilleCombat);

//Cree TOUTES les magies du jeu
Magie** creerMagies(int* nbrMagies, SDL_Renderer* renderer, TTF_Font* font, Couleurs* couleurs);

//Cree TOUS les objets du jeu
Objet** creerObjets();

//Cree TOUTES les techniques du jeu
Technique** creerTechniques();

//Cree TOUS les profiles du jeu
Profile** creerProfiles();

//Cree TOUTES les icones du jeu
Texture** creerIcones(int* nbrIcones, SDL_Renderer* renderer);

//Cree TOUS les pnjs du jeu

void creerGrilleCombat(Grille* grille, int w, int h, int l, int x, int y);

bool demandeSortie();

void initGame(Joueur* joueur, Profile* gobelin);

void follow(Texture* entite1, Texture* entite2);

Liste<SDL_Rect>* creerChemins(Texture* entite1, Texture* entite2, SDL_Rect* murs, int nbrMurs);

Liste<Point>* creerTrajectoire(Liste<SDL_Rect>* chemin);

bool followPoint(Texture* entite, SDL_Rect* rect);

SDL_Rect creerChemins2(Texture* actuel, SDL_Rect* target, SDL_Rect* murs, int nbrMurs);

double calculerDistance(SDL_Rect* rect1, SDL_Rect* rect2);

void initCombat(Liste<Profile*>* listeProfile);

void initDC(DonneesCombat* dc, int, int);

void initCombat(DonneesCombat* dc, Liste<Profile*>* listeProfiles, Liste<Profile*>* listeJoueurs);

//void gestionCombat(DonneesCombat* dc, Liste<Profile*>* listeProfiles, Profile* joueur);
void gestionCombat(DonneesCombat* dc, Liste<Profile*>* listeProfiles, Liste<Profile*>* listeJoueurs, Liste<Profile*>* ennemis[3], Liste<Profile*>* joueurs[3]);

// return true si des degats sont a afficher
bool afficherProfiles(SDL_Renderer* renderer, Liste<Profile*>* joueurs[3], Liste<Profile*>* listeEnnemis[3], Liste<Profile*>* lProfilesToRender, Texture** tabIcones, DonneesCombat* dc);

//bool afficherProjectile(SDL_Renderer* renderer, Projectile* proj, Profile* joueur, Liste<Profile*>* listeProfiles, DonneesCombat* dc);

bool afficherMagie(SDL_Renderer* renderer, Profile* joueur, Liste<Profile*>* cibles[3], DonneesCombat* dc);

void afficherDegats( SDL_Renderer* renderer, DonneesCombat* dc );

void afficherPortraits(Texture* cadrePortrait, SDL_Renderer* renderer, DonneesCombat* dc, Liste<Profile*>* listeProfiles);

bool gestionDebutTour( Profile* profile, DonneesCombat* dc);

#endif // JEU_H
