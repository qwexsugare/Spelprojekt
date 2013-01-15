#include "GameState.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"
#include <sstream>

GameState::GameState()
{
	this->m_hud = new HudMenu();
	this->m_fpsText = g_graphicsEngine->createText("", INT2(0, 0), 40, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));
	this->m_rotation = 0.0f;
	this->m_testSound = createSoundHandle("knife.wav", false);
	this->m_emilmackesFpsText = new TextInput("text1.png", INT2(1000, 600) , 80);

	// Create a fucking awesome terrain
	vector<string> textures;
	textures.push_back("terrain_texture1.png");
	textures.push_back("terrain_texture2.png");
	textures.push_back("terrain_texture3.png");
	textures.push_back("terrain_texture4.png");
	vector<string> blendMaps;
	blendMaps.push_back("blendmap.png");
	//this->m_terrain = g_graphicsEngine->createTerrain(FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(100.0f, 0.0f, 100.0f), textures, blendMaps);
	this->m_terrain = this->importTerrain("maps\\bana.txt");

	this->m_network = new Client();

	this->m_network->connect(sf::IPAddress::GetLocalAddress(), 1350);
	//this->m_network->connect(sf::IPAddress("194.47.155.248"), 1350);

	//this->s = g_graphicsEngine->createSprite("test.png", FLOAT2(0.0f, 0.0f), FLOAT2(0.5f, 0.5f), 0);
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_entities.size(); i++)
		delete this->m_entities[i];

	if(m_minimap)
		delete this->m_minimap;
	delete this->m_network;
	delete this->m_emilmackesFpsText;
	delete this->m_hud;
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

		if(e.getId() > 3)
		{
			int i = 0;
		}

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
			Model* model = g_graphicsEngine->createModel(this->m_modelIdHolder.getModel(e.getModelId()), FLOAT3(e.getPos().x, 0.0, e.getPos().z));
			if(model)
			{
				this->m_entities.push_back(new Entity(model, e.getId()));
			}
		}
	}

	while(this->m_network->removeEntityQueueEmpty() == false)
	{
		RemoveEntityMessage rem = this->m_network->removeEntityQueueFront();
		bool found = false;

		for(int i = 0; i < this->m_entities.size() && found == false; i++)
		{
			if(this->m_entities[i]->m_id == rem.getId())
			{
				g_graphicsEngine->removeModel(this->m_entities[i]->m_model);
				delete this->m_entities[i];
				this->m_entities.erase(this->m_entities.begin() + i);
				i = this->m_entities.size();
			}
		}
	}

	this->m_network->sendMsg(Msg("Ready"));
	this->m_network->sendMsg(Msg("Start"));

	static float CAMERA_SPEED = 16.0f;
	if(g_graphicsEngine->getCamera()->getPos().x < m_terrain->getWidth()-27.0f && (g_mouse->getPos().x >= g_graphicsEngine->getScreenSize().x-10 || g_keyboard->getKeyState(VK_RIGHT) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->moveStatic(0.0f, CAMERA_SPEED*_dt, 0.0f);
	}
	else if(g_graphicsEngine->getCamera()->getPos().x > 27.0f && (g_mouse->getPos().x <= 10 || g_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->moveStatic(0.0f, -(CAMERA_SPEED*_dt), 0.0f);
	}
	if(g_graphicsEngine->getCamera()->getPos().z < m_terrain->getHeight()-4.0f && (g_mouse->getPos().y >= g_graphicsEngine->getScreenSize().y-10 || g_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->moveStatic(CAMERA_SPEED*_dt, 0.0f, 0.0f);
	}
	else if(g_graphicsEngine->getCamera()->getPos().z > 25.0f && (g_mouse->getPos().y <= 10 || g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->moveStatic(-(CAMERA_SPEED*_dt), 0.0f, 0.0f);
	}

	static bool canMove = false;
	static bool usingMinimap = false;
	if(g_mouse->isLButtonPressed())
	{
		for(int i = 0; i < m_entities.size(); i++)
		{
			D3DXVECTOR3 pickDir;
			D3DXVECTOR3 pickOrig;
			g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
			float dist;
			if(m_entities[i]->m_model->intersects(dist, pickOrig, pickDir))
			{
				canMove = true;
			}
		}
	}
	if(g_mouse->isLButtonDown())
	{

	}
	if(g_mouse->isRButtonPressed())
	{
		if(m_minimap->isMouseInMap(g_mouse->getPos()))
		{
			playSound(this->m_testSound);
			FLOAT2 pos = m_minimap->getTerrainPos(g_mouse->getPos(), m_terrain->getTopLeftCorner(), m_terrain->getBottomRightCorner());
			usingMinimap = true;

			EntityMessage e;
			e.setPosition(FLOAT3(pos.x, 0.0f, pos.y));
			this->m_network->sendEntity(e);
		}
		else
		{
			for(int i = 0; i < m_entities.size(); i++)
			{
				D3DXVECTOR3 pickDir;
				D3DXVECTOR3 pickOrig;
				g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
				float dist;
				if(m_entities[i]->m_model->intersects(dist, pickOrig, pickDir))
				{
					this->m_network->sendAttackEntityMessage(AttackEntityMessage(0, m_entities[i]->m_id));
				}
			}
		}
	}
	else if(g_mouse->isRButtonReleased())
	{
		usingMinimap = false;
	}
	if(g_mouse->isRButtonDown())
	{
		if(!usingMinimap)
		{
			bool validMove = true;

			for(int i = 0; i < m_entities.size(); i++)
			{
				D3DXVECTOR3 pickDir;
				D3DXVECTOR3 pickOrig;
				g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
				float dist;
				if(m_entities[i]->m_model->intersects(dist, pickOrig, pickDir))
				{
					validMove = false;
				}
			}

			if(validMove)
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
		}
	}

	this->m_hud->Update(_dt);
	this->m_emilmackesFpsText->update(_dt);

	//this->m_cursor.setPosition(g_mouse->getPos());
}

Terrain *GameState::importTerrain(string filepath)
{
	FLOAT3 v1 = FLOAT3(0.0f, 0.0f, 0.0f); 
	FLOAT3 v2 = FLOAT3(100.0f, 0.0f, 100.0f);

	vector<string> blendMaps = vector<string>(2);
	vector<string> textures;
	textures.push_back("textures\\1.jpg");
	textures.push_back("textures\\2.jpg");
	textures.push_back("textures\\3.jpg");
	textures.push_back("textures\\4.jpg");
	textures.push_back("textures\\5.jpg");
	textures.push_back("textures\\6.jpg");
	textures.push_back("textures\\7.jpg");
	textures.push_back("textures\\8.jpg");

	ifstream stream;
	stream.open(filepath);
	
	while(!stream.eof())
	{
		char buf[1024];
		char key[100];
		stream.getline(buf, 1024);
		sscanf(buf, "%s", key);

		if(strcmp(key, "bmp1:") == 0)
		{
			char file[100];
			sscanf(buf, "bmp1: %s", &file);
			blendMaps[0] = "maps\\" + string(file);
		}
		else if(strcmp(key, "bmp2:") == 0)
		{
			char file[100];
			sscanf(buf, "bmp2: %s", &file);
			blendMaps[1] = "maps\\" + string(file);
		}
		else if(strcmp(key, "minimap:") == 0)
		{
			char file[100];
			sscanf(buf, "minimap: %s", &file);
			m_minimap = new Minimap("maps\\" + string(file));
		}
	}
	
	stream.close();

	return g_graphicsEngine->createTerrain(v1, v2, textures, blendMaps);
}