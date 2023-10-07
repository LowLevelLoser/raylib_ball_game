#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"

int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
    //InitAudioDevice();
    SetTargetFPS(120);

    srand(time(NULL));
    game_t game;
    game.EMPTY_CIRCLE.exists = false;
    game.EMPTY_CIRCLE.radius = 0;
    game.EMPTY_CIRCLE.position.x = 0;
    game.EMPTY_CIRCLE.position.y = 0;
    game.EMPTY_CIRCLE.velocity.x = 0;
    game.EMPTY_CIRCLE.velocity.y = 0;
    game.game_state = RUNNING;

    for (int i = 0; i < MAX_AMOUNT_OF_CIRCLES; i++){
        game.circles[i] = game.EMPTY_CIRCLE;
    }

    while(!WindowShouldClose()){
        RunGame(&game);
        BeginDrawing();
            ClearBackground(BLACK);
            RenderGame(&game);
        EndDrawing();
    }
    
    //StopMusicStream(game.music);

    //CloseAudioDevice();

    CloseWindow();

    return 0;
}
