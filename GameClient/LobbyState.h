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
	vector<bool> m_hostsSuperVector; // Used for checking if all players are ready (For the Host only).
	bool m_hostMayStartGame; // Stores a bool which determines if the host can start the game or not.
	bool m_clientMayReady; // Stores a bool which determines if the client can ready up or not.

	LobbyMenu *m_menu;
	StateEnum  m_nextState;
	Client* m_network;
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
	bool m_sliderMove;

public:
	LobbyState();
	LobbyState(Client* _network);
	~LobbyState();

	void update(float _dt);
	StateEnum nextState();
	string getMapName();
};