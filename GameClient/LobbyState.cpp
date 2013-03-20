#include "LobbyState.h"
#include "GameState.h"
#include "Input.h"
#include "NetworkReadyMessage.h"

LobbyState::LobbyState() : State(State::LOBBY)
{
	
}

LobbyState::LobbyState(Client* _network) : State(State::LOBBY)
{
	this->m_network = _network;
	this->m_sliderMove = false;
	m_heroType = Hero::HERO_TYPE::NONE;

	g_graphicsEngine->setSSAO(10, 0.01f, 0, 0.4f);
	//pl[0] = g_graphicsEngine->createPointLight(FLOAT3(0.0f, 1.0f, 4.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	dl = g_graphicsEngine->createDirectionalLight(FLOAT3(0.0f, 1.0f, 1.0f), FLOAT3(0.3f, 0.3f, 0.3f), FLOAT3(0.01f, 0.01f, 0.01f), FLOAT3(0.0f, 0.0f, 0.0f));
	g_graphicsEngine->getCamera()->set(FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(0.0f, 0.0f, 1.0f), FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(1.0f, 0.0f, 0.0f));

	speed = 2.5f;

	// 1.899036
	step = 1.899036f;
	float x = -1.4f;
	float y =  -0.5f;
	float z = 6;
	float inLightZ = -0.5;
	float inLightY = 1.6f;
	float frontLightZ = -0.5f;
	float frontLightY = 0.5f;
	
	this->m_officer		= new Room(0, 95, "color", "", FLOAT3(x, y, z), step);
	this->m_redKnight	= new Room(1, 96, "color", "", FLOAT3(x, y, z), step);
	this->m_engi		= new Room(2, 97, "color", "", FLOAT3(x, y, z), step);
	this->m_doctor		= new Room(3, 98, "color", "", FLOAT3(x, y, z), step);
	this->m_mentalist	= new Room(4, 99, "color", "", FLOAT3(x, y, z), step);
	this->m_emtyRoom	= new Room(5, "color", FLOAT3(x, y, z), step);

	this->m_officer->getCharacter()->getAnimation()->PlayLoop("OfficerIdle");
	this->m_redKnight->getCharacter()->getAnimation()->PlayLoop("RedKnightIdle");
	this->m_engi->getCharacter()->getAnimation()->PlayLoop("EngiIdle");
	this->m_doctor->getCharacter()->getAnimation()->PlayLoop("DoctorIdle");
	this->m_mentalist->getCharacter()->getAnimation()->PlayLoop("MentalistIdle");
	
	this->cameraRealPos = 0;
	distToSlider = 0.0f;
	
	sf::Clock mySuperClock;
	while(m_network->networkWelcomeMessageEmpty() && mySuperClock.GetElapsedTime() < 60.0f){}
	if(m_network->networkWelcomeMessageEmpty())
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
		m_playerId = -1;
	}
	else
	{
		NetworkWelcomeMessage nwm = m_network->networkWelcomeMessageFront();
		this->mapName = nwm.getMapName();
		this->m_playerId = nwm.getPlayerId();
	}
	
	if(m_playerId == 0)
	{
		m_hostMayStartGame = true;
		m_menu = new LobbyMenu(true);
	}
	else
	{
		m_menu = new LobbyMenu(false);
		m_clientMayReady = false;
	}
}

LobbyState::~LobbyState()
{
	delete this->m_menu;

	delete m_officer;
	delete m_redKnight;
	delete m_engi;
	delete m_doctor;
	delete m_mentalist;
	delete m_emtyRoom;

	g_graphicsEngine->removeDirectionalLight(dl);
	//g_graphicsEngine->removeChainEffect(test);
}

