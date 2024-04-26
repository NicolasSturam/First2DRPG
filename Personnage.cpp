#include "Personnage.h"

Personnage::Personnage(){
    this->vitX = 0;
    this->vitY = 0;
    this->maxVit = 0;
    this->currentClip = NULL;
    this->playAnimation = false;
    this->frame = 0;
}

Personnage::~Personnage(){
}

Personnage::Personnage(string path, SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect collider )
:Texture(path, renderer, rect, collider)
{
    this->vitX = 0;
    this->vitY = 0;
    this->maxVit = 0;
    this->currentClip = NULL;
    playAnimation = false;
    frame = 0;
}

void Personnage::setArcher(){
    this->maxVit = 3;

    //Clips de marche vers le bas
    this->marcheBas[0].x = 7;
    this->marcheBas[0].y = 3;
    this->marcheBas[0].w = 33;
    this->marcheBas[0].h = 45;

    this->marcheBas[1].x = 55;
    this->marcheBas[1].y = 3;
    this->marcheBas[1].w = 33;
    this->marcheBas[1].h = 45;

    this->marcheBas[2].x = 103;
    this->marcheBas[2].y = 3;
    this->marcheBas[2].w = 33;
    this->marcheBas[2].h = 45;

    this->marcheBas[3].x = 55;
    this->marcheBas[3].y = 3;
    this->marcheBas[3].w = 33;
    this->marcheBas[3].h = 45;


    //Clips de marche vers le haut
    this->marcheHaut[0].x = 7;
    this->marcheHaut[0].y = 147;
    this->marcheHaut[0].w = 33;
    this->marcheHaut[0].h = 45;

    this->marcheHaut[1].x = 55;
    this->marcheHaut[1].y = 147;
    this->marcheHaut[1].w = 33;
    this->marcheHaut[1].h = 45;

    this->marcheHaut[2].x = 103;
    this->marcheHaut[2].y = 147;
    this->marcheHaut[2].w = 33;
    this->marcheHaut[2].h = 45;

    this->marcheHaut[3].x = 55;
    this->marcheHaut[3].y = 147;
    this->marcheHaut[3].w = 33;
    this->marcheHaut[3].h = 45;

    //Clips de marche vers la gauche
    this->marcheGauche[0].x = 7;
    this->marcheGauche[0].y = 51;
    this->marcheGauche[0].w = 34;
    this->marcheGauche[0].h = 45;

    this->marcheGauche[1].x = 55;
    this->marcheGauche[1].y = 51;
    this->marcheGauche[1].w = 34;
    this->marcheGauche[1].h = 45;

    this->marcheGauche[2].x = 103;
    this->marcheGauche[2].y = 51;
    this->marcheGauche[2].w = 34;
    this->marcheGauche[2].h = 45;

    this->marcheGauche[3].x = 55;
    this->marcheGauche[3].y = 51;
    this->marcheGauche[3].w = 34;
    this->marcheGauche[3].h = 45;

    //Clips de marche vers la droite
    this->marcheDroite[0].x = 6;
    this->marcheDroite[0].y = 99;
    this->marcheDroite[0].w = 34;
    this->marcheDroite[0].h = 45;

    this->marcheDroite[1].x = 54;
    this->marcheDroite[1].y = 99;
    this->marcheDroite[1].w = 34;
    this->marcheDroite[1].h = 45;

    this->marcheDroite[2].x = 102;
    this->marcheDroite[2].y = 99;
    this->marcheDroite[2].w = 33;
    this->marcheDroite[2].h = 45;

    this->marcheDroite[3].x = 54;
    this->marcheDroite[3].y = 99;
    this->marcheDroite[3].w = 34;
    this->marcheDroite[3].h = 45;

    this->currentClip = marcheBas;

}

void Personnage::setVoleur(){
    this->maxVit = 2;

    //Clips de marche vers le bas
    this->marcheBas[0].x = 293;
    this->marcheBas[0].y = 194;
    this->marcheBas[0].w = 39;
    this->marcheBas[0].h = 45;

    this->marcheBas[1].x = 341;
    this->marcheBas[1].y = 194;
    this->marcheBas[1].w = 39;
    this->marcheBas[1].h = 45;

    this->marcheBas[2].x = 389;
    this->marcheBas[2].y = 194;
    this->marcheBas[2].w = 39;
    this->marcheBas[2].h = 45;

    this->marcheBas[3].x = 341;
    this->marcheBas[3].y = 194;
    this->marcheBas[3].w = 39;
    this->marcheBas[3].h = 45;


    //Clips de marche vers le haut
    this->marcheHaut[0].x = 293;
    this->marcheHaut[0].y = 339;
    this->marcheHaut[0].w = 39;
    this->marcheHaut[0].h = 45;

    this->marcheHaut[1].x = 341;
    this->marcheHaut[1].y = 339;
    this->marcheHaut[1].w = 39;
    this->marcheHaut[1].h = 45;

    this->marcheHaut[2].x = 389;
    this->marcheHaut[2].y = 339;
    this->marcheHaut[2].w = 39;
    this->marcheHaut[2].h = 45;

    this->marcheHaut[3].x = 341;
    this->marcheHaut[3].y = 339;
    this->marcheHaut[3].w = 39;
    this->marcheHaut[3].h = 45;

    //Clips de marche vers la gauche
    this->marcheGauche[0].x = 297;
    this->marcheGauche[0].y = 242;
    this->marcheGauche[0].w = 36;
    this->marcheGauche[0].h = 45;

    this->marcheGauche[1].x = 345;
    this->marcheGauche[1].y = 242;
    this->marcheGauche[1].w = 36;
    this->marcheGauche[1].h = 45;

    this->marcheGauche[2].x = 393;
    this->marcheGauche[2].y = 242;
    this->marcheGauche[2].w = 36;
    this->marcheGauche[2].h = 45;

    this->marcheGauche[3].x = 345;
    this->marcheGauche[3].y = 242;
    this->marcheGauche[3].w = 36;
    this->marcheGauche[3].h = 45;

    //Clips de marche vers la droite
    this->marcheDroite[0].x = 292;
    this->marcheDroite[0].y = 290;
    this->marcheDroite[0].w = 36;
    this->marcheDroite[0].h = 45;

    this->marcheDroite[1].x = 340;
    this->marcheDroite[1].y = 290;
    this->marcheDroite[1].w = 36;
    this->marcheDroite[1].h = 45;

    this->marcheDroite[2].x = 388;
    this->marcheDroite[2].y = 290;
    this->marcheDroite[2].w = 36;
    this->marcheDroite[2].h = 45;

    this->marcheDroite[3].x = 340;
    this->marcheDroite[3].y = 290;
    this->marcheDroite[3].w = 36;
    this->marcheDroite[3].h = 45;

    this->currentClip = marcheBas;

}

