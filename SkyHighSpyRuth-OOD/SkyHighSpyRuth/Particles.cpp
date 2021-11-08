#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Particles.h"

Particles::Particles(Point2f pos, float scaleIncrement, const char* spriteName)
{
	m_pos = pos;
	m_scaleIncrement = scaleIncrement;
	m_type = OBJ_PARTICLES;
	m_spriteId = Play::GetSpriteId(spriteName);
}

void Particles::Spawn(GameState& state)
{
	GameObject* agent = GetObjectOfType(OBJ_AGENT8);
	int posOffset_x = Play::RandomRoll(5);
	int posOffset_y = Play::RandomRoll(5);
	Particles* particle = new Particles({ agent->GetOldPosition().x + posOffset_x, agent->GetOldPosition().y + posOffset_y }, -0.02, "particle");
	particle->m_drawOrder = agent->GetDrawOrder() + 1;
}

void Particles::Update(GameState& state)
{
	m_scale += m_scaleIncrement;

	//Decreasing in size - dust particles
	if (m_scaleIncrement <= 0)
	{
		if (m_scale <= 0.05)
		{
			m_active = { false };
		}
	}
	//Increasing in size - ring effects
	else
	{
		if (m_scale >= 1.5)
		{
			m_active = { false };
		}
	}
}

void Particles::Draw(GameState& state)
{
	Play::DrawSpriteRotated(m_spriteId, m_pos, 0, 0, m_scale, 1.0f);
}