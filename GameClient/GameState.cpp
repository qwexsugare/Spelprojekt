#include "GameState.h"
#include "Input.h"
#include "Graphics.h"
#include <sstream>

GameState::GameState()
{
	this->m_testModel = NULL;
	this->m_fpsText = g_graphicsEngine->createText("", INT2(50, 100), 100, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));
}

GameState::~GameState()
{

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
		ss << "FPS: " << 1.0f/_dt;
		this->m_fpsText->setString(ss.str());
	}

	if(g_mouse->isLButtonPressed())
	{
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