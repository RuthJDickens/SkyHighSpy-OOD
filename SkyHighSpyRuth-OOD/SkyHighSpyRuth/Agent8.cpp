#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Agent8.h"
#include "Particles.h"
#include "Pieces.h"
#include "Gem.h"
#include "UserInterface.h"

Agent8::Agent8()
{
	m_type = OBJ_AGENT8;
	m_radius = 50;
	m_spriteId = Play::GetSpriteId("agent8_left");
}

void Agent8::Update(GameState& state)
{
	GameObject* rock = GetObjectOfType(OBJ_ATTACHED);

	switch (m_state)
	{
	case STATE_FLYING:
		StateFlying(state);

		break;

	case STATE_ATTACHED:
		StateAttached(state);

		break;

	case STATE_DEAD:
		StateDead(state);

		break;

	case STATE_START:
		StateStart(state);

		break;
	}
}

void Agent8::StateFlying(GameState& state)
{
	//Movement
	m_spriteId = Play::GetSpriteId("agent8_fly");
	m_velocity.x = m_flyingSpeed * sin(m_rotation);
	m_velocity.y = m_flyingSpeed * -cos(m_rotation);
	m_oldPos = m_pos;
	m_pos += m_velocity;
	m_drawOrder = 1;
	Particles::Spawn(state);
	if (Play::KeyDown(VK_RIGHT))
	{
		m_rotation += 0.05;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		m_rotation += -0.05;
	}
	LeavingArea();

	//Landing on another asteroid
	std::vector<GameObject*> vRocks;
	GetObjectList(OBJ_ASTEROID, vRocks);
	for (GameObject* rock : vRocks)
	{
		if (IsColliding(rock))
		{
			m_state = STATE_ATTACHED;
			m_spriteId = Play::GetSpriteId("agent8_left");
			rock->SetType(OBJ_ATTACHED);
			//Point Agent in direction of where he was
			float xdiff = m_pos.x - m_oldPos.x;
			float ydiff = m_pos.y - m_oldPos.y;
			m_rotation = atan2(ydiff, xdiff) - (PLAY_PI / 2);
		}
	}

	//Hitting a deadly meteor
	std::vector<GameObject*> vMeteors;
	GetObjectList(OBJ_METEOR, vMeteors);
	for (GameObject* m : vMeteors)
	{
		if (IsColliding(m))
		{
			Play::PlayAudio("combust");
			m_state = STATE_DEAD;
		}
	}

	//Collecting gems
	std::vector<GameObject*> vGems;
	GetObjectList(OBJ_GEM, vGems);
	for (GameObject* gem : vGems)
	{
		if (IsColliding(gem))
		{
			Gem* g = dynamic_cast<Gem*>(gem);
			if (!g->IsHidden())
			{
				state.score++;
				Play::PlayAudio("collect");
				Particles* ring = new Particles(gem->GetPosition(), 0.1, "ring");
				ring->SetScale(0.25);
				gem->SetInactive();
			}
		}
	}
}

void Agent8::StateAttached(GameState& state)
{
	GameObject* rock = GetObjectOfType(OBJ_ATTACHED);
	m_pos = rock->GetPosition();
	m_rotation += m_rotSpeed;
	m_drawOrder = rock->GetDrawOrder();
	//Animation
	m_framePos += m_animSpeed;
	if (m_framePos > 1)
	{
		m_frame++;
		m_framePos -= 1;
	}
	//Left and right movement
	if (Play::KeyDown(VK_RIGHT))
	{
		m_rotSpeed = 0.05;
		m_spriteId = Play::GetSpriteId("agent8_right_7");
		m_animSpeed = 0.5;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		m_rotSpeed = -0.05;
		m_spriteId = Play::GetSpriteId("agent8_left_7");
		m_animSpeed = 0.5;
	}
	else
	{
		m_rotSpeed = 0;
		m_animSpeed = 0;
	}

	//Launch from asteroid
	if (Play::KeyPressed(VK_SPACE))
	{
		m_state = STATE_FLYING;
		Play::PlayAudio("explode");
		m_pos.x += 20 * sin(m_rotation);
		m_pos.y += 20 * -cos(m_rotation);
		Pieces::Spawn(state);
		Gem::Spawn(state);
		rock->SetInactive();
	}
}

void Agent8::StateDead(GameState& state)
{
	m_spriteId = Play::GetSpriteId("agent8_dead");
	m_animSpeed = 1;
	m_velocity.x = (m_flyingSpeed*2) * sin(m_rotation);
	m_velocity.y = (m_flyingSpeed*2) * -cos(m_rotation);
	m_oldPos = m_pos;
	m_pos += m_velocity;
	LeavingArea();
	//Restart current level
	if (Play::KeyPressed(VK_SPACE))
	{
		Restart();
		m_spriteId = Play::GetSpriteId("agent8_left_7");
		m_animSpeed = 0;
	}
}

void Agent8::StateStart(GameState& state)
{
	//Attach to asteroid
	GameObject* rock = GetObjectOfType(OBJ_ATTACHED);
	m_pos = rock->GetPosition();
	m_drawOrder = rock->GetDrawOrder();

	//Instructions
	GameObject* text = GetObjectOfType(OBJ_UI);
	UserInterface* UI = dynamic_cast<UserInterface*>(text);
	UI->SetStart();

	//Start Game
	if (Play::KeyPressed(VK_SPACE))
	{
		m_state = STATE_ATTACHED;
		UI->SetPlaying();
	}
}

void Agent8::Draw(GameState& state)
{
	Play::DrawSpriteRotated(m_spriteId, m_pos, m_frame, m_rotation, 1.0f);
}