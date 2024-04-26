#ifndef JEU_CPP
#define JEU_CPP

#include "jeu.h"

int randomNumber100(){
    int N = 100;
    return (rand()%N)+1; //renvoie un nombre aleatoire entre 1 et 100
}

int hachage(string cle, int tailleTableau){
    int somme = 0, b=2, i=0;
    for(string::iterator it=cle.begin(); it!=cle.end();it++){
        somme+=(*it)*pow(b,i);
        i++;
    }
    return somme%tailleTableau;

}

void creerGrilleCombat(Grille* grille, int w, int h, int l, int x, int y){
    for(int i=0;i < 5; i++){
        for(int j=0;j < 3;j++){
            grille->tab[i][j].x = x + l*j + w*i;
            grille->tab[i][j].y = y - h*i;
        }
    }

    grille->w = w;
    grille->h = h;
    grille->l = l;
}
Magie** creerMagies(int* nbrMagies, SDL_Renderer* renderer, TTF_Font* font, Couleurs* couleurs){
    *nbrMagies = 100;
    SDL_Rect rect;
    Magie** tabMagies = (Magie**) malloc(sizeof(Magie*)*(*nbrMagies));

    //1) Flammes
    rect = {0, 0, 200, 200};
    Magie* flammes = new Magie();
    flammes->setFlammes(renderer, &rect, font, &couleurs->blanc);
    tabMagies[hachage(flammes->getName(), *nbrMagies)] = flammes;
    //listeMagies[0]->setFlammes(renderer, &rect, font, &couleurs->blanc);
    //2) Soin
    rect = {0, 0, 100, 100};
    Magie* soin = new Magie();
    soin->setSoin(renderer, &rect, font, &couleurs->blanc);
    tabMagies[hachage(soin->getName(), *nbrMagies)] = soin;
    //listeMagies[1]->setSoin(renderer, &rect, font, &couleurs->blanc);
    //3) Barriere
    Magie* barriere = new Magie();
    barriere->setBarriere(renderer, &rect, font, &couleurs->blanc);
    tabMagies[hachage(barriere->getName(), *nbrMagies)] = barriere;

    /*
    for(int i=0;i<*nbrMagies;i++){
        listeMagies[i] = new Magie();
    }*/

    return tabMagies;
}

Texture** creerIcones(int* nbrIcones, SDL_Renderer* renderer){
    *nbrIcones = 2;
    SDL_Rect rect = {0,0,25,25};
    Texture** listeIcones = (Texture**) malloc(sizeof(Texture*)*(*nbrIcones));
    for(int i=0; i<*nbrIcones;i++){
        listeIcones[i] = new Texture();
    }
    //1) Brulure
    listeIcones[0]->loadNewTexture("images/icones/brulure.png", renderer, rect);
    //2) Barriere
    listeIcones[1]->loadNewTexture("images/icones/bouclier.png", renderer, rect);

    return listeIcones;
}

