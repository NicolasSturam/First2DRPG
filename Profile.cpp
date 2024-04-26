#include "Profile.h"


Profile::Profile()
{
    this->name = "Vide";
    this->texture = NULL;
    this->isTurn = false;
    this->pmEnRecharge = false;
    this->enDefense = false;
    this->isDead = false;
    this->portrait = NULL;

    this->rect = {0,0,0,0};
    this->frame = 0;

    this->idleFrames = 0;
    this->idle = NULL;
    this->attackFrames = 0;
    this->attack = NULL;
    this->magieFrames = 0;
    this->magieEff = 0;
    this->magie = NULL;
    this->hurtFrames = 0;
    this->hurt = NULL;
    this->walkFrames = 0;
    this->walk = NULL;
    this->prepareFrames = 0;
    this->prepare = NULL;
    this->deathFrames = 0;
    this->death = NULL;
    this->defendreFrames = 0;
    this->defendreEff=0;
    this->defendre = NULL;

    this->currentFrames = NULL;
    this->currentClip = NULL;

    this->playAnimation = false;
    this->isPlayer = false;
    for(int i=0;i<2;i++){
        this->target[i] = 0;
    }
    this->tTarget = ENNEMI; //Par defaut on cible un ennemi
    this->listeMagies = NULL;
    this->currentMagie = NULL;

    this->debutTour = false;
    this->fleau = ZERO;
    this->fleauDuree = 0;

    this->nbrEtats = 0;
    this->distant = false;
}

Profile::Profile(string name, string path, SDL_Renderer* renderer, SDL_Rect rect, bool type)
:Texture(path, renderer, rect)
{
    this->name = name;
    this->depart = rect;
    this->isTurn = false;
    this->isDead = false;
    this->pmEnRecharge = false;
    this->enDefense = false;
    this->portrait = NULL;

    this->attr = attr;
    calculerStats();

    this->res = res;
    this->rect = rect;
    this->frame = 0;

    this->idleFrames = 0;
    this->idle = NULL;
    this->attackFrames = 0;
    this->attack = NULL;
    this->hurtFrames = 0;
    this->hurt = NULL;
    this->walkFrames = 0;
    this->walk = NULL;
    this->prepareFrames = 0;
    this->prepare = NULL;
    this->deathFrames = 0;
    this->death = NULL;

    this->magieFrames = 0;
    this->magieEff = 0;
    this->magie = NULL;

    this->defendreFrames = 0;
    this->defendreEff=0;
    this->defendre = NULL;

    this->currentFrames = NULL;
    this->currentClip = NULL;

    this->playAnimation = true;
    this->isPlayer = type;

    this->listeMagies = new Liste<Magie*>();
    this->currentMagie = NULL;
    for(int i=0;i<2;i++){
        this->target[i] = 0;
    }
    this->tTarget = ENNEMI; //Par defaut on cible un ennemi
    this->debutTour = false;
    this->fleau = ZERO;
    this->fleauDuree = 0;

    this->nbrEtats = 0;
    this->dureeEtats[10] = {0};
    this->distant = false;

    this->typeArme = FORCE;

    initAttributs();
    initRes();
}

Profile::~Profile(){
    if(this->idle != NULL){
        free(this->idle);
        this->idle = NULL;
    }
    if(this->attack != NULL){
        free(this->attack);
        this->attack = NULL;
    }
}

//renvoie True seulement si on a atteint une frame efficace
//return false sinon
bool Profile::render(SDL_Renderer* renderer, double angle, SDL_Point* center, SDL_RendererFlip flip){
    bool eff = false;
    if(this->playAnimation){
        if(this->frame == this->attackEff*this->coeffFrame && this->anim == ATTACK){
            eff = true;
        }
        else if(this->frame == this->magieEff*this->coeffFrame && this->anim == MAGIE){
            eff = true;
        }
        else if(this->frame == this->defendreEff*this->coeffFrame && this->anim == DEFENDRE){
            this->playAnimation = false;
            eff = true;
            this->isTurn = false;
        }
        else if(this->frame == this->hurtEff*this->coeffFrame && this->anim == HURT && this->stats.pv ==0){
            //eff = true;
        }
        if(this->anim == RECULER){
            SDL_RenderCopyEx( renderer, this->texture, &this->currentClip[this->frame/this->coeffFrame], &this->rect, angle, center, SDL_FLIP_HORIZONTAL );
        }
        else{
            SDL_RenderCopyEx( renderer, this->texture, &this->currentClip[this->frame/this->coeffFrame], &this->rect, angle, center, flip );
        }
        this->frame ++;
        if(this->frame/this->coeffFrame >= (*currentFrames) ){
            this->frame = 0;

            if(this->anim == PREPARE){
                this->currentClip = attack;
                this->currentFrames = &attackFrames;
                this->anim = ATTACK;
            }
            else if(this->anim == ATTACK){
                if(this->getPv() > 0){
                    this->isTurn = false;
                }
                resetAnimation();
            }
            else if( this->anim == HURT ){
                eff = true;
                if(this->getPv() > 0){
                    resetAnimation();
                }
                else{
                    this->frame = 0;
                }
            }
            else if( this->anim == DEATH){
                this->playAnimation = false;
                this->frame = deathFrames-1;
                this->isTurn = false;
                this->debutTour = false;
                this->isDead = true;
                eff = true;
            }
            else if( this->anim == MAGIE){
                changeAnimation(WAIT);
            }
            else if( this->anim == WAIT){
                if(!isTurn){
                    resetAnimation();
                }
                else{
                    this->frame = 0;
                }
            }
            else if( this->anim !=  IDLE ){
                resetAnimation();
            }
        }
    }
    else{
        if(this->anim == DEATH){
            SDL_RenderCopyEx( renderer, this->texture, &this->currentClip[this->frame], &rect, angle, center, flip );
        }
        else{//Defendre par exemple
            SDL_RenderCopyEx( renderer, this->texture, &this->currentClip[this->frame/this->coeffFrame], &rect, angle, center, flip );
        }
    }

    return eff;
}

