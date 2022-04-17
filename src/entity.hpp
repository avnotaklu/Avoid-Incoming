#pragma once
#include "common.h"
class Entity {
public:
    SDL_Surface *mSurface;
    SDL_Rect mRect;
    SDL_Rect mCollisionBox;
    SDL_Rect mCollisionBoxLayout;
    SDL_Texture *mTexture;
    void blit();
    void load(std::string path, SDL_Rect Rect,SDL_Rect mCollisionBoxLayout);
    virtual ~Entity(){};
};
