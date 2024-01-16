#ifndef SDL_FUNCTIONS
#define SDL_FUNCTIONS

#include "Bibliotecas.h"

bool init(SDL_Window** gWindow, SDL_Renderer** gRenderer);
SDL_Texture* loadTexture(char c[], SDL_Renderer* gRenderer);
bool loadMedia(SDL_Texture** gBall, SDL_Renderer* gRenderer, char c[], Mix_Music** gMusic, Mix_Chunk** gHitBrick, Mix_Chunk** gHitRect);
void close(SDL_Window** gWindow, SDL_Renderer** gRenderer, SDL_Texture** gBall, Mix_Music** gMusic, Mix_Chunk** gHitBrick, Mix_Chunk** gHitRect);

#endif // SDL_H_INCLUDED