const char* Profile::getName(){
    return this->name.c_str();
}

int Profile::getPv(){
    return this->stats.pv;
}

int Profile::getPm(){
    return this->stats.pm;
}

int Profile::getAtq(){
    return this->stats.atq;
}

int Profile::getMagieNoire(){
    return this->stats.magieNoire;
}

int Profile::getMagieBlanche(){
    return this->stats.magieBlanche;
}

/*
int Profile::getRes(){
    return this->stats.res;
}*/

bool Profile::getIsTurn() const{
    return this->isTurn;
}

bool Profile::getEnDefense(){
    return this->enDefense;
}

void Profile::updateIsTurn(bool value){
    this->isTurn = value;
}

void Profile::updateEnDefense(bool value){
    this->enDefense = value;
}


void Profile::updateStats(Operation operation, Sts stat, int value){
    switch(operation){
    case Add:
        switch(stat){
        case PV:
            this->stats.pv+=value;
            break;
        case PM:
            this->stats.pm+=value;
            break;
        case ATQ:
            this->stats.atq+=value;
            break;
        case MAG:
            this->stats.magieNoire+=value;
            break;
        }
        break;
    case Substract:
        switch(stat){
        case PV:
            this->stats.pv-=value;
            if(this->stats.pv < 0)
                this->stats.pv = 0;
            break;
        case PM:
            this->stats.pm-=value;
            if(this->stats.pm < 0)
                this->stats.pm = 0;
            break;
        case ATQ:
            this->stats.atq-=value;
            break;
        case MAG:
            this->stats.magieNoire-=value;
        }
        break;
    case Multiply:
        switch(stat){
        case PV:
            this->stats.pv*=value;
            break;
        case PM:
            this->stats.pm*=value;
            break;
        case ATQ:
            this->stats.atq*=value;
            break;
        case MAG:
            this->stats.magieNoire=value;
            break;
        }
        break;
    case Divide:
        switch(stat){
        case PV:
            this->stats.pv/=value;
            break;
        case PM:
            this->stats.pm/=value;
            break;
        case ATQ:
            this->stats.atq/=value;
            break;
        case MAG:
            this->stats.magieNoire/=value;
            break;
        }
        break;
    }

    if(this->stats.pv > this->stats.pvMax){
        this->stats.pv = this->stats.pvMax;
    }
    else if(this->stats.pv < 0){
        this->stats.pv = 0;
    }
}

void Profile::setPortrait(string path, SDL_Renderer* renderer ){
    SDL_Rect rect = {0,0,85,85};
    this->portrait = new Texture(path, renderer, rect);
}

