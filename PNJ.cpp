#include "PNJ.h"

PNJ::PNJ(){
    this->p = NULL;
    //this->profile = NULL;
    this->chemin = NULL;
    this->inBase = false;
    //this->iaOutCombat = false;
    this->nextStep = NULL;
    this->currentStep = NULL;
    this->temp = NULL;

    this->profiles = NULL;
}

PNJ::PNJ(string path, SDL_Renderer* renderer, SDL_Rect rect, SDL_Rect collider){
    this->p = new Personnage(path, renderer, rect, collider);
    //this->profile = NULL;
    this->chemin = NULL;
    this->inBase = false;

    this->nextStep = NULL;
    this->currentStep = NULL;
    this->temp = NULL;

    this->profiles = NULL;
}

PNJ::~PNJ(){
    this->p = NULL;
    delete chemin;
    this->chemin = NULL;

    this->nextStep = NULL;
    this->currentStep = NULL;
    this->temp = NULL;
}

void PNJ::initVoleur(){
    this->p->setVoleur();
    //this->iaOutCombat = &PNJ::patrouille;
    this->inBase = true;
    this->base.x = this->p->getColliderX();
    this->base.y = this->p->getColliderY();
    this->base.w = this->p->getColliderW();
    this->base.h = this->p->getColliderH();

    this->stepOne = {450, this->p->getColliderY(), this->p->getColliderW(), this->p->getColliderH()};
    this->stepTwo = {900, this->p->getColliderY(), this->p->getColliderW(), this->p->getColliderH()};
}

/*
void PNJ::createProfile( string name, Stats stats, Resistances res, string path, SDL_Renderer* renderer, SDL_Rect rect ){
    this->profile = new Profile(name, stats, res, path, renderer, rect );
}*/
/*
void PNJ::follow(Personnage* entite){

    int centreX1 = entite1->getX() + entite1->getW()/2;
    int centreY1 = entite1->getY() + entite1->getH()/2;

    int centreX2 = entite2->getX() + entite2->getW()/2;
    int centreY2 = entite2->getY() + entite2->getH()/2;

    int distanceX = centreX2 - centreX1;
    int distanceY = centreY2 - centreY1;
    double distance = sqrt(pow(distanceX, 2) + pow(distanceY, 2));

    double distance = calculerDistance(this->p->collider, entite1->collider);
    //On ajuste la vitesse de l'entite2 en fonction de la distance avec l'entite1
    if(distance < 200.0){
        if(distanceX > entite1->getW()){
            entite2->vitX = -entite2->getMaxVit();
        }
        else if(distanceX < -entite1->getW()){
            entite2->vitX = entite2->getMaxVit();
        }
        else if(distanceX < entite1->getW() && distanceX > -entite1->getW()){
            entite2->vitX = 0;
        }

        if(distanceY > entite1->getH()){
            entite2->vitY = -entite2->getMaxVit();
        }
        else if(distanceY < -entite1->getH()){
            entite2->vitY = entite2->getMaxVit();
        }
        else if(distanceY < entite1->getH() && distanceY > -entite1->getH()){
            entite2->vitY = 0;
        }
    }
    else{
        entite2->vitX = 0;
        entite2->vitY = 0;
    }
}*/

//Renvoie true si le point est atteint
//Renvoie false si le point n'est pas atteint

bool PNJ::followPoint(SDL_Rect* rect){
    //On regle la vitesse en x en fonction de la distance
    if( this->p->getColliderX() - rect->x > 0 ){
        this->p->setMinVitX();
    }
    else if( this->p->getColliderX() - rect->x < 0 ){
        this->p->setMaxVitX();
    }

    else if( this->p->getColliderX() - rect->x ==0 ){
        this->p->setVitX(0);
    }
    //On regle la vitesse en y en fonction de la distance
    if( this->p->getColliderY() - rect->y > 0 ){
        this->p->setMinVitY();
    }
    else if( this->p->getColliderY() - rect->y < 0 ){
        this->p->setMaxVitY();
    }

    else if( this->p->getColliderY() - rect->y ==0 ){
        this->p->setVitY(0);
    }


    if( this->p->getColliderX() == rect->x && this->p->getColliderY() == rect->y ){
        return true;
    }
    else{
        return false;
    }
}


