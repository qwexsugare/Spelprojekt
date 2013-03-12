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

	//pl[0] = g_graphicsEngine->createPointLight(FLOAT3(0.0f, 1.0f, 4.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	dl = g_graphicsEngine->createDirectionalLight(FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(0.3f, 0.3f, 0.3f), FLOAT3(0.01f, 0.01f, 0.01f), FLOAT3(0.0f, 0.0f, 0.0f));

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

	this->m_officer->getCharacter()->getAnimation()->PlayLoop("idle");
	this->m_redKnight->getCharacter()->getAnimation()->PlayLoop("idle");
	this->m_engi->getCharacter()->getAnimation()->PlayLoop("idle");
	this->m_doctor->getCharacter()->getAnimation()->PlayLoop("idle");
	this->m_mentalist->getCharacter()->getAnimation()->PlayLoop("idle");
	
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
}

void LobbyState::update(float _dt)
{
	this->m_menu->Update(_dt);
	// waddapigotabigcock
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

	float slice = 1/(max-min);

	float value = this->m_menu->getSlider()->GetValue();

	g_graphicsEngine->getCamera()->set(FLOAT2(this->m_menu->getSlider()->GetValue() * max, 0));


	
	float mouseX = (g_mouse->getPos().x / float(g_graphicsEngine->getScreenSize().x))*2-1;

	if(g_mouse->isLButtonReleased() && mouseX >= -0.45f && mouseX <= 0.45f)
	{
		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
		float dist;
		if(m_officer->getRoom()->intersects(dist, pickOrig, pickDir))
		{
			this->m_currentHeroSelected = Hero::OFFICER;
			m_network->sendMessage(NetworkSelectHeroMessage(0, this->m_menu->getCombat()));
		}
		else if(m_redKnight->getRoom()->intersects(dist, pickOrig, pickDir))
		{
			this->m_currentHeroSelected = Hero::RED_KNIGHT;
			m_network->sendMessage(NetworkSelectHeroMessage(1, this->m_menu->getCombat()));
		}
		else if(m_engi->getRoom()->intersects(dist, pickOrig, pickDir))
		{
			this->m_currentHeroSelected = Hero::ENGINEER;
			m_network->sendMessage(NetworkSelectHeroMessage(2, this->m_menu->getCombat()));
		}
		else if(m_doctor->getRoom()->intersects(dist, pickOrig, pickDir))
		{
			this->m_currentHeroSelected = Hero::DOCTOR;
			m_network->sendMessage(NetworkSelectHeroMessage(3, this->m_menu->getCombat()));
		}
		else if(m_mentalist->getRoom()->intersects(dist, pickOrig, pickDir))
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