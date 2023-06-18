#ifndef PLAYER_H
#define PLAYER_H
#include "common.h"
#include "entity.hpp"
#include "input.h"
#include "vector"

extern SDL_Rect playerStartingRect;
extern std::string playerSprite;

class Player : public Entity {
public:
  void handle(const std::vector<Entity> &vehicles);
  Player() {
    mRect = playerStartingRect;
    this->mCollisionBox = {40, 10, 48, 110};
  }

  Player &operator=(Player &&other) noexcept {
    speed = other.speed;
    mRect = other.mRect;
    return *this;
  }

  Player(Player &&other) noexcept {
    speed = other.speed;
    mRect = other.mRect;
  }

  virtual ~Player() override{};
  float speed = 10;

private:
  const float steerStrength = 11;
  void movement();
  void collision(const std::vector<Entity> &vehicles);
};
#endif // PLAYER_H