Joueur* creerJoueur(SDL_Renderer* renderer, Grille* grilleCombat){

    int x = 0, y = 610, w = 50, h = 75;
    SDL_Rect rect = {x, y, w, h}; //surface pour coller le sprite
    SDL_Rect collider = {rect.x + 5, rect.y + 50, w - 10, h - 50};
    string name;

    Joueur* joueur = new Joueur("Zack", "images/personnages/archer.png", renderer, rect, collider );
    joueur->p->setArcher();

    //creation du profil joueur
//    stats.pv = 100;
//    stats.pvMax = 100;
//    stats.pm = 100;
//    stats.pmMax = 100;
//    stats.atq = 20;
//    //stats.def = 10;
//    stats.magie = 20;
//    stats.initiative = 30;
//    res.resContondant = 0;
//    res.resEau = 0;
//    res.resExplosion = 0;
//    res.resFeu = 100;
//    res.resFoudre = 0;
//    res.resGlace = 0;
//    res.resPercant = 0;
//    res.resTranchant = 0;
//    res.resVent = 0;
//    res.resTerre = 0;

    Liste<Profile*>* listeJoueurs = new Liste<Profile*>();

    name = "Zack";
    double fact = 2.2;
    w = 288*fact;
    h = 128*fact;
    rect = {0, 0, w, h};
    Profile* archer = new Profile("Archer", "images/personnages/archerCombat.png", renderer, rect, true);
    archer->setPortrait("images/personnages/portraits/archer.png", renderer);
    int x_cr = 131*fact; //coordinnee du collider dans le repere du rect
    int y_cr = 83*fact;
    collider.w = 25*fact;
    collider.h = 45*fact;
    archer->ligne = 0;
    archer->colonne = 1;
    collider.x = grilleCombat->tab[0][1].x ;
    collider.y = grilleCombat->tab[0][1].y - collider.h;
    archer->setArcher(&collider);
    archer->setPosition(collider.x - x_cr, collider.y - y_cr);
    listeJoueurs->inserer(0, archer);
    //joueur->profiles[archer->ligne] = archer;
    //joueur->nbrProfiles++;

    fact=2.3;
    rect.w = 288*fact;
    rect.h = 128*fact;
    collider.w = 25*fact;
    x_cr = 131*fact;
    y_cr = 83*fact;
    Profile* samourai = new Profile("Samourai", "images/personnages/bretteur.png", renderer, rect, true);
    samourai->setPortrait("images/personnages/portraits/bretteur.png", renderer);
    samourai->ligne = 1;
    samourai->colonne = 2;
    collider.x = grilleCombat->tab[1][2].x ;
    collider.y = grilleCombat->tab[1][2].y - collider.h;
    samourai->setBretteur(&collider);
    samourai->setPosition(collider.x - x_cr, collider.y - y_cr);
    listeJoueurs->inserer(1, samourai);
    //joueur->profiles[samourai->ligne] = samourai;
    //joueur->nbrProfiles++;

    fact=2.2;
    rect.w = 288*fact;
    rect.h = 128*fact;
    collider.w = 25*fact;
    x_cr = 131*fact; //coordinnee du collider dans le repere du rect
    y_cr = 83*fact;
    Profile* ninja = new Profile("Ninja", "images/personnages/ninja.png", renderer, rect, true);
    ninja->setPortrait("images/personnages/portraits/ninja.png", renderer);
    ninja->ligne = 2;
    ninja->colonne = 2;
    collider.x = grilleCombat->tab[2][2].x ;
    collider.y = grilleCombat->tab[2][2].y - collider.h;
    ninja->setNinja(&collider);
    ninja->setPosition(collider.x - x_cr, collider.y - y_cr);
    listeJoueurs->inserer(2, ninja);
    //joueur->profiles[ninja->ligne] = ninja;
    //joueur->nbrProfiles++;

    rect.w = 192*fact;
    rect.h = 112*fact;
    x_cr = 88*fact;
    y_cr = 47*fact;
    collider.w = 15*fact;
    collider.h = 49*fact;
    Profile* elementaliste = new Profile("Elementaliste", "images/personnages/elementalist.png", renderer, rect, true);
    elementaliste->setPortrait("images/personnages/portraits/elementalist.png", renderer);
    elementaliste->ligne = 3;
    elementaliste->colonne = 0;
    collider.x = grilleCombat->tab[3][0].x ;
    collider.y = grilleCombat->tab[3][0].y - collider.h;
    elementaliste->setElementaliste(&collider);
    elementaliste->setPosition(collider.x - x_cr, collider.y - y_cr);
    listeJoueurs->inserer(3, elementaliste);
    //joueur->profiles[elementaliste->ligne] = elementaliste;
    //joueur->nbrProfiles++;

    rect.w = 288*fact;
    rect.h = 128*fact;
    x_cr = 136*fact;
    y_cr = 82*fact;
    collider.w = 20*fact;
    collider.h = 45*fact;
    Profile* chevalier = new Profile("Chevalier", "images/personnages/chevalier.png", renderer, rect, true);
    chevalier->setPortrait("images/personnages/portraits/chevalier.png", renderer);
    chevalier->ligne = 4;
    chevalier->colonne = 2;
    collider.x = grilleCombat->tab[4][2].x ;
    collider.y = grilleCombat->tab[4][2].y - collider.h;
    chevalier->setChevalier(&collider);
    chevalier->setPosition(collider.x - x_cr, collider.y - y_cr);
    listeJoueurs->inserer(4, chevalier);
    joueur->profiles = listeJoueurs;

    return joueur;
}

bool demandeSortie(){
    bool continuer = true;
    bool quit = false;
    SDL_Event e;
    printf("Voulez-vous vraiment quitter le jeu ? \nAppuyez sur o pour oui, sur n pour non.\n");

    while(continuer){
        while(SDL_PollEvent(&e) != 0){
            if(e.type==SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                case SDLK_o:
                    continuer = false;
                    quit = true;
                    break;
                case SDLK_n:
                    continuer = false;
                    quit = false;
                    printf("Reprise du jeu.\n");
                    break;
                }
            }
        }
    }

    return quit;
}

/*
void initGame(Joueur* joueur, Profile* gobelin){
    printf("Le combat contre le %s debute !\n", gobelin->getName());
    printf("Au joueur de commencer. L'ennemi repondra apres le joueur.\n");
    printf("Attaquez le %s !\n\n", gobelin->getName());
    printf("CONTROLES : \n");
    printf("A pour attaquer.\n");
    printf("E pour lancer un sort.\n");
    printf("D pour se proteger(degats reduits de moitier).\n");
    printf("I pour afficher l'inventaire.\n");
    printf("R pour utiliser une Potion (redonne 50 PV)\n");
    printf("P pour passer son tour.\n");
    printf("ESC pour quitter le jeu.\n");
    printf("Fleches directionnelles pour deplacer le curseur (aucun effet pour l'instant).\n\n");

    printf("%s : %f PV\n", joueur->getName(), joueur->getPv());
    printf("%s : %f PV\n\n", gobelin->getName(), gobelin->getPv());
}*/

