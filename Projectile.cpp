#include "Projectile.h"

Projectile::Projectile(){
    this->trajectFrames = 0;
    this->trajet= NULL;

    this->impactFrames = 0;
    this->impactEff = 0;
    this->impact = NULL;

    this->playAnimation = false;

    this->frame = 0;
    this->currentFrames = NULL;
    this->currentClip = NULL;

    this->type = TRAJET;
}

Projectile::~Projectile(){
    if(this->trajet != NULL){
        free(this->trajet);
    }
    if(this->impact != NULL){
        free(this->impact);
    }
}

void Projectile::setFeu( string path, SDL_Renderer* renderer, SDL_Rect rect1, SDL_Rect rect2, SDL_Rect collider ){
    this->texture = loadTexture(path, renderer);
    this->trajetRect = rect1;
    this->impactRect = rect2;
    this->xStart = rect1.x;
    this->yStart = rect1.y;
    this->collider = collider;

    //clips du trajet
    int w = 64;
    int h = 32;
    this->trajectFrames = 5;
    this->trajet = (SDL_Rect*) malloc(sizeof(SDL_Rect) * trajectFrames ); //clips pour le trajet du projectile
    for(int i=0;i < trajectFrames;i++){
        if(i < trajectFrames-1){
            this->trajet[i].x = w*i;
            this->trajet[i].y = 0;
        }
        else{
            this->trajet[i].x = 0;
            this->trajet[i].y = 32;
        }
        this->trajet[i].w = w;
        this->trajet[i].h = h;
    }

    this->currentFrames = &this->trajectFrames;
    this->currentClip = this->trajet;
    this->type = TRAJET;

    //clips  de l'impact
    h = 64;
    this->impactFrames = 13;
    this->impactEff = 2;
    this->impact = (SDL_Rect*) malloc(sizeof(SDL_Rect) * impactFrames );
    for(int i=0;i < impactFrames;i++){
        if(i < 3){
            this->impact[i].x = 64 + i*w;
            this->impact[i].y = 32;
        }
        else if(i > 2 && i < 7){
            this->impact[i].x = i*w - 3*w;
            this->impact[i].y = h+32;
        }
        else if(i > 6 && i < 11){
            this->impact[i].x = i*w - 7*w;
            this->impact[i].y = h*2+32;
        }
        else{
            this->impact[i].x = i*w - 11*w;
            this->impact[i].y = h*3+32;
        }
        this->impact[i].w = w;
        this->impact[i].h = h;
    }
}

bool Projectile::render(SDL_Renderer* renderer, Profile* profile, double angle, SDL_Point* center, SDL_RendererFlip flip){
    bool eff = false;
    if(this->playAnimation){
        if(this->frame == this->impactEff*10 && this->type == IMPACT){
            eff = true;
            profile->updateIsTurn(false);
        }
        if(this->type == TRAJET){
            SDL_RenderCopyEx( renderer, this->texture, &this->currentClip[this->frame/10], &this->trajetRect, angle, center, flip );
        }
        else{
            SDL_RenderCopyEx( renderer, this->texture, &this->currentClip[this->frame/10], &this->impactRect, angle, center, flip );
        }
        this->frame ++;
        if(this->frame/10 >= (*currentFrames) ){
            this->frame = 0;
            if( this->type ==  IMPACT ){
                this->playAnimation = false;
                this->currentFrames = &this->trajectFrames;
                this->currentClip = this->trajet;
                this->type = TRAJET;

                this->trajetRect.x = xStart;
                this->trajetRect.y = yStart;

                this->impactRect.x = xStart;
                this->impactRect.y = yStart;

                this->collider.x = xStart;
                this->collider.y = yStart;

                if(profile->getAnimType() == WAIT){
                    profile->changeAnimation(IDLE);
                }
            }
        }
    }
    return eff;
}

void Projectile::setAnimType(Etape type){
    this->frame = 0;
    if(type == IMPACT){
        this->currentClip = this->impact;
        this->currentFrames = &impactFrames;
        this->type = IMPACT;
    }

}

void Projectile::startAnimation(){
    this->playAnimation = true;
}

bool Projectile::getAnimationState(){
    return this->playAnimation;
}

Etape Projectile::getType(){
    return this->type;
}

void Projectile::addToTrajet(int x){
    this->trajetRect.x += x;
}
