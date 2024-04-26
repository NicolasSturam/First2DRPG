#include "Menu.h"

void Menu::initTexturesMenu(int h, SDL_Renderer* renderer, TTF_Font* font, Couleurs* couleurs){
    int hText = h/4;
    SDL_Rect rect;
    texturesMenu.attaquer = new Texture();
    texturesMenu.attaquer->loadNewTexture("Attaque", renderer, font, &couleurs->blanc);
    rect.x = this->rect.x + 12;
    rect.y = this->rect.y + 10;
    rect.h = hText -10;
    rect.w = this->rect.w - 24;
    texturesMenu.attaquer->setRect(&rect);

    texturesMenu.magie = new Texture();
    texturesMenu.magie->loadNewTexture("Magie", renderer, font, &couleurs->blanc);
    rect.x = this->rect.x + 28;
    rect.y += hText - 2;
    rect.w = this->rect.w - 66;
    texturesMenu.magie->setRect(&rect);

    texturesMenu.techniques = new Texture();
    texturesMenu.techniques->loadNewTexture("Technique", renderer, font, &couleurs->blanc);
    rect.x = this->rect.x + 8;
    rect.w = this->rect.w -16;
    rect.y += hText ;
    texturesMenu.techniques->setRect(&rect);


    texturesMenu.objet = new Texture();
    texturesMenu.objet->loadNewTexture("Objet", renderer, font, &couleurs->blanc);
    rect.y += hText;
    rect.x = this->rect.x + 32;
    rect.w = this->rect.w - 66;
    texturesMenu.objet->setRect(&rect);

    texturesMenu.defendre = new Texture();
    texturesMenu.defendre->loadNewTexture("Defendre", renderer, font, &couleurs->blanc);
    rect.y = this->rect.y + 10;
    rect.x = this->rect.x + this->rect.w + 15;
    rect.w = this->rect.w -30;
    texturesMenu.defendre->setRect(&rect);

    texturesMenu.avancer = new Texture();
    texturesMenu.avancer->loadNewTexture("Avancer", renderer, font, &couleurs->blanc);
    rect.y += hText;
    rect.x = this->rect.x + this->rect.w + 12;
    rect.w = this->rect.w - 24;
    texturesMenu.avancer->setRect(&rect);

    texturesMenu.reculer = new Texture();
    texturesMenu.reculer->loadNewTexture("Reculer", renderer, font, &couleurs->blanc);
    rect.x = this->rect.x + this->rect.w + 15;
    rect.w = this->rect.w - 30;
    rect.y += hText;
    texturesMenu.reculer->setRect(&rect);

    texturesMenu.fuir = new Texture();
    texturesMenu.fuir->loadNewTexture("Fuir", renderer, font, &couleurs->blanc);
    rect.x = this->rect.x + this->rect.w + 40;
    rect.w = this->rect.w - 80;
    rect.y += hText - 2;
    texturesMenu.fuir->setRect(&rect);

    rect.y = 580, rect.w = 60, rect.h = 40;
    //rect.x = menuCombat->getRectX() - rect.w;
    rect.x = this->rect.x - rect.w;
    texturesMenu.cursor = new Texture("images/HUD/cursor.png", renderer, rect);
    setMenuCombat(texturesMenu.cursor->getRect());
    rect.w = 30;
    rect.h = 30;
    rect.x = this->rect.x + this->rect.w - 15;
    rect.y = this->rect.y + 10;
    texturesMenu.flecheDoree = new Texture("images/HUD/flecheDoree.png", renderer, rect);
    rect.w = this->rect.w;
    rect.h = this->rect.h;
    rect.x = this->rect.x + this->rect.w;
    rect.y = this->rect.y;

    texturesMenu.panneau2 = new Texture("images/HUD/panneauVide.png", renderer, rect);
    rect = {0,0, 50, 30};
    texturesMenu.triangle = new Texture("images/HUD/triangle.png", renderer, rect);
}

