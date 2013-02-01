#include "GameState.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"
#include <sstream>
#include "Skill.h"
#include "ClientSkillEffects.h"

GameState::GameState()
{
	this->m_rotation = 0.0f;
	this->m_fpsText = g_graphicsEngine->createText("", INT2(300, 0), 40, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));
	this->m_network = new Client();
	this->m_hud = new HudMenu(this->m_network);

	g_graphicsEngine->getCamera()->set(FLOAT3(50.0f, 7.50f, 50.0f), FLOAT3(0.0f, -1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 1.0f), FLOAT3(1.0f, 0.0f, 0.0f));
	g_graphicsEngine->getCamera()->rotate(0.0f, 0.4f, 0.0f);

	this->m_network->connect(sf::IPAddress::GetLocalAddress(), 1350);
	//this->m_network->connect(sf::IPAddress("194.47.155.248"), 1350);

	//g_graphicsEngine->createPointLight(FLOAT3(50.0f, 5.0f, 50.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 10.0f);
	//g_graphicsEngine->createPointLight(FLOAT3(25.0f, 10.0f, 75.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 0.0f), FLOAT3(0.5f, 0.5f, 0.0f), 20.0f);
	//g_graphicsEngine->createPointLight(FLOAT3(25.0f, 10.0f, 25.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(0.0f, 1.0f, 1.0f), FLOAT3(0.0f, 0.5f, 0.5f), 20.0f);
	//g_graphicsEngine->createPointLight(FLOAT3(75.0f, 10.0f, 25.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 0.0f, 1.0f), FLOAT3(0.2f, 0.0f, 0.5f), 20.0f);
	g_graphicsEngine->createDirectionalLight(FLOAT3(0.5f, 1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(0.01f, 0.01f, 0.01f));
	this->s = g_graphicsEngine->createSpotLight(FLOAT3(50.0f, 5.0f, 50.0f), FLOAT3(2.0f, 1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(0.5f, 0.5f, 0.5f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT2(0.6f, 0.3f), 50.0f);
	this->importMap("race");
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_entities.size(); i++)
		delete this->m_entities[i];
	for(int i = 0; i < this->m_roads.size(); i++)
		g_graphicsEngine->removeRoad(m_roads[i]);
	for(int i = 0; i < m_ClientSkillEffects.size(); i++)
		delete m_ClientSkillEffects[i];

	if(m_minimap)
		delete this->m_minimap;
	delete this->m_network;
	delete this->m_hud;
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
		ss << "FPS: " << 1.0f/_dt << "            Dt*1000: " << _dt*1000.0f << " Entities: " << this->m_entities.size() << "\nLifezorz: ";
		for(int i = 0; i < m_entities.size(); i++)
		{
			if(m_entities[i]->m_type == ServerEntity::HeroType)
			{
				ss << m_entities[i]->m_health;
			}
		}
		this->m_fpsText->setString(ss.str());
		lol = -0.5f;
	}

	D3DXVECTOR3 pickDir;
	D3DXVECTOR3 pickOrig;
	g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
	this->s->setPosition(FLOAT3(pickOrig.x, pickOrig.y, pickOrig.z));
	this->s->setDirection(FLOAT3(pickDir.x, pickDir.y, pickDir.z));

	while(this->m_network->entityQueueEmpty() == false)
	{
		NetworkEntityMessage e = this->m_network->entityQueueFront();
		bool found = false;

		if(e.getEntityId() > 3)
		{
			int i = 0;
		}

		for(int i = 0; i < this->m_entities.size() && found == false; i++)
		{
			if(this->m_entities[i]->m_id == e.getEntityId())
			{
				this->m_entities[i]->m_model->setPosition(e.getPosition());
				this->m_entities[i]->m_model->setRotation(e.getRotation());
				this->m_entities[i]->m_type = (ServerEntity::Type)e.getEntityType();
				this->m_entities[i]->m_health = e.getHealth();
				found = true;
			}
		}

		if(found == false)
		{
			Model* model = g_graphicsEngine->createModel(this->m_modelIdHolder.getModel(e.getModelId()), FLOAT3(e.getPosition().x, 0.0, e.getPosition().z));
			if(model)
			{
				this->m_entities.push_back(new Entity(model, e.getEntityId()));
			}
		}
	}

	while(this->m_network->removeEntityQueueEmpty() == false)
	{
		NetworkRemoveEntityMessage rem = this->m_network->removeEntityQueueFront();
		bool found = false;

		for(int i = 0; i < this->m_entities.size() && found == false; i++)
		{
			if(this->m_entities[i]->m_id == rem.getEntityId())
			{
				g_graphicsEngine->removeModel(this->m_entities[i]->m_model);
				delete this->m_entities[i];
				this->m_entities.erase(this->m_entities.begin() + i);
				i = this->m_entities.size();
			}
		}
	}

	while(this->m_network->createActionQueueEmpty() == false)
	{
		NetworkCreateActionMessage e = this->m_network->createActionQueueFront();
		
		switch(e.getActionId())
		{
		case Skill::STUNNING_STRIKE:
			m_ClientSkillEffects.push_back(new StunningStrikeClientSkillEffect(e.getPosition()));
			break;
		/*case Skill::DEMONIC_PRESENCE:
			m_ClientSkillEffects.push_back(new StunningStrikeClientSkillEffect(e.getPosition()));
			break;*/
		}
	}

	while(this->m_network->createActionPositionQueueEmpty() == false)
	{
		NetworkCreateActionPositionMessage e = this->m_network->createActionPositionQueueFront();
		
		switch(e.getActionId())
		{
		case Skill::CLOUD_OF_DARKNESS:
			m_ClientSkillEffects.push_back(new CloudOfDarknessClientSkillEffect(e.getPosition()));
			break;
		}
	}

	while(this->m_network->createActionTargetQueueEmpty() == false)
	{
		NetworkCreateActionTargetMessage e = this->m_network->createActionTargetQueueFront();
		
		switch(e.getActionId())
		{
		case Skill::HEALING_TOUCH:
			m_ClientSkillEffects.push_back(new HealingTouchClientSkillEffect(e.getPosition()));
			break;
		/*case Skill::CHAIN_STRIKE:
			m_ClientSkillEffects.push_back(new ChainStrikeSkillEffect(e.getPosition()));
			break;*/
		}
	}

	while(this->m_network->skillBoughtQueueEmpty() == false)
	{
		NetworkSkillBoughtMessage e = this->m_network->skillBoughtQueueFront();
		
		// Do something!
		this->m_hud->addSkill(e.getActionId());
		this->m_hud->setResources(e.getResources());
	}

	for(int i = 0; i < m_ClientSkillEffects.size(); i++)
	{
		m_ClientSkillEffects[i]->update(_dt);
		if(!m_ClientSkillEffects[i]->getActive())
		{
			delete m_ClientSkillEffects[i];
			m_ClientSkillEffects.erase(m_ClientSkillEffects.begin()+i);
			i--;
		}
	}

	static float CAMERA_SPEED = 16.0f;
	if((g_mouse->getPos().x >= g_graphicsEngine->getScreenSize().x-10 || g_keyboard->getKeyState(VK_RIGHT) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setX(g_graphicsEngine->getCamera()->getPos().x+CAMERA_SPEED*_dt);
	}
	else if((g_mouse->getPos().x <= 10 || g_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setX(g_graphicsEngine->getCamera()->getPos().x-CAMERA_SPEED*_dt);
	}
	if((g_mouse->getPos().y >= g_graphicsEngine->getScreenSize().y-10 || g_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setZ(g_graphicsEngine->getCamera()->getPos().z+CAMERA_SPEED*_dt);
	}
	else if((g_mouse->getPos().y <= 10 || g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setZ(g_graphicsEngine->getCamera()->getPos().z-CAMERA_SPEED*_dt);
	}
	/*if(g_graphicsEngine->getCamera()->getPos().x < m_terrain->getWidth()-5.0f && (g_mouse->getPos().x >= g_graphicsEngine->getScreenSize().x-10 || g_keyboard->getKeyState(VK_RIGHT) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setX(min(g_graphicsEngine->getCamera()->getPos().x+CAMERA_SPEED*_dt, m_terrain->getWidth()-5.0f));
	}
	else if(g_graphicsEngine->getCamera()->getPos().x > 5.0f && (g_mouse->getPos().x <= 10 || g_keyboard->getKeyState(VK_LEFT) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setX(max(g_graphicsEngine->getCamera()->getPos().x-CAMERA_SPEED*_dt, 5.0f));
	}
	if(g_graphicsEngine->getCamera()->getPos().z < m_terrain->getHeight()+6.0f && (g_mouse->getPos().y >= g_graphicsEngine->getScreenSize().y-10 || g_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setZ(min(g_graphicsEngine->getCamera()->getPos().z+CAMERA_SPEED*_dt, m_terrain->getHeight()+6.0f));
	}
	else if(g_graphicsEngine->getCamera()->getPos().z > 15.0f && (g_mouse->getPos().y <= 10 || g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setZ(max(g_graphicsEngine->getCamera()->getPos().z-CAMERA_SPEED*_dt, 15.0f));
	}*/

	if(g_keyboard->getKeyState('Q') == Keyboard::KEY_PRESSED)
	{
		// Calc some fucken pick ray out mofos
		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());

		float k = (-pickOrig.y)/pickDir.y;
		D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;
		this->m_network->sendMessage(NetworkUseActionPositionMessage(Skill::DEATH_TOWER, FLOAT3(terrainPos.x, 0.0f, terrainPos.z)));
	}
	if(g_mouse->isLButtonPressed())
	{
		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());

		float k = (-pickOrig.y)/pickDir.y;
		D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;
		this->m_network->sendMessage(NetworkUseActionPositionMessage(Skill::CLOUD_OF_DARKNESS, FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z)));

		for(int i = 0; i < m_entities.size(); i++)
		{
			float dist;
			if(m_entities[i]->m_model->intersects(dist, pickOrig, pickDir))
			{
				this->m_network->sendMessage(NetworkUseActionTargetMessage(Skill::CHAIN_STRIKE, m_entities[i]->m_id));
			}
		}
	}
	if(g_mouse->isLButtonDown())
	{

	}
	else if(g_mouse->isLButtonReleased())
	{

	}
	if(g_mouse->isRButtonPressed())
	{
		if(m_minimap->isMouseInMap(g_mouse->getPos()))
		{
			FLOAT2 pos = m_minimap->getTerrainPos(g_mouse->getPos());

			NetworkUseActionPositionMessage e = NetworkUseActionPositionMessage(Skill::MOVE, FLOAT3(pos.x, 0.0f, pos.y));
			this->m_network->sendMessage(e);
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
					this->m_network->sendMessage(NetworkUseActionTargetMessage(Skill::ATTACK, m_entities[i]->m_id));
				}
			}
		}
	}
	if(g_mouse->isRButtonDown() && !m_minimap->isMouseInMap(g_mouse->getPos()))
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

			NetworkUseActionPositionMessage e = NetworkUseActionPositionMessage(Skill::MOVE, FLOAT3(terrainPos.x, 0.0f, terrainPos.z));
			this->m_network->sendMessage(e);
		}
	}
	else if(g_mouse->isRButtonReleased())
	{

	}

	this->m_hud->Update(_dt, m_entities);
	m_minimap->update(m_entities, g_graphicsEngine->getCamera()->getPos2D(), this->m_terrain->getWidth(), this->m_terrain->getHeight());
	//this->m_cursor.setPosition(g_mouse->getPos());
}