/*
Liste <SDL_Rect>* creerChemins(Texture* entite1, Texture* entite2, SDL_Rect* murs, int nbrMurs){
    bool done = false; //condition d'arret
    SDL_Rect successor[8];
    SDL_Rect smallSuccesor;
    //bool valide[8] = {true}; //par defaut, tous les successeur sont valides
    double f[8] = {0.0};
    double q = 0.0;
    double h = 0.0;

    double centre1x = 0.0;
    double centre1y = 0.0;
    double centre2x = 0.0;
    double centre2y = 0.0;

    double distanceX = 0.0;
    double distanceY = 0.0;

    double goalX = entite2->collider.x + entite2->collider.w /2.0;
    double goalY = entite2->collider.y + entite2->collider.h /2.0;

    int indice = 0; //endroit de la liste ou on stocke le rect
    int indiceMin = 0; //indice du sccesseur de f min
    double fMin = 0.0;
    Liste<SDL_Rect>* chemin = new Liste<SDL_Rect>();
    SDL_Rect initial = entite1->collider;
    chemin->inserer(indice, entite1->collider);
    indice++;

    while(!done){
        f[8] = {0};
        fMin = 0.0;
        //printf("prout\n %d\n", indice);
        //On cree le successeur 1
        successor[0].x = initial.x ;
        successor[0].y = initial.y - initial.h;
        successor[0].w = entite1->collider.w ;
        successor[0].h = entite1->collider.h ;

        //On cree le successeur 2
        successor[1].x = initial.x + initial.w;
        successor[1].y = initial.y - initial.h;
        successor[1].w = entite1->collider.w ;
        successor[1].h = entite1->collider.h ;

        //On cree le successeur 3
        successor[2].x = initial.x + initial.w;
        successor[2].y = initial.y ;
        successor[2].w = entite1->collider.w ;
        successor[2].h = entite1->collider.h ;

        //On cree le successeur 4
        successor[3].x = initial.x + initial.w;
        successor[3].y = initial.y + initial.h;
        successor[3].w = entite1->collider.w ;
        successor[3].h = entite1->collider.h ;

        //On cree le successeur 5
        successor[4].x = initial.x;
        successor[4].y = initial.y + initial.h;
        successor[4].w = entite1->collider.w ;
        successor[4].h = entite1->collider.h ;

        //On cree le successeur 6
        successor[5].x = initial.x - initial.w;
        successor[5].y = initial.y + initial.h;
        successor[5].w = entite1->collider.w ;
        successor[5].h = entite1->collider.h ;

        //On cree le successeur 7
        successor[6].x = initial.x - initial.w;
        successor[6].y = initial.y ;
        successor[6].w = entite1->collider.w ;
        successor[6].h = entite1->collider.h ;

        //On cree le successeur 8
        successor[7].x = initial.x - initial.w;
        successor[7].y = initial.y - initial.h;
        successor[7].w = entite1->collider.w ;
        successor[7].h = entite1->collider.h ;

        //On regarde chaque successor
        for(int i=0; i<8 && !done;i++){
            //on regarde si on est arrive a destination
            if(checkCollision(&successor[i], &entite2->collider, 1)){
                done = true; //on arrete de chercher
                chemin->inserer(indice, successor[i]);
                //indice++;
            }
            //On regarde s'il y a collision avec le decor
            else if( checkCollision(&successor[i], murs, nbrMurs) ){
                //valide[i] = false; //le successeur est bloque
                //en fonction de quelle direction  a bloque
                switch(i){
                    case 0: //nord
                        smallSuccesor.x = successor[i].x;
                        smallSuccesor.y = successor[i].y - 10;
                        smallSuccesor.w = successor[i].w;
                        smallSuccesor.h = 10;
                        successor[i] = smallSuccesor;
                        break;
                    case 1: //nord est
                        smallSuccesor.x = successor[i].x + successor[i].w;
                        smallSuccesor.y = successor[i].y - 10;
                        smallSuccesor.w = 10;
                        smallSuccesor.h = 10;
                        successor[i] = smallSuccesor;
                        break;
                    case 2: //est
                        smallSuccesor.x = successor[i].x + successor[i].w;
                        smallSuccesor.y = successor[i].y;
                        smallSuccesor.w = 10;
                        smallSuccesor.h = successor[i].h;
                        successor[i] = smallSuccesor;
                        break;
                    case 3: //sud est
                        smallSuccesor.x = successor[i].x + successor[i].w;
                        smallSuccesor.y = successor[i].y + successor[i].h;
                        smallSuccesor.w = 10;
                        smallSuccesor.h = 10;
                        successor[i] = smallSuccesor;
                        break;
                    case 4: //sud
                        smallSuccesor.x = successor[i].x;
                        smallSuccesor.y = successor[i].y + successor[i].h;
                        smallSuccesor.w = successor[i].w;
                        smallSuccesor.h = 10;
                        successor[i] = smallSuccesor;
                        break;
                    case 5: //sud ouest
                        smallSuccesor.x = successor[i].x -10;
                        smallSuccesor.y = successor[i].y + successor[i].h;
                        smallSuccesor.w = 10;
                        smallSuccesor.h = 10;
                        successor[i] = smallSuccesor;
                        break;
                    case 6: //ouest
                        smallSuccesor.x = successor[i].x -10;
                        smallSuccesor.y = successor[i].y;
                        smallSuccesor.w = 10;
                        smallSuccesor.h = successor[i].h;
                        successor[i] = smallSuccesor;
                        break;
                    case 7: //nord ouest
                        smallSuccesor.x = successor[i].x - 10;
                        smallSuccesor.y = successor[i].y - 10;
                        smallSuccesor.w = 10;
                        smallSuccesor.h = 10;
                        successor[i] = smallSuccesor;
                        break;
                }//switch
                if(!checkCollision(&successor[i], murs, nbrMurs)){//on verifie s'il n'y a pas de nouvelle collision
                    //calcul de g, h et f
                    centre1x = initial.x + (double)initial.w/2.0;
                    centre1y = initial.y + (double)initial.h/2.0;

                    centre2x = successor[i].x + (double)successor[i].w/2.0;
                    centre2y = successor[i].y + (double)successor[i].w/2.0;

                    distanceX = centre2x-centre1x;
                    distanceY = centre2y-centre1y;

                    q = sqrt(pow(distanceX, 2)+pow(distanceY, 2));

                    distanceX = goalX-centre2x;
                    distanceY = goalY-centre2y;

                    h = sqrt(pow(distanceX, 2)+pow(distanceY,2));

                    f[i] = q + h;
                    if(fMin == 0.0){
                        fMin = f[i];
                        indiceMin = i;
                    }
                    else if(f[i] < fMin){
                        fMin = f[i];
                        indiceMin = i;
                    }
                }
            }
            else{
                //calcul de g, h et f
                centre1x = initial.x + (double)initial.w/2.0;
                centre1y = initial.y + (double)initial.h/2.0;

                centre2x = successor[i].x + (double)successor[i].w/2.0;
                centre2y = successor[i].y + (double)successor[i].w/2.0;

                distanceX = centre2x-centre1x;
                distanceY = centre2y-centre1y;

                q = sqrt(pow(distanceX, 2)+pow(distanceY, 2));

                distanceX = goalX-centre2x;
                distanceY = goalY-centre2y;

                h = sqrt(pow(distanceX, 2)+pow(distanceY,2));

                f[i] = q + h;
                if(fMin == 0.0){
                    fMin = f[i];
                    indiceMin = i;
                }
                else if(f[i] < fMin){
                    fMin = f[i];
                    indiceMin = i;
                }
            }
        }//for
        //Si on a pas atteint la destination, on ajoute le successeur de fMin a la liste
        //celui-ci devient le nouvel initial pour la prochaine iteration
        if(!done ){
        chemin->inserer(indice, successor[indiceMin]);
        indice++;
        initial = successor[indiceMin];
        }
    }//while

    printf("%d\n", chemin->taille());
    return chemin;
}*/

