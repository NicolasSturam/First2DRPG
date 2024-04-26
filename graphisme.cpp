#include "graphisme.h"

Window* init_video(){
    Window* window = NULL;

    //SDL initialization
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER|SDL_INIT_AUDIO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else{
        //Window creation
        //window = SDL_CreateWindow("MyFirst2DRPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, 0);
        window = new Window(window_width, window_height);
        if(window == NULL){
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else{
            if(IMG_Init(IMG_INIT_PNG) < 0){
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            }

            if(TTF_Init() == -1){
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            }
            else{
                printf("SDL_ttf initialise.\n");
            }
        }

         //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
    }

    return window ;
}

SDL_Renderer* createRenderer(SDL_Window* window){
    SDL_Renderer* renderer = NULL;
    if(window == NULL){
        printf("Erreur window n'existe pas !\n");
    }
    else{
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL){
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else{
            //Initialize renderer color
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }

    return renderer;
}

SDL_Surface* loadSurface(string path, SDL_Surface* screenSurface){
    SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else{
        optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
        if(optimizedSurface==NULL){
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer){
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else{
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFE, 0xFE, 0xFE ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL){
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

SDL_Texture* loadRenderText(string textureText, SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor){
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
    SDL_Texture* texture = NULL;
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return texture;

}


void close(Window* window, SDL_Surface* surface, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);

    SDL_FreeSurface(surface);
    //SDL_DestroyWindow(window);
    window->free();

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool checkCollision(SDL_Rect* a, SDL_Rect* b, int sizeB){
    bool collision = false; //on considere par defaut qu'il n'y a pas de collision
    if(a == NULL || b == NULL){
        collision = false;
    }
    else{
        //The sides of the rectangles
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;

        for(int i = 0; (i < sizeB) && !collision; i++){
            //Calculate the sides of rect A
            leftA = a->x;
            rightA = a->x + a->w;
            topA = a->y;
            bottomA = a->y + a->h;

            //Calculate the sides of rect B
            leftB = b[i].x;
            rightB = b[i].x + b[i].w;
            topB = b[i].y;
            bottomB = b[i].y + b[i].h;

            //Si aucun cote de A n'est en dehors de B, il y a collision
            if( bottomA >= topB && topA <= bottomB && rightA >= leftB && leftA <= rightB)
            {
                collision = true;
            }
        } // for
    } // else
    //printf("collision : %d\n", collision);
    return collision;
}
