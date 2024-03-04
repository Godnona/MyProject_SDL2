#pragma once
#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "Def.h"

class BaseObject
{
    protected:
        SDL_Rect rect;
        SDL_Texture *texture;
    public:
        BaseObject(/* args */);
        ~BaseObject();

        void SetRect(int x, int y);
        SDL_Rect GetRect();
        SDL_Texture* GetTexture();

        void LoadImage(SDL_Renderer *renderer, const char *filePath);
        void Render(SDL_Renderer *renderer, SDL_Rect *src = NULL);

};


#endif // BASEOBJECT_H