Liste<Point>* creerTrajectoire(Liste<SDL_Rect>* chemin){
    Liste <Point>* trajectoire = new Liste<Point>();
    Point pt = {0,0};
    SDL_Rect* rect = NULL; //rectangle du chemin

    for(int i=0; i < chemin->taille(); i++){
        rect = chemin->getNoeud(i);
        pt.x = rect->x + rect->w / 2;
        pt.y = rect->y + rect->h / 2;
        trajectoire->inserer(i, pt);
    }

    return trajectoire;
}

double calculerDistance(SDL_Rect* rect1, SDL_Rect* rect2){
    double distanceX = 0.0;
    double distanceY = 0.0;

    distanceX = rect1->x - rect2->x;
    distanceY = rect1->y - rect2->y;

    return sqrt(pow(distanceX, 2)+pow(distanceY, 2));
}

void initDC(DonneesCombat* dc, int nbrJoueurs, int nbrEnnemis){
    dc->afficherDegats = false;
    dc->currentEntite = 0;
    dc->decallageDegats = 0;
    dc->defaite = false;
    dc->degats = 0;
    dc->degatsTimer = Timer();
    dc->timerFin = Timer();
    dc->tour = 0;
    dc->victoire = false;
    dc->degatsRect = {0,0,70,50};
    dc->degatsText = new Texture();
    dc->nbrJoueurs = nbrJoueurs;
    dc->nbrEnnemi = nbrEnnemis;
    dc->nbrJoueursDead = 0;
    dc->nbrEnnemiDead = 0;

    dc->increment = 0;
    dc->fuite = false;

    dc->currentMagie = NULL;
    dc->compteur = new Texture();

    for(int i=0; i < 3; i++){
        dc->joueursDead[i] = 0;
        dc->ennemisDead[i] = 0;
    }

}

void initCombat(DonneesCombat* dc, Liste<Profile*>* listeProfiles, Liste<Profile*>* listeJoueurs){
    Profile* joueur = NULL;

    for(int j = 0; j < listeJoueurs->taille(); j++){
        joueur = listeJoueurs->getNoeud2(j);
        //printf("%s\n", joueur->getName());
        //on insere le joueur dans la liste en fonction de son initiative
        for(int i = 0; i <= listeProfiles->taille();i++){
            if(i < listeProfiles->taille()){
                if(listeProfiles->getNoeud2(i)->getInit() < joueur->getInit()){
                    listeProfiles->inserer(i, joueur);
                    break;
                }
            }
            else{
                listeProfiles->inserer(i, joueur);
                break;
            }
        }
    }

    listeProfiles->getNoeud2(0)->updateIsTurn(true);
    if(listeProfiles->getNoeud2(0)->pmEnRecharge){
        listeProfiles->getNoeud2(0)->updateStats(Add, PM, listeProfiles->getNoeud2(0)->getPmMax()/10);
    }
    /*
    bool foundJoueur = false;
    bool foundEnnemi = false;
    for(int j = 0; j < listeProfiles->taille(); j++){
        if(!listeProfiles->getNoeud2(j)->getIsPlayer() && !foundEnnemi){
            for(int i = 0; i < listeJoueurs->taille(); i++){
                listeJoueurs->getNoeud2(i)->target = j;
            }
            foundEnnemi = true;
        }
        else if(listeProfiles->getNoeud2(j)->getIsPlayer() &&!foundJoueur){
            for(int i = 0; i < listeProfiles->taille(); i++){
                if(!listeProfiles->getNoeud2(i)->getIsPlayer()){
                    listeProfiles->getNoeud2(i)->target = j;
                }
            }
            foundJoueur = true;
        }
    }*/
    for(int i=0; i < listeJoueurs->taille(); i++){
        listeJoueurs->getNoeud2(i)->target[0] = 0;
        listeJoueurs->getNoeud2(i)->target[1] = 0;
    }

    //On  choisit une premiere cible pour les ennemis
    dc->tour ++;
}

