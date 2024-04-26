#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

class Camera{
public:
    Camera();
    Camera(SDL_Rect rect);
    ~Camera();
    //void cMove(); //change la position base sur la vitesse
    //void checkDistance(SDL_Rect* rect); //change les vitesses
    int getX() const;
    int getY() const;

    SDL_Rect* getRect();

    void setCamera(SDL_Rect* rect, int w, int h);
    void keepInBounds(int w, int h);
private:
    SDL_Rect rect;

    /*
    int posX;
    int posY;

    int vitX;
    int vitY;
    */

};

#endif // CAMERA_H