void GameState::importMap(string _map)
{
	string path = "maps/" + _map + "/";

	FLOAT3 v1 = FLOAT3(0.0f, 0.0f, 0.0f);
	FLOAT3 v2 = FLOAT3(100.0f, 0.0f, 100.0f);

	vector<string> blendMaps = vector<string>(2);
	vector<string> textures;
	textures.push_back("textures\\1.png");
	textures.push_back("textures\\2.png");
	textures.push_back("textures\\3.png");
	textures.push_back("textures\\4.png");
	textures.push_back("textures\\5.png");
	textures.push_back("textures\\6.png");
	textures.push_back("textures\\7.png");
	textures.push_back("textures\\8.png");

	string minimap;
	ifstream stream;
	stream.open(path + _map + ".txt");
	while(!stream.eof())
	{
		char buf[1024];
		char key[1024];
		stream.getline(buf, 1024);
		sscanf(buf, "%s", key);

		if(strcmp(key, "bmp1:") == 0)
		{
			char file[100];
			sscanf(buf, "bmp1: %s", &file);
			blendMaps[0] = path + string(file);
		}
		else if(strcmp(key, "bmp2:") == 0)
		{
			char file[100];
			sscanf(buf, "bmp2: %s", &file);
			blendMaps[1] = path + string(file);
		}
		else if(strcmp(key, "width:") == 0)
		{
			int width;
			sscanf(buf, "width: %d", &width);
			v2.x = width;
		}		
		else if(strcmp(key, "height:") == 0)
		{
			int height;
			sscanf(buf, "height: %d", &height);
			v2.z = height;
		}
		else if(strcmp(key, "minimap:") == 0)
		{
			char file[100];
			sscanf(buf, "minimap: %s", &file);
			minimap = string(file);
		}
		else if(strcmp(key, "Surfaceplanes:") == 0)
		{
			string texture;
			bool done = false;
			while(!done)
			{
				stream.getline(buf, 1024);
				sscanf(buf, "%s", key);
				
				if(strcmp(key, "SF:") == 0)
				{
					char in[100];
					sscanf(buf, "SF: %s", &in);
					texture = string(in);
				}
				else if(strcmp(key, "end") == 0)
				{
					done = true;
				}
				else // Else its an actual road piece (at least we hope so because else we are screwed)
				{
					float rot;
					float x, z;
					sscanf(buf, "%f %f %f", &rot, &x, &z);

					m_roads.push_back(g_graphicsEngine->createRoad(texture, FLOAT3(x, 0.0f, v2.z+z), rot));
				}
			}
		}
		else if(strcmp(key, "MODELS:") == 0)
		{
			string s;
			bool done = false;
			while(!done)
			{
				stream.getline(buf, 1024);
				sscanf(buf, "%s", key);
				
				if(strcmp(key, "end") == 0)
				{
					done = true;
				}
				else
				{
					char in[100];
					FLOAT3 position;
					FLOAT3 rotation;
					sscanf(buf, "%s %f %f %f %f %f %f", &in, &position.x, &position.y, &position.z, &rotation.y, &rotation.x, &rotation.z);

					position.z = v2.z+position.z;
					rotation.x = rotation.x * (D3DX_PI/180.0f);
					
					Model *m = g_graphicsEngine->createModel(key, position);
					m->setRotation(rotation);

					position.y = position.y + 1.0f;

					if(strcmp(in, "Lamp") == 0)
					{
						g_graphicsEngine->createPointLight(position, FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f,0.9f), FLOAT3(0.1f, 0.1f,0.1f), 0.6f);
					}
				}
			}
		}


		sscanf("bugfix", "%s", key);
	}
	stream.close();
	vector<string> nm; nm.push_back("textures/1_2_3_4_Normalmap.png");
	m_terrain = g_graphicsEngine->createTerrain(v1, v2, textures, blendMaps, nm);
	m_minimap = new Minimap(path + minimap, m_terrain->getTopLeftCorner(), m_terrain->getBottomRightCorner(), g_graphicsEngine->getCamera()->getPos2D());
}