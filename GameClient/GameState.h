#pragma once

#include "State.h"
#include "Entity.h"
#include "Client.h"
#include "TextInput.h"
#include "TextLabel.h"
#include "ModelIdHolder.h"
#include "Minimap.h"
#include "HudMenu.h"
//#include "Cursor.h"

class GameState : public State
{
private:
	HudMenu *m_hud;
	Text* m_fpsText;
	TextInput* m_emilmackesFpsText;
	TextLabel* m_emilsFps;
	vector<Entity*> m_entities;
	float m_rotation;
	Terrain* m_terrain;
	Client *m_network;
	ModelIdHolder m_modelIdHolder;
	Minimap* m_minimap;
	vector<Road*> m_roads;
	Model* m_testModel;

	SpotLight* s;
	//Cursor m_cursor;

	void end();
	void importMap(string _map);
public:
	GameState();
	~GameState();

	StateEnum nextState();
	void update(float _dt);
};