void Menu::renderTextures(Profile* currentProfile, SDL_Renderer* renderer){
    if(currentProfile->getIsTurn() && currentProfile->getAnimType()==IDLE && currentProfile->getIsPlayer()){
        texturesMenu.triangle->setPosition(currentProfile->getColliderX(), currentProfile->getColliderY() - texturesMenu.triangle->getRectH() -10);
        texturesMenu.triangle->render(renderer);
        render(renderer);
        if(!showMagies()){
            texturesMenu.attaquer->render(renderer);
            texturesMenu.magie->render(renderer);
            texturesMenu.techniques->render(renderer);
            texturesMenu.objet->render(renderer);
            if(isOpened()){
                texturesMenu.panneau2->render(renderer);
                texturesMenu.defendre->render(renderer);
                texturesMenu.avancer->render(renderer);
                texturesMenu.reculer->render(renderer);
                texturesMenu.fuir->render(renderer);
                texturesMenu.flecheDoree->render(renderer, NULL, 0,0,0.0, NULL, SDL_FLIP_HORIZONTAL);
            }
        }
        else if(showMagies()){
            texturesMenu.panneau2->render(renderer);
            for(int i=0; i<currentProfile->listeMagies->taille(); i++){
                currentProfile->listeMagies->getNoeud2(i)->renderName(renderer, this->rect.x + 5, texturesMenu.panneau2->getRectY() + i*50 + 5);
            }
        }
        else{
            texturesMenu.flecheDoree->render(renderer);
        }
        texturesMenu.cursor->render(renderer);
    }
}

Menu::Menu()
{
    this->nbreCase = 0;
    this->current = 0;
    this->tableau = NULL;
    this->caseCourante = NULL;
    this->selectedAction = false;
    this->selectedTarget = false;

    this->opened = false;
    this->magieListe = false;
    this->techniqueListe = false;
    this->objetListe = false;
    this->indice = 0;

    this->currentMagie = NULL;
    this->chooseTarget = false;

    this->pLEnnemie = 0;
    this->tLigne = 0;

    this->cProfile = NULL;
    this->stop = false;
}

Menu::Menu(string path, SDL_Renderer* renderer, SDL_Rect rect)
: Texture(path, renderer, rect)
{
    this->nbreCase = 0;
    this->current = 0;
    this->tableau = NULL;
    this->caseCourante = NULL;
    this->selectedAction = false;
    this->selectedTarget = false;

    this->opened = false;
    this->indice = 0;
    this->magieListe = false;
    this->techniqueListe = false;
    this->objetListe = false;

    this->currentMagie = NULL;
    this->chooseTarget = false;

    this->pLEnnemie = 0;
    this->tLigne = 0;

    this->cProfile = NULL;
    this->stop = false;
    this->actual = 0;

    this->cListe = NULL;
    this->swap = false;
}

Menu::~Menu(){
    if(tableau != NULL){
        free(tableau);
        tableau = NULL;
    }

    if(texturesMenu.attaquer != NULL){
        free(texturesMenu.attaquer );
        texturesMenu.attaquer = NULL;
    }
    if(texturesMenu.magie != NULL){
        free(texturesMenu.magie );
        texturesMenu.magie = NULL;
    }
    if(texturesMenu.techniques != NULL){
        free(texturesMenu.techniques );
        texturesMenu.techniques = NULL;
    }
    if(texturesMenu.objet != NULL){
        free(texturesMenu.objet );
        texturesMenu.objet = NULL;
    }
    if(texturesMenu.defendre != NULL){
        free(texturesMenu.defendre );
        texturesMenu.defendre = NULL;
    }
    if(texturesMenu.avancer != NULL){
        free(texturesMenu.avancer );
        texturesMenu.avancer = NULL;
    }
    if(texturesMenu.cursor != NULL){
        free(texturesMenu.cursor );
        texturesMenu.cursor = NULL;
    }
    if(texturesMenu.flecheDoree != NULL){
        free(texturesMenu.flecheDoree );
        texturesMenu.flecheDoree = NULL;
    }
    if(texturesMenu.fuir != NULL){
        free(texturesMenu.fuir );
        texturesMenu.fuir = NULL;
    }
    if(texturesMenu.panneau2 != NULL){
        free(texturesMenu.panneau2 );
        texturesMenu.panneau2 = NULL;
    }
    if(texturesMenu.reculer != NULL){
        free(texturesMenu.reculer );
        texturesMenu.reculer = NULL;
    }
    if(texturesMenu.triangle != NULL){
        free(texturesMenu.triangle );
        texturesMenu.triangle = NULL;
    }


}