void Profile::setArcher(SDL_Rect* collider){
    this->distant = true;
    this->collider = *collider;
    this->departCollider = *collider;
    int w = 288;
    int h = 128;

    int ligne = 0;
    this->idleFrames = 12;
    this->idle = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->idleFrames);
    for(int i = 0; i < idleFrames; i++){
        this->idle[i].x = w*i;
        this->idle[i].y = h*ligne;
        this->idle[i].w = w;
        this->idle[i].h = h;
    }
    this->currentClip = idle;
    this->currentFrames = &idleFrames;
    this->anim = IDLE;
    this->coeffFrame = 10;

    ligne = 1;
    this->walkFrames = 10;
    this->walk = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->walkFrames);
    for(int i = 0; i < walkFrames; i++){
        this->walk[i].x = w*i;
        this->walk[i].y = h*ligne;
        this->walk[i].w = w;
        this->walk[i].h = h;
    }

    ligne = 10;
    this->magieFrames = 10;
    this->magieEff = 5;
    this->magie = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->magieFrames);
    for(int i = 0; i < magieFrames; i++){
        this->magie[i].x = w*i;
        this->magie[i].y = h*ligne;
        this->magie[i].w = w;
        this->magie[i].h = h;
    }

    ligne = 11;
    this->attackFrames = 15;
    this->attackEff = 9;
    this->attack = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->attackFrames);
    for(int i = 0; i < attackFrames; i++){
        this->attack[i].x = w*i;
        this->attack[i].y = h*ligne;
        this->attack[i].w = w;
        this->attack[i].h = h;
    }

    ligne = 12;
    this->aoeFrames = 12;
    this->aoeEff = 9;
    this->aoe = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->aoeFrames);
    for(int i = 0; i < aoeFrames; i++){
        this->aoe[i].x = w*i;
        this->aoe[i].y = h*ligne;
        this->aoe[i].w = w;
        this->aoe[i].h = h;
    }

    ligne = 13;
    this->laserBeamFrames = 17;
    this->laserBeamEff = 9;
    this->laserBeam = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->laserBeamFrames);
    for(int i = 0; i < laserBeamFrames; i++){
        this->laserBeam[i].x = w*i;
        this->laserBeam[i].y = h*ligne;
        this->laserBeam[i].w = w;
        this->laserBeam[i].h = h;
    }

    ligne = 14;
    this->defendreFrames = 19;
    this->defendreEff = 9;
    this->defendre = (SDL_Rect*) malloc(sizeof(SDL_Rect) * defendreFrames);
    for(int i = 0; i < defendreFrames; i++){
        this->defendre[i].x = w*i + 35;
        this->defendre[i].y = h*ligne;
        this->defendre[i].w = w;
        this->defendre[i].h = h;
    }

    ligne = 15;
    this->hurtFrames = 5;
    //this->hurtEff = 3 ;
    this->hurt = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->hurtFrames);
    for(int i = 0; i < hurtFrames; i++){
        this->hurt[i].x = w*i;
        this->hurt[i].y = h*ligne;
        this->hurt[i].w = w;
        this->hurt[i].h = h;
    }

    ligne = 16;
    this->deathFrames = 19;
    this->death = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->deathFrames);
    for(int i = 0; i < deathFrames; i++){
        this->death[i].x = w*i;
        this->death[i].y = h*ligne;
        this->death[i].w = w;
        this->death[i].h = h;
    }
}

void Profile::setBretteur(SDL_Rect* collider){
    //this->distant = true;
    this->collider = *collider;
    this->departCollider = *collider;
    int w = 288;
    int h = 128;

    int ligne = 0;
    this->idleFrames = 10;
    this->idle = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->idleFrames);
    for(int i = 0; i < idleFrames; i++){
        this->idle[i].x = w*i;
        this->idle[i].y = h*ligne;
        this->idle[i].w = w;
        this->idle[i].h = h;
    }
    this->currentClip = idle;
    this->currentFrames = &idleFrames;
    this->anim = IDLE;
    this->coeffFrame = 10;

    ligne = 1;
    this->walkFrames = 8;
    this->walk = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->walkFrames);
    for(int i = 0; i < walkFrames; i++){
        this->walk[i].x = w*i;
        this->walk[i].y = h*ligne;
        this->walk[i].w = w;
        this->walk[i].h = h;
    }

    ligne = 15;
    this->magieFrames = 19;
    this->magieEff = 16;
    this->magie = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->magieFrames);
    for(int i = 0; i < magieFrames; i++){
        this->magie[i].x = w*i;
        this->magie[i].y = h*ligne;
        this->magie[i].w = w;
        this->magie[i].h = h;
    }

    ligne = 13;
    this->attackFrames = 8;
    this->attackEff = 2;
    this->attack = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->attackFrames);
    for(int i = 0; i < attackFrames; i++){
        this->attack[i].x = w*i;
        this->attack[i].y = h*ligne;
        this->attack[i].w = w;
        this->attack[i].h = h;
    }

    ligne = 16;
    this->aoeFrames = 20;
    this->aoeEff = 13;
    this->aoe = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->aoeFrames);
    for(int i = 0; i < aoeFrames; i++){
        this->aoe[i].x = w*i;
        this->aoe[i].y = h*ligne;
        this->aoe[i].w = w;
        this->aoe[i].h = h;
    }
    /*
    ligne = 13;
    this->laserBeamFrames = 17;
    this->laserBeamEff = 9;
    this->laserBeam = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->laserBeamFrames);
    for(int i = 0; i < laserBeamFrames; i++){
        this->laserBeam[i].x = w*i;
        this->laserBeam[i].y = h*ligne;
        this->laserBeam[i].w = w;
        this->laserBeam[i].h = h;
    }*/

    ligne = 17;
    this->defendreFrames = 8;
    this->defendreEff = 4;
    this->defendre = (SDL_Rect*) malloc(sizeof(SDL_Rect) * defendreFrames);
    for(int i = 0; i < defendreFrames; i++){
        this->defendre[i].x = w*i;
        this->defendre[i].y = h*ligne;
        this->defendre[i].w = w;
        this->defendre[i].h = h;
    }

    ligne = 18;
    this->hurtFrames = 6;
    //this->hurtEff = 3 ;
    this->hurt = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->hurtFrames);
    for(int i = 0; i < hurtFrames; i++){
        this->hurt[i].x = w*i;
        this->hurt[i].y = h*ligne;
        this->hurt[i].w = w;
        this->hurt[i].h = h;
    }

    ligne = 20;
    this->deathFrames = 20;
    this->death = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->deathFrames);
    for(int i = 0; i < deathFrames; i++){
        this->death[i].x = w*i;
        this->death[i].y = h*ligne;
        this->death[i].w = w;
        this->death[i].h = h;
    }
}

