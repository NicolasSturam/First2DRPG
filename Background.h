#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <cstdlib>
#include "Texture.h"

class Background : Texture{
public:
    Background();
    ~Background();
    Background(string path, SDL_Renderer* renderer, SDL_Rect rect);

    void initVillage(); //on aura une fonction associee a chaque niveau pour placer les murs physiques

    void render(SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Accesseurs
    SDL_Rect* getMurs() const;
    int getNbrMurs() const;

private:
    int nbrMur;
    SDL_Rect* murs;
};

#endif // BACKGROUND_H