void gestionCombat(DonneesCombat* dc, Liste<Profile*>* listeProfiles, Liste<Profile*>* listeJoueurs, Liste<Profile*>* ennemis[3], Liste<Profile*>* joueurs[3]){
    Profile* currentProfile = NULL;
    //Profile* ennemiTarget = listeJoueurs->getNoeud2(0);
    if(dc->currentEntite < listeProfiles->taille() ){
        currentProfile = listeProfiles->getNoeud2(dc->currentEntite);
    }
    //on initialise le combat
    if(dc->tour == 0){
        initCombat(dc, listeProfiles, listeJoueurs);
    }
    //S'il ne reste que des joueurs dans la liste, fin du combat
    else if(dc->nbrEnnemi == dc->nbrEnnemiDead){
            if(!dc->timerFin.isStarted()){
                dc->timerFin.start();
            }
            else if(dc->timerFin.getTicks() > 2000){
                dc->victoire = true;
                dc->timerFin.stop();
            }
    }
    else if(dc->nbrJoueurs == dc->nbrJoueursDead){
        dc->defaite = true;
    }
    //fin du tour et debut d'un nouveau
    else if(dc->currentEntite == listeProfiles->taille()){
        dc->currentEntite = 0;
        dc->tour++;
        currentProfile = listeProfiles->getNoeud2(dc->currentEntite);
        if(!currentProfile->getIsDead()){
            currentProfile->updateIsTurn(true);
            currentProfile->debutTour = true;
        }
    }
    else{
        if(!currentProfile->getIsPlayer() && currentProfile->getIsTurn() && (currentProfile->getPv() > 0)){
        //On gere le comportement des ennemis
            //1) On verifie si la position sur la grille est correcte
            if(currentProfile->colonne > 0){//on avance d'une ligne
                if(currentProfile->getAnimType() == IDLE){
                    currentProfile->changeAnimation(WALK);
                }
                else if(currentProfile->getAnimType() == WALK && dc->increment > -150){
                    currentProfile->addToX(-10);
                    currentProfile->addToCollider(-10);
                    dc->increment -= 10;
                }
                else if(currentProfile->getAnimType() == WALK && dc->increment <= -150){
                    currentProfile->changeAnimation(IDLE);
                    currentProfile->updateIsTurn(false);
                    dc->increment = 0;
                    currentProfile->depart = *currentProfile->getRect(); //on reset la position
                    currentProfile->departCollider = *currentProfile->getCollider();

                    //On supprime l'ennemi de la liste
                    //On cherche sa position dans la liste
                    bool stop = false;
                    Profile* cProfile = NULL;
                    for(int i = 0; i < ennemis[currentProfile->colonne]->taille() && !stop; i++){
                        cProfile = ennemis[currentProfile->colonne]->getNoeud2(i);
                        if( currentProfile->getNameString() == cProfile->getNameString() ){
                            ennemis[currentProfile->colonne]->supprimer(i);
                            stop = true;
                        }
                    }
                    //On place l'ennemi a sa nouvelle position
                    currentProfile->colonne--;
                    stop = false;
                    for(int i = 0; i < ennemis[currentProfile->colonne]->taille() && !stop; i++){
                        cProfile = ennemis[currentProfile->colonne]->getNoeud2(i);
                        if(cProfile->ligne > currentProfile->ligne){
                            ennemis[currentProfile->colonne]->inserer(i, currentProfile);
                            stop = true;
                        }
                    }
                    if(!stop){
                        ennemis[currentProfile->colonne]->inserer(ennemis[currentProfile->colonne]->taille(), currentProfile);
                    }
                }
            }
            //2) Si tout est ok on attaque
            else{
                if(currentProfile->getAnimType() == IDLE){
                    Profile* cProfile = NULL;
                    bool done = false;
                    //On choisit une cible
                    for(int i = 2; i >=0 && !done;i--){
                        for(int j=0; j < joueurs[i]->taille(); j++){
                            cProfile = joueurs[i]->getNoeud2(j);
                            if( !cProfile->getIsDead() ){
                                currentProfile->target[0] = j;
                                currentProfile->target[1] = i;
                                done = true;
                                break;
                            }
                        }
                    }
                    if(!joueurs[currentProfile->target[1]]->getNoeud2(currentProfile->target[0])->getIsDead())
                        currentProfile->changeAnimation(PREPARE);
                    //currentProfile->changeAnimation(WALK);
                }

                /*else if(currentProfile->getAnimType() == WALK && (currentProfile->getColliderX() > (ennemiTarget->getColliderX() + ennemiTarget->getColliderW()))){
                    currentProfile->addToX(-10);
                    currentProfile->addToCollider(-10);
                }
                else if(currentProfile->getAnimType() == WALK && (currentProfile->getColliderX() <= (ennemiTarget->getColliderX() + ennemiTarget->getColliderW()))){
                    currentProfile->changeAnimation(PREPARE);
                }*/
            }

        }
        else if(currentProfile->getIsPlayer() && currentProfile->getIsTurn() && (currentProfile->getPv() > 0)){
            if(currentProfile->getAnimType() == AVANCER && dc->increment < 150){
                currentProfile->addToX(10);
                currentProfile->addToCollider(10);
                dc->increment += 10;
            }
            else if(currentProfile->getAnimType() == AVANCER && dc->increment >= 150){
                currentProfile->changeAnimation(IDLE);
                currentProfile->updateIsTurn(false);
                dc->increment = 0;
                currentProfile->depart = *currentProfile->getRect(); //on reset la position
                currentProfile->departCollider = *currentProfile->getCollider();
            }
            else if(currentProfile->getAnimType() == RECULER && dc->increment > -150){
                currentProfile->addToX(-10);
                currentProfile->addToCollider(-10);
                dc->increment -= 10;
            }
            else if(currentProfile->getAnimType() == RECULER && dc->increment <= -150){
                currentProfile->changeAnimation(IDLE);
                currentProfile->updateIsTurn(false);
                dc->increment = 0;
                currentProfile->depart = *currentProfile->getRect(); //on reset la position
                currentProfile->departCollider = *currentProfile->getCollider();
            }
        }
        else if(!currentProfile->getIsTurn()){
            dc->currentEntite++;
            if(dc->currentEntite < listeProfiles->taille()){
                currentProfile = listeProfiles->getNoeud2(dc->currentEntite);
                if(currentProfile->getPv() > 0){
                    currentProfile->updateIsTurn(true);
                    currentProfile->debutTour = true;
                }
            }
        }
    }

}

