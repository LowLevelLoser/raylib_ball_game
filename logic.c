#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <raylib.h>

#include "game.h"
#include "logic.h"

//bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);  Check if point is inside Circle

int GetInactiveCircleIndex(game_t *game);
Circle CreateCircle();
void UpdateCircle(game_t *game, Circle *circle_u);
void ResetGame(game_t *game);
void PlayRunningGame(game_t *game);

void RunGame(game_t *game){
#if 0
    static float time_to_create_circle = 0;
    time_to_create_circle += GetFrameTime();
    game->timer += time_to_create_circle;
    if (time_to_create_circle > 0.5){
        time_to_create_circle = 0;
        int circle_index = GetInactiveCircleIndex(game);
        if (circle_index >= 0){
            game->circles[circle_index] = CreateCircle();
        }
    }
    for (int i = 0; i < MAX_AMOUNT_OF_CIRCLES; i++){
        if (game->circles[i].exists){
            UpdateCircle(game, &game->circles[i]);
        }
    }
#else
    switch(game->game_state){
        case RUNNING:
            PlayRunningGame(game);
            break;
        case GAME_OVER:
            if(IsKeyPressed(KEY_R)){
                ResetGame(game);
            }
            break;
    }
#endif
}

void PlayRunningGame(game_t *game){
    static float time_cache = 0;
    static float time_to_create_circle = 0;
    time_cache += GetFrameTime();
    time_to_create_circle += GetFrameTime();
    game->timer += GetFrameTime();
    if (time_to_create_circle > 0.5){
        time_to_create_circle = 0;
        int circle_index = GetInactiveCircleIndex(game);
        if (circle_index >= 0){
            game->circles[circle_index] = CreateCircle();
        }
    }

    if (time_cache > 0.01){
        time_cache = 0;
        for (int i = 0; i < MAX_AMOUNT_OF_CIRCLES; i++){
            if (game->circles[i].exists){
                UpdateCircle(game, &game->circles[i]);
            }
        }
    }

}

int GetInactiveCircleIndex(game_t *game){
    for (int i = 0; i < MAX_AMOUNT_OF_CIRCLES; i++){
        if (!game->circles[i].exists){
            return i;
        }
    }
    return -1;
}

Circle CreateCircle(){
    Vector2 mouse_position = GetMousePosition();

    srand(rand());
    float speed = (float)rand()/(float)(RAND_MAX/(10.0)) + 0.15;
    srand(rand());
    float angle = (float)rand()/(float)(RAND_MAX/(PI*2));
    Circle my_circle;
    my_circle.radius = (20*sqrtf(speed));
    my_circle.exists = true;
    my_circle.position.x = (SCREEN_WIDTH/2.0-10)*cos(angle) + SCREEN_WIDTH/2.0;
    my_circle.position.y = (SCREEN_HEIGHT/2.0-10)*sin(angle) + SCREEN_HEIGHT/2.0;

    float dx = mouse_position.x - my_circle.position.x;
    float dy = mouse_position.y - my_circle.position.y;
    float distance = sqrtf(dx*dx + dy*dy);
    dx /= distance*speed/3;
    dy /= distance*speed/3;

    my_circle.velocity.x = dx;
    my_circle.velocity.y = dy;

    return my_circle;
}

void UpdateCircle(game_t *game, Circle *circle_u){
    circle_u->position.x += circle_u->velocity.x;
    circle_u->position.y += circle_u->velocity.y;

    if (CheckCollisionPointCircle(GetMousePosition(), circle_u->position, circle_u->radius)){
        game->game_state = GAME_OVER;
        return;
    }
    if (circle_u->position.x + circle_u->radius < 0 || circle_u->position.x - circle_u->radius > SCREEN_WIDTH ||
        circle_u->position.y + circle_u->radius< 0 || circle_u->position.y - circle_u->radius > SCREEN_HEIGHT){
        //printf("blam\n");
        circle_u->exists = false;
    }
}

void ResetGame(game_t *game){
    for (int i = 0; i < MAX_AMOUNT_OF_CIRCLES; i++){
        game->circles[i] = game->EMPTY_CIRCLE;
    }
    game->timer = 0;
    game->game_state = RUNNING;
}
