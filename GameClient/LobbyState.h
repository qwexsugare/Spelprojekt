#pragma once

#include "State.h"
#include "LobbyMenu.h"
#include "client.h"
#include "ModelIdHolder.h"

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
	Model* cube[6];
	Model* officer;
	Model* redKnight;
	Model* engi;
	Model* doctor;
	Model* mentalist;
	PointLight* pl[6];
	DirectionalLight* dl;
	Model* boll;
	float step;
	float speed;
public:
	LobbyState();
	LobbyState(Client* _network);
	~LobbyState();

	void update(float _dt);
	StateEnum nextState();
	string getMapName();
};