//SDL_Rect creerChemins2(Texture* actuel, SDL_Rect* target, SDL_Rect* murs, int nbrMurs){
void PNJ::addToChemin(SDL_Rect* target, SDL_Rect* murs, int nbrMurs){
    SDL_Rect successor[8];
    SDL_Rect smallSuccesor;
    bool valide[8] = {}; //par defaut, tous les successeur sont valides
    double f[8] = {};
    for(int i=0;i<8;i++){
        valide[i] = true;
        f[i] = 0.0;
    }

    double q = 0.0;
    double h = 0.0;

    int indiceMin = 0; //indice du sccesseur de f min
    double fMin = 0.0;

    int largeur = 8;
    int hauteur = 8;

    //On cree le successeur 1
    successor[0].x = this->p->getColliderX() ;
    successor[0].y = this->p->getColliderY() - hauteur;
    successor[0].w = this->p->getColliderW() ;
    successor[0].h = this->p->getColliderH() ;

    //On cree le successeur 2
    successor[1].x = this->p->getColliderX() + 40;
    successor[1].y = this->p->getColliderY() - 40;
    successor[1].w = this->p->getColliderW() ;
    successor[1].h = this->p->getColliderH() ;

    //On cree le successeur 3
    successor[2].x = this->p->getColliderX() + largeur;
    successor[2].y = this->p->getColliderY() ;
    successor[2].w = this->p->getColliderW() ;
    successor[2].h = this->p->getColliderH() ;

    //On cree le successeur 4
    successor[3].x = this->p->getColliderX() + 40;
    successor[3].y = this->p->getColliderY() + 40;
    successor[3].w = this->p->getColliderW() ;
    successor[3].h = this->p->getColliderH() ;

    //On cree le successeur 5
    successor[4].x = this->p->getColliderX();
    successor[4].y = this->p->getColliderY() + hauteur;
    successor[4].w = this->p->getColliderW() ;
    successor[4].h = this->p->getColliderH() ;

    //On cree le successeur 6
    successor[5].x = this->p->getColliderX() - 40;
    successor[5].y = this->p->getColliderY() + 40;
    successor[5].w = this->p->getColliderW() ;
    successor[5].h = this->p->getColliderH() ;

    //On cree le successeur 7
    successor[6].x = this->p->getColliderX() - largeur;
    successor[6].y = this->p->getColliderY() ;
    successor[6].w = this->p->getColliderW() ;
    successor[6].h = this->p->getColliderH() ;

    //On cree le successeur 8
    successor[7].x = this->p->getColliderX() - 40;
    successor[7].y = this->p->getColliderY() - 40;
    successor[7].w = this->p->getColliderW() ;
    successor[7].h = this->p->getColliderH() ;

    //On regarde chaque successor
    for(int i=0; i<8 ;i++){
        if( checkCollision(&successor[i], murs, nbrMurs) ){
            switch(i){
                case 0: //nord
                    smallSuccesor.x = successor[i].x ;
                    smallSuccesor.y = successor[i].y - 2;
                    smallSuccesor.w = successor[i].w;
                    smallSuccesor.h = 2;
                    successor[i] = smallSuccesor;
                    if(checkCollision(&successor[i], murs, nbrMurs)){//on verifie s'il n'y a pas de nouvelle collision
                        valide[0] = false;
                        valide[1] = false;
                        valide[7] = false;
                        if( this->p->getVitY() < 0){
                            valide[3] = false;
                            valide[4] = false;
                            valide[5] = false;
                        }
                    }
                    break;
                case 2: //est
                    smallSuccesor.x = this->p->getColliderX() + 2;
                    smallSuccesor.y = successor[i].y;
                    smallSuccesor.w = successor[i].w;
                    smallSuccesor.h = successor[i].h;
                    successor[i] = smallSuccesor;
                    if(checkCollision(&successor[i], murs, nbrMurs)){
                            valide[1] = false;
                            valide[2] = false;
                            valide[3] = false;
                            if(this->p->getVitX() > 0){
                                valide[5] = false;
                                valide[6] = false;
                                valide[7] = false;
                            }
                    }

                    break;
                case 4: //sud
                    smallSuccesor.x = successor[i].x;
                    smallSuccesor.y = this->p->getColliderY() + 2;
                    smallSuccesor.w = successor[i].w;
                    smallSuccesor.h = successor[i].h;
                    successor[i] = smallSuccesor;
                    if(checkCollision(&successor[i], murs, nbrMurs)){
                            valide[3] = false;
                            valide[5] = false;
                            valide[4] = false;
                            if( this->p->getVitY() > 0 ){
                                valide[0] = false;
                                valide[1] = false;
                                valide[7] = false;
                            }
                    }

                    break;
                case 6: //ouest
                    smallSuccesor.x = successor[i].x -2;
                    smallSuccesor.y = successor[i].y;
                    smallSuccesor.w = successor[i].w;
                    smallSuccesor.h = successor[i].h;
                    successor[i] = smallSuccesor;
                    if(checkCollision(&successor[i], murs, nbrMurs)){
                            valide[5] = false;
                            valide[6] = false;
                            valide[7] = false;
                            if(this->p->getVitX() < 0){
                                valide[1] = false;
                                valide[2] = false;
                                valide[3] = false;
                        }
                    }


                    break;
                default:
                    valide[i] = false;
                    break;
            }//switch

        }

        q = calculerDistance(&successor[i], this->p->getCollider() );

        h = calculerDistance(target, &successor[i]);

        f[i] = q + h;
    }//for

    for(int i=0;i<8;i++){
        if(fMin == 0.0 && valide[i]){
                fMin = f[i];
                indiceMin = i;
        }
        else if(f[i] < fMin && valide[i]){
            fMin = f[i];
            indiceMin = i;
        }
    }
    if(fMin == 0.0){
        this->chemin->inserer(0,{0,0,0,0});
    }
    else{
        this->chemin->inserer(0,successor[indiceMin]);
    }

}

