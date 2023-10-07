#ifndef GAME_H_
#define GAME_H_

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 800
#define MAX_AMOUNT_OF_CIRCLES 64

//#define MAX_RADIUS 25.0
//#define MIN_RADIUS 10.0

#include <raylib.h>

enum state{
    RUNNING,
    GAME_OVER,
};

typedef struct {
    float radius;
    Vector2 position;
    Vector2 velocity;
    bool exists;
} Circle;

typedef struct {
    Circle circles[MAX_AMOUNT_OF_CIRCLES];
    Circle EMPTY_CIRCLE;
    enum state game_state;
    float timer;
} game_t;

#endif
