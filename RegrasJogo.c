#include "RegrasJogo.h"
#include "Bibliotecas.h"

SDL_Rect* makeBricks()
{
    SDL_Rect* p;
    p = (SDL_Rect*)malloc(sizeof(SDL_Rect) * AMOUNT_BRICKS);

    int j = 0, k = 0;

    for (int i = 0; i < AMOUNT_BRICKS; i++)
	{
        if (i % 5 == 0 && i != 0)
		{
            j = 0;
            k += TILE_HEIGHT;
        }

        p[i].x = j;
        p[i].y = k;
        p[i].w = TILE_WIDTH;
        p[i].h = TILE_HEIGHT;

        j += TILE_WIDTH;
    }
    return p;
}

void makeRect (SDL_Rect* fillRect, int i)
{
	fillRect->x = SCREEN_WIDTH / 2.6;
	fillRect->y = SCREEN_HEIGHT - 13;
	fillRect->w = SCREEN_WIDTH / 4 * i;
	fillRect->h = SCREEN_HEIGHT / 65;
}

void makeBall (Ball* b)
{
	b->quad.x = SCREEN_WIDTH / 2.05;
	b->quad.y = SCREEN_HEIGHT - 29;
	b->quad.w = QUAD_SIZES;
	b->quad.h = QUAD_SIZES;
}