void PNJ::setInBase(bool b){
    this->inBase = b;
}

void PNJ::creerChemins(){
    if(this->chemin != NULL){
        delete this->chemin;
        this->chemin = NULL;
    }
    else{
        this->chemin = new Liste<SDL_Rect>();
    }
}

Liste<SDL_Rect>* PNJ::getChemin() const{
    return this->chemin;
}

bool PNJ::isInBase() const{
    return this->inBase;
}

void PNJ::patrouille(Joueur* joueur, SDL_Rect* murs, int nbrMurs){
    if(calculerDistance(this->p->getCollider(), joueur->p->getCollider()) <= 150.0){//on suit le joueur s'il est suffisamment proche
        if(this->chemin == NULL && !checkCollision(this->p->getCollider(), joueur->p->getCollider())){
            this->inBase = false;
            this->creerChemins();
            this->addToChemin(joueur->p->getCollider(), murs, nbrMurs) ;
        }
        if(this->chemin !=NULL){
            this->inBase = false;
            if(this->chemin->taille() > 0){
                if(checkCollision(this->p->getCollider(), joueur->p->getCollider())){//on regarde si on est arrive a destination
                    this->chemin->supprimer(0);
                    this->p->stop();
                }
                else if(this->followPoint(this->chemin->getNoeud(0))){//on regarde si on a atteint le prochain point de passage
                    this->addToChemin(joueur->p->getCollider(), murs,  nbrMurs ) ;
                    this->chemin->supprimer(1);
                }
            }
            else if(!checkCollision(this->p->getCollider(), joueur->p->getCollider()) && this->chemin->taille() == 0){//si la liste est vide et qu'on a pas atteint la destination
                this->addToChemin(joueur->p->getCollider(), murs,  nbrMurs );
            }
        }

    }
    else{ //on est trop loin du joueur
        if(this->inBase){//si on est a la base
            if(this->chemin == NULL){
                this->creerChemins();
                this->addToChemin(&this->stepOne, murs,  nbrMurs ) ;
                this->currentStep = &this->stepOne;
                this->nextStep = &this->stepTwo;
            }
            else{
                if(this->chemin->taille() == 0){
                    this->addToChemin(&this->stepOne, murs,  nbrMurs );
                    this->currentStep = &this->stepOne;
                    this->nextStep = &this->stepTwo;
                }
                else if(checkCollision(this->p->getCollider(), this->currentStep)){
                    this->temp = this->currentStep;
                    this->currentStep = this->nextStep;
                    this->nextStep = this->temp;
                    this->temp = NULL;
                }
                else if(this->followPoint(this->chemin->getNoeud(0))){
                    this->addToChemin(this->currentStep, murs,  nbrMurs ) ;
                    this->chemin->supprimer(1);
                }
            }
        }
        else{//si on est en dehors de la base
        //on retourne a la base
            if(this->chemin == NULL && !checkCollision(this->p->getCollider(), &this->base)){
                this->creerChemins();
                this->addToChemin(&this->base, murs,  nbrMurs ) ;
            }
            if(this->chemin !=NULL ){
                if(this->chemin->taille() > 0){
                    if(checkCollision(this->p->getCollider(), &this->base)){//on regarde si on est arrive a destination
                        this->chemin->supprimer(0);
                        this->p->stop();
                        this->inBase = true;
                    }
                    else if(this->followPoint(this->chemin->getNoeud(0))){//on regarde si on a atteint le prochain point de passage
                        this->addToChemin(&this->base, murs,  nbrMurs );
                        this->chemin->supprimer(1);
                    }
                }
                else if(!checkCollision(this->p->getCollider(), &this->base) && this->chemin->taille() == 0){//si la liste est vide et qu'on a pas atteint la destination
                    this->addToChemin(&this->base, murs,  nbrMurs );
                }
            }
        }
    }
}
