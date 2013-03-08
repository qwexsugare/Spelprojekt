#include "LoadingState.h"
#include "Graphics.h"
#include "SoundWrapper.h"

LoadingState::LoadingState(Client* _network)
{
	m_network = _network;
	m_skip = new Button();
	m_skip->Init(FLOAT2(0.5f, -0.8f), FLOAT2(0.3f, 0.15f), "menu_textures/skip.png", "");
	m_speech = createSoundHandle("lorebook/Level1.wav", false, false);
	playSound(m_speech);
	m_img = g_graphicsEngine->createSprite("menu_textures/MENU-LEVEL-0.png", FLOAT2(0.0f, 0.0f), FLOAT2(2.0f, 2.0f), 0);

	Model* temp;
	for(int i = 0; i < ModelIdHolder::MAX_IDS; i++)
	{
		if(m_modelIdHolder.getModel(i) != "")
		{
			temp = g_graphicsEngine->createModel(m_modelIdHolder.getModel(i), FLOAT3());
			g_graphicsEngine->removeModel(temp);
		}
	}
}

LoadingState::~LoadingState()
{
	g_graphicsEngine->removeSprite(m_img);
	delete m_skip;
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
		stopSound(m_speech);
		deactivateSound(m_speech);
		m_network->sendMessage(NetworkReadyMessage(true));
		this->setDone(true);
	}
}