#pragma once

#include "State.h"
#include "GraphicsHandler.h"

class GameState : public State
{
private:
	Model* m_testModel;
	Text* m_fpsText;
	Sprite *m_testSprite;
	float m_rotation;
public:
	GameState();
	~GameState();

	void update(float _dt);
	void render();
	bool done();
	State* nextState();
};