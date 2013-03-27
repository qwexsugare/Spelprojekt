#include "EndState.h"
#include "Graphics.h"
#include "SoundWrapper.h"
#include "MyAlgorithms.h"

EndState::EndState(NetworkEndGameMessage endMessage,MissionEndMessage mem) : State(State::END)
{
	stringstream ss;
	int graphics = g_configFile->getScreenSize().y;
	int windowed = g_configFile->getWindowed();
	m_changePosY= 1.0f;
	m_fontsize = 1.0f;
	m_graphicstext ="1080";
	if (graphics == 1080)
	{
		m_changePosY= 1.0f;
		m_graphicstext ="1080";
		if (windowed == 1)
		{
			m_fontsize = 1;
		}
		else
		{
			m_fontsize =1;
		}
	}
	if (graphics == 900)
	{
		m_changePosY= 0.833333333334f;
		m_graphicstext ="900";
		if (windowed == 1)
		{
			m_fontsize = 1;
		}
		else
		{
			m_fontsize = 0.833333333334f;
		}
	}
	if (graphics == 720)
	{
		m_changePosY = 0.66666666666667f;
		m_graphicstext ="720";
		if (windowed == 1)
		{
			m_fontsize = 1;
		}
		else
		{
			m_fontsize = 0.66666666666667f;
		}
	}
	if(endMessage.getIsAtWave()<0)
	{
		this->m_background = g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-END-1.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);
		this->m_resultText = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", "YOU LEFT THE GAME, NOOB", INT2(120*m_changePosY,100), 150*m_fontsize);

		// Music
		m_music = createSoundHandle("music/defeat.wav", true, false);

		this->m_nrOfPlayers = 0;
	}
	else
	{
		if(endMessage.getVictory() == true)
		{
			this->m_background = g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-END-1.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);
			this->m_resultText = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", "VICTORY", INT2(120*m_changePosY,100), 150*m_fontsize);

			ss<<"Lives remaining: "<<endMessage.getStartLife();
			this->m_resultMoreInfo = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", ss.str(), INT2(120*m_changePosY,250), 50*m_fontsize);
			ss.clear();
			ss.str("");

			// Music
			switch(random(0, 1))
			{
			case 0:
				m_music = createSoundHandle("music/win1.wav", true, false);
				break;
			case 1:
				m_music = createSoundHandle("music/win2.wav", true, false);
				break;
			}
		}
		else
		{
			this->m_background = g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-END-0.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);
			this->m_resultText = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", "DEFEAT", INT2(120*m_changePosY,100), 150*m_fontsize);

			ss<<"Wave: "<<endMessage.getIsAtWave();
			this->m_resultMoreInfo = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", ss.str(), INT2(120*m_changePosY,200), 50*m_fontsize);
			ss.clear();
			ss.str("");

			// Music
			m_music = createSoundHandle("music/defeat.wav", true, false);
		}

		ss<<"Time played: "<<(int)endMessage.getTimePlayed()/60<<" minutes "<<(int)endMessage.getTimePlayed()%60<<" seconds";
		this->m_timeplayed = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", ss.str(), INT2(120*m_changePosY,225), 50*m_fontsize);
		ss.clear();
		ss.str("");

		this->m_nrOfPlayers = endMessage.getPlayers().size();

		int jumpRow=0;
		int jumpColumn=0;
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

			this->m_playerInfo[i] = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", ss.str(), INT2((120+jumpColumn*400)*m_changePosY,325 + jumpRow * 200), 75*m_fontsize);
			ss.clear();
			ss.str("");

			ss<<"Demons killed: "<<endMessage.getPlayers()[i].getDeamonsKilled();
			this->m_playerMonstersKilled[i] = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", ss.str(), INT2((120+jumpColumn*400)*m_changePosY,375 + jumpRow * 200), 50*m_fontsize);
			ss.clear();
			ss.str("");

			ss<<"Damage done: "<<endMessage.getPlayers()[i].getPhysicalDamageDealth() + endMessage.getPlayers()[i].getMentalDamageDealth()<<" (physical: "<<endMessage.getPlayers()[i].getPhysicalDamageDealth()<<", mental: "<<endMessage.getPlayers()[i].getMentalDamageDealth()<<")";
			this->m_playerDamageDone[i] = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", ss.str(), INT2((120+jumpColumn*400)*m_changePosY,405 + jumpRow * 200), 50*m_fontsize);
			ss.clear();
			ss.str("");

			ss<<"Damage taken: "<<endMessage.getPlayers()[i].getPhysicalDamageRecived() + endMessage.getPlayers()[i].getMentalDamageRecived()<<" (physical: "<<endMessage.getPlayers()[i].getPhysicalDamageRecived()<<", mental: "<<endMessage.getPlayers()[i].getMentalDamageRecived()<<")";
			this->m_playerDamageTaken[i] = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", ss.str(), INT2((120+jumpColumn*400)*m_changePosY,435 + jumpRow * 200), 50*m_fontsize);
			ss.clear();
			ss.str("");

			ss<<"Resources collected: "<<endMessage.getPlayers()[i].getGoldCollected();
			this->m_playerResourcesCollected[i] = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", ss.str(), INT2((120+jumpColumn*400)*m_changePosY,465 + jumpRow * 200), 50*m_fontsize);
			ss.clear();
			ss.str("");

			ss << "Healed for: " << endMessage.getPlayers()[i].getHealedAmount();
			this->m_healedFor[i] =  g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", ss.str(), INT2((120+jumpColumn*400)*m_changePosY,495 + jumpRow * 200), 50*m_fontsize);
			ss.clear();
			ss.str("");

			jumpRow++;
			
			if(jumpRow==2)
			{
				jumpColumn++;
				jumpRow=0;
			}
			if(jumpColumn==2)
				jumpColumn=0;
		}
		
		this->missionText = g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", "Missions", INT2(120*m_changePosY,750), 150*m_fontsize);
		
		for(int i=0;i<mem.nrOfMissions();i++)
		{
			string fullMissionString = mem.getMissionName(i)+":  " +mem.getMissionStatus(i);
			textures.push_back(g_graphicsEngine->createMyText("text3.png", "text/", "offsets.txt", fullMissionString, INT2(120*m_changePosY,850+i*75), 50*m_fontsize));
		}
	}
	playSound(m_music);
	this->m_mainMenuButton = new Button();
	this->m_mainMenuButton->Init(FLOAT2(0.45f,  -0.8f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,1,5);
}

EndState::~EndState()
{
	stopSound(m_music);
	deactivateSound(m_music);
	g_graphicsEngine->removeSprite(this->m_background);
	g_graphicsEngine->removeMyText(this->m_resultText);
	g_graphicsEngine->removeMyText(this->m_resultMoreInfo);
	g_graphicsEngine->removeMyText(this->m_timeplayed);
	g_graphicsEngine->removeMyText(this->missionText);
	for(int i=0;i<this->textures.size();i++)
	{
		g_graphicsEngine->removeMyText(this->textures[i]);
	}

	for(int i = 0; i < this->m_nrOfPlayers; i++)
	{
		g_graphicsEngine->removeMyText(this->m_playerInfo[i]);
		g_graphicsEngine->removeMyText(this->m_playerDamageDone[i]);
		g_graphicsEngine->removeMyText(this->m_playerDamageTaken[i]);
		g_graphicsEngine->removeMyText(this->m_playerMonstersKilled[i]);
		g_graphicsEngine->removeMyText(this->m_playerResourcesCollected[i]);
		g_graphicsEngine->removeMyText(this->m_healedFor[i]);
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