#pragma once

class Gem : public GameObject
{
private:
	bool m_hidden{ true };

public:
	Gem(Point2f pos);
	bool IsHidden() const { return m_hidden; };
	void Update(GameState& state);
	void Draw(GameState& state);
	static void Spawn(GameState& state);
};

