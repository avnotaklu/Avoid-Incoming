#ifndef PLAYER_H
#define PLAYER_H
#include "common.h"
#include "entity.hpp"
#include "input.h"
#include "vector"
class Player : public Entity
{
public:
    void handle(const std::vector<Entity> &vehicles);
    Player()
    {
        speed = 15;
        mRect = {450,450,256,256};
    }

    Player& operator=(Player && other) noexcept
    {
        speed = other.speed;
        mRect = other.mRect;
        return *this;
    }


    Player(Player && other) noexcept
    {
        speed = other.speed;
        mRect = other.mRect;
    }

    virtual ~Player() override{ };
    float speed;
private:
    const float steerStrength =  16;
    void movement();
    void collision(const std::vector<Entity> &vehicles);
};
#endif //PLAYER_H
