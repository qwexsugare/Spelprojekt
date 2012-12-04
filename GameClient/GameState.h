#pragma once

#include "State.h"
#include "Entity.h"
#include "Graphics.h"

class GameState : public State
{
private:
	Text* m_fpsText;
	vector<Entity*> m_entities;
public:
	GameState();
	~GameState();

	void update(float _dt);
	bool done();
	State* nextState();
};