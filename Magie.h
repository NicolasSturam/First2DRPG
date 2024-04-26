#ifndef MAGIE_H
#define MAGIE_H

#include <SDL.h>
#include <string>

using namespace std;

#include "Texture.h"
#include "Action.h"


class Magie : public Texture{
public:
    Magie();
    ~Magie();

    void setFlammes(SDL_Renderer* renderer, SDL_Rect* rect, TTF_Font* font, SDL_Color* textColor);
    void setSoin(SDL_Renderer* renderer, SDL_Rect* rect, TTF_Font* font, SDL_Color* textColor);
    void setBarriere(SDL_Renderer* renderer, SDL_Rect* rect, TTF_Font* font, SDL_Color* textColor);

    bool render(SDL_Renderer* renderer, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void renderName(SDL_Renderer* renderer, int x, int y);

    void startAnimation();

    const char* getName();
    int getPuissance();
    int getPmCost();
    bool getZone();
    TypeDegat getTypeDegat();
    Element getElem();
    Etat getEtat();

    int getFleauSucces();
    int getPeriodeTours();
    bool getSucces();
    int getTours();
    void incrementTours();
    void resetTours();
    void resetSucces();
    void setSucces();
    int getFleauDuree();
    void decrementFleauDuree();
    void setFleauDuree(int i);
    int getDureeEtat();
    string getNom();

private:
    string name;
    int pmCost;
    int puissance;
    bool zone;
    Type t;
    TypeDegat tDegat;
    Element elem;
    Etat etat;
    int dureeEtat;

    int fleauDuree;
    int fleauSucces; // 1 a 100
    int periodeTours; // maximum 100 tours a verifier
    int tours; //compteur pour le nombre de tours
    bool succes;

    int frame;
    int frames;
    int eff;
    SDL_Rect* clips;
    bool playAnimation;

    SDL_Texture* nameTexture;
    int w;
    int h;
};

#endif // MAGIE_H
