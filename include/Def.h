#pragma once
#ifndef DEF_H
#define DEF_H

#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

// Variable
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

#define PATH_PLAYER "../assets/images/player/character0.png"

#endif // DEF_H
