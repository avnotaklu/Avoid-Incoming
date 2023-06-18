#include"player.hpp"
#include"util.hpp"
void restart_game_on_collision(Player &player);


SDL_Rect playerStartingRect = {100,600,128, 128};
std::string playerSprite = "../../graphics/Car128x128.png";


void Player::movement(){

    if((this->mRect.y+this->mRect.h + 10) < SCREEN_HEIGHT){
        if(app.down){
            this->mRect.y += speed;
        }
    }
    if((this->mRect.y + 100) > (SCREEN_HEIGHT / 2)){
        if(app.up){

            this->mRect.y -= speed;
        }
    }
    //std::cout<<this->mRect.x<<std::endl;
    if(app.right){
        if((this->mRect.x+100>SCREEN_WIDTH)){
            this->mRect.x = SCREEN_WIDTH-100;

        }
        this->mRect.x +=steerStrength;
    }                               
    if(app.left){
        auto emptySpacePaddingInSprite = (playerStartingRect.w / 5);
        if((this->mRect.x < -emptySpacePaddingInSprite)){
            this->mRect.x = -emptySpacePaddingInSprite;
        }
        this->mRect.x -=steerStrength;
    }
}
void Player::collision(const std::vector<Entity> &vehicles){
    for (const auto& vehiclePointer : vehicles){
        int x1 = this->mCollisionBox.x;
        int y1 = this->mCollisionBox.y;
        int w1 = this->mCollisionBox.w;
        int h1 = this->mCollisionBox.h;
        int x2 = vehiclePointer.mCollisionBox.x;
        int y2 = vehiclePointer.mCollisionBox.y;
        int w2 = vehiclePointer.mCollisionBox.w;
        int h2 = vehiclePointer.mCollisionBox.h;
        if (collosion(x1,y1,w1,h1,x2,y2,w2,h2)){
            restart_game_on_collision(*this);
        }
    }
}
void Player::handle(const std::vector<Entity> &vehicles){
    Player::movement();
    Player::collision(vehicles);
}
