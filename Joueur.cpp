#include "Joueur.h"
#include "Graphisme.h"
#include "Profile.h"

Joueur::Joueur(){
    this->p = NULL;
    this->inventaire = NULL;
    this->hud = NULL;
    this->profiles = NULL;
}

Joueur::Joueur(string name, string path, SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect collider){
    this->name = name;
    this->p = new Personnage(path, renderer, rect, collider);
    this->inventaire = NULL;
    this->hud = NULL;
    for(int i=0; i < 5;i++){
        this->hpJoueur[i] = 0;
        this->mpJoueur[i] = 0;
    }
    this->profiles = NULL;
}

/*
void Joueur::createProfile( string name, Stats stats, string path, SDL_Renderer* renderer, SDL_Rect rect ){
    //this->profile = new Profile(name, stats, path, renderer, rect , true);

    this->currentHPJoueur = stats.pv;
    this->currentMPJoueur = stats.pm;
}*/

Joueur::~Joueur(){
    delete inventaire;
}

void Joueur::setHUDCombat(SDL_Renderer* renderer, TTF_Font* font, SDL_Color* color){

    SDL_Rect rect;
    Profile* jProfile = NULL;
    string pvString;
    string pmString;

    this->clipBarreNoire = {307, 6, 58, 4};
    this->clipHpBarre = {308, 118, 56, 4};
    this->clipMpBarre = {308, 54, 56, 4};
    this->clipMpBarre2 = {308, 86, 56, 4};

    this->hud = new Texture("images/HUD/hud.png", renderer, this->hudRect[0]);

    for(int i=0;i < this->profiles->taille(); i++){
            jProfile = this->profiles->getNoeud2(i);
            this->hudRect[i] = {650, 580 + 40*i, 300, 10}; //reference pour afficher les barres de stats
            this->hpRect[i].x = this->hudRect[i].x + 1;
            this->hpRect[i].y = this->hudRect[i].y + 1;
            this->hpRect[i].w = this->hudRect[i].w  - 2;
            this->hpRect[i].h = this->hudRect[i].h - 2;
            rect.w = 15 * jProfile->getNameString().length();
            rect.h = 30;
            rect.x = this->hudRect[i].x - rect.w - 10;
            rect.y = this->hudRect[i].y - 10;
            this->nomJoueur[i] = new Texture(&rect);
            this->nomJoueur[i]->loadNewTexture(jProfile->getName(), renderer, font, color);

            pvString = to_string(jProfile->getPv());
            rect.w = 15 * pvString.length();
            rect.h = 20;
            rect.x = this->hudRect[i].x + this->hudRect[i].w - rect.w;
            rect.y = this->hudRect[i].y - this->hudRect[i].h - 10;
            this->hpJoueur[i] = new Texture(&rect);
            this->hpJoueur[i]->loadNewTexture(pvString, renderer, font, color );

            this->hudRect2[i].x = hudRect[i].x + this->hudRect[i].w + 5;
            this->hudRect2[i].y = hudRect[i].y ;
            this->hudRect2[i].w = 100;
            this->hudRect2[i].h = hudRect[i].h;
            this->mpRect[i].x = hudRect2[i].x + 1;
            this->mpRect[i].y = hudRect2[i].y + 1;
            this->mpRect[i].w = hudRect2[i].w - 2;
            this->mpRect[i].h = hudRect2[i].h - 2;
            rect.x = this->hudRect2[i].x + this->hudRect2[i].w - rect.w;
            rect.y = this->hudRect2[i].y - rect.h;
            pmString = to_string(jProfile->getPm());
            rect.w = 15 * pmString.length();
            this->mpJoueur[i] = new Texture(&rect);
            this->mpJoueur[i]->loadNewTexture(pmString, renderer, font, color);

            this->hpRect[i].w = jProfile->getPv()*100/jProfile->getPvMax()*(this->hudRect[i].w-2)/100;
            this->mpRect[i].w = jProfile->getPm()*100/jProfile->getPmMax()*(this->hudRect2[i].w-2)/100;
    }
}