bool afficherProfiles(SDL_Renderer* renderer, Liste<Profile*>* joueurs[3], Liste<Profile*>* ennemis[3], Liste<Profile*>* lProfilesToRender, Texture** tabIcones, DonneesCombat* dc){
    bool d = false;
    int x = 0;
    int y = 0;
    Profile* thisProfile = NULL;
    Profile* target = NULL;
    Profile* joueur = NULL;
    for(int i=0;i < lProfilesToRender->taille();i++){
        //S'il s'agit du joueur
        thisProfile = lProfilesToRender->getNoeud2(i);
        if( thisProfile->getIsPlayer() ){
            if(thisProfile->render(renderer)){
                switch(thisProfile->tTarget){
                case ALLIE:
                    target = joueurs[thisProfile->target[1]]->getNoeud2(thisProfile->target[0]);
                    break;
                case ENNEMI:
                    target = ennemis[thisProfile->target[1]]->getNoeud2(thisProfile->target[0]);
                    break;
                }
                if(thisProfile->getAnimType() == ATTACK){
                    thisProfile->attaquer(target, &dc->degats);
                    dc->afficherDegats = true;
                    dc->degatsRect.x = target->getColliderX() + dc->decallageDegats;
                    dc->degatsRect.y = target->getColliderY();
                    if(!(target->getAnimType() == DEFENDRE) && dc->degats > 0){
                        target->changeAnimation(HURT);
                    }
                    //On verifie si on s'est attaque soi meme
                    if(target->getName() == thisProfile->getName()){
                        thisProfile->updateIsTurn(false);
                    }
                    d = true;
                }
                else if(thisProfile->getAnimType() == MAGIE){
                    dc->currentMagie = thisProfile->currentMagie;
                    x += target->getColliderX();
                    x += target->getColliderW()/2;
                    x -= dc->currentMagie->getRectW()/2;
                    dc->currentMagie->setX(x);
                    y += target->getColliderY();
                    y += target->getColliderH()/2;
                    y -= dc->currentMagie->getRectH()/2;
                    dc->currentMagie->setY(y);
                    dc->currentMagie->startAnimation();
                }
                else if(thisProfile->getAnimType() == HURT && thisProfile->getPv() == 0){
                    thisProfile->changeAnimation(DEATH);
                }
                else if(thisProfile->getAnimType() == DEATH){
                    thisProfile->setIsDead(true);
                    //dc->nbrJoueursDead++;
                    //printf("%d\n", dc->nbrJoueursDead);
                }
                else if(thisProfile->getAnimType() == DEFENDRE){
                    thisProfile->seDefendre();
                }

                if(target->getPv() <= 0 && thisProfile->getAnimType()!=IDLE){
                    target->setIsDead(true);
                    switch(thisProfile->tTarget){
                    case ALLIE:
                        dc->nbrJoueursDead++;
                        printf("%d\n", dc->nbrJoueursDead);
                        break;
                    case ENNEMI:
                        dc->nbrEnnemiDead++;
                        dc->ennemisDead[thisProfile->colonne]++;
                        printf("nbrEnnemiDead : %d\n", dc->nbrEnnemiDead);
                        break;
                    }
                }
            }
        }//player
        //S'il s'agit d'un pnj
        else{
            if(thisProfile->render(renderer)){
                target = joueurs[thisProfile->target[1]]->getNoeud2(thisProfile->target[0]);
                if(thisProfile->getAnimType() == ATTACK ){
                    thisProfile->attaquer(target, &dc->degats);
                    dc->afficherDegats = true;
                    dc->degatsRect.x = target->getColliderX() - dc->decallageDegats;
                    dc->degatsRect.y = target->getColliderY();
                    if(!(target->getAnimType() == DEFENDRE) && dc->degats > 0){
                        target->changeAnimation(HURT);
                    }
                    d = true;
                }
                else if(thisProfile->getAnimType() == HURT && thisProfile->getPv() == 0){
                    thisProfile->changeAnimation(DEATH);
                }
                else if(thisProfile->getAnimType() == DEATH){
                    thisProfile->setIsDead(true);
                }
                if(target->getPv() <= 0){
                    target->setIsDead(true);
                    switch(thisProfile->tTarget){
                    case ALLIE:
                        dc->nbrJoueursDead++;
                        printf("%d\n", dc->nbrJoueursDead);
                        break;
                    case ENNEMI:
                        dc->nbrEnnemiDead++;
                        dc->ennemisDead[thisProfile->colonne]++;
                        printf("nbrEnnemiDead : %d\n", dc->nbrEnnemiDead);
                        break;
                    }
                }
            }
        }//pnj case
        //Affichage des icones
        if(!thisProfile->getIsDead()){
            switch(thisProfile->fleau){
            case BRULURE:
                tabIcones[0]->setX(thisProfile->getColliderX());
                tabIcones[0]->setY(thisProfile->getColliderY() + thisProfile->getColliderH() - tabIcones[0]->getRectH());
                tabIcones[0]->render(renderer);
                break;
            }
            for(int i=0; i < thisProfile->nbrEtats; i++){
                switch(thisProfile->listeEtats[i]){
                case BARRIERE:
                    tabIcones[1]->setX(thisProfile->getColliderX());
                    tabIcones[1]->setY(thisProfile->getColliderY() + thisProfile->getColliderH() - tabIcones[1]->getRectH());
                    tabIcones[1]->render(renderer);
                    break;
                }
            }
        }
    }//for

    return d;
}