void Profile::setNinja(SDL_Rect* collider){
    this->collider = *collider;
    this->departCollider = *collider;
    int w = 288;
    int h = 128;

    int ligne = 0;
    this->idleFrames = 8;
    this->idle = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->idleFrames);
    for(int i = 0; i < idleFrames; i++){
        this->idle[i].x = w*i;
        this->idle[i].y = h*ligne;
        this->idle[i].w = w;
        this->idle[i].h = h;
    }
    this->currentClip = idle;
    this->currentFrames = &idleFrames;
    this->anim = IDLE;
    this->coeffFrame = 10;

    ligne = 1;
    this->walkFrames = 8;
    this->walk = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->walkFrames);
    for(int i = 0; i < walkFrames; i++){
        this->walk[i].x = w*i;
        this->walk[i].y = h*ligne;
        this->walk[i].w = w;
        this->walk[i].h = h;
    }

    ligne = 7;
    this->attackFrames = 6;
    this->attackEff = 2;
    this->attack = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->attackFrames);
    for(int i = 0; i < attackFrames; i++){
        this->attack[i].x = w*i;
        this->attack[i].y = h*ligne;
        this->attack[i].w = w;
        this->attack[i].h = h;
    }

    ligne = 10;
    this->magieFrames = 8;
    this->magieEff = 5;
    this->magie = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->magieFrames);
    for(int i = 0; i < magieFrames; i++){
        this->magie[i].x = w*i;
        this->magie[i].y = h*ligne;
        this->magie[i].w = w;
        this->magie[i].h = h;
    }

    ligne = 13;
    this->defendreFrames = 12;
    this->defendreEff = 7;
    this->defendre = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->defendreFrames);
    for(int i = 0; i < defendreFrames; i++){
        this->defendre[i].x = w*i;
        this->defendre[i].y = h*ligne;
        this->defendre[i].w = w;
        this->defendre[i].h = h;
    }

    ligne = 14;
    this->hurtFrames = 6;
    //this->hurtEff = 3 ;
    this->hurt = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->hurtFrames);
    for(int i = 0; i < hurtFrames; i++){
        this->hurt[i].x = w*i;
        this->hurt[i].y = h*ligne;
        this->hurt[i].w = w;
        this->hurt[i].h = h;
    }

    ligne = 15;
    this->deathFrames = 12;
    this->death = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->deathFrames);
    for(int i = 0; i < deathFrames; i++){
        this->death[i].x = w*i;
        this->death[i].y = h*ligne;
        this->death[i].w = w;
        this->death[i].h = h;
    }
}

void Profile::setChevalier(SDL_Rect* collider){
    this->collider = *collider;
    this->departCollider = *collider;
    int w = 288;
    int h = 128;

    int ligne = 0;
    this->idleFrames = 8;
    this->idle = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->idleFrames);
    for(int i = 0; i < idleFrames; i++){
        this->idle[i].x = w*i;
        this->idle[i].y = h*ligne;
        this->idle[i].w = w;
        this->idle[i].h = h;
    }
    this->currentClip = idle;
    this->currentFrames = &idleFrames;
    this->anim = IDLE;
    this->coeffFrame = 10;

    ligne = 1;
    this->walkFrames = 8;
    this->walk = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->walkFrames);
    for(int i = 0; i < walkFrames; i++){
        this->walk[i].x = w*i;
        this->walk[i].y = h*ligne;
        this->walk[i].w = w;
        this->walk[i].h = h;
    }

    ligne = 7;
    this->attackFrames = 11;
    this->attackEff = 5;
    this->attack = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->attackFrames);
    for(int i = 0; i < attackFrames; i++){
        this->attack[i].x = w*i;
        this->attack[i].y = h*ligne;
        this->attack[i].w = w;
        this->attack[i].h = h;
    }

    ligne = 5;
    this->magieFrames = 8;
    this->magieEff = 4;
    this->magie = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->magieFrames);
    for(int i = 0; i < magieFrames; i++){
        this->magie[i].x = w*i;
        this->magie[i].y = h*ligne;
        this->magie[i].w = w;
        this->magie[i].h = h;
    }

    ligne = 11;
    this->defendreFrames = 10;
    this->defendreEff = 4;
    this->defendre = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->defendreFrames);
    for(int i = 0; i < defendreFrames; i++){
        this->defendre[i].x = w*i;
        this->defendre[i].y = h*ligne;
        this->defendre[i].w = w;
        this->defendre[i].h = h;
    }

    ligne = 12;
    this->hurtFrames = 6;
    //this->hurtEff = 3 ;
    this->hurt = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->hurtFrames);
    for(int i = 0; i < hurtFrames; i++){
        this->hurt[i].x = w*i;
        this->hurt[i].y = h*ligne;
        this->hurt[i].w = w;
        this->hurt[i].h = h;
    }

    ligne = 13;
    this->deathFrames = 13;
    this->death = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->deathFrames);
    for(int i = 0; i < deathFrames; i++){
        this->death[i].x = w*i;
        this->death[i].y = h*ligne;
        this->death[i].w = w;
        this->death[i].h = h;
    }
}

