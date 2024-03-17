#pragma once
#ifndef MAP_H
#define MAP_H

#include "Def.h"
#include "BaseObject.h"

#define MAX_MAP_X 69
#define MAX_MAP_Y 25
#define BLOCK_SIZE 32
#define MAX_MAP_FORMAT 12

typedef struct
{
    int start_X, start_Y;
    int end_X, end_Y;

    int status[MAX_MAP_Y][MAX_MAP_X];
    const char *fileMapFormat;

} MapStruct;

class ObjectMap : public BaseObject
{
    private:
        
    public:
        ObjectMap(){;};
        ~ObjectMap(){;};
};


class Map
{
    private:
        ObjectMap loadFormat[MAX_MAP_FORMAT];
        MapStruct mapStruct;
    public:
        Map(){;};
        ~Map(){;};

        void SetMap(MapStruct& mapStruct);
        MapStruct GetMap();
        
        void MapLoadFormat(const char *filePath);
        void MapLoadImage(SDL_Renderer *renderer);
        void MapRender(SDL_Renderer *renderer);
       
};

#endif // MAP_H
