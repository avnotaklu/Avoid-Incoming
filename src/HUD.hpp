#ifndef HUD_H
#define HUD_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
extern TTF_Font *HUDfont;
void renderText(SDL_Renderer *renderer);
void loadFont();
#endif //HUD_H
