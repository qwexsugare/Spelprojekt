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
#include "PlayerInfo.h"
//#include "Cursor.h"

class GameState : public State
{
private:
	vector<PLAYER_INFO> m_playerInfos;
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
	unsigned int m_yourId;

	SpotLight* s;
	//Cursor m_cursor;

	bool m_idle;
	float m_idleSoundTimer;

	// Sounds
	int m_idleSound;
	static const int NR_OF_ATTACK_SOUNDS = 3;
	int m_attackSounds[NR_OF_ATTACK_SOUNDS];

	void end();
	void importMap(string _map);
public:
	static const int IDLE_SOUND_DELAY = 7;

	GameState(Client *_network);
	~GameState();

	StateEnum nextState();
	void update(float _dt);
};