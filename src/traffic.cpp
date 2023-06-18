#include "common.h"
#include <random>
#include "draw_window.hpp"
#include "entity.hpp"
#include <vector>
#include <algorithm>
#include <array>
#include <cstdlib>
#include "util.hpp"
#include "traffic.hpp"
int vehicleSpawnTimer;
void destroyCars();
std::vector<Entity> vehicles;
std::vector<Entity>::iterator vehiclePointer;
bool new_spawn_traffic_collision(SDL_Rect new_vehicle_rect);
Entity carTemplates[2];
SDL_Rect rect_new_car(){
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,4);
    SDL_Rect Rect;
    int start = -15;
    int gap = 100;
    std::array<int, 4> hMargin;

    // TODO: this generates weird values for index 0 which cause first lane cars to spawn near edge of lane
    std::generate(hMargin.begin(), hMargin.end(), [n=0, start, gap]() mutable {
            return start + ((n++) * gap);
            });
    srand(time(0));
    Rect.x = hMargin[dist(rng)];
    Rect.y = -256;
    Rect.w = 128;
    Rect.h  = 128;
    return Rect;
}

void spawn_traffic(){
    if(--vehicleSpawnTimer<=0){
        SDL_Rect randomizedRect = rect_new_car();
        if(!new_spawn_traffic_collision(randomizedRect)){
            Entity *newVehicle = new Entity;
            srand(time(0));
            int vehiclesRandomizer = rand()%2;
            //*newVehicle = carTemplates[vehiclesRandomizer];
            SDL_Rect rect = {80,20,90,220};
            //newVehicle->mCollisionBox = {80,20,170,220};
            //newVehicle->mTexture = carTemplates[vehiclesRandomizer].mTexture;
            *newVehicle = carTemplates[vehiclesRandomizer];
            //std::cout<<newVehicle->mCollisionBox.x<<newVehicle->mCollisionBox.y<<std::endl;
            newVehicle->mRect = randomizedRect;
            if(newVehicle->mTexture == NULL)
                std::cout<<"null texture"<<std::endl;
            vehicles.push_back(*newVehicle);
            vehicleSpawnTimer = 10 +(rand()%20);
        }
    }
}
void draw_all_cars(){
    for (vehiclePointer = vehicles.begin();vehiclePointer<vehicles.end();vehiclePointer++){
        vehiclePointer->blit();
    }
}
void load_all_traffic(){
    /* SDL_Rect rect = {80,20,110,220}; */
    SDL_Rect rect = {40,10,48,110};
    SDL_Rect generatedRect = rect_new_car();
    carTemplates[0].load("../../graphics/Mini_truck128x128.png",generatedRect,rect);
    carTemplates[1].load("../../graphics/taxi128x128.png",generatedRect,rect);
} 
void npc_movement(){
    for (vehiclePointer = vehicles.begin();vehiclePointer<vehicles.end();vehiclePointer++){
        vehiclePointer->mRect.y += (4 - cameraMovementSpeed);
    }
}
void traffic_manager(){
    spawn_traffic();
    npc_movement();
    destroyCars();//May cause problems such as vehicles getting deleted before they leave the scene
} 
bool new_spawn_traffic_collision(SDL_Rect new_vehicle_rect){
    for (vehiclePointer = vehicles.begin();vehiclePointer<vehicles.end();vehiclePointer++){
        int x1 = new_vehicle_rect.x;
        int y1 = new_vehicle_rect.y - 128;
        int w1 = new_vehicle_rect.w;
        int h1 = new_vehicle_rect.h + 256;
        int x2 = vehiclePointer->mCollisionBox.x;
        int y2 = vehiclePointer->mCollisionBox.y;
        int w2 = vehiclePointer->mCollisionBox.w;
        int h2 = vehiclePointer->mCollisionBox.h;
        if (collosion(x1,y1,w1,h1,x2,y2,w2,h2)){
            return true;
        }
    }
    return false;
}
void destroyCars(){
    for (vehiclePointer = vehicles.begin();vehiclePointer<vehicles.end();vehiclePointer++){
        if(vehiclePointer->mRect.y > (SCREEN_HEIGHT)){
             vehicles.erase(vehiclePointer);
        }
    }
}