void Profile::setElementaliste(SDL_Rect* collider){
    this->distant = true;
    this->collider = *collider;
    this->departCollider = *collider;
    int w = 192;
    int h = 112;

    int ligne = 0;
    this->idleFrames = 8;
    this->idle = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->idleFrames);
    for(int i = 0; i < idleFrames; i++){
        this->idle[i].x = w*i;
        this->idle[i].y = h*ligne;
        this->idle[i].w = w;
        this->idle[i].h = h;
    }
    this->currentClip = idle;
    this->currentFrames = &idleFrames;
    this->anim = IDLE;
    this->coeffFrame = 10;

    ligne = 1;
    this->walkFrames = 10;
    this->walk = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->walkFrames);
    for(int i = 0; i < walkFrames; i++){
        this->walk[i].x = w*i;
        this->walk[i].y = h*ligne;
        this->walk[i].w = w;
        this->walk[i].h = h;
    }

    ligne = 5;
    this->attackFrames = 10;
    this->attackEff = 5;
    this->attack = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->attackFrames);
    for(int i = 0; i < attackFrames; i++){
        this->attack[i].x = w*i;
        this->attack[i].y = h*ligne;
        this->attack[i].w = w;
        this->attack[i].h = h;
    }

    ligne = 5;
    this->magieFrames = 10;
    this->magieEff = 5;
    this->magie = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->magieFrames);
    for(int i = 0; i < magieFrames; i++){
        this->magie[i].x = w*i;
        this->magie[i].y = h*ligne;
        this->magie[i].w = w;
        this->magie[i].h = h;
    }

    ligne = 6;
    this->defendreFrames = 4;
    this->defendreEff = 3;
    this->defendre = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->defendreFrames);
    for(int i = 0; i < defendreFrames; i++){
        this->defendre[i].x = w*i;
        this->defendre[i].y = h*ligne;
        this->defendre[i].w = w;
        this->defendre[i].h = h;
    }

    ligne = 9;
    this->hurtFrames = 5;
    //this->hurtEff = 3 ;
    this->hurt = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->hurtFrames);
    for(int i = 0; i < hurtFrames; i++){
        this->hurt[i].x = w*i;
        this->hurt[i].y = h*ligne;
        this->hurt[i].w = w;
        this->hurt[i].h = h;
    }

    ligne = 10;
    this->deathFrames = 11;
    this->death = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->deathFrames);
    for(int i = 0; i < deathFrames; i++){
        this->death[i].x = w*i;
        this->death[i].y = h*ligne;
        this->death[i].w = w;
        this->death[i].h = h;
    }
}

void Profile::setVoleur(SDL_Rect* collider){
    this->collider = *collider;
    this->departCollider = *collider;
    int w = 48;
    int h = 48;

    int ligne = 0;
    this->idleFrames = 4;
    this->idle = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->idleFrames);
    for(int i = 0; i < idleFrames; i++){
        this->idle[i].x = w*i;
        this->idle[i].y = h*ligne;
        this->idle[i].w = w;
        this->idle[i].h = h;
    }

    this->currentClip = idle;
    this->currentFrames = &idleFrames;
    this->anim = IDLE;
    this->coeffFrame = 10;

    ligne = 1;
    this->walkFrames = 8;
    this->walk = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->walkFrames);
    for(int i = 0; i < walkFrames; i++){
        this->walk[i].x = w*i;
        this->walk[i].y = h*ligne;
        this->walk[i].w = w;
        this->walk[i].h = h;
    }

    ligne = 2;
    this->prepareFrames = 4;
    this->prepare = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->prepareFrames);
    for(int i = 0; i < prepareFrames; i++){
        this->prepare[i].x = w*i;
        this->prepare[i].y = h*ligne;
        this->prepare[i].w = w;
        this->prepare[i].h = h;
    }

    ligne = 2;
    this->attackFrames = 4;
    this->attackEff = 0;
    this->attack = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->attackFrames);
    for(int i = 0; i < attackFrames; i++){
        this->attack[i].x = w*(i + 4);
        this->attack[i].y = h*ligne;
        this->attack[i].w = w;
        this->attack[i].h = h;
    }

    ligne = 4;
    this->hurtFrames = 3;
    this->hurt = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->hurtFrames);
    for(int i = 0; i < hurtFrames; i++){
        this->hurt[i].x = w*i;
        this->hurt[i].y = h*ligne;
        this->hurt[i].w = w;
        this->hurt[i].h = h;
    }

    this->deathFrames = 1;
    this->death = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->deathFrames);
    this->death[0].x = 193;
    this->death[0].y = 192;
    this->death[0].w = 38;
    this->death[0].h = 46;

}

