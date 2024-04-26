#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <string>
#include <SDL.h>
#include "Graphisme.h"

using namespace std;

//enum Operation {Add, Substract, Multiply, Divide};
enum Coordinate {X, Y};

class GraphicElement{

public:
    GraphicElement();   //constructeur par defaut
    GraphicElement(std::string path, SDL_Surface* screenSurface, SDL_Rect* position);
    SDL_Surface* getSprite();
    SDL_Rect* getPosition();
    void blitSurface();
    void updatePosition(Operation operation, Coordinate coordinate, int value);

protected:
    SDL_Surface* sprite;
    SDL_Surface* screenSurface;
    SDL_Rect* position;

};

#endif // GRAPHICELEMENT_H
