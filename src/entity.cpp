#include "common.h"
#include "entity.hpp"
#include "draw_window.hpp"
void Entity::blit(){
    //SDL_BlitSurface(mSurface,NULL,surface,&mRect);
    SDL_Rect srcRect = {0,0,mRect.w,mRect.h};
    SDL_Rect dstRect = mRect;
    this->mCollisionBox = {mRect.x + mCollisionBoxLayout.x,mRect.y + mCollisionBoxLayout.y,mCollisionBoxLayout.w,mCollisionBoxLayout.h};
    SDL_RenderCopy(renderer,mTexture,&srcRect,&dstRect);
}
void Entity::load(std::string path, SDL_Rect Rect,SDL_Rect CollisionBox){
    this->mSurface = loadSurface(path);
    this->mTexture = SDL_CreateTextureFromSurface(renderer,mSurface);
    this->mRect = Rect;
    this->mCollisionBoxLayout = CollisionBox;
}
