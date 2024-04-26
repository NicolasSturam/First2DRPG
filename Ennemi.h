#ifndef GOBELIN_H
#define GOBELIN_H

#include <string>
#include <SDL2/SDL.h>

using namespace std;

class Gobelin{

public:
    Gobelin();   //constructeur par defaut
    Gobelin(double pv, double pm, string name);
    void getPv();
    void getPm();
    void getName();

private:
    double pv, pm;
    string name;
    SDL_Surface* sprite;
};

#endif // JOUEUR_H
