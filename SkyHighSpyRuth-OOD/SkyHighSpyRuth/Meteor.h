#pragma once

class Meteor : public Asteroid
{
private:

public:
	Meteor(Point2f pos, int rotation);
	static void Spawn(GameState& state);

};

