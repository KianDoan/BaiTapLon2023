#include"Common_Fuction.h"

Common_Fuction::Common_Fuction()
{}

Common_Fuction::~Common_Fuction()
{}

SDL_Texture* Common_Fuction::loadTex(const char* p_path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* tmpSurface = IMG_Load(p_path);
	if (tmpSurface == NULL)
	{
		cout << "failed to load img" << endl;
	}
	texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}


//Menu


Menu::Menu()
{
	main_menu = Common_Fuction::loadTex("Resources/gfx/menu.png");
	play_button = Common_Fuction::loadTex("Resources/gfx/play_button.png");
	exit_button = Common_Fuction::loadTex("Resources/gfx/exit_button.png");
	
	x_mouse = 0;
	y_mouse = 0;
}

Menu::~Menu()
{}

bool Menu::LoadMenu()
{

	while (true)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return true;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				x_mouse = e.button.x;
				y_mouse = e.button.y;

				switch (CheckMouseDown(x_mouse, y_mouse))
				{
				case 1:
					return false;
					break;
				case 2:
					return true;
					break;
				default:
					break;
				}
			}

			SDL_RenderClear(Game::renderer);

			SDL_RenderCopy(Game::renderer, main_menu, NULL, NULL);
			SDL_RenderCopy(Game::renderer, play_button, NULL, &play_button_rect);
			SDL_RenderCopy(Game::renderer, exit_button, NULL, &exit_button_rect);

			SDL_RenderPresent(Game::renderer);
		}
	}

	return false;
}

int Menu::CheckMouseDown(int p_x,int p_y)
{
	if (p_x > 100 && p_x < 203 && p_y > 50 && p_y < 159)
		return 1;
	if (p_x > 100 && p_x < 203 && p_y >170 && p_y < 279)
		return 2;
	return 0;
}

void Menu::close()
{
	SDL_DestroyTexture(main_menu);
	main_menu = NULL;
	SDL_DestroyTexture(play_button);
	play_button = NULL;
	SDL_DestroyTexture(exit_button);
	exit_button = NULL;
}