#include "Animation.h"

Animation::Animation()
{
    x_pos = 0; y_pos = 0;
    x_speed = 0; y_speed = 0;
    width_frame = 0; height_frame = 0;
    frame = 0;
    status = 1;

    input.left = 0;
    input.right = 0;
    input.up = 0;
    input.down = 0;
    input.jump = 0;

    isGround = false;
}

void Animation::LoadImage(SDL_Renderer*renderer, const char *filePath)
{
    BaseObject::LoadImage(renderer, filePath);

    width_frame = rect.w / FRAME_RUN ;
    height_frame = rect.h;
}

void Animation::SetFrame(int frameCount)
{
    if(width_frame != 0 && height_frame != 0)
    {
        for(int i = 0; i < frameCount; i++)
        {
            source[i].x = i * width_frame;
            source[i].y = 0;
            source[i].w = width_frame;
            source[i].h = height_frame;
        }
    }
    
}


void Animation::Draw(SDL_Renderer *renderer)
{
    if(status == RUN_LEFT)
        LoadImage(renderer, PATH_PLAYER_RUN_LEFT);
    if(status == RUN_RIGHT)
        LoadImage(renderer, PATH_PLAYER_RUN_RIGHT);

    if(input.right == 1 || input.left == 1)
        frame++;
    else frame = 0;
    if(frame >= FRAME_RUN) frame = 0;
    
    rect.x = x_pos;
    rect.y = y_pos;

    SDL_Rect *srcRect = &source[frame];
    SDL_Rect *dstRect = new SDL_Rect{rect.x, rect.y, width_frame, height_frame};

    if(texture == NULL)
        std::cout << "The Image animation is null \n";
    SDL_RenderCopy(renderer, texture, srcRect, dstRect);
}

void Animation::HandleInput(SDL_Renderer *renderer, SDL_Event event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_d:
                status = RUN_RIGHT;
                input.right = 1;
                input.left = 0;
                break;
            case SDLK_RIGHT:
                status = RUN_RIGHT;
                input.right = 1;
                input.left = 0;
                break;
            case SDLK_a:
                status = RUN_LEFT;
                input.left = 1;
                input.right = 0;
                break;
            case SDLK_LEFT:
                status = RUN_LEFT;
                input.left = 1;
                input.right = 0;
                break;
                
            
            default:
                break;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_d:
                input.right = 0;
                break;
            case SDLK_RIGHT:
                input.right = 0;
                break;
            case SDLK_a:
                input.left = 0;
                break;
            case SDLK_LEFT:
                input.left = 0;
                break;
                
            
            default:
                break;
        }
    }
}

void Animation::Move(MapStruct &map)
{
    x_speed = 0;
    y_speed += SPEED_GRAVITY;
    if(y_speed > MAX_GRAVITY)
        y_speed = MAX_GRAVITY;
    
    if(input.left == 1)
        x_speed += -1;
    else if(input.right == 1)
        x_speed += 1;

    CheckCollider(map);
}

void Animation::CheckCollider(MapStruct &map)
{
    int x1 = 0, y1 = 0;
    int x2 = 0, y2 = 0;

    // Check horizontal
    int height_min = std::min(height_frame, BLOCK_SIZE);
    x1 = (x_pos + x_speed) / BLOCK_SIZE;
    x2 = (x_pos + x_speed + width_frame - 1) / BLOCK_SIZE;

    y1 = y_pos / BLOCK_SIZE;
    y2 = (y_pos + height_min - 1) / BLOCK_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_speed > 0)
        {
            if(map.status[y1][x2] > 0 && map.status[y2][x2] > 0)
            {
                x_pos = x2 * BLOCK_SIZE;
                x_pos -= width_frame + 1;
                x_speed = 0;
            }
        }
        else if(x_speed < 0)
        {
            if(map.status[y1][x1] != 0 && map.status[y2][x1] != 0)
            {
                x_pos = (x1 + 1) * BLOCK_SIZE ;
                x_speed = 0;
            }
        }
    }

    // Check Vertical
    int width_min = std::min(width_frame, BLOCK_SIZE);
    x1 = x_pos / BLOCK_SIZE;
    x2 = (x_pos + width_min - 21) / BLOCK_SIZE;

    y1 = (y_pos + y_speed) / BLOCK_SIZE;
    y2 = (y_pos + y_speed + height_frame - 1) / BLOCK_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_speed > 0)
        {
            if(map.status[y2][x1] > 0 && map.status[y2][x2] > 0)
            {
                y_pos = y2 * BLOCK_SIZE;
                y_pos -= height_frame + 1;
                isGround = true;
                y_speed = 0;
            }
        }
        else if(y_speed < 0)
        {
            if(map.status[y1][x1] > 0 && map.status[y1][x2] > 0)
            {
                y_pos = (y1 + 1) * BLOCK_SIZE;
                y_speed = 0;
            }
        }
    }

    // if we don't collide with obejct, we will move
    x_pos += x_speed;
    y_pos += y_speed;

    if(x_pos < 0) x_pos = 0;
    else if(x_pos + width_frame > map.end_X) x_pos = map.end_X - width_frame; 

}