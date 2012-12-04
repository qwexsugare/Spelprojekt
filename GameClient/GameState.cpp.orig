#include "GameState.h"
#include "Input.h"
#include <sstream>

GameState::GameState()
{
	this->m_fpsText = g_graphicsEngine->createText("", INT2(50, 100), 100, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));

	this->m_testSprite = g_graphicsEngine->createSprite("GUI-Mouse.png", FLOAT2(500, 500), FLOAT2(42, 37));
	this->m_rotation = 0.0f;
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_entities.size(); i++)
		delete this->m_entities[i];
}

void GameState::update(float _dt)
{
	this->m_testSprite->setRotation(m_rotation);
	this->m_testSprite->setSize(FLOAT2(m_rotation, m_rotation));
	this->m_rotation += _dt;

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
		this->m_entities.push_back(new Entity(
		this->m_testSprite->setPosition(FLOAT2(1000, 1000));
			g_graphicsEngine->createModel("ArrowHead"),
			FLOAT3(g_graphicsEngine->getCamera()->getPos().x, 0.0f, g_graphicsEngine->getCamera()->getPos().z))
			);
	}
		this->m_testModel = g_graphicsEngine->createModel("ArrowHead");
		//this->m_testModel->setPosition(g_graphicsEngine->getCameraPos().x, 0.0f, g_graphicsEngine->getCameraPos().z);
	}
	if(g_mouse->isRButtonDown())
	{
		if(this->m_testModel)
			this->m_testModel->rotate(0.0025f, 0.0f, 0.0f);
	}
}

void GameState::render()
{

}

bool GameState::done()
{
	return false;
}

State* GameState::nextState()
{
	return new GameState();
}