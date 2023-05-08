#include"Game.h"

Map::Map()
{
	seed = 0;
	map_start = 0;
	first_map = 0;
	second_map = rand() % 5 + 1;
	snow = Common_Fuction::loadTex("Resources/gfx/snow.png");
	dirt = Common_Fuction::loadTex("Resources/gfx/dirt.png");
	right_snow = Common_Fuction::loadTex("Resources/gfx/right_snow.png");
	left_snow = Common_Fuction::loadTex("Resources/gfx/left_snow.png");
	alone_snow = Common_Fuction::loadTex("Resources/gfx/alone_snow.png");
	right_dirt = Common_Fuction::loadTex("Resources/gfx/right_dirt.png");
	left_dirt = Common_Fuction::loadTex("Resources/gfx/left_dirt.png");
	alone_dirt = Common_Fuction::loadTex("Resources/gfx/alone_dirt.png");
	dest.h = 64;
	dest.w = 64;
}

Map::~Map()
{}

void Map::loadMap()
{
	if (seed == 0)
	{
		seed = time(NULL);
	}
	srand(seed);

	map_start += 5;

	if (map_start == 1280)
	{
		map_start = 0;
		first_map = second_map;
		second_map = rand() % 15 + 1;
	}

	ifstream tile_map_1("Map/map" + (first_map == 0 ? "0" : to_string(first_map)) + ".txt");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			tile_map_1 >> gameMap[i][j];
		}
	}
	tile_map_1.close();
	ifstream tile_map_2("Map/map" + to_string(second_map) + ".txt");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 20; j < 40; j++)
		{
			tile_map_2 >> gameMap[i][j];
		}
	}
	tile_map_2.close();
}

void Map::drawMap()
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 640;

	int map_x = map_start / 64;
	int map_y = 0;

	x1 = (map_start % 64) * -1;
	x2 = x1 + 1280 + (x1 == 0 ? 0 : 64);

	for (int i = y1; i < y2; i += 64)
	{
		map_x = map_start / 64;
		for (int j = x1; j < x2; j += 64)
		{
			int val = gameMap[map_y][map_x];
			dest.x = j;
			dest.y = i;
			switch (val)
			{
			case 1:
				SDL_RenderCopy(Game::renderer, snow, NULL, &dest);
				break;
			case 2:
				SDL_RenderCopy(Game::renderer, dirt, NULL, &dest);
				break;
			case 3:
				SDL_RenderCopy(Game::renderer, right_snow, NULL, &dest);
				break;
			case 4:
				SDL_RenderCopy(Game::renderer, right_dirt, NULL, &dest);
				break;
			case 5:
				SDL_RenderCopy(Game::renderer, left_snow, NULL, &dest);
				break;
			case 6:
				SDL_RenderCopy(Game::renderer, left_dirt, NULL, &dest);
				break;
			case 7:
				SDL_RenderCopy(Game::renderer, alone_snow, NULL, &dest);
				break;
			case 8:
				SDL_RenderCopy(Game::renderer, alone_dirt, NULL, &dest);
				break;
			default:
				break;
			}
			map_x++;
		}
		map_y++;
	}
}