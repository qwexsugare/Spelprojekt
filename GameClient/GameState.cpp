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

	this->m_network = new Client();
	this->m_network->connect(sf::IPAddress::GetLocalAddress(), 1337);
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_entities.size(); i++)
		delete this->m_entities[i];

	delete this->m_network;
}

void GameState::end()
{
	for(int i = 0; i < this->m_entities.size(); i++)
	{
		g_graphicsEngine->removeModel(this->m_entities[i]->m_model);
	}
	
	g_graphicsEngine->removeText(this->m_fpsText);

	this->setDone(true);
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
	if(lol > 1.0f)
	{
		stringstream ss;
		ss << "FPS: " << 1.0f/_dt << " Entities: " << this->m_entities.size();
		this->m_fpsText->setString(ss.str());
		lol = -0.5f;
	}

	while(this->m_network->entityQueueEmpty() == false)
	{
		EntityMessage e = this->m_network->entityQueueFront();
		bool found = false;

		for(int i = 0; i < this->m_entities.size() && found == false; i++)
		{
			if(this->m_entities[i]->m_id == e.getId())
			{
				this->m_entities[i]->m_model->setPosition(e.getPos());
				found = true;
			}
		}

		if(found == false)
		{
			Model* model = g_graphicsEngine->createModel("ArrowHead", FLOAT3(g_graphicsEngine->getCamera()->getPos().x, 0.0f, g_graphicsEngine->getCamera()->getPos().z));
			if(model)
			{
				this->m_entities.push_back(new Entity(model, e.getId()));
			}
		}
	}

	static float CAMERA_SPEED = 2.0f;
	if((g_mouse->getPos().x >= g_configFile->getScreenSize().x-10)
		|| g_keyboard->getKeyState(VK_RIGHT) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, CAMERA_SPEED*_dt, 0.0f);
	}
	else if((g_mouse->getPos().x <= 10)
		|| g_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, -(CAMERA_SPEED*_dt), 0.0f);
	}
	if((g_mouse->getPos().y >= g_configFile->getScreenSize().y-10)
		|| g_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, 0.0f, CAMERA_SPEED*_dt);
	}
	else if((g_mouse->getPos().y <= 10)
		|| g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveRelative(0.0f, 0.0f, -(CAMERA_SPEED*_dt));
	}

	if(g_mouse->isLButtonPressed())
	{
		EntityMessage e; 
		e.setPosition(FLOAT3(5.0f, 0.0f, 0.0f));

		this->m_network->sendEntity(e);
	}
	else if(g_mouse->isLButtonDown())
	{
		//Model* model = g_graphicsEngine->createModel("ArrowHead", FLOAT3(g_graphicsEngine->getCamera()->getPos().x, 0.0f, g_graphicsEngine->getCamera()->getPos().z));

		//if(model)
		//{
		//	this->m_entities.push_back(new Entity(model));
		//}
	}
	else if(g_mouse->isRButtonPressed())
	{
		this->end();
	}
	else
		for(int i = 1; i < this->m_entities.size(); i++)
			this->m_entities[i]->m_model->rotate(_dt/5.0f, 0.0f, 0.0f);
}