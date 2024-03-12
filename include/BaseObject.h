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

        void SetPos(int x, int y);
        SDL_Rect GetPos();
        SDL_Texture* GetTexture();
        void SetSize(int w, int h);

        virtual void LoadImage(SDL_Renderer *renderer, const char *filePath);
        void Render(SDL_Renderer *renderer, SDL_Rect *src = NULL);

};


#endif // BASEOBJECT_H
