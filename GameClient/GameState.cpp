#include "GameState.h"
#include "Input.h"
#include <sstream>

GameState::GameState()
{
	this->m_fpsText = g_graphicsEngine->createText("", INT2(50, 100), 100, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));

	this->m_testSprite = g_graphicsEngine->createSpriteSheet("test.png", INT2(500, 500), INT2(100, 100), INT2(4, 2), 0);
	this->m_testSprite->setCurrentFrame(INT2(2,0));
	this->m_testSprite = g_graphicsEngine->createSpriteSheet("test.png", INT2(550, 550), INT2(100, 100), INT2(4, 2), 2);
	this->m_testSprite->setCurrentFrame(INT2(3,0));
	Sprite *s = g_graphicsEngine->createSprite("test.png", INT2(600, 600), INT2(100, 100), 1);
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
		this->m_entities.push_back(new Entity(
			g_graphicsEngine->createModel("ArrowHead", FLOAT3(g_graphicsEngine->getCamera()->getPos().x, 0.0f, g_graphicsEngine->getCamera()->getPos().z))));
	}
	if(g_mouse->isLButtonDown())
	{
		this->m_entities[0]->m_model->rotate(_dt, 0.0f, 0.0f);
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