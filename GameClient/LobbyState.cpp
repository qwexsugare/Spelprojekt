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
	dl = g_graphicsEngine->createDirectionalLight(FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(0.6f, 0.6f, 0.6f), FLOAT3(0.01f, 0.01f, 0.01f), FLOAT3(0.0f, 0.0f, 0.0f));

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
	cube[0] = g_graphicsEngine->createModel("rum", FLOAT3(x, y, z), false, "color");
	pl[0] = g_graphicsEngine->createPointLight(FLOAT3(x, y + inLightY, z), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	//pl[0] = g_graphicsEngine->createPointLight(FLOAT3(x, y + frontLightY, z + frontLightZ), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 2.0f, false, false);

	cube[1] = g_graphicsEngine->createModel("rum", FLOAT3(x + step, y, z), false, "color");
	pl[1] = g_graphicsEngine->createPointLight(FLOAT3(x + step, y + inLightY, z), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	//pl[1] = g_graphicsEngine->createPointLight(FLOAT3(x + step, y + frontLightY, z + frontLightZ), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, false, false);

	cube[2] = g_graphicsEngine->createModel("rum", FLOAT3(x + step*2, y, z), false, "color");
	pl[2] = g_graphicsEngine->createPointLight(FLOAT3(x + step*2, y + inLightY, z), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	//pl[2] = g_graphicsEngine->createPointLight(FLOAT3(x + step, y + frontLightY, z + frontLightZ), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, false, false);

	cube[3] = g_graphicsEngine->createModel("rum", FLOAT3(x + step*3, y, z), false, "color");
	pl[3] = g_graphicsEngine->createPointLight(FLOAT3(x + step*3, y + inLightY, z), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	//pl[3] = g_graphicsEngine->createPointLight(FLOAT3(x + step, y + frontLightY, z + frontLightZ), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, false, false);

	cube[4] = g_graphicsEngine->createModel("rum", FLOAT3(x + step*4, y, z), false, "color");
	pl[4] = g_graphicsEngine->createPointLight(FLOAT3(x + step*4, y + inLightY, z), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	//pl[4] = g_graphicsEngine->createPointLight(FLOAT3(x + step, y + frontLightY, z + frontLightZ), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, false, false);

	cube[5] = g_graphicsEngine->createModel("rum", FLOAT3(x + step*5, y, z), false, "color");
	pl[5] = g_graphicsEngine->createPointLight(FLOAT3(x + step*5, y + inLightY, z), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	//pl[5] = g_graphicsEngine->createPointLight(FLOAT3(x + step, y + frontLightY, z + frontLightZ), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, false, false);

	//boll = g_graphicsEngine->createModel("RolleBoll", FLOAT3(0, 0, 0), false, "color");

	//Officer  
	officer = g_graphicsEngine->createModel(m_modelIdHolder.getModel(95), FLOAT3(x, y, z), false, m_modelIdHolder.getTexture(95));
	officer->getAnimation()->PlayLoop("idle");
	officer->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(95)));

	//RedKnight
	redKnight = g_graphicsEngine->createModel(m_modelIdHolder.getModel(96), FLOAT3(x + step, y, z), false, m_modelIdHolder.getTexture(96));
	redKnight->getAnimation()->PlayLoop("2Hidle");
	redKnight->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(96)));
	
	//Engineer
	engi = g_graphicsEngine->createModel(m_modelIdHolder.getModel(97), FLOAT3(x + step*2, y, z), false, m_modelIdHolder.getTexture(97));
	engi->getAnimation()->PlayLoop("idle");
	engi->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(97)));
	
	//Doctor
	doctor = g_graphicsEngine->createModel(m_modelIdHolder.getModel(98), FLOAT3(x + step*3, y, z), false, m_modelIdHolder.getTexture(98));
	doctor->getAnimation()->PlayLoop("idle");
	doctor->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(98)));
	
	//Mentalist
	mentalist = g_graphicsEngine->createModel(m_modelIdHolder.getModel(99), FLOAT3(x + step*4, y, z), false, m_modelIdHolder.getTexture(99));
	mentalist->getAnimation()->PlayLoop("idle");
	mentalist->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(99)));
}

LobbyState::~LobbyState()
{
	delete this->m_menu;

	g_graphicsEngine->removeModel(officer);
	g_graphicsEngine->removeModel(redKnight);
	g_graphicsEngine->removeModel(engi);
	g_graphicsEngine->removeModel(doctor);
	g_graphicsEngine->removeModel(mentalist);
	//g_graphicsEngine->removeModel(boll);
	g_graphicsEngine->removeModel(cube[0]);
	g_graphicsEngine->removeModel(cube[1]);
	g_graphicsEngine->removeModel(cube[2]);
	g_graphicsEngine->removeModel(cube[3]);
	g_graphicsEngine->removeModel(cube[4]);
	g_graphicsEngine->removeModel(cube[5]);
	g_graphicsEngine->removePointLight(pl[0]);
	g_graphicsEngine->removePointLight(pl[1]);
	g_graphicsEngine->removePointLight(pl[2]);
	g_graphicsEngine->removePointLight(pl[3]);
	g_graphicsEngine->removePointLight(pl[4]);
	g_graphicsEngine->removePointLight(pl[5]);
	g_graphicsEngine->removeDirectionalLight(dl);
}

void LobbyState::update(float _dt)
{
	this->m_menu->Update(_dt);

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
}

State::StateEnum LobbyState::nextState()
{
	return this->m_nextState;
}
string LobbyState::getMapName()
{
	return this->mapName;
}