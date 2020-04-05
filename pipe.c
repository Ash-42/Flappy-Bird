#include "pipe.h"

void PipeInit(Pipe *pipe)
{
    pipe -> gap = 150;
    pipe -> width = 30;
    pipe -> speed = 250;
    pipe -> isActive = 0;
    pipe -> x = WIDTH - pipe -> width;

    int y_mid = rand() % (HEIGHT - pipe -> gap) + 50;

    pipe -> bot_len = HEIGHT - y_mid - (pipe -> gap / 2);
    pipe -> top_len = y_mid - (pipe -> gap / 2);

    pipe -> top.x = pipe -> x;
    pipe -> top.y = 0;
    pipe -> top.w = pipe -> width;
    pipe -> top.h = pipe -> top_len;

    pipe -> bot.x = pipe -> x;
    pipe -> bot.y = HEIGHT - pipe -> bot_len;
    pipe -> bot.w = pipe -> width;
    pipe -> bot.h = pipe -> bot_len;
}

void UpdatePipe(Pipe *pipe, double c_time)
{
    if (pipe -> isActive == 1) {
        pipe -> x -= pipe -> speed * c_time;
        pipe -> top.x = pipe -> x;
        pipe -> bot.x = pipe -> x;
        if (pipe -> x + pipe -> width < 0) {
            PipeInit(pipe);
        }
    }   
}

int CheckCollision(Pipe *pipe, Bird *bird)
{
    int x_top_dist = bird -> b.x + bird -> b.w - pipe -> top.x - pipe -> top.w; 
    int x_bot_dist = bird -> b.x + bird -> b.w - pipe -> bot.x - pipe -> bot.w; 
    int y_top_dist = bird -> b.y - pipe -> top_len;
    int y_bot_dist = bird -> b.y + bird -> b.h - pipe -> bot.y;

    if ((((x_top_dist <= bird -> b.w) && (x_top_dist >= -1 * pipe -> top.w)) || 
          ((x_bot_dist <= bird -> b.w) && (x_bot_dist >= -1 * pipe -> bot.w))) && 
          ((y_top_dist <= 0) || (y_bot_dist >= 0))) 
            return 1;

    return 0;
}
