#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Pieces.h"

Pieces::Pieces(Point2f pos)
{
	m_pos = pos;
	m_speed = 10;
	m_type = OBJ_PIECES;
	m_spriteId = Play::GetSpriteId("asteroid_pieces");
}

void Pieces::Update(GameState& state)
{
	//Movement of pieces
	m_velocity.x = m_speed * cos(m_rotation);
	m_velocity.y = m_speed * -sin(m_rotation);
	m_pos += m_velocity;

	int width = Play::GetSpriteWidth(m_spriteId);
	int height = Play::GetSpriteHeight(m_spriteId);

	if (m_pos.x >= DISPLAY_WIDTH + width || m_pos.x <= -width)
	{
		m_active = { false };
	}
	if (m_pos.y >= DISPLAY_HEIGHT + height || m_pos.y <= -height)
	{
		m_active = { false };
	}
}

void Pieces::Spawn(GameState& state)
{
	float rad = 0.25f;
	//Three pieces in three opposite directions
	for (int i = 1; i <= 3; i++)
	{
		GameObject* rock = GetObjectOfType(OBJ_ATTACHED);
		Pieces* object = new Pieces(rock->GetPosition());
		object->SetRotation(rad);
		object->m_frame = i;
		object->m_drawOrder = 2;
		rad += 0.5f;
	}
}

void Pieces::Draw(GameState& state)
{
	Play::DrawSpriteRotated(m_spriteId, m_pos, m_frame, m_rotation, 1.0f);
}