#include "Play.h"
#include "GameObject.h"
#include "MainGame.h"
#include "UserInterface.h"

UserInterface::UserInterface()
{
	m_type = OBJ_UI;
}

void UserInterface::Update(GameState& state)
{
	m_score = state.score;
	m_level = state.startingLevel - 1;
	m_gemNumber = state.gemNumber;
}

void UserInterface::Draw(GameState& state)
{
	if (m_statePlay)
	{
		Score();
	}
	else
	{
		Start();
	}
}

void UserInterface::Start()
{
	Play::DrawFontText("151px", "Level " + std::to_string(m_level), m_centreText, Play::CENTRE);
	Play::DrawFontText("64px", "Collect " + std::to_string(m_gemNumber) + " gem(s)", m_subCentreText, Play::CENTRE);
	Play::DrawFontText("64px", "Left and right keys to move, spacebar to jump", m_bottomText, Play::CENTRE);
}

void UserInterface::Score()
{
	Play::DrawFontText("105px", "Gems = " + std::to_string(m_score), { 50,50 }, Play::LEFT);
}

