#pragma once
#include "common.h"
#include "entity.hpp"
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_metal.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include "SDL2/SDL_image.h"
void draw(Entity &player, Entity &background);
bool media(Entity &player,Entity &background);
bool init();
SDL_Surface *loadSurface(std::string path);
void close(Entity &player,Entity &background);
extern SDL_Window *window;
extern SDL_Renderer *renderer;
//The surface contained by the window
extern SDL_Surface *gScreenSurface;
//The image we will load and show on the screen
extern SDL_Surface *gCar;
extern SDL_Texture *gRestartTexture ;
extern SDL_Rect playerStartingRect;
extern SDL_Rect backgroundStartingRect;
extern SDL_Rect RoadPosRect;
extern bool initialized;// is init initialized
