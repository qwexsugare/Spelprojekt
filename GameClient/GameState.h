#pragma once

#include "State.h"
#include "Entity.h"
#include "Client.h"
#include "TextInput.h"
//#include "HudMenu.h"

class GameState : public State
{
private:
	//HudMenu *m_hud;
	
	Text* m_fpsText;
	TextInput* m_emilmackesFpsText;
	vector<Entity*> m_entities;
	float m_rotation;
	Terrain* m_terrain;
	int m_testSound;
	Client *m_network;

	Sprite *s;

	void end();
public:
	GameState();
	~GameState();

	StateEnum nextState();
	void update(float _dt);
};