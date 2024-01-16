#include "Bibliotecas.h"
#include "Collision.h"
#include "SDL.h"
#include "RegrasJogo.h"

SDL_Rect* makeBricks();

int main(int argc, char* args[]) {
    srand(time(NULL));

    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Texture* gBall = NULL;
	Mix_Music* gMusic = NULL;
	Mix_Chunk* gHitBrick = NULL;
	Mix_Chunk* gHitRect = NULL;

    int didBallMove = 0, i, indiceCor, contBricks = AMOUNT_BRICKS, tamanhoRect = 1, ballMod = 0;

    Cor cores[6], corAtual;
	Ball b = {0, 0, 7.5};

    cores[0] = (Cor){0, 0, 255};
    cores[1] = (Cor){255, 0, 0};
    cores[2] = (Cor){0, 255, 0};
    cores[3] = (Cor){255, 255, 0};
    cores[4] = (Cor){75, 0, 130};
    cores[5] = (Cor){255, 165, 0};

    if (!init(&gWindow, &gRenderer))
	{
        printf("Falha ao inicializar!\n");
    }

	else
	{
        if (!loadMedia( &gBall, gRenderer, "ball.png", &gMusic, &gHitBrick, &gHitRect ))
		{
            printf("Falha ao carregar media!\n");
        }

		else
		{

            bool quit = false;
            SDL_Event e;
            SDL_Rect fillRect;

			makeRect( &fillRect, tamanhoRect );
			makeBall( &b );

			SDL_Rect* fillBricks;
			fillBricks = makeBricks();

			Uint32 startTime, endTime, frameTime;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
					quit = true;
					}
				}

				startTime = SDL_GetTicks();

				if ( Mix_PlayingMusic() == 0 )
				{
					Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
					Mix_PlayMusic ( gMusic, -1 );
				}

				const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
				if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
				{
					fillRect.x -= MOVE_SPEED;
					if (didBallMove == 0)
					{
						b.x = -1;
						b.y = 1;
					}
					didBallMove = 1;
				}

				else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
				{
					fillRect.x += MOVE_SPEED;
					if (didBallMove == 0)
					{
						b.x = -1;
						b.y = 1;
					}
					didBallMove = 1;
				}

				if (fillRect.x < 0)
					fillRect.x = 0;

				if (fillRect.x > SCREEN_WIDTH - SCREEN_WIDTH / 4)
					fillRect.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;

				if (didBallMove == 1)
				{
					if (b.y == 1)
						b.quad.y -= BALL_SPEED + ballMod;
					else
						b.quad.y += BALL_SPEED + ballMod;

					if (b.x == -1)
						b.quad.x -= BALL_SPEED + ballMod;
					else
						b.quad.x += BALL_SPEED + ballMod;
				}

				if ( collision( &b.quad, &b.x, &b.y ) )
				{
					if( didBallMove != 0)
					{
						makeRect( &fillRect, tamanhoRect );
						makeBall( &b );
						fillBricks = makeBricks();
						didBallMove = 0;
						contBricks = AMOUNT_BRICKS;
					}
				}

				if ( collisionBrickBall ( b.quad, fillRect ) )
				{
					b.y = 1;
					b.quad.y = SCREEN_HEIGHT - 40;
					Mix_PlayChannel ( -1, gHitRect, 0 );
				}

				for (i = 0; i < AMOUNT_BRICKS; i++)
				{
					if ( collisionBrickBall ( b.quad, fillBricks[i] ) )
					{
						fillBricks[i].x = SCREEN_WIDTH + 100;
						fillBricks[i].y = SCREEN_HEIGHT + 100;
						b.y = -1;
						contBricks--;
						Mix_PlayChannel ( -1, gHitBrick, 0 );
						break;
					}
				}


				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
				SDL_RenderClear(gRenderer);

				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect);
				SDL_RenderCopy ( gRenderer, gBall, NULL, &b.quad);

				for (i = 0; i < AMOUNT_BRICKS; i++)
				{
					indiceCor = i / 5;
					corAtual = cores[indiceCor];

					SDL_SetRenderDrawColor(gRenderer, corAtual.R, corAtual.G, corAtual.B, 0xFF);
					SDL_RenderFillRect(gRenderer, &fillBricks[i]);
					SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
					SDL_RenderDrawRect(gRenderer, &fillBricks[i]);
				}

				SDL_RenderPresent(gRenderer);

				endTime = SDL_GetTicks();
				frameTime = endTime - startTime;

				if (frameTime < 1000 / FPS)
				{
					SDL_Delay((Uint32)(1000 / FPS - frameTime));
				}

				if (contBricks == 0)
				{
					ballMod += 3;
					makeRect( &fillRect, tamanhoRect );
					makeBall( &b );
					fillBricks = makeBricks();
					didBallMove = 0;
					contBricks = AMOUNT_BRICKS;
				}

			}
			free(fillBricks);
        }
    }

    close(&gWindow, &gRenderer, &gBall, &gMusic, &gHitBrick, &gHitRect);

    return 0;
}

