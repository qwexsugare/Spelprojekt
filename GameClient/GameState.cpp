#include "GameState.h"
#include "LobbyState.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"
#include <sstream>

GameState::GameState()
{
	//this->m_hud = new HudMenu();
	this->m_fpsText = g_graphicsEngine->createText("", INT2(10, 10), 40, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));
	this->m_rotation = 0.0f;
	this->m_testSound = createSoundHandle("knife.wav", false);

	// Create a fucking awesome terrain
	vector<string> textures;
	textures.push_back("terrain_texture1.png");
	textures.push_back("terrain_texture2.png");
	textures.push_back("terrain_texture3.png");
	textures.push_back("terrain_texture4.png");
	vector<string> blendMaps;
	blendMaps.push_back("blendmap.png");
	this->m_terrain = g_graphicsEngine->createTerrain(FLOAT3(-50.0f, 0.0f, -50.0f), FLOAT3(50.0f, 0.0f, 50.0f), textures, blendMaps);

	this->m_network = new Client();

	this->m_network->connect(sf::IPAddress::GetLocalAddress(), 1337);
	//this->m_network->connect(sf::IPAddress("194.47.155.248"), 1337);
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_entities.size(); i++)
		delete this->m_entities[i];

	delete this->m_network;
	//delete this->m_hud;
	deactivateSound(this->m_testSound);
}

void GameState::end()
{
	g_graphicsEngine->removeTerrain(this->m_terrain);

	for(int i = 0; i < this->m_entities.size(); i++)
		g_graphicsEngine->removeModel(this->m_entities[i]->m_model);
	
	g_graphicsEngine->removeText(this->m_fpsText);

	this->setDone(true);
}

State::StateEnum GameState::nextState()
{
	return State::MAIN_MENU;
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
				this->m_entities[i]->m_model->setRotation(e.getRotation());
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

	this->m_network->sendMsg(Msg("Ready"));
	this->m_network->sendMsg(Msg("Start"));

	static float CAMERA_SPEED = 16.0f;
	if((g_mouse->getPos().x >= g_graphicsEngine->getScreenSize().x-10)
		|| g_keyboard->getKeyState(VK_RIGHT) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveStatic(0.0f, CAMERA_SPEED*_dt, 0.0f);
	}
	else if((g_mouse->getPos().x <= 10)
		|| g_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveStatic(0.0f, -(CAMERA_SPEED*_dt), 0.0f);
	}
	if((g_mouse->getPos().y >= g_graphicsEngine->getScreenSize().y-10)
		|| g_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveStatic(CAMERA_SPEED*_dt, 0.0f, 0.0f);
	}
	else if((g_mouse->getPos().y <= 10)
		|| g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveStatic(-(CAMERA_SPEED*_dt), 0.0f, 0.0f);
	}

	if(g_mouse->isLButtonPressed())
	{
		// Calc some fucken pick ray out mofos
		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());

		float k = (-pickOrig.y)/pickDir.y;
		D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;

		EntityMessage e;
		e.setPosition(FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z));
		this->m_network->sendEntity(e);
	}
	else if(g_mouse->isLButtonDown())
	{

	}
	else if(g_mouse->isRButtonPressed())
	{
		loopSound(this->m_testSound);
	}
	else
		for(int i = 0; i < this->m_entities.size(); i++)
			this->m_entities[i]->m_model->rotate(0.0f, 0.0f, _dt/5.0f);

	this->m_hud->Update();
}