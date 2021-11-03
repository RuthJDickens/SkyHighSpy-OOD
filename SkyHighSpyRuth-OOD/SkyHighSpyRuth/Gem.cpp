#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Gem.h"

Gem::Gem(Point2f pos)
{
	m_pos = pos;
	m_type = OBJ_GEM;
	m_animSpeed = 0.5;
	m_radius = 20;
	m_rotSpeed = 0.05;
}

void Gem::Update(GameState& state)
{
	int waitTime = 10;
	if (m_hidden)
	{
		//Update frame for hidden - acts as timer
		m_framePos += m_animSpeed;
		if (m_framePos <= 1)
		{
			m_frame++;
			m_framePos = 0;
		}
		if (m_frame == waitTime)
		{
			m_hidden = false;
		}
	}

	m_rotation += m_rotSpeed;
	if (m_rotation >= 1 || m_rotation <= -1)
	{
		m_rotSpeed *= -1;
	}
}

void Gem::Draw(GameState& state)
{
	Play::DrawSpriteRotated(Play::GetSpriteId("gem"), m_pos, 0, m_rotation, 1.0f);
}

void Gem::Spawn(GameState& state)
{
	GameObject* obj_attached = GetObjectOfType(OBJ_ATTACHED);
	if (state.gemsSpawned < state.gemNumber)
	{
		//Only for odd number asteroids
		if (obj_attached->GetId() % 2)
		{
			Gem* g = new Gem(obj_attached->GetPosition());

			//Check in display area
			if (g->m_pos.y >= DISPLAY_HEIGHT)
			{
				g->m_pos.y = DISPLAY_HEIGHT - 20;
			}
			if (g->m_pos.x >= DISPLAY_WIDTH)
			{
				g->m_pos.x = DISPLAY_WIDTH - 20;
			}
			if (g->m_pos.y <= 0)
			{
				g->m_pos.y = 20;
			}
			if (g->m_pos.x <= 0)
			{
				g->m_pos.x = 20;
			}
			state.gemsSpawned++;
		}
	}
}