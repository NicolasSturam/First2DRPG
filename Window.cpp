#include "Window.h"

Window::Window(){
    this->window = NULL;
    this->mouseFocus = false;
    this->keyboardFocus = false;
    this->fullScreen = false;
    this->minimized = false;
    this->width = 0;
    this->height = 0;
}

Window::Window(int window_width, int window_height){
    this->window = SDL_CreateWindow("MyFirst2DRPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);
    if(this->window == NULL){
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        this->mouseFocus = false;
        this->keyboardFocus = false;
        this->fullScreen = false;
        this->minimized = false;
        this->width = 0;
        this->height = 0;
    }
    else{
        this->mouseFocus = true;
        this->keyboardFocus = true;
        this->fullScreen = false;
        this->minimized = false;
        this->width = window_width;
        this->height = window_height;
    }
}

Window::~Window(){
    SDL_DestroyWindow(this->window);
}

void Window::free(){
    SDL_DestroyWindow(this->window);
}

SDL_Renderer* Window::createRenderer(){
    return SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
}

void Window::handleEvent(SDL_Event& e, SDL_Renderer* renderer){
    if(e.type == SDL_WINDOWEVENT){
        bool updateCaption = false;

        switch(e.window.event){
        //Get new dimensions and repaint on window size change
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            this->width = e.window.data1;
            this->height = e.window.data2;
            SDL_RenderPresent(renderer);
            break;

        //Repaint on exposure
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent( renderer );
            break;

        //Mouse entered window
        case SDL_WINDOWEVENT_ENTER:
            this->mouseFocus = true;
            updateCaption = true;
            break;

        //Mouse left window
        case SDL_WINDOWEVENT_LEAVE:
            this->mouseFocus = false;
            updateCaption = true;
            break;

        //Window has keyboard focus
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            this->keyboardFocus = true;
            updateCaption = true;
            break;

        //Window lost keyboard focus
        case SDL_WINDOWEVENT_FOCUS_LOST:
            this->keyboardFocus = false;
            updateCaption = true;
            break;

        //Window minimized
        case SDL_WINDOWEVENT_MINIMIZED:
            this->minimized = true;
            break;

        //Window maximized
        case SDL_WINDOWEVENT_MAXIMIZED:
            this->minimized = false;
            break;

        //Window restored
        case SDL_WINDOWEVENT_RESTORED:
            this->minimized = false;
            break;

        }

        //Update window caption with new data
        if( updateCaption )
        {
            stringstream caption;
            caption << "SDL Tutorial - MouseFocus:" << ( ( this->mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( this->keyboardFocus ) ? "On" : "Off" );
            SDL_SetWindowTitle( this->window, caption.str().c_str() );
        }
    }

    //Enter exit full screen on return key
    else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
    {
        if( this->fullScreen )
        {
            SDL_SetWindowFullscreen( this->window, 0 );
            this->fullScreen = false;
        }
        else
        {
            SDL_SetWindowFullscreen( this->window, SDL_WINDOW_FULLSCREEN );
            this->fullScreen = true;
            this->minimized = false;
        }
    }
}

int Window::getWidth() const
{
    return this->width;
}

int Window::getHeight() const
{
    return this->height;
}

bool Window::hasMouseFocus() const
{
    return this->mouseFocus;
}

bool Window::hasKeyboardFocus() const
{
    return this->keyboardFocus;
}

bool Window::isMinimized() const
{
    return this->minimized;
}
