#include "common.h"
#include "input.h"
#include "structs.h"
#include "draw_window.hpp"
#include <SDL2/SDL_events.h>
#include "entity.hpp"
#include "player.hpp"
#include "traffic.hpp"
#include "util.hpp"
#include <vector>

Entity background;
bool game_running = true;
SDL_Event event;
void handle_inputs();
bool player_traffic_collosion();
int cameraMovementSpeed = 0;
int cameraInitialPos;
int cameraFinalPos;
int SCORE = 0.0f;
int lastScore;
float secs = 0.0f;
float elapsedMS = 0;
SDL_Rect camera = {0,0,1000,600};
void setScore();
Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;
double deltaTime = 0;

int main(){
    player *Player = new player();
    init();
    media(*Player,background);
    //draw_all_cars();
    while(game_running){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = ((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
	Uint32 start = SDL_GetTicks();
        // Get the next event
        handle_inputs();
        Player->handle(vehicles);
        setScore();
        traffic_manager();
        //std::cout<<player.mRect.x<<" "<<player.mRect.y<<std::endl;
        draw(*Player,background);
        background.mRect.y -= cameraMovementSpeed;
        if ((background.mRect.y) > 900)
            background.mRect = backgroundStartingRect;
        //SDL_UpdateWindowSurface(window);
        Uint32 end = SDL_GetTicks();
	elapsedMS = (end - start) /1000.0f;
        if(elapsedMS < GAME_SPEED)
            SDL_Delay(floor((GAME_SPEED) - elapsedMS));
    }
    close(*Player,background);
    return 0;
}
void setScore(){
    secs += 0.05 * (-cameraMovementSpeed)/16;
    SCORE += secs;
    if(lastScore != SCORE)
        secs = 0.0f;
    lastScore = SCORE;
}
void handle_inputs(){
    cameraInitialPos = camera.y;
    doInput();
    if(app.up){
        camera.y -=24;
    }
    else if(!(app.down)){
        camera.y -=16;
    }
    cameraFinalPos = camera.y;
    cameraMovementSpeed  = cameraFinalPos - cameraInitialPos;
}
void restart_game_on_collision(player *Player){
    vehicles.clear();
    SCORE = 0;
    background.mRect = backgroundStartingRect;
    camera.y = 0;

    Entity tmp = *Player;

    SDL_RenderCopy(renderer,gRestartTexture,NULL,NULL);
    SDL_RenderPresent(renderer);
    while(app.enter == 0){
        doInput();
    } 
}
