#pragma once

//Global Variables
constexpr int DISPLAY_WIDTH = 1280; // convert to constexpr if they don't change and use upper case
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE = 1;
constexpr int origin_offset_y = 15;

//Functions
void Restart(int level);
bool IsColliding(GameObject* obj1, GameObject* obj2);

struct GameState
{
	Agent8States agentStates = STATE_START;
	int score = 0;
	int startingLevel = 2;
	int gemNumber = startingLevel / 2;
	int gemsSpawned = 0;
};
