#ifndef COMMON_H
#define COMMON_H
#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL_surface.h>
#define GAME_SPEED 16.666f
bool extern game_running;
extern int cameraMovementSpeed;
extern SDL_Rect camera;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int SCORE;
extern float elapsedMS;
extern double deltaTime;
#endif
