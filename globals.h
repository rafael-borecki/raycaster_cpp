#pragma once
#include <math.h>

#define PI 3.14159265358
#define RADIAN 57.2958
#define ONE_RAD 0.01745

int SCREEN_HEIGHT = 850;
int SCREEN_WIDTH  = 1280;
int FRAME_RATE	  = 60;

#define MAP_SCALE     24
#define MAP_X         24
#define MAP_Y         24

float dist(float px, float py, float rx, float ry){
    return (sqrt((px-rx) * (px -rx) + (py-ry) * (py - ry)));
}