void Joueur::afficherHUD( SDL_Renderer* renderer, SDL_Color* color, TTF_Font* font){
    Profile* jProfile = NULL;
    string pvString;
    string pmString;

    for(int i = 0; i< this->profiles->taille(); i++){
        jProfile = this->profiles->getNoeud2(i);

        this->hud->render(renderer, &this->clipBarreNoire, &this->hudRect[i]);
        this->hud->render(renderer, &this->clipBarreNoire, &this->hudRect2[i]);
        if( this->currentHPJoueur[i] != jProfile->getPv() ){
            pvString = to_string(jProfile->getPv());
            this->hpJoueur[i]->setW(15*pvString.length());
            this->hpJoueur[i]->setX(this->hudRect[i].x + this->hudRect[i].w - this->hpJoueur[i]->getRectW());
            this->hpJoueur[i]->loadNewTexture(pvString, renderer, font, color );
            this->currentHPJoueur[i] = jProfile->getPv();
            this->hpRect[i].w = jProfile->getPv()*100/jProfile->getPvMax()*(this->hudRect[i].w-2)/100;
        }
        if( this->currentMPJoueur[i] != jProfile->getPm() ){
            pmString = to_string(jProfile->getPm());
            this->mpJoueur[i]->setW(15*pmString.length());
            this->mpJoueur[i]->setX(this->hudRect2[i].x + this->hudRect2[i].w - this->mpJoueur[i]->getRectW());
            this->mpJoueur[i]->loadNewTexture(pmString, renderer, font, color );
            this->currentMPJoueur[i] = jProfile->getPm();
            this->mpRect[i].w = jProfile->getPm()*100/jProfile->getPmMax()*(this->hudRect2[i].w-2)/100;
        }
        this->hud->render(renderer, &this->clipHpBarre, &this->hpRect[i]);
        if(!jProfile->pmEnRecharge){
            this->hud->render(renderer, &this->clipMpBarre, &this->mpRect[i]);
        }
        else{
            this->hud->render(renderer, &this->clipMpBarre2, &this->mpRect[i]);
        }
        this->nomJoueur[i]->renderText( renderer );
        this->hpJoueur[i]->renderText(renderer);
        this->mpJoueur[i]->renderText(renderer);
    }


}

void Joueur::handleEvent( SDL_Event* e)
{
        if(e->type==SDL_KEYDOWN && e->key.repeat == 0){
            switch(e->key.keysym.sym){
                case SDLK_z:
                    this->p->setMinVitY();
                    break;
                case SDLK_s:
                    this->p->setMaxVitY();
                    break;
                case SDLK_q:
                    this->p->setMinVitX();
                    break;
                case SDLK_d:
                    this->p->setMaxVitX();
                    break;
            }
        }
        else if(e->type == SDL_KEYUP && e->key.repeat == 0){
            switch(e->key.keysym.sym){
                case SDLK_z:
                    this->p->setVitY(0);
                    break;
                case SDLK_s:
                    this->p->setVitY(0);
                    break;
                case SDLK_q:
                    this->p->setVitX(0);
                    break;
                case SDLK_d:
                    this->p->setVitX(0);
                    break;
            }
        }
        else if(e->type==SDL_CONTROLLERBUTTONDOWN){
            switch(e->cbutton.button){
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                    this->p->setMaxVitY();
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP:
                    this->p->setMinVitY();
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                    this->p->setMinVitX();
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                    this->p->setMaxVitX();
                    break;
            }
        }
        else if(e->type==SDL_CONTROLLERBUTTONUP){
            switch(e->cbutton.button){
                case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                    this->p->setVitY(0);
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_UP:
                    this->p->setVitY(0);
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                    this->p->setVitX(0);
                    break;
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                    this->p->setVitX(0);
                    break;
            }
        }
}

Objet* Joueur::getObjet(string name) const{
    return this->inventaire->recuperer(name);
}

Inventaire* Joueur::getInventaire() const{
    return this->inventaire;
}

/*
bool useObjet(Joueur* source, string name){
    //On regarde si l'objet est dans l'inventaire du joueur
    Objet* objet = source->getInventaire()->recuperer(name);
    if(objet == NULL){
        printf("L'objet %s n'est pas dans l'inventaire\n", name.c_str());
        return false;
    }
    else{
        source->updateStats(objet->getBonus()? Add:Substract, objet->getStat(), objet->getValeur());
        printf("%s utilise %s\n", source->getName(), objet->getName().c_str());
        if(objet->getBonus()){
            switch(objet->getStat()){
            case PV:
                printf("%s recupere %d PV\n", source->getName(), objet->getValeur());
                printf("PV actuels : %f \n", source->getPv());
                //printf("\n");
            break;
            case PM:
                printf("%s recupere %d PM\n", source->getName(), objet->getValeur());
                printf("PM actuels : %f \n", source->getPm());
            break;
            case ATQ:
                break;
            case MAG:
                break;
            case DEF:
                break;
            case RES:
                break;
            }
        }
        source->getInventaire()->supprimer(name);
        return true;
    }
    //On applique les effets
}*/
