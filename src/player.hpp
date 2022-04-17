#ifndef PLAYER_H
#define PLAYER_H
#include "common.h"
#include "entity.hpp"
#include "input.h"
#include "vector"
class player : public Entity
{
public:
    void handle(const std::vector<Entity> &vehicles);
    player()
    {
        speed = 15;
        mRect = {450,450,256,256};
    }
    virtual ~player() override{ };
    float speed;
private:
    const float steerStrength =  16;
    void movement();
    void collision(const std::vector<Entity> &vehicles);
};
void restart_game_on_collision(player *player);
#endif //PLAYER_H
