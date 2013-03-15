#include "EndState.h"
#include "Graphics.h"

EndState::EndState(NetworkEndGameMessage endMessage)
{
	stringstream ss;

	if(endMessage.getVictory() == true)
	{
		this->m_background = g_graphicsEngine->createSprite("menu_textures\\MENU-END-1.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);
		this->m_resultText = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", "VICTORY", INT2(120,100), 150);

		ss<<"Lives remaining: "<<endMessage.getStartLife();
		this->m_resultMoreInfo = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", ss.str(), INT2(120,250), 50);
		ss.clear();
		ss.str("");
	}
	else
	{
		this->m_background = g_graphicsEngine->createSprite("menu_textures\\MENU-END-0.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);
		this->m_resultText = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", "DEFEAT", INT2(120,100), 150);

		ss<<"Wave: "<<endMessage.getIsAtWave();
		this->m_resultMoreInfo = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", ss.str(), INT2(120,200), 50);
		ss.clear();
		ss.str("");
	}

	ss<<"Time played: "<<endMessage.getTimePlayed()<<" seconds";
	this->m_timeplayed = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", ss.str(), INT2(120,225), 50);
	ss.clear();
	ss.str("");

	this->m_nrOfPlayers = endMessage.getPlayers().size();

	for(int i = 0; i < this->m_nrOfPlayers && i < 4; i++)
	{
		ss<<endMessage.getPlayers()[i].getPlayerName()<<", ";

		switch(endMessage.getPlayers()[i].getPlayerHero())
		{
		case StatisticsPlayer::OFFICER:
			ss<<"Officer";
			break;
		case StatisticsPlayer::RED_KNIGHT:
			ss<<"Red Knight";
			break;
		case StatisticsPlayer::ENGINEER:
			ss<<"Engineer";
			break;
		case StatisticsPlayer::DOCTOR:
			ss<<"Doctor";
			break;
		case StatisticsPlayer::THE_MENTALIST:
			ss<<"The Mentalist";
			break;
		}

		this->m_playerInfo[i] = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", ss.str(), INT2(120,275 + i * 125), 75);
		ss.clear();
		ss.str("");

		ss<<"Demons killed: "<<endMessage.getPlayers()[i].getDeamonsKilled();
		this->m_playerMonstersKilled[i] = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", ss.str(), INT2(120,325 + i * 125), 50);
		ss.clear();
		ss.str("");

		ss<<"Damage done: "<<endMessage.getPlayers()[i].getPhysicalDamageDealth() + endMessage.getPlayers()[i].getMentalDamageDealth()<<" (physical: "<<endMessage.getPlayers()[i].getPhysicalDamageDealth()<<", mental: "<<endMessage.getPlayers()[i].getMentalDamageDealth()<<")";
		this->m_playerDamageDone[i] = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", ss.str(), INT2(120,355 + i * 125), 50);
		ss.clear();
		ss.str("");

		ss<<"Damage taken: "<<endMessage.getPlayers()[i].getPhysicalDamageRecived() + endMessage.getPlayers()[i].getMentalDamageRecived()<<" (physical: "<<endMessage.getPlayers()[i].getPhysicalDamageRecived()<<", mental: "<<endMessage.getPlayers()[i].getMentalDamageRecived()<<")";
		this->m_playerDamageTaken[i] = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", ss.str(), INT2(120,385 + i * 125), 50);
		ss.clear();
		ss.str("");

		ss<<"Resources collected: "<<endMessage.getPlayers()[i].getGoldCollected();
		this->m_playerResourcesCollected[i] = g_graphicsEngine->createMyText("text1.png", "text/", "offsets.txt", ss.str(), INT2(120,415 + i * 125), 50);
		ss.clear();
		ss.str("");
	}

	this->m_mainMenuButton = new Button();
	this->m_mainMenuButton->Init(FLOAT2(0.140625f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,1,5);
}

EndState::~EndState()
{
	g_graphicsEngine->removeSprite(this->m_background);
	g_graphicsEngine->removeMyText(this->m_resultText);
	g_graphicsEngine->removeMyText(this->m_resultMoreInfo);
	g_graphicsEngine->removeMyText(this->m_timeplayed);

	for(int i = 0; i < this->m_nrOfPlayers; i++)
	{
		g_graphicsEngine->removeMyText(this->m_playerInfo[i]);
		g_graphicsEngine->removeMyText(this->m_playerDamageDone[i]);
		g_graphicsEngine->removeMyText(this->m_playerDamageTaken[i]);
		g_graphicsEngine->removeMyText(this->m_playerMonstersKilled[i]);
		g_graphicsEngine->removeMyText(this->m_playerResourcesCollected[i]);
	}

	delete this->m_mainMenuButton;
}

State::StateEnum EndState::nextState()
{
	return State::MAIN_MENU;
}

void EndState::update(float _dt)
{
	this->m_mainMenuButton->Update();

	if(this->m_mainMenuButton->isClicked() == true)
	{
		this->setDone(true);
	}
}