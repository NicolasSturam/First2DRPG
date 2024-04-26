#ifndef GRAPHISME_H
#define GRAPHISME_H

using namespace std;

#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <SDL_gamecontroller.h>
#include <SDL.h>
#include <array>

#include "Texture.h"
#include "Window.h"

extern int window_width;
extern int window_height;

enum GameState {MAP , COMBAT };

//SDL initialization
Window* init_video();

//Charge images in memory
bool loadMedia();

//Load individual image
SDL_Surface* loadSurface(std::string path, SDL_Surface* screenSurface);

//Free memory and shuts down SDL
void close(Window* window, SDL_Surface* surface, SDL_Renderer* renderer);

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);

SDL_Texture* loadRenderText(string textureText, SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor);

SDL_Renderer* createRenderer(SDL_Window* window);

bool checkCollision(SDL_Rect* a, SDL_Rect* b, int sizeB = 1);



#endif // GRAPHISME
