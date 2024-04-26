#ifndef TEXTUREWRAPPER_H
#define TEXTUREWRAPPER_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

#include "graphisme.h"

typedef struct Couleurs Couleurs;
struct Couleurs{
    SDL_Color vert;
    SDL_Color grisPale;
    SDL_Color blanc;
    SDL_Color noir;
};

void initCouleurs(Couleurs* couleurs);

class Texture
{
    public:
        //Constructeurs et destructeurs
        Texture();
        Texture(SDL_Rect* rect);
        Texture(string text, SDL_Renderer* renderer, TTF_Font* font, SDL_Color* textColor);
        Texture(string path, SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect collider = {0,0,0,0});
        Texture(Texture* texture); //copy constructor
        virtual ~Texture();

        void loadNewTexture(string path, SDL_Renderer* renderer, SDL_Rect rect);
        void loadNewTexture(string text, SDL_Renderer* renderer, TTF_Font* font, SDL_Color* textColor);

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );

        //Renders texture at given point
        virtual void render(SDL_Renderer* renderer, SDL_Rect* clip = NULL,  int camX = 0, int camY = 0, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void renderText(SDL_Renderer* renderer, SDL_Rect* rect,  int camX = 0, int camY = 0, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void renderText(SDL_Renderer* renderer, int camX = 0, int camY = 0, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* rect, int camX = 0, int camY = 0, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        //void render2(int camX, int camY); //->Pour les objets animes

        // ! Il faut ajouter les methodes pour gerer le collider en fonction du rect
        void setPosition(int x, int y);
        void setX(int x);
        void setY(int y);

        void addToX(int x);

        void setSize(int w, int h);
        void setW(int w);
        void setH(int h);

        //Accesseurs
        int getRectX() const;
        int getRectY() const;
        int getRectW() const;
        int getRectH() const;

        SDL_Rect* getRect();

        int getColliderX() const;
        int getColliderY() const;
        int getColliderW() const;
        int getColliderH() const;

        SDL_Rect* getCollider() ;
        void addToCollider(int x);

        void setRect(SDL_Rect* rect);

        SDL_Rect depart;
        SDL_Rect departCollider;

        SDL_Texture* getTexture();

    protected:
        //Texture sheet
        SDL_Texture* texture;
        //Position et dimensions
        SDL_Rect rect;
        //Box collider
        SDL_Rect collider;


};

#endif // TEXTUREWRAPPER_H
