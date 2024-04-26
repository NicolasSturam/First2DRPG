#include "Camera.h"

Camera::Camera(){
    rect = {0,0,0,0};
}

Camera::Camera(SDL_Rect rect){
    this->rect = rect;
}

Camera::~Camera(){

}

int Camera::getX() const{
    return rect.x;
}

int Camera::getY() const{
    return rect.y;
}

SDL_Rect* Camera::getRect(){
    return &rect;
}

void Camera::setCamera(SDL_Rect* rect, int w, int h){
    //Set camera on player
    this->rect.x = rect->x + rect->w/2 - w/2;
    this->rect.y = rect->y + rect->h/2 - h/2;
}

void Camera::keepInBounds(int w, int h){
    if( rect.x < 0 )
    {
        rect.x = 0;
    }
    if( rect.y < 0 )
    {
        rect.y = 0;
    }
    if( rect.x > w - rect.w )
    {
        rect.x = w - rect.w;
    }
    if( rect.y > h - rect.h )
    {
        rect.y = h - rect.h;
    }
}

