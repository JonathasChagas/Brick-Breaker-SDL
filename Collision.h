#ifndef COLLISION_H
#define COLLISION_H

#include "Bibliotecas.h"

bool collision(SDL_Rect* quad, int* directionLF, int* directionUD);
bool collisionBrickBall(SDL_Rect a, SDL_Rect b);
double distanceSquared ( int x1, int y1, int x2, int y2 );

#endif // COLLISION_H
