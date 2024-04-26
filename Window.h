#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

class Window{
public:
    Window();
    Window(int window_width, int window_height);
    ~Window();

    void free();

    SDL_Renderer* createRenderer();

    void handleEvent(SDL_Event& e, SDL_Renderer* renderer);

    int getWidth() const;
    int getHeight() const;
    bool hasMouseFocus() const;
    bool hasKeyboardFocus() const;
    bool isMinimized() const;

private:
    SDL_Window* window;

    int width;
    int height;

    bool mouseFocus;
    bool keyboardFocus;
    bool fullScreen;
    bool minimized;


};

#endif // WINDOW_H
