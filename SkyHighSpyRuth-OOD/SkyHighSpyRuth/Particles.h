#pragma once

class Particles : public GameObject
{
private:
	float m_scale{ 1 };
	float m_scaleIncrement{ 0 };
public:
	Particles(Point2f pos, float scaleIncrement, const char* spriteName);
	void SetScale(int scale) { m_scale = scale; };
	void Update(GameState& state);
	static void Spawn(GameState& state);
	void Draw(GameState& state);
};

