#ifndef NIVEAU_H
#define NIVEAU_H

#include "PNJ.h"
#include "jeu.h"
#include "Background.h"
#include "Camera.h"

class Niveau{
public:
    Niveau();
    Niveau(string nom, SDL_Renderer* renderer, Grille* grilleEnnemi, int level_width, int level_height);
    ~Niveau();

    Mix_Music** getMusics();
    int getNombreEnnemis();
    PNJ* getEnnemi();

    //void renderFond(Camera* camera, SDL_Renderer* renderer);
    //void renderFront(Camera* camera, SDL_Renderer* renderer);

    void renderNiveau(GameState* jeu, Camera* camera, SDL_Renderer* renderer, Joueur* joueur);

    Texture* getFond();
    void freeEnnemi();

private:
    string nom;
    int level_width;
    int level_height;
    int nbrMusics;
    Mix_Music** niv_musics;
    //Liste<Profile*>* listeEnnemis;
    int nbrEnnemis;
    PNJ* ennemi;
    SDL_Renderer* renderer;
    Grille* grilleEnnemi;

    //Navigation
    Background* backFond;
    int nbrElements;
    Texture** premierPlan;

    //Combat
    Texture* fond;

    void creerTest(string nom);
    //void creerGrilleCombat(Grille* grille, int w, int h, int l, int x, int y);


};

#endif // NIVEAU_H
