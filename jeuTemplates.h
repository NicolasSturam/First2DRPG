#ifndef JEUTEMPLATE_H
#define JEUTEMPLATE_H

#include <SDL2/SDL.h>
#include <iostream>
#include "chainlist.cpp"

using namespace std;

template <typename T>
void updateWindow(SDL_Window* window, SDL_Surface* windowSurface, Liste <T>* liste);

#endif // JEUTEMPLATE_H
