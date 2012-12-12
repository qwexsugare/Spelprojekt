#pragma once

#include "State.h"
#include "Entity.h"
#include "NetworkClient.h"

class GameState : public State
{
private:
	Text* m_fpsText;
	vector<Entity*> m_entities;
	SpriteSheet *m_testSprite;
	float m_rotation;

	NetworkClient *m_network;
	void end();
public:
	GameState();
	~GameState();

	State* nextState();
	void update(float _dt);
};