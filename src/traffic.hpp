#pragma once
#include "entity.hpp"
#include "common.h"
#include "vector"
void draw_all_cars();
void load_all_traffic();
void traffic_manager();
void spawn_traffic();
SDL_Rect rect_new_car();
extern std::vector<Entity> vehicles;
extern std::vector<Entity>::iterator vehiclePointer;
