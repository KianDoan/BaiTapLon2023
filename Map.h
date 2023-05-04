#ifndef MAP_H_
#define MAP_H_


#include"Game.h"
#include<fstream>
#include<cstdlib>
#include<ctime>

class Map
{
public:
	Map();
	~Map();
	void loadMap();
	void drawMap();
	void setMap(int p_map_start)
	{
		map_start = p_map_start;
	}
	int gameMap[11][40];
	int map_start;

private:
	SDL_Rect dest;

	SDL_Texture* snow;

	SDL_Texture* dirt;

	SDL_Texture* right_snow;

	SDL_Texture* left_snow;

	SDL_Texture* alone_snow;

	SDL_Texture* right_dirt;

	SDL_Texture* left_dirt;

	SDL_Texture* alone_dirt;

	int first_map;
	int second_map;

};

#endif // !MAP_H_