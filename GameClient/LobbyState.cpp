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
	this->m_menu = new LobbyMenu();
	m_currentHeroSelected = Hero::HERO_TYPE::NONE;

	pl = g_graphicsEngine->createPointLight(FLOAT3(-1.3f, 0.0f, 4.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	//g_graphicsEngine->createDirectionalLight(FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(0.01f, 0.01f, 0.01f), FLOAT3(0.0f, 0.0f, 0.0f));

	// 2.063
	float y =  -0.5f;
	cube[0] = g_graphicsEngine->createModel("rum", FLOAT3(-1.55f, y, 6), false, "color");
	cube[1] = g_graphicsEngine->createModel("rum", FLOAT3(0.543f, y, 6), false, "color");
	cube[2] = g_graphicsEngine->createModel("rum", FLOAT3(2.636f, y, 6), false, "color");
	cube[3] = g_graphicsEngine->createModel("rum", FLOAT3(2555.636f, y, 6), false, "color");
	cube[4] = g_graphicsEngine->createModel("rum", FLOAT3(2555.636f, y, 6), false, "color");

	boll = g_graphicsEngine->createModel("RolleBoll", FLOAT3(0, 0, 0), false, "color");

	////Officer  
	//officer = g_graphicsEngine->createModel(m_modelIdHolder.getModel(95), FLOAT3(-1.3f, y, 4), false, m_modelIdHolder.getTexture(95));
	//officer->getAnimation()->PlayLoop("idle");
	//officer->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(95)));

	////RedKnight
	//redKnight = g_graphicsEngine->createModel(m_modelIdHolder.getModel(96), FLOAT3(-0.4f, y, 4), false, m_modelIdHolder.getTexture(96));
	//redKnight->getAnimation()->PlayLoop("2Hidle");
	//redKnight->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(96)));
	//
	////Engineer
	//engi = g_graphicsEngine->createModel(m_modelIdHolder.getModel(97), FLOAT3(0.5, y, 4), false, m_modelIdHolder.getTexture(97));
	//engi->getAnimation()->PlayLoop("RangeAttack");
	//engi->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(97)));
	//
	////Doctor
	//doctor = g_graphicsEngine->createModel(m_modelIdHolder.getModel(98), FLOAT3(1.4f, y, 4), false, m_modelIdHolder.getTexture(98));
	//doctor->getAnimation()->PlayLoop("ChainLight");
	//doctor->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(98)));
	
	////Mentalist
	//mentalist = g_graphicsEngine->createModel(m_modelIdHolder.getModel(99), FLOAT3(1.25f, y, 4), false, m_modelIdHolder.getTexture(99));
	//mentalist->getAnimation()->PlayLoop("idle");
	//mentalist->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(99)));
}

LobbyState::~LobbyState()
{
	delete this->m_menu;

	//g_graphicsEngine->removeModel(officer);
	//g_graphicsEngine->removeModel(redKnight);
	//g_graphicsEngine->removeModel(engi);
	//g_graphicsEngine->removeModel(doctor);
	//g_graphicsEngine->removeModel(mentalist);
	g_graphicsEngine->removeModel(boll);
	g_graphicsEngine->removeModel(cube[0]);
	g_graphicsEngine->removeModel(cube[1]);
	g_graphicsEngine->removeModel(cube[2]);
	g_graphicsEngine->removeModel(cube[3]);
	g_graphicsEngine->removeModel(cube[4]);
}

void LobbyState::update(float _dt)
{
	this->m_menu->Update(_dt);

	if(GetKeyState(VK_LEFT) < 0)
		pl->setPosition(pl->getPosition() + FLOAT3(-0.05f, 0, 0));
	if(GetKeyState(VK_RIGHT) < 0)
		pl->setPosition(pl->getPosition() + FLOAT3(0.05f, 0, 0));
	if(GetKeyState(VK_UP) < 0)
		pl->setPosition(pl->getPosition() + FLOAT3(0, 0.05f, 0));
	if(GetKeyState(VK_DOWN) < 0)
		pl->setPosition(pl->getPosition() + FLOAT3(0, -0.05f, 0));
	if(GetKeyState(VK_F1) < 0)
		pl->setPosition(pl->getPosition() + FLOAT3(0, 0, 0.05f));
	if(GetKeyState(VK_F2) < 0)
		pl->setPosition(pl->getPosition() + FLOAT3(0, 0, -0.05f));

	boll->setShadow(false);
	boll->setPosition(pl->getPosition());

	if(g_mouse->isLButtonReleased())
	{
		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
		float dist;
		if(cube[0]->intersects(dist, pickOrig, pickDir))
		{
			this->m_currentHeroSelected = Hero::OFFICER;
			m_network->sendMessage(NetworkSelectHeroMessage(0, this->m_menu->getCombat()));
		}
		else if(cube[1]->intersects(dist, pickOrig, pickDir))
		{
			this->m_currentHeroSelected = Hero::RED_KNIGHT;
			m_network->sendMessage(NetworkSelectHeroMessage(1, this->m_menu->getCombat()));
		}
		else if(cube[2]->intersects(dist, pickOrig, pickDir))
		{
			this->m_currentHeroSelected = Hero::ENGINEER;
			m_network->sendMessage(NetworkSelectHeroMessage(2, this->m_menu->getCombat()));
		}
		else if(cube[3]->intersects(dist, pickOrig, pickDir))
		{
			this->m_currentHeroSelected = Hero::DOCTOR;
			m_network->sendMessage(NetworkSelectHeroMessage(3, this->m_menu->getCombat()));
		}
		else if(cube[4]->intersects(dist, pickOrig, pickDir))
		{
			this->m_currentHeroSelected = Hero::THE_MENTALIST;
			m_network->sendMessage(NetworkSelectHeroMessage(4, this->m_menu->getCombat()));
		}
	}
	
	if(m_menu->MainMenuIsDown())
	{
		this->m_network->disconnect();
	}

	if(this->m_menu->CloseCombatIsDown() && this->m_currentHeroSelected != Hero::NONE)
	{
		this->m_network->sendMessage(NetworkSelectHeroMessage(this->m_currentHeroSelected, this->m_menu->getCombat()));
	}
	else if(this->m_menu->RangeCombatIsDown() && this->m_currentHeroSelected != Hero::NONE)
	{
		this->m_network->sendMessage(NetworkSelectHeroMessage(this->m_currentHeroSelected, this->m_menu->getCombat()));
	}

	if(this->m_menu->StartGameIsDown() == true)
	{
		//Skicka ready till servern
		m_network->sendMessage(NetworkReadyMessage(true));
	}
	else if(this->m_menu->MainMenuIsDown() == true)
	{
		this->setDone(true);
		this->m_nextState = State::MAIN_MENU;
	}

	//Kolla om nätverket har sagt att spelet har startat
	while(!m_network->startGameQueueEmpty())
	{
		NetworkStartGameMessage e = m_network->startGameQueueFront();
		this->mapName = e.getMapName();
		this->setDone(true);
		this->m_nextState = State::LOADING;
	}

	while(!m_network->heroSelectedQueueEmpty())
	{
		NetworkHeroSelectedMessage nhsm = m_network->heroSelectedQueueFront();
		m_heroType = Hero::HERO_TYPE(nhsm.getHeroId());
		m_menu->selectHero(nhsm.getPlayerId(), m_heroType);
	}

	while(!m_network->networkWelcomeMessageEmpty())
	{
		NetworkWelcomeMessage nwm = m_network->networkWelcomeMessageFront();
		this->mapName = nwm.getMapName();
	}

	while(!m_network->playerJoinedMessageQueueEmpty())
	{
		NetworkPlayerJoinedMessage msg = m_network->playerJoinedMessageQueueFront();
		this->m_menu->setPlayerName(msg.getPlayerIndex(), msg.getName());
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