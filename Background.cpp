#include "Background.h"

Background::Background(string path, SDL_Renderer* renderer, SDL_Rect rect)
: Texture(path, renderer, rect)
{
    this->nbrMur = 0;
    this->murs = NULL;
}

Background::~Background(){
    if(murs != NULL){
        free(murs);
    }
}

void Background::render(SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    //Set rendering space and render to screen
    if(this->texture != NULL){
        SDL_RenderCopyEx( renderer, this->texture, clip, &this->rect, angle, center, flip );
    }
    else{
        printf("Erreur ! Pas de texture assignee.\n");
    }
}

void Background::initVillage(){
    this->nbrMur = 19;
    this->murs = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 19);

    //Liste des murs physiques
    this->murs[0].x = 0;
    this->murs[0].y = 545;
    this->murs[0].w = 290;
    this->murs[0].h = 31;

    this->murs[1].x = 289;
    this->murs[1].y = 381;
    this->murs[1].w = 2;
    this->murs[1].h = 139;

    this->murs[2].x = 292;
    this->murs[2].y = 375;
    this->murs[2].w = 43;
    this->murs[2].h = 26;

    this->murs[3].x = 337;
    this->murs[3].y = 327;
    this->murs[3].w = 17;
    this->murs[3].h = 31;

    this->murs[4].x = 359;
    this->murs[4].y = 314;
    this->murs[4].w = 21;
    this->murs[4].h = 18;

    this->murs[5].x = 385;
    this->murs[5].y = 276;
    this->murs[5].w = 17;
    this->murs[5].h = 31;

    this->murs[6].x = 413;
    this->murs[6].y = 261;
    this->murs[6].w = 16;
    this->murs[6].h = 17;

    this->murs[7].x = 435;
    this->murs[7].y = 230;
    this->murs[7].w = 95;
    this->murs[7].h = 32;

    this->murs[8].x = 579;
    this->murs[8].y = 230;
    this->murs[8].w = 33;
    this->murs[8].h = 179;

    this->murs[9].x = 1000;
    this->murs[9].y = 0;
    this->murs[9].w = 40;
    this->murs[9].h = 765;

    this->murs[10].x = 610;
    this->murs[10].y = 230;
    this->murs[10].w = 182;
    this->murs[10].h = 161;

    this->murs[11].x = 794;
    this->murs[11].y = 233;
    this->murs[11].w = 39;
    this->murs[11].h = 38;

    this->murs[12].x = 917;
    this->murs[12].y = 320;
    this->murs[12].w = 79;
    this->murs[12].h = 35;

    this->murs[13].x = 846;
    this->murs[13].y = 271;
    this->murs[13].w = 26;
    this->murs[13].h = 35;

    this->murs[14].x = 869;
    this->murs[14].y = 289;
    this->murs[14].w = 16;
    this->murs[14].h = 40;

    this->murs[15].x = 0;
    this->murs[15].y = 0;
    this->murs[15].w = 151;
    this->murs[15].h = 455;

    this->murs[16].x = 152;
    this->murs[16].y = 0;
    this->murs[16].w = 96;
    this->murs[16].h = 358;

    this->murs[17].x = 249;
    this->murs[17].y = 0;
    this->murs[17].w = 96;
    this->murs[17].h = 259;

    this->murs[18].x = 346;
    this->murs[18].y = 0;
    this->murs[18].w = 100;
    this->murs[18].h = 162;

}

SDL_Rect* Background::getMurs() const{
    return this->murs;
}

int Background::getNbrMurs() const{
    return this->nbrMur;
}