void Menu::setMenuCombat(SDL_Rect* posCursor){
    this->posCursorOrigine = *posCursor;
    //temporaire
    this->nbreCase = 4; //sur une colonne
    int colonnes = 2;
    this->current = 0;
    this->tableau = (Case*) malloc(sizeof(Case) * colonnes * this->nbreCase);
    //attaque, technique, magie, objet
    //defendre, avancer, reculer, fuir

    //dimensions et positions des cases
    this->tableau[0].anim = ATTACK;
    this->tableau[0].x = this->rect.x;
    this->tableau[0].y = this->rect.y;
    this->tableau[0].w = this->rect.w;
    this->tableau[0].h = this->rect.h/4;

    this->tableau[1].anim = MAGIE;
    this->tableau[1].x = this->rect.x;
    this->tableau[1].y = this->rect.y + this->rect.h/4;
    this->tableau[1].w = this->rect.w;
    this->tableau[1].h = this->rect.h/4;

    this->tableau[2].anim = TECHNIQUE;
    this->tableau[2].x = this->rect.x;
    this->tableau[2].y = this->rect.y + this->rect.h/4*2;
    this->tableau[2].w = this->rect.w;
    this->tableau[2].h = this->rect.h/4;

    this->tableau[3].anim = OBJET;
    this->tableau[3].x = this->rect.x;
    this->tableau[3].y = this->rect.y + this->rect.h/4*3;
    this->tableau[3].w = this->rect.w;
    this->tableau[3].h = this->rect.h/4;

    this->tableau[4].anim = DEFENDRE;
    this->tableau[4].x = this->rect.x + this->rect.w;
    this->tableau[4].y = this->rect.y;
    this->tableau[4].w = this->rect.w;
    this->tableau[4].h = this->rect.h/4;

    this->tableau[5].anim = AVANCER;
    this->tableau[5].x = this->rect.x + this->rect.w;
    this->tableau[5].y = this->rect.y + this->rect.h/4;
    this->tableau[5].w = this->rect.w;
    this->tableau[5].h = this->rect.h/4;

    this->tableau[6].anim = RECULER;
    this->tableau[6].x = this->rect.x + this->rect.w;
    this->tableau[6].y = this->rect.y + this->rect.h/4*2;
    this->tableau[6].w = this->rect.w;
    this->tableau[6].h = this->rect.h/4;

    this->tableau[7].anim = FUIR;
    this->tableau[7].x = this->rect.x + this->rect.w;
    this->tableau[7].y = this->rect.y + this->rect.h/4*3;
    this->tableau[7].w = this->rect.w;
    this->tableau[7].h = this->rect.h/4;

    this->caseCourante = tableau;
}

