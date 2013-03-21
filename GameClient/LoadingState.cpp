#include "LoadingState.h"
#include "Graphics.h"
#include "SoundWrapper.h"

LoadingState::LoadingState(Client* _network, string _mapName) : State(State::LOADING)
{
	m_mapName = _mapName;
	m_network = _network;
	m_skip = new Button();
	m_skip->Init(FLOAT2(0.5f, -0.8f), FLOAT2(0.3f, 0.15f), "menu_textures/Button-LoadingMenu-Skip.png", "");
	if(this->m_mapName[10]=='o')
	{
		m_speech = createSoundHandle("lorebook/Level1.wav", false, false);
	}
	else
	{
		m_speech = createSoundHandle("lorebook/Level2.wav", false, false);
	}
	playSound(m_speech);
	if(this->m_mapName[10]=='o')
	{
		m_img = g_graphicsEngine->createSprite("menu_textures/MENU-LEVEL-0.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);
	}
	else
	{
		m_img = g_graphicsEngine->createSprite("menu_textures/MENU-LEVEL-1.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);
	}
	g_graphicsEngine->render();
	Model* temp;
	for(int i = 0; i < ModelIdHolder::MAX_IDS; i++)
	{
		if(m_modelIdHolder.getModel(i) != "")
		{
			temp = g_graphicsEngine->createModel(m_modelIdHolder.getModel(i), FLOAT3());
			g_graphicsEngine->removeModel(temp);
		}
	}

	//Sprite *tempSprite;
	//SkillIdHolder skillIdHolder;

	//for(int i = 0; i < skillIdHolder.getNrOfIds(); i++)
	//{
	//	if(skillIdHolder.getSkill(i) != "")
	//	{
	//		tempSprite = g_graphicsEngine->createSprite(skillIdHolder.getSkill(i), FLOAT2(0.0f, 0.0f), FLOAT2(1.0f, 1.0f), 0);
	//		g_graphicsEngine->removeSprite(tempSprite);
	//	}
	//}
}

LoadingState::~LoadingState()
{
	g_graphicsEngine->removeSprite(m_img);
	delete m_skip;
	stopSound(m_speech);
	deactivateSound(m_speech);
}

State::StateEnum LoadingState::nextState()
{
	return State::GAME;
}

void LoadingState::update(float _dt)
{
	m_skip->Update();
	if(m_skip->isClicked())
	{
		m_network->sendMessage(NetworkReadyMessage(true));
	}

	while(!m_network->startGameQueueEmpty())
	{
		m_network->startGameQueueFront();
		this->setDone(true);
	}
}

string LoadingState::getMapName()
{
	return this->m_mapName;
}