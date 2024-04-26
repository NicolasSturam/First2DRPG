#include "Texture.h"

void initCouleurs(Couleurs* couleurs){
    couleurs->vert = {0,255,0};
    couleurs->blanc = {255, 255, 255};
    couleurs->grisPale = {220,220,220};
    couleurs->noir = {0,0,0};
}

Texture::Texture(){
    this->texture = NULL;
    this->rect = {0,0,0,0};
    this->collider = {0,0,0,0};
}

Texture::Texture(SDL_Rect* rect){
    this->texture = NULL;
    this->rect = *rect;
    this->collider = {0,0,0,0};
}

Texture::Texture(string text, SDL_Renderer* renderer, TTF_Font* font, SDL_Color* textColor){
    this->texture = loadRenderText(text, renderer, font, *textColor);
}

Texture::Texture(string path, SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect collider)
{
    this->texture = loadTexture(path, renderer);
    this->rect = rect;
    this->collider = collider;
}

/*
Texture::Texture(Texture* texture){
    this->texture = texture->texture;
}*/

Texture::~Texture()
{
    if(this->texture != NULL ){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
    }
}

void Texture::loadNewTexture(string path, SDL_Renderer* renderer, SDL_Rect rect){
    this->texture = loadTexture(path, renderer);
    this->rect = rect;
}

void Texture::loadNewTexture(string text, SDL_Renderer* renderer, TTF_Font* font, SDL_Color* textColor){
    if(this->texture != NULL){
        if(this->texture != NULL ){
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
        }
    }
    this->texture = loadRenderText(text, renderer, font, *textColor);
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip,  int camX, int camY, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect rect2;
    rect2.x = this->rect.x - camX;
    rect2.y = this->rect.y - camY;
    rect2.w = this->rect.w;
    rect2.h = this->rect.h;

    //Set rendering space and render to screen
    if(this->texture != NULL){
        SDL_RenderCopyEx( renderer, this->texture, clip, &rect2, angle, center, flip );
    }
}

void Texture::renderText(SDL_Renderer* renderer, SDL_Rect* rect,  int camX, int camY, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect rect2;
    rect2.x = rect->x - camX;
    rect2.y = rect->y - camY;
    rect2.w = rect->w;
    rect2.h = rect->h;

    //Set rendering space and render to screen
    if(this->texture != NULL){
        SDL_RenderCopyEx( renderer, this->texture, NULL, &rect2, angle, center, flip );
    }
}

void Texture::renderText(SDL_Renderer* renderer, int camX, int camY, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect rect2;
    rect2.x = this->rect.x - camX;
    rect2.y = this->rect.y - camY;
    rect2.w = this->rect.w;
    rect2.h = this->rect.h;

    //Set rendering space and render to screen
    if(this->texture != NULL){
        SDL_RenderCopyEx( renderer, this->texture, NULL, &rect2, angle, center, flip );
    }
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* rect, int camX, int camY, double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_Rect rect2;
    rect2.x = rect->x - camX;
    rect2.y = rect->y - camY;
    rect2.w = rect->w;
    rect2.h = rect->h;

    //Set rendering space and render to screen
    if(this->texture != NULL){
        SDL_RenderCopyEx( renderer, this->texture, clip, &rect2, angle, center, flip );
    }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue){
    //Modulate texture
    if(this->texture != NULL){
        SDL_SetTextureColorMod(this->texture, red, green, blue);
    }
    else{
        printf("Erreur ! Pas de texture assignee.\n");
    }
}

void Texture::setPosition(int x, int y){
    this->rect.x = x;
    this->rect.y = y;
    this->depart.x = x;
    this->depart.y = y;
}

void Texture::setX(int x){
    this->rect.x = x;
}

void Texture::setY(int y){
    this->rect.y = y;
}

void Texture::setSize(int w, int h){
    this->rect.w = w;
    this->rect.h = h;
}

void Texture::setW(int w){
    this->rect.w = w;
}

void Texture::setH(int h){
    this->rect.h = h;
}

int Texture::getRectX()const{
    return this->rect.x;
}

int Texture::getRectY()const{
    return this->rect.y;
}

int Texture::getRectW()const{
    return this->rect.w;
}

int Texture::getRectH()const{
    return this->rect.h;
}

SDL_Rect* Texture::getRect() {
    return &this->rect;
}

int Texture::getColliderX() const{
    return this->collider.x;
}

int Texture::getColliderY() const{
    return this->collider.y;
}

int Texture::getColliderW() const{
    return this->collider.w;
}

int Texture::getColliderH() const{
    return this->collider.h;
}

SDL_Rect* Texture::getCollider() {
    return &this->collider;
}

void Texture::addToX(int x){
    this->rect.x += x;
}

void Texture::addToCollider(int x){
    this->collider.x += x;
}

void Texture::setRect(SDL_Rect* rect){
    this->rect = *rect;
}

SDL_Texture* Texture::getTexture(){
    return this->texture;
}
