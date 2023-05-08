#include"Game.h"

Game* game = NULL;

int main(int argc, char* args[])
{

	float FPS = 30;

	int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("Tiny Monster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 640, 0);

	while (!(game->gameOver()))
	{
		frameStart = SDL_GetTicks();

		game->handleEvent();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
	game->cleanUp();
	delete game;
	return 0;
}