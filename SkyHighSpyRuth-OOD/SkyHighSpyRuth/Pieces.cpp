#include "Play.h"
#include "MainGame.h"
#include "GameObject.h"
#include "Pieces.h"

Pieces::Pieces(Point2f pos)
{
	m_pos = pos;
	m_speed = 10;
	m_type = OBJ_PIECES;
}

void Pieces::Update(GameState& state)
{
	//Movement of pieces
	{
		GameObject& obj_piece = Play::GetGameObject(id);
		Play::UpdateGameObject(obj_piece);
		if (!Play::IsVisible(obj_piece))
		{
			Play::DestroyGameObject(id);
		}
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
		rad += 0.5f;
	}
}

void Pieces::Draw(GameState& state)
{
	Play::DrawSpriteRotated(Play::GetSpriteId("asteroid_pieces"), m_pos, m_frame, m_rotation, 1.0f);
}