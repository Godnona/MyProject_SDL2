#include "BaseObject.h"

BaseObject::BaseObject()
{
    rect.x = 0; rect.y = 0;
    rect.w = 0; rect.h = 0;
    texture = NULL;
}

BaseObject::~BaseObject()
{
    rect.x = 0; rect.y = 0;
    rect.w = 0; rect.h = 0;
    texture = NULL;
}

/*=============================|Set_Get|=============================*/

void BaseObject::SetPos(int x, int y)
{
    rect.x = x;
    rect.y = y;
};

SDL_Rect BaseObject::GetPos()
{
    return rect;
}

SDL_Texture* BaseObject::GetTexture()
{
    return texture;
}

void BaseObject::SetSize(int w, int h)
{
    rect.w = w;
    rect.h = h;
}

/*=============================|Handle|=============================*/

void BaseObject::LoadImage(SDL_Renderer *renderer,const char *filePath)
{
    SDL_Texture *textureImg = NULL;
    SDL_Surface *surfaceImg = IMG_Load(filePath);
    if(surfaceImg == NULL) std::cout << "Error load Surface: " << SDL_GetError() << std::endl;

    textureImg = SDL_CreateTextureFromSurface(renderer, surfaceImg);
    if(textureImg == NULL) std::cout << "Error load texture " << std::endl;
    rect.w = surfaceImg->w;
    rect.h = surfaceImg->h;

    SDL_FreeSurface(surfaceImg);
    texture = textureImg;
}

void BaseObject::Render(SDL_Renderer *renderer, SDL_Rect *src)
{
    SDL_Rect *dst = new SDL_Rect{rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(renderer, texture, src, dst);
}