void Profile::setSamourai(SDL_Rect* collider){
    this->collider = *collider;
    this->departCollider = *collider;
    int w = 200;
    int h = 200;

    int ligne = 0;
    this->attackFrames = 6;
    this->attackEff = 5;
    this->attack = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->attackFrames);
    for(int i = 0; i < attackFrames; i++){
        this->attack[i].x = w*i;
        this->attack[i].y = h*ligne;
        this->attack[i].w = w;
        this->attack[i].h = h;
    }

    ligne = 1;
    this->attack1Frames = 6;
    this->attack1 = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->attack1Frames);
    for(int i = 0; i < attack1Frames; i++){
        this->attack1[i].x = w*i;
        this->attack1[i].y = h*ligne;
        this->attack1[i].w = w;
        this->attack1[i].h = h;
    }

    ligne = 2;
    this->deathFrames = 6;
    this->death = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->deathFrames);
    for(int i = 0; i < deathFrames; i++){
        this->death[i].x = w*i;
        this->death[i].y = h*ligne;
        this->death[i].w = w;
        this->death[i].h = h;
    }

    ligne = 4;
    this->idleFrames = 8;
    this->idle = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->idleFrames);
    for(int i = 0; i < idleFrames; i++){
        this->idle[i].x = w*i;
        this->idle[i].y = h*ligne;
        this->idle[i].w = w;
        this->idle[i].h = h;
    }

    ligne = 6;
    this->walkFrames = 8;
    this->walk = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->walkFrames);
    for(int i = 0; i < walkFrames; i++){
        this->walk[i].x = w*i;
        this->walk[i].y = h*ligne;
        this->walk[i].w = w;
        this->walk[i].h = h;
    }

    ligne = 7;
    this->hurtFrames = 4;
    this->hurt = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->hurtFrames);
    for(int i = 0; i < hurtFrames; i++){
        this->hurt[i].x = w*i;
        this->hurt[i].y = h*ligne;
        this->hurt[i].w = w;
        this->hurt[i].h = h;
    }

    ligne = 6;
    this->defendreFrames = 7;
    this->defendreEff = 2;
    this->defendre = (SDL_Rect*) malloc(sizeof(SDL_Rect) * this->defendreFrames);
    for(int i = 0; i < defendreFrames; i++){
        this->defendre[i].x = w*i;
        this->defendre[i].y = h*ligne;
        this->defendre[i].w = w;
        this->defendre[i].h = h;
    }


    this->currentClip = idle;
    this->currentFrames = &idleFrames;
    this->anim = IDLE;
    this->coeffFrame = 10;
}

void Profile::changeAnimation(Animation anim){
    this->frame = 0;
    switch(anim){
    case IDLE:
        this->currentClip = idle;
        this->currentFrames = &idleFrames;
        this->anim = IDLE;
        break;
    case WAIT:
        this->currentClip = idle;
        this->currentFrames = &idleFrames;
        this->anim = WAIT;
        break;
    case ATTACK:
        this->currentClip = attack;
        this->currentFrames = &attackFrames;
        this->anim = ATTACK;
        break;
    case HURT:
        this->currentClip = hurt;
        this->currentFrames = &hurtFrames;
        this->anim = HURT;
        break;
    case WALK:
        this->currentClip = walk;
        this->currentFrames = &walkFrames;
        this->anim = WALK;
        break;
    case PREPARE:
        this->currentClip = prepare;
        this->currentFrames = &prepareFrames;
        this->anim = PREPARE;
        break;
    case DEATH:
        this->currentClip = death;
        this->currentFrames = &deathFrames;
        this->anim = DEATH;
        break;
    case MAGIE:
        this->currentClip = magie;
        this->currentFrames = &magieFrames;
        this->anim = MAGIE;
        break;
    case DEFENDRE:
        this->currentClip = defendre;
        this->currentFrames = &defendreFrames;
        this->anim = DEFENDRE;
        break;
    case AVANCER:
        this->currentClip = walk;
        this->currentFrames = &walkFrames;
        this->anim = AVANCER;
        break;
    case RECULER:
        this->currentClip = walk;
        this->currentFrames = &walkFrames;
        this->anim = RECULER;
        break;
    }
}