/*
bool afficherProjectile(SDL_Renderer* renderer, Projectile* proj, Profile* joueur, Liste<Profile*>* listeProfiles, DonneesCombat* dc){
    bool killed = false;
    if(proj->render(renderer, joueur)){
        listeProfiles->getNoeud2(joueur->target)->changeAnimation(HURT);
        dc->afficherDegats = true;
        dc->degatsRect.x = listeProfiles->getNoeud2(joueur->target)->getColliderX() + dc->decallageDegats;
        dc->degatsRect.y = listeProfiles->getNoeud2(joueur->target)->getColliderY();
        killed = joueur->lancerMagie(listeProfiles->getNoeud2(joueur->target), dc->currentMagie, &dc->degats );
        if(killed){
            listeProfiles->supprimer(joueur->target);
            if(joueur->target >= listeProfiles->taille()){joueur->target--;}
        }
        return true;
    }
    else if(proj->getAnimationState()){
        if( !checkCollision(proj->getCollider(), listeProfiles->getNoeud2(joueur->target)->getCollider()) && (proj->getType()==TRAJET)){
            proj->addToTrajet(20);
            proj->addToCollider(20);
        }
        else if(checkCollision(proj->getCollider(), listeProfiles->getNoeud2(joueur->target)->getCollider()) && (proj->getType()==TRAJET)){
            proj->setAnimType(IMPACT);
            proj->impactRect.x = listeProfiles->getNoeud2(joueur->target)->getColliderX() - proj->getColliderW()/2;
            proj->impactRect.y = listeProfiles->getNoeud2(joueur->target)->getColliderY() - proj->getColliderH()/2;
        }
    }
    return false;
}*/

bool afficherMagie(SDL_Renderer* renderer, Profile* joueur, Liste<Profile*>* cibles[3], DonneesCombat* dc){
    //bool killed = false;
    Profile* currentProfile = NULL;
        if(dc->currentMagie->render(renderer)){
            currentProfile = cibles[joueur->target[1]]->getNoeud2(joueur->target[0]);
            joueur->updateIsTurn(false);
            if(dc->currentMagie->getPuissance() != 0){
                dc->afficherDegats = true;
                dc->degatsRect.x = currentProfile->getColliderX() + dc->decallageDegats;
                dc->degatsRect.y = currentProfile->getColliderY();
            }
            if(joueur->lancerMagie(currentProfile, dc->currentMagie, &dc->degats )){
                currentProfile->setIsDead(true);
                switch(joueur->tTarget){
                case ALLIE:
                    dc->nbrJoueursDead++;
                    printf("%d\n", dc->nbrJoueursDead);
                    break;
                case ENNEMI:
                    dc->nbrEnnemiDead++;
                    dc->ennemisDead[currentProfile->colonne]++;
                    printf("nbrEnnemiDead : %d\n", dc->nbrEnnemiDead);
                    break;
                }
            }
            if(dc->degats > 0){
                currentProfile->changeAnimation(HURT);
            }
            return true;
        }
    return false;
}

void afficherDegats( SDL_Renderer* renderer, DonneesCombat* dc ){
    if( dc->afficherDegats && !dc->degatsTimer.isStarted() ){
        dc->degatsTimer.start();
    }
    if(!(dc->degatsTimer.getTicks() > 1000) && dc->afficherDegats){
        dc->degatsText->renderText(renderer, &dc->degatsRect );
    }
    else if((dc->degatsTimer.getTicks() > 1000) && dc->afficherDegats){
        dc->afficherDegats = false;
        dc->degatsTimer.stop();
    }
}

