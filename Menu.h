#ifndef MENU_H
#define MENU_H

#include <SDL.h>

#include "Profile.h"
#include "jeu.h"
#include "chainList.h"
#include "Texture.h"

struct Case{
    Animation anim;
    int x;//coordonnee du sommet haut-gauche x
    int y;//coordonnee du sommet haut-gauche y
    int w; //largeur du rectangle
    int h; //hauteur du rectangle
};

//typedef struct TexturesMenu;
struct TexturesMenu{
    Texture* attaquer;
    Texture* magie;
    Texture* techniques;
    Texture* objet;
    Texture* defendre;
    Texture* avancer;
    Texture* reculer;
    Texture* fuir;

    Texture* cursor;
    Texture* flecheDoree;
    Texture* panneau2;
    Texture* triangle;
};

//void initTexturesMenu(int h, TexturesMenu* texturesMenu, SDL_Renderer* renderer, TTF_Font* font, Couleurs* couleurs);

class Menu : public Texture{
public:
    Menu();
    ~Menu();
    Menu(string path, SDL_Renderer* renderer, SDL_Rect rect);

    void renderTextures(Profile* profile, SDL_Renderer* renderer);
    void setMenuCombat(SDL_Rect* posCursor);

    bool handleEvent(SDL_Event* e, Profile* joueur, Liste<Profile*>* joueurs[3], Liste<Profile*>* ennemis[3], DonneesCombat* dc);

    bool isOpened();
    bool showMagies();
    bool showTechniques();
    bool showObjets();

    void initTexturesMenu(int h, SDL_Renderer* renderer, TTF_Font* font, Couleurs* couleurs);
private:
    int nbreCase; //taille du tableau
    int current; //indice de la case courante
    int indice; //pour naviguer d'une magie, technique ou objet a l'autre
    Case* tableau;
    Case* caseCourante;

    SDL_Rect posCursorOrigine;

    //flags
    bool selectedAction;
    bool selectedTarget;

    bool opened;
    bool magieListe;
    bool techniqueListe;
    bool objetListe;

    bool chooseTarget;

    Magie* currentMagie;

    int pLEnnemie; //premiere ligne ennemie
    int tLigne; //taille ligne
    Profile* cProfile;
    bool stop;
    int actual;

    Liste<Profile*>** cListe;
    bool swap;

    TexturesMenu texturesMenu;
};

#endif // MENU_H