Animation Profile::getAnimType() const{
    return this->anim;
}

void Profile::resetAnimation(){
    this->frame = 0;
    this->currentClip = idle;
    this->currentFrames = &idleFrames;
    this->anim = IDLE;
    this->rect = depart; //on reset la position
    this->collider = departCollider;
}

int Profile::getInit(){
    return this->stats.init;
}

bool Profile::getIsPlayer(){
    return this->isPlayer;
}

void Profile::startAnimation(){
    this->playAnimation = true;
}

string Profile::getNameString(){
    return this->name;
}

int Profile::getPvMax(){
    return this->stats.pvMax;
}

int Profile::getPmMax(){
    return this->stats.pmMax;
}

//Renvoit false si la cible est toujours en vie, renvoit true si la cible est tuee
bool Profile::attaquer(Profile* cible, int* degats, TypeDegat tDegat, Element e){
    int resistance = 0, cpt=0;
    int attaque = 0;

    this->enDefense = false;

    printf("%s attaque %s\n", this->name.c_str(), cible->getName());

    if(tDegat != NEUTRE){
        cpt++;
        switch(tDegat){
        case TRANCHANT:
            resistance += cible->getResTranchant();
            break;
        case PERCANT:
            resistance += cible->getResPercant();
            break;
        case CONTONDANT:
            resistance += cible->getResContondant();
            break;
        case EXPLOSIF:
            resistance += cible->getResExplosif();
            break;
        }
    }
    if(e != NONE){
        cpt++;
        switch(e){
        case FEU:
            resistance += cible->getResFeu();
            break;
        case GLACE:
            resistance += cible->getResGlace();
            break;
        case FOUDRE:
            resistance += cible->getResFoudre();
            break;
        case AIR:
            resistance += cible->getResAir();
            break;
        case EAU:
            resistance += cible->getResEau();
            break;
        case TERRE:
            resistance += cible->getResTerre();
            break;
        case LUMIERE:
            resistance += cible->getResLumiere();
            break;
        case TENEBRES:
            resistance += cible->getResTenebres();
            break;
        }
    }
    if(cpt !=0)
        *degats = this->getAtq() * (100-resistance/cpt)/100;
    else
        throw("Division par 0 !");

    //Crit
    if(randomNumber100() <= this->stats.crit){
        *degats*=(1 + this->stats.multCrit);
    }

    if(cible->getEnDefense()){
        *degats /= 2;
    }
    if(*degats < 0){
        *degats = 0;
    }
    cible->updateStats(Substract, PV, *degats);
    printf("%s inflige %d degats a %s.\n", this->name.c_str(), *degats, cible->getName());
    printf("Il reste %d PV a %s.\n\n", cible->getPv(), cible->getName());

    if(cible->getPv() == 0){
        return true;
    }
    else{
        return false;
    }
}

bool Profile::lancerMagie(Profile* cible, Magie* magie, int* degats){
        this->enDefense = false;
        int factElem = 0;

        bool succes = false; //permet de verifier le succes d'un evenement aleatoire

        switch(magie->getElem()){
        case FEU:
            factElem = cible->getResFeu();
            succes = randomNumber100() > magie->getFleauSucces();
            magie->incrementTours();
            if(!magie->getSucces() && (magie->getTours() < magie->getPeriodeTours())){
                if(succes){
                    cible->fleau = BRULURE;
                    cible->fleauDuree = magie->getFleauDuree();
                    printf("%s se met a bruler.\n", cible->getName());
                    magie->setSucces();
                }
                else{
                    printf("%s resiste a la brulure.\n", cible->getName());
                }
            }
            else if(magie->getSucces() && (magie->getTours() < magie->getPeriodeTours()) ){
                printf("%s resiste a la brulure.\n", cible->getName());
            }
            if(magie->getTours() >= magie->getPeriodeTours()){
                if(!magie->getSucces()){
                    cible->fleau = BRULURE;
                    cible->fleauDuree = magie->getFleauDuree();
                    printf("%s se met a bruler.\n", cible->getName());
                    magie->setSucces();
                }
                else{
                    printf("%s resiste a la brulure.\n", cible->getName());
                }
                magie->resetTours();
                magie->resetSucces();
            }

            break;
        case GLACE:
            factElem = cible->getResGlace();
            break;
        case FOUDRE:
            factElem = cible->getResFoudre();
            break;
        case AIR:
            factElem = cible->getResAir();
            break;
        case EAU:
            factElem = cible->getResEau();
            break;
        case TERRE:
            factElem = cible->getResTerre();
            break;
        }
        if(magie->getPuissance() != 0){
            if(magie->getTypeDegat() != SOIN){
                *degats = (100 - factElem) * (this->stats.magieNoire + magie->getPuissance())/100;
                if(cible->getEnDefense()){
                    *degats /= 2;
                }
                if(*degats < 0){
                    *degats == 0;
                }
            }
            else{
                *degats = (100-factElem) * (-this->stats.magieNoire + magie->getPuissance())/100;
            }

            cible->updateStats(Substract, PV, *degats);
            printf("%s inflige %d degats a %s. \n", this->name.c_str(), *degats, cible->getName());
            printf("Il reste %d PV a %s.\n\n", cible->getPv(), cible->getName());
        }
        else{
            *degats = 0;
        }


        //Gestion des etats
        if(magie->getEtat() != AUCUN){
            cible->listeEtats[nbrEtats] = magie->getEtat();
            cible->dureeEtats[nbrEtats] = magie->getDureeEtat();
            cible->nbrEtats ++;

            switch(magie->getEtat()){
            case BARRIERE:
                cible->updateStats(Multiply, DEF, 13);
                cible->updateStats(Divide, DEF, 10);
                break;
            }
        }

        if(cible->getPv() == 0){
            return true;
        }
        else{
            return false;
        }
}

