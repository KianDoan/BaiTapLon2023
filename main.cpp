#include"Game.h"

Game* game = NULL;

Menu* menu = NULL;

int main(int argc, char* args[])
{

	float FPS = 30;

	int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("Tiny Monster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 640, 0);

	menu = new Menu();

	bool quit = menu->LoadMenu();

	menu->close();

	while (!(game->gameOver()) && !quit)
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
	delete menu;
	menu = NULL;
	delete game;
	game = NULL;
	return 0;
}