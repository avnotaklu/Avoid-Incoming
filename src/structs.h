#ifndef STRUCTS_H
#define STRUCTS_H
#include "common.h"
typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int left;
    int right;
    int enter;
} App;
#endif
