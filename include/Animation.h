#pragma once
#ifndef ANIMATION
#define ANIMATION

#include "Def.h"
#include "BaseObject.h"
#include "Map.h"

class Animation : public BaseObject
{
private:
    float x_pos, y_pos;
    float x_move, y_move;
    int width_frame, height_frame;

    SDL_Rect source[FRAME_RUN];
    Input input;

    int frame;
    int status;

public:
    Animation();
    ~Animation(){;};

    enum RunType
    {
        RUN_LEFT = -1,
        RUN_RIGHT = 1
    };

    void LoadImage(SDL_Renderer*renderer, const char *filePath);
    void SetFrame(int frameCount);
    void Draw(SDL_Renderer *renderer);
    void HandleInput(SDL_Renderer *renderer, SDL_Event event);

    void Move(MapStruct &map);
    void CheckCollider(MapStruct &map);

};


#endif //ANIMATION