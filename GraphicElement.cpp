#include "GraphicElement.h"

GraphicElement::GraphicElement(){
    SDL_Rect p;
    this->position = &p;
    this->sprite = NULL;
    this->screenSurface = NULL;
}

GraphicElement::GraphicElement(std::string path, SDL_Surface* screenSurface, SDL_Rect* position){
    this->sprite = loadSurface(path, screenSurface);
    this->position = position;
    this->screenSurface = screenSurface;
}

SDL_Surface* GraphicElement::getSprite(){
    return sprite;
}

SDL_Rect* GraphicElement::getPosition(){
    return position;
}

void GraphicElement::blitSurface(){
    SDL_BlitSurface(this->sprite, NULL, this->screenSurface, this->position);
}

void GraphicElement::updatePosition(Operation operation, Coordinate coordinate, int value){
    if(coordinate == X){
        switch(operation){
        case Add:
            this->position->x+=value;
            break;
        case Substract:
            this->position->x-=value;
            break;
        case Multiply:
            this->position->x*=value;
            break;
        case Divide:
            this->position->x/=value;
            break;
        }
    }
    else if(coordinate == Y){
        switch(operation){
        case Add:
            this->position->y+=value;
            break;
        case Substract:
            this->position->y-=value;
            break;
        case Multiply:
            this->position->y*=value;
            break;
        case Divide:
            this->position->y/=value;
            break;
        }
    }
    else{
        printf("Erreur : type de coordonnee incorrecte");
    }
}
