#pragma once
#ifndef DEF_H
#define DEF_H

#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>

// Global
static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;
static SDL_Event g_event;

// Screen
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define SCREEN_TITLE "10 point."

// Path
#define PATH_BACKGROUND "../assets/images/map/bg2.png"
#define PATH_MAP_FORMAT "../assets/images/map/mapFormat.txt"
#define PATH_MAP_IMG "../assets/images/map/Tileset%d.png"
#define PATH_PLAYER_IDLE "../assets/images/player/DarkSamurai_Idle_R.png"
#define PATH_PLAYER_RUN_LEFT "../assets/images/player/DarkSamurai_L.png"
#define PATH_PLAYER_RUN_RIGHT "../assets/images/player/DarkSamurai_R.png"
#define PATH_PLAYER_IDLE_LEFT "../assets/images/player/DarkSamurai_Idle_L.png"
#define PATH_PLAYER_IDLE_RIGHT "../assets/images/player/DarkSamurai_Idle_R.png"

// Input
typedef struct
{
    int idle;
    int left;
    int right;
    int up;
    int down;
    int jump;
} Input;

// Animation class
#define FRAME_PLAYER 8
#define SPEED_PLAYER 6
#define SPEED_GRAVITY 0.8
#define MAX_GRAVITY 9.8
#define FPS 30

#endif // DEF_H
