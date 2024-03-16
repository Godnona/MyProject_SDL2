#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Def.h"
#include "BaseObject.h"
#include "Map.h"
#include "Animation.h"

int Init();

int main(int argc, char* argv[])
{
    if(Init() == 0) return -1;
    
    // Background
    BaseObject *bg = new BaseObject;
    bg->LoadImage(g_renderer, PATH_BACKGROUND);
    
    // Map
    Map *map = new Map;
    map->MapLoadFormat(PATH_MAP_FORMAT);
    map->MapLoadImage(g_renderer);

    // Player
    Animation *player = new Animation;
    player->LoadImage(g_renderer, PATH_PLAYER_IDLE);
    player->SetFrame(FRAME_RUN);

    bool isRunning = true;
    while(isRunning)
    {
        while(SDL_PollEvent(&g_event))
        {
            if(g_event.type == SDL_QUIT)
                isRunning = false;
            player->HandleInput(g_renderer, g_event);

        }

        SDL_RenderClear(g_renderer);

        bg->Render(g_renderer, NULL);
        map->MapRender(g_renderer);

        MapStruct map_data = map->GetMap();
        player->Move(map_data);
        player->Draw(g_renderer);

        SDL_RenderPresent(g_renderer);

    }

    delete bg;bg = NULL;
    delete map; map = NULL;
    delete player; player = NULL;

    IMG_Quit();
    SDL_Quit();

    return 0;
}

int Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return 0;
    if(!(IMG_Init(IMG_INIT_PNG))) return 0;
    if(!(IMG_Init(IMG_INIT_JPG))) return 0;

    g_window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if(g_window == NULL) return 0;

    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if(g_renderer == NULL) return 0;

    return 1;
}

