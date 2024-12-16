#pragma once
#include <math.h>

#define PI 3.14159265358
#define RADIAN 57.2957795131
#define ONE_RAD 0.01745329251

int SCREEN_HEIGHT = 850;
int SCREEN_WIDTH  = 1280;
int FRAME_RATE	  = 60;

#define MAP_SCALE     24
#define MAP_X         24
#define MAP_Y         24
#define FOV 	      60

#define MAXTIMEOUT    300.f
#define MINTIMEOUT    60.f

#define FPS_HUDPOSITION     350,50
#define TIMER_HUDPOSITION   750,50
#define LEVEL_HUDPOSITION   1150,50


#define FPS_ILPOSITION     350,50
#define TIMER_ILPOSITION   750,50
#define LEVEL_ILPOSITION   1150,50


float dist(float px, float py, float rx, float ry){
    return (sqrt((px-rx) * (px -rx) + (py-ry) * (py - ry)));
}
