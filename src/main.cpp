#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Def.h"
#include "BaseObject.h"
#include "Map.h"

int Init();

int main(int argc, char* argv[])
{
    if(Init() == 0) return -1;
    
    BaseObject *bg = new BaseObject;
    bg->LoadImage(g_renderer, PATH_BACKGROUND);

    BaseObject *player = new BaseObject;
    player->LoadImage(g_renderer, PATH_PLAYER);
    player->SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 32 * 6);
    player->SetSize(32, 32);
    SDL_Rect *srcRect = new SDL_Rect{32,0,32 ,32 - 3};

    Map *map = new Map;
    map->MapLoadFormat(PATH_MAP_FORMAT);
    map->MapLoadImage(g_renderer);


    bool isRunning = true;
    while(isRunning)
    {
        while(SDL_PollEvent(&g_event))
        {
            switch (g_event.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                
                default:
                    break;
            }

        }
        SDL_RenderClear(g_renderer);

        bg->Render(g_renderer, NULL);
        map->MapRender(g_renderer);
        
        player->Render(g_renderer, srcRect);
        
        SDL_RenderPresent(g_renderer);

    }

    delete bg;bg = NULL;
    delete map; map = NULL;

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