void Profile::setStats(Sts stat, int value){
    //PV, PM, INIT, ATQ, MAG, DEF
    switch(stat){
    case PV:
        stats.pv = value;
        stats.pvMax = value;
        break;
    case PM:
        stats.pm = value;
        stats.pmMax = value;
        break;
    case INIT:
        stats.init = value;
        break;
    case ATQ:
        stats.atq = value;
        break;
    case MAG:
        stats.magieNoire = value;
        break;
    }
}

void Profile::seDefendre(){
    printf("%s se defend des attaques. \n\n", this->name.c_str());
    this->enDefense = true;
}

bool Profile::getIsDead(){
    return this->isDead;
}

void Profile::setIsDead(bool b){
    this->isDead = b;
}

int Profile::getResTranchant(){
    return this->res.resTranchant;
}

int Profile::getResPercant(){
    return this->res.resPercant;
}

int Profile::getResContondant(){
    return this->res.resContondant;
}

int Profile::getResExplosif(){
    return this->res.resExplosion;
}

int Profile::getResFeu(){
    return this->res.resFeu;
}

int Profile::getResGlace(){
    return this->res.resGlace;
}

int Profile::getResFoudre(){
    return this->res.resFoudre;
}

int Profile::getResAir(){
    return this->res.resAir;
}

int Profile::getResEau(){
    return this->res.resEau;
}

int Profile::getResTerre(){
    return this->res.resTerre;
}

int Profile::getResLumiere(){
    return this->res.resLumiere;
}

int Profile::getResTenebres(){
    return this->res.resTenebres;
}

void Profile::setDistant(){
    this->distant = true;
}

Texture* Profile::getPortrait(){
    return this->portrait;
}

void Profile::calculerStats(){
    this->stats.pv = 50 + this->attr.force/2 + this->attr.cons;
    this->stats.pvMax = this->stats.pv;
    this->stats.regPv = this->stats.pv/10 + this->attr.cons/10;

    this->stats.pmMax= 50 + this->attr.intel + this->attr.piete;
    this->stats.pm = this->stats.pmMax;
    this->stats.regPm = 10 + this->attr.piete/10;

    this->stats.init = this->attr.dext + this->attr.intel + this->attr.tena;

    switch(this->typeArme){
    case FORCE:
        this->stats.atq = this->attr.force;
        break;
    case DEXTERITE:
        this->stats.atq = this->attr.dext;
        break;
    }

    this->stats.atq += this->attr.cons/2 + this->attr.deter;
    this->stats.magieNoire = this->attr.intel + this->attr.deter;
    this->stats.magieBlanche = this->attr.sag + this->attr.deter;

    this->stats.prc = 90 + this->attr.dext + this->attr.chc + this->attr.deter/2;
    this->stats.esq = this->attr.deter + this->attr.sag + this->attr.chc;
    this->stats.crit = this->attr.dext + this->attr.chc + this->attr.deter/2;

    this->stats.multCrit = 25 + this->attr.force;
}

void Profile::initAttributs(){
    this->attr.force=1;
    this->attr.dext=1;
    this->attr.cons=5;
    this->attr.intel=1;
    this->attr.sag=1;
    this->attr.chc=1;
    this->attr.deter=0;
    this->attr.tena=0;
    this->attr.piete=0;

    calculerStats();
}

void Profile::setAttributs(){

}

void Profile::initRes(){

    int tena = this->attr.tena;

    //res physiques
    this->res.resTranchant=tena;
    this->res.resPercant=tena;
    this->res.resContondant=tena;
    this->res.resExplosion=tena;

    //res élémentaires
    this->res.resFeu=tena;
    this->res.resGlace=tena;
    this->res.resFoudre=tena;
    this->res.resAir=tena;
    this->res.resEau=tena;
    this->res.resTerre=tena;
    this->res.resLumiere=tena;
    this->res.resTenebres=tena;

    this->res.resAlterations=this->attr.cons+this->attr.sag;
    this->res.resCrit=this->attr.chc;

}
