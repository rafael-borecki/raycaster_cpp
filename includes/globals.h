#pragma once


#ifndef GLOBALS_H
#define GLOBALS_H

#include <math.h>

#define PI 3.14159265358
#define RADIAN 57.2957795131
#define ONE_RAD 0.01745329251

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
extern const int FRAME_RATE;

#define MAP_SCALE     24
#define MAP_X         24
#define MAP_Y         24
#define FOV 	      60

// Defines main
#define MAXTIMEOUT    120.f
#define MINTIMEOUT    30.f
#define MAPID         3

// Defines HUD
#define FPS_HUDPOSITION     350,50
#define TIMER_HUDPOSITION   750,50
#define LEVEL_HUDPOSITION   1150,50

// Defines IL
#define OPT1_TEXT_POSITION   500,300
#define OPT2_TEXT_POSITION   500,400
#define OPT1_RECT_POSITION   480,300
#define OPT2_RECT_POSITION   480,400
#define OPT1_RECT_SIZE       20,50
#define OPT2_RECT_SIZE       20,50
#define TIMER_ILPOSITION   350,50
#define LEVEL_ILPOSITION   950,50


inline float dist(float px, float py, float rx, float ry){
    return (sqrt((px-rx) * (px -rx) + (py-ry) * (py - ry)));
}


#endif // GLOBALS_H
