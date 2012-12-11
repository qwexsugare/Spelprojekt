#include "GameState.h"
#include "LobbyState.h"
#include "Input.h"
#include "Graphics.h"
#include <sstream>

GameState::GameState()
{
	this->m_fpsText = g_graphicsEngine->createText("", INT2(50, 100), 100, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));

	this->m_testSprite = g_graphicsEngine->createSpriteSheet("test.png", INT2(500, 500), INT2(100, 100), INT2(4, 2), 0);
	this->m_testSprite->setCurrentFrame(INT2(2,0));
	this->m_testSprite = g_graphicsEngine->createSpriteSheet("test.png", INT2(550, 550), INT2(100, 100), INT2(4, 2), 2);
	this->m_testSprite->setCurrentFrame(INT2(3,0));
	this->m_rotation = 0.0f;
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_entities.size(); i++)
		delete this->m_entities[i];
}

bool GameState::done()
{
	return false;
}

State* GameState::nextState()
{
	return new LobbyState();
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

	static float CAMERA_SPEED = 2.0f;
	if((g_mouse->getPos().x >= g_configFile->getScreenSize().x-10 && g_mouse->getPos().x <= g_configFile->getScreenSize().x)
		|| g_keyboard->getKeyState(VK_RIGHT) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, CAMERA_SPEED*_dt, 0.0f);
	}
	else if((g_mouse->getPos().x <= 10 && g_mouse->getPos().x >= 0)
		|| g_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, -(CAMERA_SPEED*_dt), 0.0f);
	}
	if((g_mouse->getPos().y >= g_configFile->getScreenSize().y-10 && g_mouse->getPos().y <= g_configFile->getScreenSize().y)
		|| g_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, 0.0f, CAMERA_SPEED*_dt);
	}
	else if((g_mouse->getPos().y <= 10 && g_mouse->getPos().y >= 0)
		|| g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, 0.0f, -(CAMERA_SPEED*_dt));
	}

	if(g_mouse->isLButtonPressed())
	{
		Model* model = g_graphicsEngine->createModel("ArrowHead", FLOAT3(g_graphicsEngine->getCamera()->getPos().x, 0.0f, g_graphicsEngine->getCamera()->getPos().z));
		if(model)
		{
			this->m_entities.push_back(new Entity(model));
		}
	}
	if(g_mouse->isLButtonDown())
	{
		for(int i = 0; i < this->m_entities.size(); i++)
			this->m_entities[i]->m_model->rotate(_dt, 0.0f, 0.0f);
	}
}