#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include"HUD.hpp"
#include"common.h"
#include<sstream>
TTF_Font *HUDfont = NULL;
SDL_Color color = {255,0,0};
void loadFont(){
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    else
        printf("passed");
     HUDfont = TTF_OpenFont("../../graphics/fonts/VCR_OSD_MONO_1.001.ttf",20);
}
void renderText(SDL_Renderer *renderer){
    if(HUDfont == NULL){
        printf("\nfailed to load font");
         printf("TTF_Init: %s\n", TTF_GetError());
    }
    std::string scoreText;
    std::stringstream ss;
    ss<<SCORE;
    ss>>scoreText;
    SDL_Surface *HUDTextSurface = TTF_RenderText_Solid(HUDfont,scoreText.c_str(),color);
    SDL_Texture *HUDTextTexture = SDL_CreateTextureFromSurface(renderer,HUDTextSurface);
    SDL_Rect dstRect = { 20,20,100,100};
    SDL_RenderCopy(renderer,HUDTextTexture,NULL,&dstRect);
    SDL_DestroyTexture(HUDTextTexture);
    SDL_FreeSurface(HUDTextSurface);
}
