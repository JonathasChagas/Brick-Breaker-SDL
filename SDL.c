#include "SDL.h"
#include "Bibliotecas.h"

bool init(SDL_Window** gWindow, SDL_Renderer** gRenderer)
{

	bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
        printf("SDL nao pode ser inicializado! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

	else
		{
        *gWindow = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (*gWindow == NULL)
		{
            printf("Janela nao pode ser criada! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }

		else
		{
            *gRenderer = SDL_CreateRenderer(*gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (*gRenderer == NULL)
			{
                printf("Renderer nao pode ser criado! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }

			else
			{
                SDL_SetRenderDrawColor(*gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
				{
                    printf("SDL_image nao pode ser inicializado! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

				if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf ( "SDL_Mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
            }
        }
    }
    return success;
}

SDL_Texture* loadTexture(char c[], SDL_Renderer* gRenderer)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(c);
    if (loadedSurface == NULL)
	{
        printf("Nao foi possivel carregar a imagem %s! SDL_image Error: %s\n", c, IMG_GetError());
    }
	else
	{
		SDL_SetColorKey (loadedSurface, SDL_TRUE, SDL_MapRGB ( loadedSurface->format, 10, 94, 25 ) );
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
		{
            printf("Nao foi possivel criar textura a partir de %s! SDL Error: %s\n", c, SDL_GetError());
        }

        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool loadMedia(SDL_Texture** gBall, SDL_Renderer* gRenderer, char c[], Mix_Music** gMusic, Mix_Chunk** gHitBrick, Mix_Chunk** gHitRect)
{
    bool success = true;
    *gBall = loadTexture(c, gRenderer);

    if (*gBall == NULL)
	{
        printf("Falha ao carregar textura da imagem!\n");
        success = false;
    }

	//Musica
	*gMusic = Mix_LoadMUS ( "finalevel.mp3" );
	if (*gMusic == NULL)
	{
		printf ( "Falha ao carregar a musica! SDL_Mixer Error: %s", Mix_GetError() );
		success = false;
	}

	*gHitBrick = Mix_LoadWAV ( "brick.ogg" );
	if (*gHitBrick == NULL)
	{
		printf ( "Falha ao carregar efeito sonoro brick! SDL_Mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	*gHitRect = Mix_LoadWAV ( "rect.ogg" );
	if (*gHitRect == NULL)
	{
		printf ( "Falha ao carregar efeito sonoro rect! SDL_Mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    return success;
}

void close(SDL_Window** gWindow, SDL_Renderer** gRenderer, SDL_Texture** gBall, Mix_Music** gMusic, Mix_Chunk** gHitBrick, Mix_Chunk** gHitRect)
{
    SDL_DestroyTexture(*gBall);
    *gBall = NULL;

	Mix_FreeChunk ( *gHitBrick );
	Mix_FreeChunk ( *gHitRect );
	*gHitBrick = NULL;
	*gHitRect = NULL;

	Mix_FreeMusic ( *gMusic );
	gMusic = NULL;

    SDL_DestroyRenderer(*gRenderer);
    SDL_DestroyWindow(*gWindow);
    *gRenderer = NULL;
    *gWindow = NULL;

	Mix_Quit();
    SDL_Quit();
    IMG_Quit();
}
