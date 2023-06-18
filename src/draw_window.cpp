#include "draw_window.hpp"
#include "HUD.hpp"
#include "TextureManager.h"
#include "common.h"
#include "entity.hpp"
#include "player.hpp"
#include "traffic.hpp"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;
// The image we will load and show on the screen
SDL_Texture *gRestartTexture = NULL;

SDL_Rect backgroundStartingRect = {0, 0, 400, 720};
Entity desertbackground;
const int SCREEN_HEIGHT = 720;
const int SCREEN_WIDTH = 400;
bool initialized = false;
bool init();
bool init() {
  bool success = true;
  // Initialize all the systems of SDL
  if (!initialized) {
    if (SDL_Init(SDL_INIT_EVERYTHING < 0)) {
      printf("sdl could not be initialized");
      success = false;
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      printf("could not load SDL_INIT_VIDEO");
      success = false;
    } else {
      // Create a window with a title, "Getting Started", in the centre
      //(or undefined x and y positions), with dimensions of 800 px width
      // and 600 px height and force it to be shown on screen
      window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if (window == NULL) {
        std::cout << "window could not be created" << std::endl;
        success = false;
      } else {
        // Create a renderer for the window created above, with the first
        // display driver present and with no additional settings
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      }
      if (renderer != NULL) {
        std::cout << "renderer created";
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = false;
        }
        // else
        //{
        //     gScreenSurface = SDL_GetWindowSurface(window);
        // }
      }
      initialized = true;
    }
  }
  return success;
}
SDL_Surface *loadSurface(std::string path) {
  // The final optimized image

  SDL_Surface *optimizedSurface = NULL;
  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    // Convert surface to screen format
    optimizedSurface =
        SDL_ConvertSurface(loadedSurface, loadedSurface->format, 0);
    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }
    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
  // return loadedSurface;
}
// media is loaded here
bool media(Entity &player, Entity &background) {
  std::cout << "loading" << std::endl;
  bool success = true;
  background.load("../../graphics/TwoLaneRoad400x720.png",
                  backgroundStartingRect, SDL_Rect{0, 0, 0, 0});
  SDL_Surface *gRestartScreenSurface =
      loadSurface("../../graphics/restart_screen.png");
  gRestartTexture =
      SDL_CreateTextureFromSurface(renderer, gRestartScreenSurface);

  if (background.mSurface == NULL) {
    std::cout << "loading of image failed" << std::endl;
    success = false;
  }
  player.load(playerSprite, playerStartingRect, player.mCollisionBox);
  if (player.mSurface == NULL) {
    std::cout << "loading of image failed" << std::endl;
    success = false;
  }
  loadFont();
  load_all_traffic();
  return success;
}
void close(Entity &player, Entity &background) {
  SDL_FreeSurface(background.mSurface);
  background.mSurface = NULL;
  SDL_FreeSurface(player.mSurface);
  player.mSurface = NULL;
  for (vehiclePointer = vehicles.begin(); vehiclePointer < vehicles.end();
       vehiclePointer++) {
    SDL_FreeSurface(vehiclePointer->mSurface);
  }
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  TTF_Quit();
}
void draw(Entity &player, Entity &background) {
  // draw road at initial position
  background.blit();
  // draw another road above the initial one
  background.mRect.y -= backgroundStartingRect.h;
  background.blit();
  background.mRect.y += backgroundStartingRect.h;
  player.blit();
  draw_all_cars();
  renderText(renderer);
  SDL_RenderPresent(renderer);
}
