#include "Map.h"

void Map::MapLoadFormat(const char *filePath)
{
    FILE *file = NULL;
    fopen_s(&file, filePath, "rb");
    if(file == NULL) return;

    mapStruct.end_X = 0;
    mapStruct.end_Y = 0;

    for(int i = 0; i < MAX_MAP_Y; i++)
    {
        for(int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf_s(file, "%d", &mapStruct.status[i][j]);
            int value = mapStruct.status[i][j];
            if(value != 0)
            {
                if(j > mapStruct.end_X) mapStruct.end_X = j;
                if(i > mapStruct.end_Y) mapStruct.end_Y = i;
            }
        }
    }

    mapStruct.end_X = (mapStruct.end_X + 1) * BLOCK_SIZE;
    mapStruct.end_Y = (mapStruct.end_Y + 1) * BLOCK_SIZE;
    mapStruct.start_X = 0;
    mapStruct.start_Y = 0;

    mapStruct.fileMapFormat = filePath;
    fclose(file);
}

void Map::MapLoadImage(SDL_Renderer *renderer)
{
    char fileImg[100];
    FILE *file = NULL;

    for(int i = 0; i < MAX_MAP_FORMAT; i++)
    {
        sprintf_s(fileImg, PATH_MAP_IMG, i);
        fopen_s(&file, fileImg, "rb");
        if(file == NULL) continue;
        fclose(file);

        loadFormat[i].LoadImage(renderer, fileImg);
        
    }    
}

void Map::MapRender(SDL_Renderer *renderer)
{
    int x1 = 0; int x2 = 0;
    int y1 = 0; int y2 = 0;
    int block_X = 0; int block_Y = 0;

    x1 = (mapStruct.start_X % BLOCK_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : BLOCK_SIZE);
    block_X = mapStruct.start_X / BLOCK_SIZE;

    y1 = (mapStruct.start_Y % BLOCK_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : BLOCK_SIZE);
    block_Y = mapStruct.start_Y / BLOCK_SIZE;

    for(int i = y1; i < y2; i += BLOCK_SIZE)
    {
        
        block_X = mapStruct.start_X / BLOCK_SIZE;
        for(int j = x1; j < x2; j += BLOCK_SIZE)
        {
            
            int value = mapStruct.status[block_Y][block_X];
            if(value != 0)
            {
                loadFormat[value].SetPos(j, i);
                loadFormat[value].Render(renderer);
            
            }
            block_X++;
        }
        block_Y++;
    }
}