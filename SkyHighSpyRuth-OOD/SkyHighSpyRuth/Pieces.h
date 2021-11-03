#pragma once

class Pieces : public GameObject
{
private:

public:
	Pieces(Point2f pos);
	void Update(GameState& state);
	static void Spawn(GameState& state);
	void Draw(GameState& state);
};

