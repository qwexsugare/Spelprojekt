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
public:
	LoadingState(Client* _network);
	~LoadingState();

	State::StateEnum nextState();
	void update(float _dt);
};

