#define PLAY_IMPLEMENTATION
//#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Agent8.h"
#include "Asteroid.h"
#include "Meteor.h"
#include "UserInterface.h"

GameState gameState;

// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground("Data\\Backgrounds\\background.png");
	Play::StartAudioLoop("music");

	//Spawn Player and set origin for crawling sprites
	new Agent8();
	new UserInterface();

	int agent_height = Play::GetSpriteHeight("agent8_left");
	Play::MoveSpriteOrigin("agent8_left_7", 0, agent_height / 2 + origin_offset_y);
	Play::MoveSpriteOrigin("agent8_right_7", 0, agent_height / 2 + origin_offset_y);
	Play::MoveSpriteOrigin("asteroid_2", 0, 1 - origin_offset_y);

	//Platforms and hazards
	Meteor::Spawn(gameState);
	Asteroid::Spawn(gameState);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::DrawBackground();
	//Play::ClearDrawingBuffer(Play::cBlack);
	GameObject::UpdateAll(gameState);
	GameObject::DrawAll(gameState);

	//Next level - Create method in Main Game.h to check for next level condition
	if (gameState.score == gameState.gemNumber)
	{
		gameState.startingLevel += 1;
		gameState.gemNumber = gameState.startingLevel / 2;
		Play::PlayAudio("reward");
		Restart();
	}
	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

void Restart()
{
	GameObject::DestroyAll();

	//Spawn new asteroids an meteors
	Meteor::Spawn(gameState);
	Asteroid::Spawn(gameState);
	new Agent8();

	//Reset variables
	gameState.score = 0;
	gameState.gemsSpawned = 0;
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

