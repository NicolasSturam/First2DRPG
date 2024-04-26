#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL.h>

using namespace std;

#include "Profile.h"

enum Etape{TRAJET, IMPACT};

class Projectile : public Texture{
public:
    Projectile();
    //Projectile(string path, SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect collider );
    ~Projectile();

    void setFeu(string path, SDL_Renderer* renderer, SDL_Rect rect1, SDL_Rect rect2, SDL_Rect collider ); //charge les sprites pour feu

    bool render(SDL_Renderer* renderer, Profile* profile, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void setAnimType(Etape type);
    void addToTrajet(int x);

    void startAnimation();
    bool getAnimationState();
    Etape getType();

     SDL_Rect impactRect;
private:
    int trajectFrames;
    SDL_Rect* trajet; //clips pour le trajet du projectile

    int impactFrames;
    int impactEff;
    SDL_Rect* impact; //clips pour l'impact du projectile

    bool playAnimation;

    int frame;
    int* currentFrames;
    SDL_Rect* currentClip;

    SDL_Rect trajetRect;

    int xStart;
    int yStart;

    Etape type;
};

#endif // PROJECTILE_H