void Personnage::render(SDL_Renderer* renderer, int camX, int camY, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect rect2 = this->rect;
    //On redefinit rect en fonction de cam
    rect2.x = rect2.x - camX;
    rect2.y = rect2.y - camY;

    if(this->playAnimation){
        SDL_RenderCopyEx( renderer, this->texture, &this->currentClip[this->frame/10], &rect2, angle, center, flip );
        this->frame ++;
        if(this->frame/10 >= this->FRAMES){
            this->frame = 0;
        }
    }
    else{
        SDL_RenderCopyEx( renderer, this->texture, &this->currentClip[1], &rect2, angle, center, flip );
    }
}

void Personnage::ajusterClip(){
    //On ajuste le clip du perso en fonction de sa vitesse
    if(this->vitX != 0 || this->vitY != 0){
        this->playAnimation = true;
        if(this->vitX > 0){
            this->currentClip = this->marcheDroite;
        }
        else if(this->vitX < 0){
            this->currentClip = this->marcheGauche;
        }
        else if(this->vitY > 0 && this->vitX == 0){
            this->currentClip = this->marcheBas;
        }
        else if(this->vitY < 0 && this->vitX == 0){
            this->currentClip = this->marcheHaut;
        }
    }
}

void Personnage::stop(){
    this->vitX = 0;
    this->vitY = 0;
    this->playAnimation = false;
}

void Personnage::ajusterVitesse(){
    //On ajuste la  vitesse en diagonale
    if( abs(this->vitX) == this->getMaxVit() && abs(this->vitY) == this->getMaxVit() ){
        this->vitX = sqrt(2.0)/2.0 * this->vitX;
        this->vitY = sqrt(2.0)/2.0 * this->vitY;
    }
    else if(this->vitX > 0 && this->vitY == 0){
        this->vitX = this->maxVit;
    }
    else if(this->vitX < 0 && this->vitY == 0){
        this->vitX = -this->maxVit;
    }
    else if(this->vitY > 0 && this->vitX == 0){
        this->vitY = this->maxVit;
    }
    else if(this->vitY < 0 && this->vitX == 0){
        this->vitY = -this->maxVit;
    }
}

void Personnage::moveSprite(int level_width, int level_height, SDL_Rect* wall, int nbrMur){
    //Move the character left or right
    this->rect.x += this->vitX;
    this->collider.x += this->vitX;
    //If the character went too far to the left or right or collided
    if( ( this->rect.x < 0 ) || ( this->rect.x + this->rect.w > level_width   ) || checkCollision(&this->collider, wall, nbrMur))
    {
        //Move back
        this->rect.x -= this->vitX;
        this->collider.x -= this->vitX;
    }
    //Move the character up or down
    this->rect.y += this->vitY;
    this->collider.y += this->vitY;

    //If the character went too far up or down
    if( ( this->rect.y < 0 ) || ( this->rect.y + this->rect.h > level_height  ) || checkCollision(&this->collider, wall, nbrMur))
    {
        //Move back
        this->rect.y -= this->vitY;
        this->collider.y -= this->vitY;
    }
}

void Personnage::setMaxVitX(){
    this->vitX = this->maxVit;
}

void Personnage::setMinVitX(){
    this->vitX = -this->maxVit;
}

void Personnage::setMaxVitY(){
    this->vitY = this->maxVit;
}

void Personnage::setMinVitY(){
    this->vitY = -this->maxVit;
}

void Personnage::setVitX(int vit){
    this->vitX = vit;
}

void Personnage::setVitY(int vit){
    this->vitY = vit;
}

int Personnage::getMaxVit() const{
    return this->maxVit;
}
int Personnage::getVitX() const{
    return this->vitX;
}

int Personnage::getVitY() const{
    return this->vitY;
}

int Personnage::getFrames() const{
    return this->FRAMES;
}

SDL_Rect* Personnage::getCurrentClip() const{
    return this->currentClip;
}

bool Personnage::getPlayAnimation() const{
    return this->playAnimation;
}

int Personnage::getFrame() const{
    return this->frame;
}
