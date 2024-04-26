#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "Texture.h"

class Personnage : public Texture{
public :
    Personnage();
    Personnage(string path, SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect collider = {0,0,0,0});
    ~Personnage();

    void setArcher();//->creation d'un personnage archer

    void setVoleur();//->creation d'un personnage voleur

    void render(SDL_Renderer* renderer, int camX = 0, int camY = 0, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void ajusterClip();
    void ajusterVitesse();
    void stop();
    void moveSprite(int level_width, int level_height, SDL_Rect* wall, int nbrMur); //deplacement base sur la vitesse
    //-> objets deplacable physiquement

    //Modificateurs
    void setMaxVitX();
    void setMaxVitY();
    void setMinVitX();
    void setMinVitY();
    void setVitX(int vit);
    void setVitY(int vit);
    //Accesseurs
    int getVitX() const;
    int getVitY() const;
    int getMaxVit() const;

    int getFrames() const;
    SDL_Rect* getCurrentClip() const;
    bool getPlayAnimation() const;
    int getFrame() const;

    bool playAnimation;
private:
    //The velocity of the dot
    int vitX, vitY;
    int maxVit;
    //Pour les animations
    static const int FRAMES = 4;
    SDL_Rect marcheBas[4];
    SDL_Rect marcheGauche[4];
    SDL_Rect marcheHaut[4];
    SDL_Rect marcheDroite[4];
    SDL_Rect* currentClip;

    int frame;
};

#endif // PERSONNAGE_H
