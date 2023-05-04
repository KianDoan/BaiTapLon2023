#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include<vector>

#include"Game.h"
#include"Map.h"

using namespace std;

enum STATUS
{
	MOVE_RIGHT,
	MOVE_LEFT,
	STAND_RIGHT,
	STAND_LEFT,
	RIGHT_FALL,
	LEFT_FALL
};

class GameObject
{
public:
	GameObject(const char* p_path, int p_x, int p_y);
	~GameObject();

	void update(Map& map_data);
	void render();
	void loadClips();
	void renderClip();
	bool handlePlayerInput();
	void accident(Map& map_data);
	void scrollMap(Map& map_data);

private:
	float x_pos;
	float y_pos;
	int object_scroll;
	int map_scroll;
	int frame;
	int jump;
	int left;
	int right;
	STATUS status;
	float gravity_speed;
	float velocity;
	float jump_speed;
	bool on_ground;
	bool is_dead;
	SDL_Event event;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect, frame_clip[6];
	int lever;
};

#endif // !GAME_OBJECT_H_
