#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Asteroid.h"
#include "Meteor.h"

Meteor::Meteor(Point2f pos, int rotation)
{
	m_pos = pos;
	m_rotation = rotation;
	m_type = OBJ_METEOR;
	m_animSpeed = 0.05;
	m_speed = 4;
	m_radius = 60;
}

void Meteor::Spawn(GameState& state)
{
	//Same as for asteroids but half has many meteors
	for (int i = 1; i <= state.startingLevel / 2; i++)
	{
		//Random Positon
		int pos_x = Play::RandomRoll(DISPLAY_WIDTH);
		int pos_y = Play::RandomRoll(DISPLAY_HEIGHT);
		float rotation = (((float)rand() / RAND_MAX) * (PLAY_PI * 2));	// 0-2PI radians
		new Meteor({ pos_x, pos_y }, rotation);
	}
}