void afficherPortraits(Texture* cadrePortrait, SDL_Renderer* renderer, DonneesCombat* dc, Liste<Profile*>* listeProfiles){
    cadrePortrait->setPosition(window_width/2 - cadrePortrait->getRectW()/2 - 50, 7); //on reinitialise la pos du portrait
    int nbrGauche = 0, nbrDroite = 0, nbrMax = 1, indice = dc->currentEntite;
    int offset = 5; //px, ecrat entre les cadres
    if(indice>=listeProfiles->taille()){
        indice = listeProfiles->taille()-1;
    }
    if(listeProfiles->taille()%2==0){
        //Si pair
        nbrDroite = listeProfiles->taille()/2;
        nbrGauche = nbrDroite-1;
    }
    else{
        //Si impair
        nbrDroite = (listeProfiles->taille()-1)/2;
        nbrGauche = nbrDroite;
    }
    nbrMax += (nbrDroite+nbrGauche);

    //On print le milieu et à droite
    for(int i=0; i<=nbrDroite;i++){
        cadrePortrait->render(renderer);
        if(i==0){
            cadrePortrait->setY(0);
            listeProfiles->getNoeud2(indice)->getPortrait()->setPosition(cadrePortrait->getRectX()+3, 10);
        }
        else{
            listeProfiles->getNoeud2(indice)->getPortrait()->setPosition(cadrePortrait->getRectX()+3, 3);
        }
        //Print du perso :
        listeProfiles->getNoeud2(indice)->getPortrait()->render(renderer);
        //Si mort, on ajoute un filtre sombre par dessus
        if(listeProfiles->getNoeud2(indice)->getIsDead()){
            SDL_SetRenderDrawColor( renderer, 0x40, 0x40, 0x40, 0x00 );
            SDL_RenderFillRect( renderer, listeProfiles->getNoeud2(indice)->getPortrait()->getRect() );
        }
        //On ajuste la position du cadre
        cadrePortrait->setX(cadrePortrait->getRectX() + cadrePortrait->getRectW() + offset);


        //On verifie si l'indice ne depasse pas la taille de la liste
        indice++;
        if(indice >= listeProfiles->taille()){
            //Alors, on repart au début de la liste
            indice = 0;
        }
    }

    //On reset l'indice
    indice = dc->currentEntite-1;
    if(indice<0){
        indice = listeProfiles->taille()-1;
    }
    //On remet le cadre au milieu
    cadrePortrait->setX(window_width/2 - cadrePortrait->getRectW()/2 - 50);
    //On print ceux à gauche
    for(int i=0; i<nbrGauche; i++){
        //On ajuste la position du cadre
        cadrePortrait->setX(cadrePortrait->getRectX() - cadrePortrait->getRectW() - offset);
        cadrePortrait->render(renderer);
        listeProfiles->getNoeud2(indice)->getPortrait()->setPosition(cadrePortrait->getRectX()+3, 3);
        listeProfiles->getNoeud2(indice)->getPortrait()->render(renderer);
        //Si mort, on ajoute un filtre sombre par dessus
        if(listeProfiles->getNoeud2(indice)->getIsDead()){
            SDL_SetRenderDrawColor( renderer, 0x40, 0x40, 0x40, 0x99 );
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect( renderer, listeProfiles->getNoeud2(indice)->getPortrait()->getRect() );
        }

        //On verifie si l'indice ne depasse pas la taille de la liste
        indice--;
        if(indice < 0){
            //Alors, on repart au début de la liste
            indice = listeProfiles->taille()-1;
        }
    }
}

bool gestionDebutTour(Profile* profile, DonneesCombat* dc){
    bool b = false;
    //Recharge PM, action DEFENDRE
    if(profile->pmEnRecharge){
        profile->updateStats(Add, PM, profile->getPmMax()/10);
        if( profile->getPm() >=  profile->getPmMax()){
            profile->pmEnRecharge = false;
        }
    }
    if(profile->getIsPlayer()&& (profile->getAnimType()==DEFENDRE)){
    profile->startAnimation();};
    profile->debutTour = false;

    //Gestion des degats periodiques
    switch(profile->fleau){
    case BRULURE:
        dc->degats = (100 - profile->getResFeu())/100 * profile->getPvMax()/50; //degats bruts 2% des pv max
        profile->updateStats(Substract, PV, dc->degats);
        printf("%s se consumme et perd %d PV. Il lui reste %d PV.\n\n", profile->getName(), dc->degats, profile->getPv());
        dc->afficherDegats = true;
        if(profile->getIsPlayer()){
            dc->degatsRect.x = profile->getColliderX()- dc->decallageDegats;
        }
        else{
            dc->degatsRect.x = profile->getColliderX()+ profile->getColliderW() + dc->decallageDegats;
        }

        dc->degatsRect.y = profile->getColliderY();
        b = true;
        profile->fleauDuree--;
        if(profile->fleauDuree == 0){
            profile->fleau = ZERO;
        }
        break;
    case GELURE:

        break;
    case CONGELATION:

        break;
    case CHARGE:

        break;
    case SUFFOCATION:

        break;
    case CHANCELEMENT:

        break;
    }

    for(int i=0; i < profile->nbrEtats; i++){
        profile->dureeEtats[i]--;
        if(profile->dureeEtats[i] == 0){
            switch(profile->listeEtats[i]){
            case BARRIERE:
                profile->updateStats(Divide, DEF, 13);
                profile->updateStats(Multiply, DEF, 10);
                break;
            }
            profile->listeEtats[i] = AUCUN;
            profile->nbrEtats--;
        }
    }
    return b;
}

#endif // JEU_CPP
