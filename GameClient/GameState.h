#pragma once

#include "State.h"
#include "Entity.h"
#include "Client.h"
#include "TextInput.h"
#include "TextLabel.h"
#include "ModelIdHolder.h"
#include "Minimap.h"
#include "HudMenu.h"
#include "ClientSkillEffect.h"
#include "ClientEntityHandler.h"
#include "Hero.h"
//#include "Cursor.h"

class GameState : public State
{
private:
	HudMenu *m_hud;
	Text* m_fpsText;
	float m_rotation;
	Terrain* m_terrain;
	Client *m_network;
	ModelIdHolder m_modelIdHolder;
	Minimap* m_minimap;
	vector<Road*> m_roads;
	vector<ClientSkillEffect*> m_ClientSkillEffects;
	ClientEntityHandler *m_clientEntityHandler;
	ParticleEngine *testParticleSystem;
	Hero::HERO_TYPE m_heroType;
	float m_timeSinceLastAction;

	SpotLight* s;
	//Cursor m_cursor;

	// Sounds
	int m_idleSound;

	void end();
	void importMap(string _map);
public:
	static const int TIME_TO_IDLE = 7;

	GameState(Client *_network, Hero::HERO_TYPE _heroType);
	~GameState();

	StateEnum nextState();
	void update(float _dt);
};