#include "Magie.h"

Magie::Magie(){
    this->clips = NULL;

    this->name = "";
    this->puissance = 0;
    this->pmCost = 0;
    this->zone = false;
    this->tDegat = NEUTRE;
    this->elem = NONE;
    this->etat = AUCUN;

    this->frame = 0;
    this->frames = 0;
    this->eff = 0;
    this->playAnimation = false;

    this->fleauSucces = 0;
    this->periodeTours = 0;
    this->succes = false;
    this->tours = 0;
    this->fleauDuree = 0;

    this->dureeEtat = 0;
    this->t = Offensive;
}

Magie::~Magie(){
    if(clips!=NULL){
        free(clips);
        this->clips = NULL;
    }
}

void Magie::setFlammes(SDL_Renderer* renderer, SDL_Rect* rect, TTF_Font* font, SDL_Color* textColor){
    this->rect = *rect;
    this->name = "Flammes";
    this->pmCost = 50;
    this->puissance = 50;
    this->zone = false;
    this->tDegat = NEUTRE;
    this->elem = FEU;
    this->etat = AUCUN;

    this->texture = loadTexture("images/magies/Burn.png", renderer);
    this->nameTexture = loadRenderText(this->name + "  " + to_string(this->pmCost), renderer, font, *textColor);

    this->w = 15*(this->name.size() + (to_string(this->pmCost)).size());
    this->h = 40;

    int w = 128;
    int h = 128;
    this->frames = 10;
    this->eff = 0;
    this->clips = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->frames);
    for(int i = 0; i < this->frames; i++){
        this->clips[i].x = 0;
        this->clips[i].y = h*i;
        this->clips[i].w = w;
        this->clips[i].h = h;
    }

    this->fleauSucces = 100;
    this->periodeTours = 100/fleauSucces;
    this->succes = false;
    this->tours = 0;
    this->fleauDuree = 5;
    this->t = Offensive;
}

void Magie::setSoin(SDL_Renderer* renderer, SDL_Rect* rect, TTF_Font* font, SDL_Color* textColor){
    this->rect = *rect;
    this->name = "Soin";
    this->pmCost = 30;
    this->puissance = -30;
    this->zone = false;
    this->tDegat = SOIN;
    this->elem = NONE;
    this->etat = AUCUN;

    this->texture = loadTexture("images/magies/soin.png", renderer);
    this->nameTexture = loadRenderText(this->name + "  " + to_string(this->pmCost), renderer, font, *textColor);

    this->w = 15*(this->name.size() + (to_string(this->pmCost)).size());
    this->h = 40;

    int w = 64;
    int h = 64;
    this->frames = 13;
    this->eff = 5;
    this->clips = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->frames);
    for(int i = 0; i < this->frames; i++){
        this->clips[i].x = w*i;
        this->clips[i].y = 0;
        this->clips[i].w = w;
        this->clips[i].h = h;
    }
    this->t = Defensive;
}

void Magie::setBarriere(SDL_Renderer* renderer, SDL_Rect* rect, TTF_Font* font, SDL_Color* textColor){
    this->rect = *rect;
    this->name = "Barriere";
    this->pmCost = 20;
    this->puissance = 0;
    this->zone = false;
    this->tDegat = SOIN;
    this->elem = NONE;
    this->etat = BARRIERE;

    this->texture = loadTexture("images/magies/barriere.png", renderer);
    this->nameTexture = loadRenderText(this->name + "  " + to_string(this->pmCost), renderer, font, *textColor);

    this->w = 15*(this->name.size() + (to_string(this->pmCost)).size());
    this->h = 40;

    int w = 64;
    int h = 64;
    this->frames = 14;
    this->eff = 13;
    this->clips = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->frames);
    for(int i = 0; i < this->frames; i++){
        this->clips[i].x = w*i;
        this->clips[i].y = 0;
        this->clips[i].w = w;
        this->clips[i].h = h;
    }

    this->dureeEtat = 5;
    this->t = Defensive;
}

//Renvoie true pour que les degats s'appliquent. Le tour de la source doit aussi être mis à false.
bool Magie::render(SDL_Renderer* renderer, double angle, SDL_Point* center, SDL_RendererFlip flip){
    bool eff = false;
    if(this->playAnimation){
        if(this->frame == this->eff*10){
            eff = true;
        }
        SDL_RenderCopyEx( renderer, this->texture, &this->clips[this->frame/10], &this->rect, angle, center, flip );
        this->frame ++;
        if(this->frame/10 >= this->frames ){
            this->frame = 0;
            this->playAnimation = false;
        }
    }
    return eff;
}

void Magie::renderName(SDL_Renderer* renderer, int x, int y){
    SDL_Rect rect2;
    rect2.x = x;
    rect2.y = y;
    rect2.w = this->w;
    rect2.h = this->h;

    SDL_RenderCopyEx( renderer, this->nameTexture, NULL, &rect2, 0.0, NULL, SDL_FLIP_NONE);
}

void Magie::startAnimation(){
    this->playAnimation = true;
}

const char* Magie::getName(){
    return this->name.c_str();
}

int Magie::getPuissance(){
    return this->puissance;
}

bool Magie::getZone(){
    return this->zone;
}

TypeDegat Magie::getTypeDegat(){
    return this->tDegat;
}

Element Magie::getElem(){
    return this->elem;
}

Etat Magie::getEtat(){
    return this->etat;
}

int Magie::getPmCost(){
    return this->pmCost;
}

int Magie::getFleauSucces(){
    return this->fleauSucces;
}

int Magie::getPeriodeTours(){
    return this->periodeTours;
}

bool Magie::getSucces(){
    return this->succes;
}

int Magie::getTours(){
    return this->tours;
}

void Magie::incrementTours(){
    this->tours++;
}

void Magie::resetTours(){
    this->tours = 0;
}

void Magie::resetSucces(){
    this->succes = false;
}

void Magie::setSucces(){
    this->succes = true;
}

int Magie::getFleauDuree(){
    return this->fleauDuree;
}

void Magie::decrementFleauDuree(){
    this->fleauDuree --;
}

void Magie::setFleauDuree(int i){
    this->fleauDuree = i;
}

int Magie::getDureeEtat(){
    return this->dureeEtat;
}

string Magie::getNom(){
    return name;
}
