#include "Collision.h"
#include "Bibliotecas.h"

bool collision(SDL_Rect* quad, int* directionLF, int* directionUD) {

	if (quad->x < 0)
	{
        quad->x = 0;
        *directionLF = 1;
    }

    if (quad->x > SCREEN_WIDTH - QUAD_SIZES)
	{
        quad->x = SCREEN_WIDTH - QUAD_SIZES;
        *directionLF = -1;
    }

    if (quad->y < 0)
	{
        quad->y = 0;
        *directionUD = -1;
    }

    if (quad->y > SCREEN_HEIGHT - QUAD_SIZES)
	{
        return true;
    }
	
	return false;
	
}

bool collisionBrickBall(SDL_Rect a, SDL_Rect b)
{

	Circle ball;
    ball.r = QUAD_SIZES / 2;

    // Coordenadas do centro do círculo
    ball.x = a.x + ball.r;
    ball.y = a.y + ball.r;

    int closestX, closestY;

    // Mais perto X
    if (ball.x < b.x)
	{
        closestX = b.x;
    }

	else if (ball.x > b.x + b.w)
	{
        closestX = b.x + b.w;
    }

	else
	{
        closestX = ball.x;
    }

    // Mais perto Y
    if (ball.y < b.y)
	{
        closestY = b.y;
    }

	else if (ball.y > b.y + b.h)
	{
        closestY = b.y + b.h;
    }

	else
	{
        closestY = ball.y;
    }

    if ( distanceSquared( ball.x, ball.y, closestX, closestY ) < ball.r * ball.r )
	{
		return true;
	}

	return false;

}

double distanceSquared ( int x1, int y1, int x2, int y2 )
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}
