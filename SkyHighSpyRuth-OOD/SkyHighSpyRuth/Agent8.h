#pragma once

class Agent8 : public GameObject
{
	enum States
	{
		STATE_FLYING = 0,
		STATE_ATTACHED,
		STATE_DEAD,
		STATE_START,
	};	

private:
	int m_flyingSpeed = 7;
	States m_state = STATE_START;
public:
	Agent8();
	void Update(GameState& state);
	void Draw(GameState& state);
	void StateFlying(GameState& state);
	void StateAttached(GameState& state);
	void StateDead(GameState& state);
	void StateStart(GameState& state);
};

