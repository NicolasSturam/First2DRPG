#ifndef JEUTEMPLATE_CPP
#define JEUTEMPLATE_CPP

#include <type_traits>
#include "jeu.h"
#include "GraphicElement.h"

template <typename T>
void updateWindow(SDL_Window* window, SDL_Surface* windowSurface, Liste <T>* liste){
    if(is_same<T, GraphicElement>::value){
        SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 255, 255, 255)); //1 on efface l'ecran precedent

    int taille = liste->taille();
    //2 on parcourt la liste chainee pour afficher toutes les images a l'ecran
    for(int i = 0; i < taille; i++){
        liste->getNoeud(i)->blitSurface();
    }
    //3 on met a jour l'ecran
    SDL_UpdateWindowSurface(window);
    }
    else{
        cout << "Erreur ! Mauvais type de liste" ;
    }
}

#endif // JEUTEMPLATE_CPP
