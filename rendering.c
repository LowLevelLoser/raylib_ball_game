#include <raylib.h>
#include <stdio.h>

#include "game.h"
#include "rendering.h"

void RenderGameOverScreen(const game_t *game);
void RenderRunningGame(const game_t *game);

void RenderGame(const game_t *game){
    switch(game->game_state){
        case RUNNING:
            RenderRunningGame(game);
            break;
        case GAME_OVER:
            RenderGameOverScreen(game);
            break;
    }
}

void RenderRunningGame(const game_t *game){
    for (int i = 0; i < MAX_AMOUNT_OF_CIRCLES; i++){
        Circle circle_r = game->circles[i];
        if(circle_r.exists){
            DrawCircleV(circle_r.position, circle_r.radius, RAYWHITE);
        }
    }
    char timer[10];
    snprintf(timer, 10, "%.2lf s", game->timer);
    DrawText(timer, 0, 0, 20, GREEN);
}

void RenderGameOverScreen(const game_t *game){
    char timer[22];
    snprintf(timer, 22, "YOU LASTED %.2lf s", game->timer);
    DrawText(timer, SCREEN_WIDTH/6, SCREEN_HEIGHT/2 - 20, 50, RAYWHITE);
}
