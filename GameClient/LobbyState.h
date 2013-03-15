#pragma once

#include "State.h"
#include "LobbyMenu.h"
#include "client.h"
#include "ModelIdHolder.h"
#include "Room.h"

#define numCharacters 5

class LobbyState : public State
{
private:
	LobbyMenu *m_menu;
	StateEnum  m_nextState;
	Client* m_network;
	int m_currentHeroSelected;
	Hero::HERO_TYPE m_heroType;
	string mapName;
	ModelIdHolder m_modelIdHolder;
	Room* m_officer;
	Room* m_redKnight;
	Room* m_engi;
	Room* m_doctor;
	Room* m_mentalist;
	Room* m_emtyRoom;
	DirectionalLight* dl;
	float step;
	float speed;
	float cameraRealPos;
	float distToSlider;
	int m_playerId;
	
	ChainEffect* test;

public:
	LobbyState();
	LobbyState(Client* _network);
	~LobbyState();

	void update(float _dt);
	StateEnum nextState();
	string getMapName();
};