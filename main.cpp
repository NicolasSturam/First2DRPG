#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <cmath>
#include <math.h>
#include <array>

using namespace std;

#include "Camera.h"
#include "graphisme.h"
#include "Joueur.h"
#include "Profile.h"
#include "jeu.h"
//#include "Objet.h"
#include "Texture.h"
#include "Timer.h"
#include "Background.h"
#include "PNJ.h"
#include "Menu.h"
#include "Projectile.h"
#include "Magie.h"
#include "Niveau.h"

int window_width = 1360;
int window_height = 765;

int main(int argc, char *argv[]){

    //Pointeurs
    Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_GameController* controller = NULL;
    TTF_Font* font = NULL;
    TTF_Font* font_outline = NULL;
    Niveau** niveaux = NULL;

    //Variables
    int screen_fps = 60;
    int screen_ticks_per_frame = 1000/screen_fps;
    int level_width = 1360;
    int level_height = 765;
    SDL_GameControllerType controllerType;
    Timer fpsTimer;
    Timer capTimer;
    int countedFrames = 0;
    int avgFPS = 0;
    int frameTicks = 0;
    int nbrNiveaux = 1;
    int nbrMagies = 3;
    int nbrIcones = 0;

    //Tableaux de donnees
    Magie** listeMagies = NULL;
    Profile** bestiaire = NULL;

    //Structures
    GameState jeu = MAP; //Par defaut on commence sur l'ecran de "deplacement"
    SDL_Rect fpsTextRect;
    SDL_Rect rect; //Pour blit les images
    DonneesCombat dc;
    Couleurs couleurs;
    initCouleurs(&couleurs);

    //Grille d'affichage pour le combat
    Grille grilleCombat, grilleEnnemi;
    int w = 20, h = 80, l = 150;
    creerGrilleCombat(&grilleCombat, w, h, l, 100, 550);
    w = -20, h = 80, l = -150;
    creerGrilleCombat(&grilleEnnemi, w, h, l, level_width - 300, 550);

    //Initialisation
    window = init_video();
    if(window == NULL){
        printf("Window was not created! SDL_Error: %s\n", SDL_GetError());
    }
    else{
        printf("Video initialized\n");
    }
    renderer = window->createRenderer();

    controller = SDL_GameControllerOpen(0);
    if(controller == NULL){
        printf("Erreur ! Impossible d'ouvrir le controleur.\n");
        printf("%s\n",SDL_GetError());
    }
    else{
        controllerType = SDL_GameControllerGetType(controller);
        cout << controllerType <<"\n";
    }
    if(SDL_GameControllerHasLED(controller)){printf("Has LED\n");}
    else{printf("Don't have LED\n");}
    if(SDL_GameControllerSetLED(controller, 0, 0, 0)==-1){printf("No modifiable LED\n");}

    niveaux = (Niveau**) malloc(sizeof(Niveau*)*nbrNiveaux);
    if(niveaux != NULL){
        niveaux[0] = new Niveau("test", renderer, &grilleEnnemi, level_width, level_height);
    }

    font = TTF_OpenFont("fonts/NotJamSlabSerif11/NotJamSlabSerif11.ttf", 24);
    //font = TTF_OpenFont("fonts/TTF/AvenuePixelStroke-Regular.ttf", 24);
    //font = TTF_OpenFont("fonts/Arialic_Hollow.ttf", 24);
    font_outline = TTF_OpenFont("fonts/NotJamSlabSerif11/NotJamSlabSerif11.ttf", 24);
    TTF_SetFontOutline(font_outline, 2);
    Texture* fpsText = NULL;

    if(font == NULL){
        printf("Impossible d'ouvrir le font ! %s\n", TTF_GetError() );
    }
    fpsText = new Texture();
    fpsTextRect = {window_width - 40, 0, 40, 30};
    int frameText = 0;
    int framesText = 20;

    //Creation des entites
    //Map
    rect = {0, 0, window_width, window_height};
    Camera* camera = new Camera(rect);
    Joueur* joueur = creerJoueur(renderer, &grilleCombat);
    //joueur->profiles->getNoeud2(0)->setStats(ATQ, 500);
    //Scene combat
    //Liste avec tous les profils, tries par ordre d'initiative
    //Liste des ennemis
    PNJ* ennemi = niveaux[0]->getEnnemi();
    Liste<Profile*>* listeProfiles = new Liste<Profile*>();
    for(int i=0;i<ennemi->profiles->taille();i++){
        listeProfiles->inserer(i, ennemi->profiles->getNoeud2(i));
    }
    //Liste avec tous les profils pour les afficher
    Liste<Profile*>* listeProfileToRender =  new Liste<Profile*>();
    for(int i=0;i<ennemi->profiles->taille();i++){
        listeProfileToRender->inserer(0, ennemi->profiles->getNoeud2(i));
    }
    for(int i = 0;i < joueur->profiles->taille(); i++){
        listeProfileToRender->inserer(0, joueur->profiles->getNoeud2(i));
    }

    //HUD
    joueur->setHUDCombat(renderer, font, &couleurs.blanc);
    rect = {80, 580, 150, 160};
    Menu* menuCombat = new Menu("images/HUD/panneauVide.png", renderer, rect);
    menuCombat->initTexturesMenu(rect.h, renderer, font, &couleurs);

    rect = {window_width/2-400, window_height/2-50, 800, 100};
    Texture* gameOver = new Texture(&rect);
    gameOver->loadNewTexture("Game Over", renderer, font, &couleurs.blanc);

    //Magies
    listeMagies = creerMagies(&nbrMagies, renderer, font, &couleurs);
    Texture** listeIcones = creerIcones(&nbrIcones, renderer);

    //Magie des persos
    //Ninja
    joueur->profiles->getNoeud2(2)->listeMagies->inserer(0, listeMagies[hachage("Flammes", nbrMagies)]);
    //Mage
    joueur->profiles->getNoeud2(3)->listeMagies->inserer(0, listeMagies[hachage("Flammes", nbrMagies)]);
    joueur->profiles->getNoeud2(3)->listeMagies->inserer(0, listeMagies[hachage("Soin",nbrMagies)]);
    joueur->profiles->getNoeud2(3)->listeMagies->inserer(0, listeMagies[hachage("Barriere", nbrMagies)]);
    //Donnees de combat
    initDC(&dc, joueur->profiles->taille(), ennemi->profiles->taille());
    dc.decallageDegats = 100;

    Profile* currentProfile = NULL;
    Liste<Profile*>* listeAllies[3];
    Liste<Profile*>* listeEnnemis2[3];

    for(int i=0; i < 3; i++){
        listeAllies[i] = new Liste<Profile*>();
        listeEnnemis2[i] = new Liste<Profile*>();
    }

    Profile* j = NULL;
    int pos = 0;
    for(int i=0; i < joueur->profiles->taille(); i++){
        j = joueur->profiles->getNoeud2(i);
        pos = listeAllies[j->colonne]->taille();
        listeAllies[j->colonne]->inserer(pos, j);
    }
    for(int i=0; i < ennemi->profiles->taille(); i++){
        j = ennemi->profiles->getNoeud2(i);
        printf("%d\n", j->colonne);
        pos = listeEnnemis2[j->colonne]->taille();
        listeEnnemis2[j->colonne]->inserer(pos, j);
    }
    SDL_Rect rectCadre = {0,0,91,91};
    Texture* cadrePortrait = new Texture("images/personnages/portraits/cadre.png", renderer, rectCadre);

    //main loop
    bool quit = false;
    SDL_Event e;
    fpsTimer.start();
    while(!quit){
        capTimer.start();
        //Boucle d'evenement SDL
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
            else if(e.type==SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a){
                jeu = COMBAT;
                if(Mix_PlayingMusic()){
                     Mix_HaltMusic();
                }
                Mix_PlayMusic( niveaux[0]->getMusics()[0], -1 );
            }
            else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e){
                jeu = MAP;
                if(Mix_PlayingMusic()){
                     Mix_HaltMusic();
                }
                Mix_PlayMusic( niveaux[0]->getMusics()[1], -1 );
            }
            else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r && !e.key.repeat){
                printf("On lance un de 100.\n");
                printf("%d\n", randomNumber100());
            }
            //Gestion des evenements SDL
            switch(jeu){
            case MAP:
                joueur->handleEvent(&e);
                break;
            case COMBAT:
                if(currentProfile != NULL && (dc.currentEntite < listeProfiles->taille() ) ){
                    if(currentProfile->getAnimType() == IDLE && currentProfile->getIsTurn() && currentProfile->getIsPlayer()){
                        menuCombat->handleEvent(&e, listeProfiles->getNoeud2(dc.currentEntite), listeAllies, listeEnnemis2, &dc);
                    }
                }
                break;
            }
            window->handleEvent(e, renderer);
        }
        if(!window->isMinimized()){
                switch(jeu){
                case MAP:
                    if(!Mix_PlayingMusic()){
                         Mix_PlayMusic( niveaux[0]->getMusics()[1], -1 );
                    }
                    //Clear screen
                    niveaux[0]->renderNiveau(&jeu, camera, renderer, joueur);
                    break;
                case COMBAT:
                    if(!Mix_PlayingMusic()){
                         Mix_PlayMusic( niveaux[0]->getMusics()[0], -1 );
                    }
                    if(!dc.victoire && !dc.defaite && !dc.fuite){
                        //Clear screen
                        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( renderer );

                        gestionCombat(&dc, listeProfiles, joueur->profiles, listeEnnemis2, listeAllies);
                        if(dc.currentEntite < listeProfiles->taille()){
                            currentProfile = listeProfiles->getNoeud2(dc.currentEntite);
                        }

                        //Gestion du debut du tour de l'entite en cours
                        if(currentProfile->debutTour){
                            //regen PM, degats periodiques, etc
                            if(gestionDebutTour(currentProfile, &dc) ){
                                if(dc.degats < 0){
                                    dc.degats = -dc.degats;
                                    dc.degatsText->loadNewTexture(to_string(dc.degats), renderer, font, &couleurs.vert);
                                }
                                else{
                                    dc.degatsText->loadNewTexture(to_string(dc.degats), renderer, font, &couleurs.grisPale);
                                }

                                dc.degatsRect.w = (30*to_string(dc.degats).size());
                            }
                        }
                        //Affichage des elements
                        //Arriere plan
                        niveaux[0]->getFond()->render(renderer);

                        //Personnages
                        if( afficherProfiles(renderer, listeAllies, listeEnnemis2, listeProfileToRender, listeIcones, &dc) ){
                            if(dc.degats < 0){
                                dc.degats = -dc.degats;
                                dc.degatsText->loadNewTexture(to_string(dc.degats), renderer, font, &couleurs.vert);
                            }
                            else{
                                dc.degatsText->loadNewTexture(to_string(dc.degats), renderer, font, &couleurs.grisPale);
                            }
                            dc.degatsRect.w = (30*to_string(dc.degats).size());
                        }

                        //HUD
                        joueur->afficherHUD( renderer, &couleurs.grisPale, font ); //HP MP
                        menuCombat->renderTextures(currentProfile, renderer);

                        //gestion de la magie
                        if(dc.currentMagie != NULL){
                            if(afficherMagie(renderer, currentProfile, (currentProfile->tTarget==ENNEMI) ? listeEnnemis2 : listeAllies, &dc)){
                                if(dc.degats < 0){
                                    dc.degats = -dc.degats;
                                    dc.degatsText->loadNewTexture(to_string(dc.degats), renderer, font, &couleurs.vert);
                                }
                                else{
                                    dc.degatsText->loadNewTexture(to_string(dc.degats), renderer, font, &couleurs.grisPale);
                                }
                                dc.degatsRect.w = (30*to_string(dc.degats).size());
                            }
                        }

                        afficherPortraits(cadrePortrait, renderer, &dc , listeProfiles);
                        //Affichage des degats
                        afficherDegats(renderer, &dc);

                    }
                    else if(dc.victoire){
                        jeu = MAP;
                        if(Mix_PlayingMusic()){
                            Mix_HaltMusic();
                        }
                        Mix_PlayMusic( niveaux[0]->getMusics()[1], -1 );
                        niveaux[0]->freeEnnemi();
                        dc.victoire = false;
                    }
                    else if(dc.defaite){
                        if(Mix_PlayingMusic()){
                            Mix_HaltMusic();
                        }
                        gameOver->renderText( renderer );
                    }
                    break;
                }//switch(jeu)

            //Calculate and correct fps
            avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
            if( avgFPS > 2000000 )
            {
                avgFPS = 0;
            }
            if(fpsText != NULL && avgFPS > 0){
                if(frameText == framesText){ //pour limiter la frequence d'affichage
                    fpsText->loadNewTexture(to_string(avgFPS).c_str(), renderer, font, &couleurs.vert);
                    frameText = 0;
                }
                else{
                    frameText++;
                }
                fpsText->renderText(renderer, &fpsTextRect);

            }
            //Update screen
            SDL_RenderPresent( renderer );
            ++countedFrames;

            //If frame finished early
            frameTicks = capTimer.getTicks();
            if(frameTicks < screen_ticks_per_frame){
                //wait remaining time
               SDL_Delay(screen_ticks_per_frame - frameTicks);
            }
        } //if(!window->isMinimized())
    } //while

    //Liberation de la memoire
    if(camera != NULL){
        delete(camera);
        camera = NULL;
    }

    if(joueur != NULL){
        delete(joueur);
        joueur = NULL;
    }

    if(menuCombat != NULL){
        delete(menuCombat);
        menuCombat = NULL;
    }

    //Stop the music
    Mix_HaltMusic();
    if(niveaux != NULL){
        for(int i=0;i<nbrNiveaux;i++){
            free(niveaux[i]);
        }
        free(niveaux);
    }

    if(controller!=NULL){
        SDL_GameControllerClose(controller);
    }
    close(window, NULL, renderer);
    controller = NULL;
    joueur = NULL;
    renderer = NULL;
    window = NULL;

    return 0;
}
