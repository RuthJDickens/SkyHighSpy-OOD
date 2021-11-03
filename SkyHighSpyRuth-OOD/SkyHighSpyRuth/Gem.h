#pragma once

class Gem : public GameObject
{
private:
	bool m_hidden{ true };

public:
	Gem(Point2f pos);
	void Update(GameState& state);
	void Draw(GameState& state);
	static void Spawn(GameState& state);
};