bool Menu::handleEvent(SDL_Event* e, Profile* joueur, Liste<Profile*>* joueurs[3], Liste<Profile*>* ennemis[3], DonneesCombat* dc){
    if(!opened){
        if(!selectedAction){
            if((e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_DOWN && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_A) ){
                //On verifie si target est valide (cible non morte)
                switch(joueur->tTarget){
                case ALLIE:
                    this->cListe = joueurs;
                    break;
                case ENNEMI:
                    this->cListe = ennemis;
                    break;
                }
                this->cProfile = this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                if(this->cProfile == NULL){
                    bool done = false;
                    for(int i = 0; i < 3 && !done;i++){
                        for(int j=0; j < ennemis[i]->taille(); j++){
                            this->cProfile = ennemis[i]->getNoeud2(j);
                            if( !this->cProfile->getIsDead() ){
                                joueur->target[0] = j;
                                joueur->target[1] = i;
                                done = true;
                                break;
                            }
                        }
                    }
                }

                if(caseCourante->anim == MAGIE){
                    if(joueur->listeMagies->taille() > 0){
                        this->selectedAction = true;
                        this->magieListe = true;
                        this->currentMagie = joueur->listeMagies->getNoeud2(0);
                        joueur->currentMagie = this->currentMagie;
                        texturesMenu.cursor->setPosition(this->tableau[0].x - texturesMenu.cursor->getRectW(), this->tableau[0].y);
                    }
                }
                else if(caseCourante->anim == ATTACK){
                    if(joueur->colonne == 2 || joueur->distant){
                        this->selectedAction = true;
                        this->chooseTarget = true;
                        if(this->cProfile->getIsDead()){
                            bool done = false;
                            for(int i = 0; i < 3 && !done;i++){
                                for(int j=0; j < ennemis[i]->taille(); j++){
                                    this->cProfile = ennemis[i]->getNoeud2(j);
                                    if( !this->cProfile->getIsDead() ){
                                        joueur->target[0] = j;
                                        joueur->target[1] = i;
                                        done = true;
                                        break;
                                    }
                                }
                            }
                        }
                        texturesMenu.cursor->setPosition(this->cProfile->getColliderX() - texturesMenu.cursor->getRectW(), this->cProfile->getColliderY() );

                    }//if(joueur->colonne == 2)
                }
                else{
                    this->selectedAction = true;
                    this->chooseTarget = true;
                }
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_s && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_DOWN)){
                current++;
                if(current >= nbreCase){
                    current = nbreCase-1;
                }
                this->caseCourante = &this->tableau[current];
                texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_z && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_UP)){
                current--;
                if(current < 0){
                    current = 0;
                }
                this->caseCourante = &this->tableau[current];
                texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_d && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ){//ouverture du menu etendu
                this->opened = true;
                current += 4;
                this->caseCourante = &this->tableau[current];
                texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
            }
        }//if(!selectedAction)
        else if(magieListe && !this->chooseTarget){
            if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_RIGHT && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_B) ){
                this->selectedAction = false;
                this->magieListe = false;
                this->indice = 0;
                current = 1;
                this->caseCourante = &this->tableau[current];
                texturesMenu.cursor->setPosition(this->caseCourante->x- texturesMenu.cursor->getRectW(), this->caseCourante->y);
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_DOWN && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_A) ){
                if(!joueur->pmEnRecharge){
                    this->chooseTarget = true;
                    if( this->currentMagie->getTypeDegat() == SOIN ){
                        if(joueur->tTarget == ENNEMI){//on est pas sur la bonne liste
                            joueur->tTarget = ALLIE;
                            this->cListe = joueurs;
                            joueur->target[1] = joueur->colonne;
                            joueur->target[0] = 0;
                            this->stop = false;
                            while(!this->stop){
                                this->cProfile = this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                                if(joueur->getNameString() == this->cProfile->getNameString()){
                                    this->stop = true;
                                }
                                else{
                                    joueur->target[0]++;
                                }
                            }
                        }
                    }
                    else{
                        if(joueur->tTarget == ALLIE){
                            joueur->tTarget = ENNEMI;
                            this->cListe = ennemis;
                            joueur->target[1] = 0;
                            joueur->target[0] = 0;
                            this->stop = false;
                            for(int i=0; i < 3 && !this->stop; i++){
                                if(this->cListe[i]->taille() > 0){
                                    this->stop = true;
                                }
                            }
                        }
                        //Si la liste avait ete changee, il faut changer la cible
                        printf("target 1 : %d \ntarget 2 : %d\n", joueur->target[1], joueur->target[0]);
                        this->cProfile = this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                        if(this->cProfile->getIsDead()){
                            bool done = false;
                            for(int i = 0; i < 3 && !done;i++){
                                for(int j=0; j < this->cListe[i]->taille(); j++){
                                    this->cProfile = this->cListe[i]->getNoeud2(j);
                                    if( !this->cProfile->getIsDead() ){
                                        joueur->target[0] = j;
                                        joueur->target[1] = i;
                                        done = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    texturesMenu.cursor->setPosition(this->cProfile->getColliderX() - texturesMenu.cursor->getRectW(), this->cProfile->getColliderY() );
                }
                else{
                    printf("PM insuffisants.\n");
                }
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_s && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_DOWN) ){
                if(this->indice < joueur->listeMagies->taille() - 1){
                    this->indice++;
                    this->currentMagie = joueur->listeMagies->getNoeud2(indice);
                    joueur->currentMagie = this->currentMagie;
                    texturesMenu.cursor->setY(texturesMenu.cursor->getRectY() + this->rect.h/4);
                }
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_z && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_UP) ){
                if(this->indice > 0){
                    indice--;
                    this->currentMagie = joueur->listeMagies->getNoeud2(indice);
                    joueur->currentMagie = this->currentMagie;
                    texturesMenu.cursor->setY( texturesMenu.cursor->getRectY() - this->rect.h/4);
                }
            }
        }
        else if(this->chooseTarget){
            if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_DOWN && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_A) ){
                if(caseCourante->anim == MAGIE){
                    //printf("%s lance %s sur %s\n", joueur->getName(), this->currentMagie->getName(), ennemis->getNoeud2(joueur->target)->getName());
                    joueur->updateStats(Substract, PM, this->currentMagie->getPmCost());
                    if(joueur->getPm() <= 0){
                        joueur->pmEnRecharge = true;
                    }
                    printf("PM reduit de %d (%d PM restant)\n", this->currentMagie->getPmCost(), joueur->getPm());
                    joueur->changeAnimation( caseCourante->anim );
                    //on reset le menu
                    selectedAction = false;
                    this->indice = 0;
                    current = 0;
                    this->caseCourante = &this->tableau[current];
                    texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
                    this->magieListe = false;
                    this->chooseTarget = false;
                    return true;
                }
                else{
                    joueur->changeAnimation( caseCourante->anim );
                    //on reset le menu
                    selectedAction = false;
                    current = 0;
                    this->caseCourante = &this->tableau[current];
                    texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
                    this->chooseTarget = false;
                    return true;
                }
            }
            //Retour arriere
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_RIGHT && !e->key.repeat)|| (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_B) ){
                this->chooseTarget = false;
                if(this->magieListe){
                    this->selectedAction = true;
                    texturesMenu.cursor->setPosition(this->tableau[0].x - texturesMenu.cursor->getRectW(), this->tableau[0].y);
                }
                else{
                    this->selectedAction = false;
                    texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
                }
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_s && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_DOWN) ){
                this->actual = joueur->target[0];
                joueur->target[0]--;
                //Pour savoir dans quelle liste on se trouve
                switch(joueur->tTarget){
                    case ALLIE:
                        this->cListe = joueurs;
                    break;
                    case ENNEMI:
                        this->cListe = ennemis;
                    break;
                }
                //On verifie les limites et si la cible est non morte.
                this->stop = false;
                while(!stop){
                    if(joueur->target[0] < 0){//si on sort de la liste
                        joueur->target[0] = this->actual;
                        this->stop = true;
                    }
                    else{
                        this->cProfile = this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                        if(this->cProfile->getIsDead()){
                            joueur->target[0]--;
                        }
                        else{//if !isDead
                            this->stop = true;
                        }
                    }
                }
                this->cProfile = cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                texturesMenu.cursor->setPosition(this->cProfile->getColliderX() - texturesMenu.cursor->getRectW(), this->cProfile->getColliderY() );
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_z && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_UP) ){
                this->actual = joueur->target[0];
                joueur->target[0]++;
                switch(joueur->tTarget){
                    case ALLIE:
                        this->cListe = joueurs;
                    break;
                    case ENNEMI:
                        this->cListe = ennemis;
                    break;
                }
                //On verifie les limites et si la cible est non morte.
                this->stop = false;
                while(!stop){
                    if(joueur->target[0] > this->cListe[joueur->target[1]]->taille() - 1){//si on sort de la liste
                        joueur->target[0] = this->actual;
                        this->stop = true;
                    }
                    else{
                        this->cProfile = this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                        if(this->cProfile->getIsDead()){
                            joueur->target[0]++;
                        }
                        else{//if !isDead
                            this->stop = true;
                        }
                    }
                }
                this->cProfile = cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                texturesMenu.cursor->setPosition(this->cProfile->getColliderX() - texturesMenu.cursor->getRectW(), this->cProfile->getColliderY() );
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_q && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_LEFT) ){
                //1) on regarde dans quelle liste on se situe
                this->swap = false;
                switch(joueur->tTarget){
                    case ALLIE:
                        this->cListe = joueurs;
                    break;
                    case ENNEMI:
                        this->cListe = ennemis;
                    break;
                }
                //2) On recule d'une colonne
                this->cProfile = this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                joueur->target[1]--;
                this->stop = false;
                this->actual = joueur->target[0];
                while(!this->stop){
                    if(joueur->target[1] < 0){
                        joueur->target[1] = 0;
                        if(joueur->tTarget == ENNEMI){
                            this->swap = true;
                        }
                        this->stop = true;
                    }
                    else if(this->cListe[joueur->target[1]]->taille() == 0){
                        joueur->target[1]--;
                    }
                    else if((dc->ennemisDead[joueur->target[1]] == this->cListe[joueur->target[1]]->taille()) && joueur->tTarget == ENNEMI ){
                        joueur->target[1]--;
                    }
                    else{
                        //On verifie que la ligne soit correcte
                        if(joueur->target[0] > (this->cListe[joueur->target[1]]->taille() - 1) ){
                            joueur->target[0] = this->cListe[joueur->target[1]]->taille() - 1;
                            this->stop = true;
                        }
                        else if(joueur->target[0] < 0){
                            joueur->target[0] = 0;
                            this->stop = true;
                        }
                        else{
                            if(!this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0])->getIsDead()){
                                this->actual = joueur->target[0]; //on trouve une cible potentielle
                                //On essaye de placer le curseur sur la meme ligne
                                if(this->cProfile->ligne == this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0])->ligne ){
                                    this->stop = true;
                                }
                                else if(this->cProfile->ligne > this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0])->ligne){
                                    joueur->target[0]++;
                                }
                                else {
                                    this->stop = true;
                                }
                            }
                            else{
                                joueur->target[0]++;
                            }
                        }
                    }
                }
                //3) Gestion de la sortie de la liste
                if(this->swap){
                    this->stop = false;
                    joueur->target[1] = joueur->colonne;
                    joueur->target[0] = 0;
                    while(!stop){
                        this->cProfile = joueurs[joueur->target[1]]->getNoeud2(joueur->target[0]);
                        if(this->cProfile->getNameString() == joueur->getNameString()){
                            this->stop = true;
                        }
                        else{
                            joueur->target[0]++;
                        }
                    }
                    joueur->tTarget = ALLIE;
                    this->cListe = joueurs;
                }
                this->cProfile = cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                texturesMenu.cursor->setPosition(this->cProfile->getColliderX() - texturesMenu.cursor->getRectW(), this->cProfile->getColliderY() );
            }
            else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_d && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_RIGHT) ){
                //1) on regarde dans quelle liste on se situe
                this->swap = false;
                this->actual = joueur->target[1];
                switch(joueur->tTarget){
                    case ALLIE:
                        this->cListe = joueurs;
                    break;
                    case ENNEMI:
                        this->cListe = ennemis;
                    break;
                }
                //2) On recule d'une colonne
                joueur->target[1]++;
                this->stop = false;
                while(!this->stop){
                    if(joueur->target[1] > 2){
                        if(joueur->tTarget == ALLIE){
                            this->swap = true;
                            joueur->target[1] = 0;
                        }
                        else{
                            joueur->target[1] = this->actual;
                        }
                        this->stop = true;
                    }
                    else if(caseCourante->anim == ATTACK && joueur->tTarget==ENNEMI && !joueur->distant){
                        joueur->target[1] = 0;
                        this->stop = true;
                    }
                    else if(this->cListe[joueur->target[1]]->taille() == 0){
                        joueur->target[1]++;
                    }
                    else if((dc->ennemisDead[joueur->target[1]] == this->cListe[joueur->target[1]]->taille()) && joueur->tTarget == ENNEMI ){
                        joueur->target[1]++;
                    }
                    else{
                        //On verifie que la ligne soit correcte
                        if(joueur->target[0] > (this->cListe[joueur->target[1]]->taille() - 1) ){
                            joueur->target[0] = this->cListe[joueur->target[1]]->taille() - 1;
                            this->stop = true;
                        }
                        else if(joueur->target[0] < 0){
                            joueur->target[0] = 0;
                            this->stop = true;
                        }
                        else{
                            if(!this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0])->getIsDead()){
                                this->actual = joueur->target[0]; //on trouve une cible potentielle
                                //On essaye de placer le curseur sur la meme ligne
                                if(this->cProfile->ligne == this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0])->ligne ){
                                    this->stop = true;
                                }
                                else if(this->cProfile->ligne > this->cListe[joueur->target[1]]->getNoeud2(joueur->target[0])->ligne){
                                    joueur->target[0]++;
                                }
                                else {
                                    this->stop = true;
                                }
                            }
                            else{
                                joueur->target[0]++;
                            }
                        }
                    }
                }
                //3) Gestion de la sortie de la liste
                if(this->swap){
                    joueur->target[1] = 0;
                    joueur->target[0] = 0;
                    this->stop = false;
                    for(int i = 0; i < 3 && !stop;i++){
                        for(int j=0; j < ennemis[i]->taille(); j++){
                            this->cProfile = ennemis[i]->getNoeud2(j);
                            if( !this->cProfile->getIsDead() ){
                                joueur->target[0] = j;
                                joueur->target[1] = i;
                                stop = true;
                                break;
                            }
                        }
                    }
                    joueur->tTarget = ENNEMI;
                    this->cListe = ennemis;
                }
                this->cProfile = cListe[joueur->target[1]]->getNoeud2(joueur->target[0]);
                texturesMenu.cursor->setPosition(this->cProfile->getColliderX() - texturesMenu.cursor->getRectW(), this->cProfile->getColliderY() );
            }
        }
    }//if(!opened)
    else{
        if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_q && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_LEFT) ){//fermeture du menu etendu
            this->opened = false;
            current -= 4;
            this->caseCourante = &this->tableau[current];
            texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
        }
        else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_DOWN && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_A) ){
            //Il faut verifier si l'action est realisable
            if(caseCourante->anim == MAGIE){
                //printf("%s lance un sort sur %s\n", joueur->getName(), ennemis->getNoeud2(joueur->target)->getName());
                joueur->updateStats(Substract, PM, 20);
                if(joueur->getPm() == 0){
                    joueur->pmEnRecharge = true;
                }
                printf("PM reduit de 20 (%d PM restant)\n", joueur->getPm());
                joueur->changeAnimation( caseCourante->anim );
                //on reset le menu
                selectedAction = false;
                opened = false;
                current = 0;
                this->caseCourante = &this->tableau[current];
                texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
                return true;
            }
            else if(caseCourante->anim == AVANCER){
                if(joueur->colonne < 2){
                    joueur->changeAnimation( caseCourante->anim );
                    //On supprime le joueur de la liste
                    //On cherche sa position dans la liste
                    this->stop = false;
                    for(int i = 0; i < joueurs[joueur->colonne]->taille() && !this->stop; i++){
                        this->cProfile = joueurs[joueur->colonne]->getNoeud2(i);
                        if( joueur->getNameString() == this->cProfile->getNameString() ){
                            joueurs[joueur->colonne]->supprimer(i);
                            this->stop = true;
                        }
                    }
                    //On place le joueur a sa nouvelle position
                    joueur->colonne++;
                    this->stop = false;
                    for(int i = 0; i < joueurs[joueur->colonne]->taille() && !this->stop; i++){
                        this->cProfile = joueurs[joueur->colonne]->getNoeud2(i);
                        if(this->cProfile->ligne > joueur->ligne){
                            joueurs[joueur->colonne]->inserer(i, joueur);
                            this->stop = true;
                        }
                    }
                    if(!this->stop){
                        joueurs[joueur->colonne]->inserer(joueurs[joueur->colonne]->taille(), joueur);
                    }
                    //on reset le menu
                    selectedAction = false;
                    opened = false;
                    current = 0;
                    this->caseCourante = &this->tableau[current];
                    texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
                    return true;
                }
            }
            else if(caseCourante->anim == RECULER){
                if(joueur->colonne > 0){
                    joueur->changeAnimation( caseCourante->anim );
                    //On supprime le joueur de la liste
                    //On cherche sa position dans la liste
                    this->stop = false;
                    for(int i = 0; i < joueurs[joueur->colonne]->taille() && !this->stop; i++){
                        this->cProfile = joueurs[joueur->colonne]->getNoeud2(i);
                        if( joueur->getNameString() == this->cProfile->getNameString() ){
                            joueurs[joueur->colonne]->supprimer(i);
                            this->stop = true;
                        }
                    }
                    //On place le joueur a sa nouvelle position
                    joueur->colonne--;
                    this->stop = false;
                    for(int i = 0; i < joueurs[joueur->colonne]->taille() && !this->stop; i++){
                        this->cProfile = joueurs[joueur->colonne]->getNoeud2(i);
                        if(this->cProfile->ligne > joueur->ligne){
                            joueurs[joueur->colonne]->inserer(i, joueur);
                            this->stop = true;
                        }
                    }
                    if(!this->stop){
                        joueurs[joueur->colonne]->inserer(joueurs[joueur->colonne]->taille(), joueur);
                    }

                    //on reset le menu
                    selectedAction = false;
                    opened = false;
                    current = 0;
                    this->caseCourante = &this->tableau[current];
                    texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
                    return true;
                }
            }
            //else if(caseCourante->anim == FUIR){
            //}
            else{
                joueur->changeAnimation( caseCourante->anim );
                //on reset le menu
                selectedAction = false;
                opened = false;
                current = 0;
                this->caseCourante = &this->tableau[current];
                texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
                return true;
            }
        }
        else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_s && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_DOWN) ){
            current++;
            if(current >= (nbreCase * 2) ){
                current = (2*nbreCase)-1;
            }
            this->caseCourante = &this->tableau[current];
            texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
        }
        else if( (e->type==SDL_KEYDOWN && e->key.keysym.sym == SDLK_z && !e->key.repeat) || (e->type==SDL_CONTROLLERBUTTONDOWN && e->cbutton.button==SDL_CONTROLLER_BUTTON_DPAD_UP) ){
            current--;
            if(current < 4){
                current = 4;
            }
            this->caseCourante = &this->tableau[current];
            texturesMenu.cursor->setPosition(this->caseCourante->x - texturesMenu.cursor->getRectW(), this->caseCourante->y);
        }
    }

    return false;
}

bool Menu::isOpened(){
    return this->opened;
}

bool Menu::showMagies(){
    return this->magieListe;
}

bool Menu::showTechniques(){
    return this->techniqueListe;
}

bool Menu::showObjets(){
    return this->objetListe;
}
