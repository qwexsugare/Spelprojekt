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
#include "Text.h"
#include "AmbientSoundsManager.h"
//#include "Cursor.h"

class GameState : public State
{
private:
	vector<PLAYER_INFO> m_playerInfos;
	HudMenu *m_hud;
	Text* m_fpsText;
	Terrain* m_terrain;
	Client *m_network;
	ModelIdHolder m_modelIdHolder;
	Minimap* m_minimap;
	vector<Road*> m_roads;
	vector<ClientSkillEffect*> m_ClientSkillEffects;
	ClientEntityHandler *m_clientEntityHandler;
	ParticleEngine *testParticleSystem;
	unsigned int m_yourId;

	bool m_idle;
	float m_idleSoundTimer;

	// Sounds
	AmbientSoundsManager m_ambientSoundsManager;
	int m_lowHealthSound;
	static const int LOW_HEALTH_SOUND_DELAY = 10;
	float m_lowHealthSoundDelayTimer;
	int m_idleSound;
	static const int NR_OF_ATTACK_SOUNDS = 3;
	int m_attackSounds[NR_OF_ATTACK_SOUNDS];
	static const int NR_OF_MOVE_SOUNDS = 3;
	int m_moveSounds[NR_OF_MOVE_SOUNDS];
	static const int ATTACK_SOUND_DELAY = 5;
	float m_attackSoundTimer;
	vector<int> m_timeIsMoneySounds;
	int m_churchSound;
	bool m_idling;

	void importMap(string _map);
	void playPursueSound(unsigned int _speakerId);
	void playWallDeathSound(FLOAT3 _position);
public:
	static const int IDLE_SOUND_DELAY = 30;

	GameState(Client *_network);
	~GameState();

	StateEnum nextState();
	void update(float _dt);
};