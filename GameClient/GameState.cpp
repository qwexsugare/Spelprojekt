#include "GameState.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"
#include <sstream>

GameState::GameState()
{
	this->m_hud = new HudMenu();
	this->m_rotation = 0.0f;
	this->m_testSound = createSoundHandle("knife.wav", false);
	this->m_fpsText = g_graphicsEngine->createText("", INT2(300, 0), 40, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));
	this->m_emilmackesFpsText = new TextInput("text1.png", INT2(1000, 600), 100);
	this->m_emilsFps = new TextLabel("fps = 10", "text1.png", INT2(g_graphicsEngine->getRealScreenSize().x/2.0f, 0) , 100);

	// Create a fucking awesome terrain
	vector<string> textures;
	textures.push_back("terrain_texture1.png");
	textures.push_back("terrain_texture2.png");
	textures.push_back("terrain_texture3.png");
	textures.push_back("terrain_texture4.png");
	vector<string> blendMaps;
	blendMaps.push_back("blendmap.png");
	this->m_terrain = this->importTerrain("maps\\race.txt");

	this->m_network = new Client();

	this->m_network->connect(sf::IPAddress::GetLocalAddress(), 1350);
	//this->m_network->connect(sf::IPAddress("194.47.155.248"), 1350);

	g_graphicsEngine->createPointLight(FLOAT3(50.0f, 10.0f, 50.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(0.5f, 0.5f, 0.5f), FLOAT3(0.2f, 0.2f, 0.2f), 10.0f);
	g_graphicsEngine->createPointLight(FLOAT3(25.0f, 10.0f, 75.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 0.0f), FLOAT3(0.5f, 0.5f, 0.0f), 10.0f);
	g_graphicsEngine->createPointLight(FLOAT3(25.0f, 10.0f, 25.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(0.0f, 1.0f, 1.0f), FLOAT3(0.0f, 0.5f, 0.5f), 10.0f);
	g_graphicsEngine->createPointLight(FLOAT3(75.0f, 10.0f, 25.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 0.0f, 1.0f), FLOAT3(0.2f, 0.0f, 0.5f), 10.0f);
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_entities.size(); i++)
		delete this->m_entities[i];

	if(m_minimap)
		delete this->m_minimap;
	delete this->m_network;
	delete this->m_emilmackesFpsText;
	delete this->m_emilsFps;
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
		this->m_emilsFps->setText(ss.str());
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
				this->m_entities[i]->m_type = (ServerEntity::Type)e.getType();
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
		g_graphicsEngine->getCamera()->setX(min(g_graphicsEngine->getCamera()->getPos().x+CAMERA_SPEED*_dt, m_terrain->getWidth()-27.0f));
	}
	else if(g_graphicsEngine->getCamera()->getPos().x > 27.0f && (g_mouse->getPos().x <= 10 || g_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setX(max(g_graphicsEngine->getCamera()->getPos().x-CAMERA_SPEED*_dt, 27.0f));
	}
	if(g_graphicsEngine->getCamera()->getPos().z < m_terrain->getHeight()-4.0f && (g_mouse->getPos().y >= g_graphicsEngine->getScreenSize().y-10 || g_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setZ(min(g_graphicsEngine->getCamera()->getPos().z+CAMERA_SPEED*_dt, m_terrain->getHeight()-4.0f));
	}
	else if(g_graphicsEngine->getCamera()->getPos().z > 25.0f && (g_mouse->getPos().y <= 10 || g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setZ(max(g_graphicsEngine->getCamera()->getPos().z-CAMERA_SPEED*_dt, 25.0f));
	}

	static bool usingMinimap = false;
	static bool movingCameraWithMinimap = false;
	if(g_mouse->isLButtonPressed())
	{
		if(m_minimap->isMouseInMap(g_mouse->getPos()))
		{
			movingCameraWithMinimap = true;
		}
	}
	if(g_mouse->isLButtonDown())
	{

	}
	else if(g_mouse->isLButtonReleased())
	{
		movingCameraWithMinimap = false;
	}
	if(g_mouse->isRButtonPressed())
	{
		if(m_minimap->isMouseInMap(g_mouse->getPos()))
		{
			playSound(this->m_testSound);
			FLOAT2 pos = m_minimap->getTerrainPos(g_mouse->getPos());
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
	else if(g_mouse->isRButtonReleased())
	{
		usingMinimap = false;
	}

	if(movingCameraWithMinimap)
	{
		if(m_minimap->isMouseInMap(g_mouse->getPos()))
		{
			FLOAT2 pos = m_minimap->getTerrainPos(g_mouse->getPos());

			if(pos.x > m_terrain->getWidth()-27.0f)
			{
				g_graphicsEngine->getCamera()->setX(m_terrain->getWidth()-27.0f);
			}
			else if(pos.x < 27.0f)
			{
				g_graphicsEngine->getCamera()->setX(27.0f);
			}
			else
			{
				g_graphicsEngine->getCamera()->setX(pos.x);
			}
			
			if(pos.y < 25.0f)
			{
				g_graphicsEngine->getCamera()->setZ(25.0f);
			}
			else if(pos.y > m_terrain->getHeight()-4.0f)
			{
				g_graphicsEngine->getCamera()->setZ(m_terrain->getHeight()-4.0f);
			}
			else
			{
				g_graphicsEngine->getCamera()->setZ(pos.y);
			}
		}
		else
			movingCameraWithMinimap = false;
	}

	this->m_hud->Update(_dt);
	this->m_emilmackesFpsText->update(_dt);
	m_minimap->update(m_entities, g_graphicsEngine->getCamera()->getPos2D());
	//this->m_cursor.setPosition(g_mouse->getPos());
}

Terrain *GameState::importTerrain(string filepath)
{
	Terrain* terrain = NULL;

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

	string minimap;
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
			minimap = string(file);
		}

		sscanf("lololol", "%s", key);
	}
	
	stream.close();
	
	terrain = g_graphicsEngine->createTerrain(v1, v2, textures, blendMaps);
	m_minimap = new Minimap("maps\\" + minimap, terrain->getTopLeftCorner(), terrain->getBottomRightCorner(), g_graphicsEngine->getCamera()->getPos2D());

	return terrain;
}