void LobbyState::update(float _dt)
{
	if(m_playerId == 0)
		m_menu->Update(_dt, m_hostMayStartGame);
	else
		m_menu->Update(_dt, m_clientMayReady);

	if(GetKeyState(VK_LEFT) < 0)
	{
		if(g_graphicsEngine->getCamera()->getPos().x >= 0)
		{
			FLOAT2 newPos = FLOAT2(g_graphicsEngine->getCamera()->getPos().x, g_graphicsEngine->getCamera()->getPos().y);
			g_graphicsEngine->getCamera()->set( newPos + FLOAT2(-speed * _dt, 0));
			//pl[0]->setPosition(pl[0]->getPosition() + FLOAT3(-0.05f, 0, 0));
		}
	}
	if(GetKeyState(VK_RIGHT) < 0)
	{
		if(g_graphicsEngine->getCamera()->getPos().x <= step*3)
		{
			FLOAT2 newPos = FLOAT2(g_graphicsEngine->getCamera()->getPos().x, g_graphicsEngine->getCamera()->getPos().y);
			g_graphicsEngine->getCamera()->set( newPos + FLOAT2(speed * _dt, 0));
			//pl[0]->setPosition(pl[0]->getPosition() + FLOAT3(0.05f, 0, 0));
		}
	}

	float max = step*3;
	float min = 0;


	float value = this->m_menu->getSlider()->GetValue();

	//camera linear velocity
	float camVel=0.8;
	//distance from the real camera pos to the slider pos
	distToSlider=abs(cameraRealPos-this->m_menu->getSlider()->GetValue() * max)*3;
	//if you are close enough, it will keep a constant speed before it stops
	if(distToSlider < 1.0)
		distToSlider = 1.0;

	//ugly solution for if the enterkey was pressed, fetch chat string
	if(m_menu->wasEnterPressed())
	{
		this->m_network->sendMessage(NetworkTextMessage(m_menu->getChatString()));
		m_menu->resetEnterPressed();
	}
	//camera real pos is the camera position, which tries to reach the position from the slider
	//if the real pos is inside a certain value, it wont move
	this->m_sliderMove = false;
	if(cameraRealPos > this->m_menu->getSlider()->GetValue() * max-0.05 && cameraRealPos < this->m_menu->getSlider()->GetValue() * max + 0.05)
	{
	}
	else
	{	//otherwise, move the cameras pos toward the slider
		if(cameraRealPos<this->m_menu->getSlider()->GetValue() * max)
			cameraRealPos+=_dt*camVel*distToSlider;
		else if(cameraRealPos>this->m_menu->getSlider()->GetValue() * max)
			cameraRealPos-=_dt*camVel*distToSlider;
		g_graphicsEngine->getCamera()->set(FLOAT2(cameraRealPos, 0));
		this->m_sliderMove = true;
	}

	float mouseX = (g_mouse->getPos().x / float(g_graphicsEngine->getScreenSize().x))*2-1;
	 max = step*5;
	if(g_mouse->isLButtonReleased() && mouseX >= -0.58f && mouseX <= 0.58f && !m_sliderMove)
	{
		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		float alve = 1.0f/5.0f;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
		float dist;
		if(m_officer->getRoom()->intersects(dist, pickOrig, pickDir))
		{
			this->m_heroType = Hero::OFFICER;
			m_network->sendMessage(NetworkSelectHeroMessage(0, this->m_menu->getCombat()));
			//this->m_menu->getSlider()->setValue(alve*0);
			this->m_menu->getSlider()->setPosition((m_officer->getRoom()->getPosition().x-step*2+0.6)/max);
			//this->m_menu->getSlider()->setPosition((m_officer->getRoom()->getPosition().x));
		} 
		else if(m_redKnight->getRoom()->intersects(dist, pickOrig, pickDir))
		{
			this->m_heroType = Hero::RED_KNIGHT;
			m_network->sendMessage(NetworkSelectHeroMessage(1, this->m_menu->getCombat()));
			//this->m_menu->getSlider()->setValue(alve*0);
			this->m_menu->getSlider()->setPosition((m_redKnight->getRoom()->getPosition().x-step*2)/max);
			//this->m_menu->getSlider()->setPosition((m_redKnight->getRoom()->getPosition().x));
		}
		else if(m_engi->getRoom()->intersects(dist, pickOrig, pickDir))
		{
			this->m_heroType = Hero::ENGINEER;
			m_network->sendMessage(NetworkSelectHeroMessage(2, this->m_menu->getCombat()));
			//this->m_menu->getSlider()->setValue(alve*2);
			this->m_menu->getSlider()->setPosition((m_engi->getRoom()->getPosition().x-step)/max);
			//this->m_menu->getSlider()->setPosition((m_engi->getRoom()->getPosition().x));
		}
		else if(m_doctor->getRoom()->intersects(dist, pickOrig, pickDir))
		{
			this->m_heroType = Hero::DOCTOR;
			m_network->sendMessage(NetworkSelectHeroMessage(3, this->m_menu->getCombat()));
			//this->m_menu->getSlider()->setValue(alve*3);
			this->m_menu->getSlider()->setPosition((m_doctor->getRoom()->getPosition().x-step)/max);
			//this->m_menu->getSlider()->setPosition((m_doctor->getRoom()->getPosition().x));
		}
		else if(m_mentalist->getRoom()->intersects(dist, pickOrig, pickDir))
		{
			this->m_heroType = Hero::THE_MENTALIST;
			m_network->sendMessage(NetworkSelectHeroMessage(4, this->m_menu->getCombat()));
			this->m_menu->getSlider()->setPosition((m_mentalist->getRoom()->getPosition().x-step)/max);
			//this->m_menu->getSlider()->setValue(alve*4);
			//this->m_menu->getSlider()->setPosition((m_mentalist->getRoom()->getPosition().x));
		}
	}
	
	if(m_menu->MainMenuIsDown())
	{
		sf::Packet dispack;
		dispack << (int)NetworkMessage::PLAYERDISCONNECTED;
		this->m_network->sendPacket(dispack);
		this->m_network->disconnect();
	}

	if(this->m_menu->CloseCombatIsDown() && this->m_heroType != Hero::NONE)
	{
		this->m_network->sendMessage(NetworkSelectHeroMessage(this->m_heroType, this->m_menu->getCombat()));
	}
	else if(this->m_menu->RangeCombatIsDown() && this->m_heroType != Hero::NONE)
	{
		this->m_network->sendMessage(NetworkSelectHeroMessage(this->m_heroType, this->m_menu->getCombat()));
	}

	if(this->m_menu->StartGameIsDown())
	{
		// The host has some restrictions
		if(m_playerId == 0)
		{
			if(m_hostMayStartGame)
			{
				//Skicka ready till servern
				m_network->sendMessage(NetworkReadyMessage(true));
			}
		}
		else if(m_heroType != Hero::HERO_TYPE::NONE)
		{
			//Skicka ready till servern
			m_network->sendMessage(NetworkReadyMessage(true));
		}
	}
	else if(this->m_menu->MainMenuIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}

	//Kolla om n�tverket har sagt att spelet har startat
	while(!m_network->startGameQueueEmpty())
	{
		NetworkStartGameMessage e = m_network->startGameQueueFront();
		this->mapName = e.getMapName();
		this->setDone(true);
		this->m_nextState = State::LOADING;
	}

	//kollar om n�n klient skickat ett text medelande
	while(!m_network->networkTextMessageQueueEmpty())
	{
		NetworkTextMessage e = m_network->networkTextMessageFront();
		m_menu->addStringToChat(e.getTxtMessage());
	}

	while(!m_network->heroSelectedQueueEmpty())
	{
		NetworkHeroSelectedMessage nhsm = m_network->heroSelectedQueueFront();

		// Check if a player has disconnected (chosen hero NONE)
		if(nhsm.getHeroId()== Hero::HERO_TYPE::NONE)
		{
			m_menu->removePlayer(nhsm.getPlayerId());
			m_hostsSuperVector.erase(nhsm.getPlayerId());
		}
		else
		{
			m_heroType = Hero::HERO_TYPE(nhsm.getHeroId());
		
			if(nhsm.getPlayerId() == this->m_playerId)
			{
				m_menu->selectHero(nhsm.getPlayerId(), m_heroType, true);
				if(m_playerId != 0)
					m_clientMayReady = true;
			}
			else
			{
				m_menu->selectHero(nhsm.getPlayerId(), m_heroType, false);
			}
			//Select
			switch(nhsm.getHeroId())
			{
				case Hero::HERO_TYPE::OFFICER:
					if(this->m_officer->getCharacter()->getAnimation()->getCurrentAnimation() == "OfficerIdle")
					{
						this->m_officer->getCharacter()->getAnimation()->PlayLoop("OfficerSelectIdle");
						this->m_officer->getCharacter()->getAnimation()->Play("OfficerSelect");
						this->m_officer->getRoom()->setGlowIndex("glowIntensity");
						this->m_officer->getDoor()->getAnimation()->PlayLoop("OpenIdle");
						this->m_officer->getDoor()->getAnimation()->Play("DoorOpen");
					}
					break;
				case Hero::HERO_TYPE::RED_KNIGHT:
					if(this->m_redKnight->getCharacter()->getAnimation()->getCurrentAnimation() == "RedKnightIdle")
					{
						this->m_redKnight->getCharacter()->getAnimation()->PlayLoop("RedKnightSelectIdle");
						this->m_redKnight->getCharacter()->getAnimation()->Play("RedKnightSelect");
						this->m_redKnight->getRoom()->setGlowIndex("glowIntensity1");
						this->m_redKnight->getDoor()->getAnimation()->PlayLoop("OpenIdle");
						this->m_redKnight->getDoor()->getAnimation()->Play("DoorOpen");
					}
					break;
				case Hero::HERO_TYPE::ENGINEER:
					if(this->m_engi->getCharacter()->getAnimation()->getCurrentAnimation() == "EngiIdle")
					{
						this->m_engi->getCharacter()->getAnimation()->PlayLoop("EngiSelectIdle");
						this->m_engi->getCharacter()->getAnimation()->Play("EngiSelect");
						this->m_engi->getRoom()->setGlowIndex("glowIntensity2");
						this->m_engi->getDoor()->getAnimation()->PlayLoop("OpenIdle");
						this->m_engi->getDoor()->getAnimation()->Play("DoorOpen");
					}
					break;
				case Hero::HERO_TYPE::DOCTOR:
					if(this->m_doctor->getCharacter()->getAnimation()->getCurrentAnimation() == "DoctorIdle")
					{
						this->m_doctor->getCharacter()->getAnimation()->PlayLoop("DoctorSelectedIdle");
						this->m_doctor->getCharacter()->getAnimation()->Play("DoctorSelected");
						this->m_doctor->getRoom()->setGlowIndex("glowIntensity3");
						this->m_doctor->getDoor()->getAnimation()->PlayLoop("OpenIdle");
						this->m_doctor->getDoor()->getAnimation()->Play("DoorOpen");
					}
					break;
				case Hero::HERO_TYPE::THE_MENTALIST:
					if(this->m_mentalist->getCharacter()->getAnimation()->getCurrentAnimation() == "MentalistIdle")
					{
						this->m_mentalist->getCharacter()->getAnimation()->PlayLoop("MentalistSelectIdle");
						this->m_mentalist->getCharacter()->getAnimation()->Play("MentalistSelect");
						this->m_mentalist->getRoom()->setGlowIndex("glowIntensity4");
						this->m_mentalist->getDoor()->getAnimation()->PlayLoop("OpenIdle");
						this->m_mentalist->getDoor()->getAnimation()->Play("DoorOpen");
					}
					break;
			}
		}

		bool heroesNotSelected[] = {false, false, false, false, false};
		for(int i = 0; i < 4; i++)
		{
			if(m_menu->getHeroesSelected()[i] != Hero::HERO_TYPE::NONE)
			{
				heroesNotSelected[m_menu->getHeroesSelected()[i]] = true;
			}
		}

		//Deselect
		for(int i = 0; i < numCharacters; i++)
		{
			if(heroesNotSelected[i] == false)
			{
				switch(i)
				{
				case Hero::HERO_TYPE::OFFICER:
					if(this->m_officer->getCharacter()->getAnimation()->getCurrentAnimation() == "OfficerSelectIdle")
					{
						this->m_officer->getCharacter()->getAnimation()->PlayLoop("OfficerIdle");
						this->m_officer->getCharacter()->getAnimation()->Play("OfficerDeselect");
						this->m_officer->getRoom()->setGlowIndex("");
						this->m_officer->getDoor()->getAnimation()->PlayLoop("ClosedIdle");
						this->m_officer->getDoor()->getAnimation()->Play("DoorClose");
					}
					break;
				case Hero::HERO_TYPE::RED_KNIGHT:
					if(this->m_redKnight->getCharacter()->getAnimation()->getCurrentAnimation() == "RedKnightSelectIdle")
					{
						this->m_redKnight->getCharacter()->getAnimation()->PlayLoop("RedKnightIdle");
						this->m_redKnight->getCharacter()->getAnimation()->Play("RedKnightDeselect");
						this->m_redKnight->getRoom()->setGlowIndex("");
						this->m_redKnight->getDoor()->getAnimation()->PlayLoop("ClosedIdle");
						this->m_redKnight->getDoor()->getAnimation()->Play("DoorClose");
					}
					break;
				case Hero::HERO_TYPE::ENGINEER:
					if(this->m_engi->getCharacter()->getAnimation()->getCurrentAnimation() == "EngiSelectIdle")
					{
						this->m_engi->getCharacter()->getAnimation()->PlayLoop("EngiIdle");
						this->m_engi->getCharacter()->getAnimation()->Play("EngiDeselect");
						this->m_engi->getRoom()->setGlowIndex("");
						this->m_engi->getDoor()->getAnimation()->PlayLoop("ClosedIdle");
						this->m_engi->getDoor()->getAnimation()->Play("DoorClose");
					}
					break;
				case Hero::HERO_TYPE::DOCTOR:
					if(this->m_doctor->getCharacter()->getAnimation()->getCurrentAnimation() == "DoctorSelectedIdle")
					{
						this->m_doctor->getCharacter()->getAnimation()->PlayLoop("DoctorIdle");
						this->m_doctor->getCharacter()->getAnimation()->Play("DoctorDeselected");
						this->m_doctor->getRoom()->setGlowIndex("");
						this->m_doctor->getDoor()->getAnimation()->PlayLoop("ClosedIdle");
						this->m_doctor->getDoor()->getAnimation()->Play("DoorClose");
					}
					break;
				case Hero::HERO_TYPE::THE_MENTALIST:
					if(this->m_mentalist->getCharacter()->getAnimation()->getCurrentAnimation() == "MentalistSelectIdle")
					{
						this->m_mentalist->getCharacter()->getAnimation()->PlayLoop("MentalistIdle");
						this->m_mentalist->getCharacter()->getAnimation()->Play("MentalistDeselect");
						this->m_mentalist->getRoom()->setGlowIndex("");
						this->m_mentalist->getDoor()->getAnimation()->PlayLoop("ClosedIdle");
						this->m_mentalist->getDoor()->getAnimation()->Play("DoorClose");
					}
					break;
				}
			}
		}
	}

	while(!m_network->playerJoinedMessageQueueEmpty())
	{
		NetworkPlayerJoinedMessage msg = m_network->playerJoinedMessageQueueFront();

		if(msg.getPlayerIndex() == this->m_playerId)
		{
			this->m_menu->setPlayerName(msg.getPlayerIndex(), msg.getName(), true);
		}
		else
		{
			this->m_menu->setPlayerName(msg.getPlayerIndex(), msg.getName(), false);
		}

		if(m_playerId == 0)
		{
			m_hostsSuperVector[msg.getPlayerIndex()] = false;
			if(msg.getPlayerIndex() != 0)
				m_hostMayStartGame = false;
		}
	}
	
	while(!m_network->readyMessageToClientQueueEmpty())
	{
		NetworkReadyMessageToClient msg = m_network->readyMessageToClientQueueFront();
		this->m_menu->setReady(msg.m_playerIndex);
		if(m_playerId == 0)
		{
			m_hostsSuperVector[msg.m_playerIndex] = true;

			// Check how many players are ready
			int notReadyCounter = 0;
			for(map<int, bool>::iterator iter = m_hostsSuperVector.begin(); iter != m_hostsSuperVector.end(); iter++)
			{
				if(!iter->second)
				{
					notReadyCounter++;
				}
			}
			// The host can only ready up if he is the only one not ready.
			if(notReadyCounter < 2)
			{
				if(m_heroType != Hero::HERO_TYPE::NONE)
				{
					m_hostMayStartGame = true;
				}
			}
		}
	}
}

State::StateEnum LobbyState::nextState()
{
	return this->m_nextState;
}
string LobbyState::getMapName()
{
	return this->mapName;
}
