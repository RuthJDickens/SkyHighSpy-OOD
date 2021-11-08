#pragma once

class UserInterface : public GameObject
{
private:
	bool m_statePlay{ false };
	int m_score{ 0 };
	int m_gemNumber{ 0 };
	int m_level{ 0 };
	Point2f m_centreText{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 };
	Point2f m_subCentreText{ DISPLAY_WIDTH / 2 - 17, DISPLAY_HEIGHT / 2 + 100 };
	Point2f m_bottomText{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 50 };

public:
	UserInterface();
	void Update(GameState& state);
	void Draw(GameState& state);
	void Start();
	void Score();
	void SetPlaying() { m_statePlay = true; };
	void SetStart() { m_statePlay = false; };
};

