#pragma once

#include "state.h"
#include "ModelIdHolder.h"
#include "Sprite.h"
#include "Button.h"
#include "client.h"

class LoadingState :
	public State
{
private:
	Sprite* m_img;
	ModelIdHolder m_modelIdHolder;
	int m_speech;
	Button* m_skip;
	Client* m_network;
	string m_mapName;
public:
	LoadingState(Client* _network, string _mapName);
	~LoadingState();

	State::StateEnum nextState();
	void update(float _dt);

	string getMapName();
};

