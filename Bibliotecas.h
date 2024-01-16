#ifndef BIBLIOTECAS
#define BIBLIOTECAS

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int MOVE_SPEED;
extern const int BALL_SPEED;
extern const int QUAD_SIZES;
extern const int TILE_WIDTH;
extern const int TILE_HEIGHT;
extern const int AMOUNT_BRICKS;
extern const int FPS;

typedef struct rgb
{
    int R;
    int G;
    int B;
} Cor;

typedef struct circle
{
	int x, y;
	int r;
} Circle;

typedef struct ballg
{
	SDL_Rect quad;
	int x;
	int y;
} Ball;

#endif // BIBLIOTECAS
