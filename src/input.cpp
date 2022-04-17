#include "input.h"
#include <iostream>
App app;
void doKeyDown(SDL_KeyboardEvent *event){
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
                app.up = 1;
        }
        
        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
                app.down = 1;
        }
        
        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
                app.left = 1;
        }
        
        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
                app.right = 1;
        }
        if (event->keysym.scancode == SDL_SCANCODE_RETURN)
        {
                app.enter = 1;
        }
    }
}
void doKeyUp(SDL_KeyboardEvent *event){
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
                app.up = 0;
        }
        
        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
                app.down = 0;
        }
        
        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
                app.left = 0;
        }
        
        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
                app.right = 0;
        }
        if (event->keysym.scancode == SDL_SCANCODE_RETURN)
        {
                app.enter = 0;
        }
    }
}
void doInput(void){
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                exit(0);
                game_running = false;
                break;
            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
            case SDL_KEYUP:
                doKeyUp(&event.key);
                break;
            default:
                break;
        }
    }
}
