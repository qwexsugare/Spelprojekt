#pragma once

#include "State.h"
#include "Entity.h"

class GameState : public State
{
private:
	Text* m_fpsText;
	vector<Entity*> m_entities;
	SpriteSheet *m_testSprite;
	float m_rotation;
public:
	GameState();
	~GameState();

	void update(float _dt);
	bool done();
	State* nextState();
};