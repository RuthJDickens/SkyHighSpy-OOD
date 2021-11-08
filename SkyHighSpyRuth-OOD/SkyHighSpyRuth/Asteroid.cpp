#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Asteroid.h"

Asteroid::Asteroid()
{
	m_type = OBJ_ASTEROID;
}
Asteroid::Asteroid(Point2f pos, int rotation)
{
	m_pos = pos;
	m_rotation = rotation;
	m_animSpeed = 0.05;
	m_speed = 4;
	m_radius = 60;
	m_type = OBJ_ASTEROID;
	m_spriteId = Play::GetSpriteId("asteroid");
}

void Asteroid::Update(GameState& state)
{
	//Movement
	m_velocity.x = m_speed * sin(m_rotation);
	m_velocity.y = m_speed * -cos(m_rotation);

	m_oldPos = m_pos;
	m_pos += m_velocity;
	//Animation
	m_framePos += m_animSpeed;
	if (m_framePos >= 1)
	{
		m_frame++;
		m_framePos = 0;
	}
	LeavingArea();
}

void Asteroid::Spawn(GameState& state)
{
	for (int i = 1; i <= state.startingLevel; i++)
	{
		//Randomly set position and rotation - can we design it in a way for both asteroid and meteors to remore repeat code?
		int pos_x = Play::RandomRoll(DISPLAY_WIDTH);
		int pos_y = Play::RandomRoll(DISPLAY_HEIGHT);
		float rotation = (((float)rand() / RAND_MAX) * (PLAY_PI * 2));
		Asteroid* rock = new Asteroid({ pos_x,pos_y }, rotation);
		rock->m_drawOrder = 4;

		//Check not sharing space with deadly meteor - unfair for player
		std::vector<GameObject*> vMeteors;
		GetObjectList(OBJ_METEOR, vMeteors);
		for (GameObject* m : vMeteors)
		{
			if (rock->IsColliding(m))
			{
				int newPos_x = rock->GetPosition().x + 20 * sin(rock->GetRotation());
				int newPos_y = rock->GetPosition().y + 20 * -cos(rock->GetRotation());
				rock->SetPosition({ newPos_x, newPos_y });
			}
		}
	}
	//Randomly choose one for Agent8 to start on
	std::vector<GameObject*> vRocks;
	GetObjectList(OBJ_ASTEROID, vRocks);
	int n = Play::RandomRollRange(0, vRocks.size() - 1);
	vRocks[n]->SetType(OBJ_ATTACHED);
}

void Asteroid::Draw(GameState& state)
{
	Play::DrawSpriteRotated(m_spriteId, m_pos, 0, m_rotation, 1.0f);
}