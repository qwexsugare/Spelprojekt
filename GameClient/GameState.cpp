#include "GameState.h"
#include "Input.h"
#include <sstream>

GameState::GameState()
{
	this->m_fpsText = g_graphicsEngine->createText("", INT2(50, 100), 100, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));

	//this->m_testSprite = g_graphicsEngine->createSprite("test.png", FLOAT2(500, 500), FLOAT2(50, 50));
	this->m_rotation = 0.0f;
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_entities.size(); i++)
		delete this->m_entities[i];
}

void GameState::update(float _dt)
{
	// Update FRAMES PER SECOND (FPS) text
	static float lol = 0.0f;
	lol += _dt;
	if(lol > 0.0f)
	{
		lol = -0.5f;
		stringstream ss;
		ss << "FPS: " << 1.0f/_dt << " Entities: " << this->m_entities.size();
		this->m_fpsText->setString(ss.str());
	}

	if(g_mouse->isLButtonPressed())
	{
		//this->m_testSprite->setRotation(this->m_rotation);
		this->m_rotation += 0.1;

		this->m_entities.push_back(new Entity(
			g_graphicsEngine->createModel("ArrowHead", FLOAT3(g_graphicsEngine->getCamera()->getPos().x, 0.0f, g_graphicsEngine->getCamera()->getPos().z))));
	}
}

bool GameState::done()
{
	return false;
}

State* GameState::nextState()
{
	return new GameState();
}