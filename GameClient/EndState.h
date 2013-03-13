#pragma once

#include "state.h"
#include "Graphics.h"
#include "NetworkEndGameMessage.h"
#include "Button.h"

class EndState : public State
{
private:
	Sprite *m_background;
	MyText *m_resultText;
	MyText *m_resultMoreInfo;
	MyText *m_timeplayed;

	int m_nrOfPlayers;
	MyText *m_playerInfo[4];
	MyText *m_playerMonstersKilled[4];
	MyText *m_playerDamageDone[4];
	MyText *m_playerDamageTaken[4];
	MyText *m_playerResourcesCollected[4];

	Button *m_mainMenuButton;
public:
	EndState(NetworkEndGameMessage endMessage);
	~EndState();

	StateEnum nextState();
	void update(float _dt);
};

