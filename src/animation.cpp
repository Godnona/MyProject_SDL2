#include "Animation.h"

Animation::Animation()
{
    x_pos = 0; y_pos = 0;
    x_speed = 0; y_speed = 0;
    width_frame = 0; height_frame = 0;
    frame = 0;
    status = 0;

    input.idle = 1;
    input.left = 0;
    input.right = 0;
    input.up = 0;
    input.down = 0;
    input.jump = 0;
    isRight = true;
    isGround = false;
    map_x = 0;
    map_y = 0;
}

void Animation::SetCamera(int x, int y)
{
    map_x = x;
    map_y = y;
}

void Animation::LoadImage(SDL_Renderer*renderer, const char *filePath)
{
    BaseObject::LoadImage(renderer, filePath);

    width_frame = rect.w / FRAME_PLAYER;
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
    else if(status == RUN_RIGHT)
        LoadImage(renderer, PATH_PLAYER_RUN_RIGHT);
    else if(status == IDLE_LEFT && isRight == false)
        LoadImage(renderer, PATH_PLAYER_IDLE_LEFT);
    else if(status == IDLE_LEFT && isRight == true)
        LoadImage(renderer, PATH_PLAYER_IDLE_RIGHT);

    if(input.right == 1 || input.left == 1 || input.idle == 1)
        frame++;
    //else frame = 0;
    if(frame >= FRAME_PLAYER) frame = 0;
    
    std::cout << input.left << " " << input.idle << " " << input.right << "\n";

    rect.x = x_pos - map_x;
    rect.y = y_pos - map_y;

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
                input.idle = 0;
                input.right = 1;
                input.left = 0;
                isRight = true;
                break;
            case SDLK_RIGHT:
                status = RUN_RIGHT;
                input.idle = 0;
                input.right = 1;
                input.left = 0;
                isRight = true;
                break;
            case SDLK_a:
                status = RUN_LEFT;
                input.idle = 0;
                input.left = 1;
                input.right = 0;
                isRight = false;
                break;
            case SDLK_LEFT:
                status = RUN_LEFT;
                input.idle = 0;
                input.left = 1;
                input.right = 0;
                isRight = false;
                break;
                
            default:
                //status = IDLE_LEFT;
                //input.idle = 1;
                break;
        }
    }
    else if(event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_d:
                status = IDLE_LEFT;
                input.idle = 1;
                input.right = 0;
                isRight = true;
                break;
            case SDLK_RIGHT:
                status = IDLE_LEFT;
                input.idle = 1;
                input.right = 0;
                isRight = true;
                break;
            case SDLK_a:
                status = IDLE_LEFT;
                input.idle = 1;
                input.left = 0;
                isRight = false;
                break;
            case SDLK_LEFT:
                status = IDLE_LEFT;
                input.idle = 1;
                input.left = 0;
                isRight = false;
                break;
                
            default:
                status = IDLE_LEFT;
                input.idle = 1;
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
        x_speed += -SPEED_PLAYER;
    else if(input.right == 1)
        x_speed += SPEED_PLAYER;

    CheckCollider(map);
    MoveCamera(map);
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
            if(map.status[y1][x2] > 0 || map.status[y2][x2] > 0)
            {
                x_pos = x2 * BLOCK_SIZE;
                x_pos -= width_frame + 1;
                x_speed = 0;
            }
        }
        else if(x_speed < 0)
        {
            if(map.status[y1][x1] != 0 || map.status[y2][x1] != 0)
            {
                x_pos = (x1 + 1) * BLOCK_SIZE ;
                x_speed = 0;
            }
        }
    }

    // Check Vertical
    int width_min = std::min(width_frame, BLOCK_SIZE);
    x1 = x_pos / BLOCK_SIZE;
    x2 = (x_pos + width_min) / BLOCK_SIZE;

    y1 = (y_pos + y_speed) / BLOCK_SIZE;
    y2 = (y_pos + y_speed + height_frame - 1) / BLOCK_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_speed > 0)
        {
            if(map.status[y2][x1] > 0 || map.status[y2][x2] > 0)
            {
                y_pos = y2 * BLOCK_SIZE;
                y_pos -= height_frame + 1;
                isGround = true;
                y_speed = 0;
            }
        }
        else if(y_speed < 0)
        {
            if(map.status[y1][x1] > 0 || map.status[y1][x2] > 0)
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

void Animation::MoveCamera(MapStruct &map)
{
    map.start_X = x_pos - (SCREEN_WIDTH / 2);
    if(map.start_X < 0) map.start_X = 0;
    else if(map.start_X + SCREEN_WIDTH > map.end_X) map.start_X = map.end_X - SCREEN_WIDTH;

    map.start_Y = 0;
    map.start_Y = y_pos - (SCREEN_HEIGHT / 2);
    if(map.start_Y < 0) map.start_Y = 0;
    else if(map.start_Y + SCREEN_HEIGHT > map.end_Y) map.start_Y = map.end_Y - SCREEN_HEIGHT;
    
}