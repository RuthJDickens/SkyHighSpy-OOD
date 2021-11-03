#pragma once

class Asteroid : public GameObject
{
private:

public:
	Asteroid(Point2f pos, int rotation);
	void Update(GameState& state);
	static void Spawn(GameState& state);
	void Draw(GameState& state);
};

