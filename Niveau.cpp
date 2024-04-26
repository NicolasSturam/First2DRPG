#include "Niveau.h"

Niveau::Niveau(){

}

Niveau::Niveau(string nom, SDL_Renderer* renderer, Grille* grilleEnnemi, int level_width, int level_height){
    niv_musics = NULL;
    this->renderer = renderer;
    this->grilleEnnemi = grilleEnnemi;
    this->level_width = level_width;
    this->level_height = level_height;
    if(nom == "test"){
        creerTest(nom);
    }
    else{
        cout << "Erreur. Nom de niveau invalide." << endl;
    }

}

Niveau::~Niveau(){
    if(niv_musics != NULL){
        for(int i=0;i<nbrMusics;i++){
            free(niv_musics[i]);
        }
        free(niv_musics);
        niv_musics = NULL;
    }

    if(fond != NULL){
        delete(fond);
        fond = NULL;
    }

    if(premierPlan != NULL){
        for(int i=0;i<nbrElements;i++){
            delete(premierPlan[i]);
        }
        delete(premierPlan);
        premierPlan=NULL;
    }
    if(ennemi!=NULL){
        freeEnnemi();
    }
}

void Niveau::creerTest(string nom){
    this->nom = nom;
    int nbrMusics = 2;
    niv_musics = (Mix_Music**) malloc(sizeof(Mix_Music*) * nbrMusics);

    niv_musics[0] = Mix_LoadMUS( "musiques/ff7BattleTheme.mp3" );
    if( niv_musics[0] == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    niv_musics[1] = Mix_LoadMUS( "musiques/StardewValleySpring.mp3" );
    if( niv_musics[1] == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    //Creation des ennemis
    Stats stats;
    Resistances res;

    int x = 680;
    int y = 420;
    int w = 50;
    int h = 75;
    double fact = 0.0;
    SDL_Rect rect = {x, y, w, h}; //surface pour coller le sprite
    SDL_Rect collider = {rect.x + 5, rect.y + 50, w - 10, h - 50};
    ennemi = new PNJ("images/personnages/voleur.png", renderer, rect, collider);
    ennemi->initVoleur();
    //creation du profil ennemi
//    stats.pv = 100;
//    stats.pvMax = 100;
//    stats.pm = 0;
//    stats.pmMax = 0;
//    stats.atq = 20;
//    stats.def = 0;
//    stats.magie = 0;
//    stats.initiative = 12;
//    res.resFeu = 0;

    fact = 2.7;
    rect.w = 48*fact;
    rect.h = 48*fact;
    int x_cr = 16*fact;
    int y_cr = 9*fact;
    collider.w = 16*fact;
    collider.h = 37*fact;
    Profile* ennemi1 = new Profile("Voleur 1", "images/personnages/LightBandit.png", renderer, rect );
    ennemi1->setPortrait("images/personnages/portraits/voleur.png", renderer);
    collider.x = grilleEnnemi->tab[1][2].x;
    collider.y = grilleEnnemi->tab[1][2].y - collider.h;
    ennemi1->setVoleur(&collider);
    ennemi1->setPosition(collider.x - x_cr, collider.y - y_cr);
    ennemi1->colonne = 0;
    ennemi1->ligne = 1;

    //creation du second profil ennemi
    fact = 2.7;
    rect.w = 48*fact;
    rect.h = 48*fact;
    x_cr = 16*fact;
    y_cr = 9*fact;
    collider.w = 16*fact;
    collider.h = 37*fact;
    Profile* ennemi2 = new Profile("Voleur 2", "images/personnages/LightBandit.png", renderer, rect);
    ennemi2->setPortrait("images/personnages/portraits/voleur.png", renderer);
    collider.x = grilleEnnemi->tab[2][2].x;
    collider.y = grilleEnnemi->tab[2][2].y - collider.h;
    ennemi2->setVoleur(&collider);
    ennemi2->setPosition(collider.x - x_cr, collider.y - y_cr);
    ennemi2->ligne = 2;
    ennemi2->colonne = 0;

    Profile* ennemi3 = new Profile("Voleur 3", "images/personnages/LightBandit.png", renderer, rect);
    ennemi3->setPortrait("images/personnages/portraits/voleur.png", renderer);
    collider.x = grilleEnnemi->tab[3][1].x;
    collider.y = grilleEnnemi->tab[3][1].y - collider.h;
    ennemi3->setVoleur(&collider);
    ennemi3->setPosition(collider.x - x_cr, collider.y - y_cr);
    ennemi3->ligne = 3;
    ennemi3->colonne = 1;

    nbrEnnemis = 3;

    Liste<Profile*>* listeEnnemis = new Liste<Profile*>();
    listeEnnemis->inserer(0, ennemi1);
    listeEnnemis->inserer(1, ennemi2);
    listeEnnemis->inserer(2, ennemi3);
    ennemi->profiles = listeEnnemis;


    //Carte
    rect = {0, 0, window_width, window_height };
    backFond = new Background("images/niveaux/village2.png", renderer, rect);
    backFond->initVillage();
    rect = {615, 133 ,178, 178};

    nbrElements = 1;
    premierPlan = (Texture**) malloc(sizeof(Texture*) * nbrElements);
    premierPlan[0] = new Texture("images/elements/toitMaison1.png", renderer, rect);
    rect = {0, 0, window_width, window_height };
    fond = new Texture("images/niveaux/combatVillage2.png", renderer, rect );
}
/*
void Niveau::renderFond(Camera* camera, SDL_Renderer* renderer){
    backFond->render(renderer, camera->getRect());
}*/

void Niveau::renderNiveau(GameState* jeu, Camera* camera, SDL_Renderer* renderer, Joueur* joueur){
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );
    joueur->p->ajusterClip();
    joueur->p->ajusterVitesse();
    if(joueur->p->getVitX() == 0 && joueur->p->getVitY() == 0){
        joueur->p->playAnimation = false;
    }
    joueur->p->moveSprite(level_width, level_height, backFond->getMurs(), backFond->getNbrMurs());
    camera->setCamera(joueur->p->getRect(), window_width, window_height);
    camera->keepInBounds(level_width, level_height);
    if(ennemi != NULL){
        if(checkCollision(joueur->p->getCollider(), ennemi->p->getCollider())){
            *jeu = COMBAT;
            if(Mix_PlayingMusic()){
            Mix_HaltMusic();
            }
            Mix_PlayMusic( niv_musics[0], -1 );
            joueur->p->stop();
        }
        ennemi->patrouille(joueur, backFond->getMurs(), backFond->getNbrMurs());
        ennemi->p->ajusterClip();
        ennemi->p->ajusterVitesse();
        ennemi->p->moveSprite(level_width, level_height, backFond->getMurs(), backFond->getNbrMurs());
    }
    backFond->render(renderer, camera->getRect());

    //Personnages
    joueur->p->render(renderer, camera->getX(), camera->getY());

    if(ennemi != NULL){
        ennemi->p->render(renderer, camera->getX(), camera->getY());
    }
    //Premier plan
    for(int i=0;i<nbrElements;i++){
        premierPlan[i]->render(renderer, NULL, camera->getX(), camera->getY());
    }


}

Mix_Music** Niveau::getMusics(){
    return niv_musics;
}

int Niveau::getNombreEnnemis(){
    return nbrEnnemis;
}

PNJ* Niveau::getEnnemi(){
    return ennemi;
}

Texture* Niveau::getFond(){
    return fond;
}

void Niveau::freeEnnemi(){
    free(ennemi);
    ennemi = NULL;
}
