#include "GameState.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"
#include <sstream>
#include "Skill.h"
#include "ClientSkillEffects.h"
#include "Path.h"
#include "MyAlgorithms.h"
#include "SpeechManager.h"

GameState::GameState(Client *_network)
{
	this->m_network = _network;
	this->importMap("levelone");

	// Get all hero data from the network
	while(m_network->heroInitQueueEmpty()){}
	NetworkHeroInitMessage e = m_network->heroInitQueueFront();
	m_playerInfos.resize(e.getIds().size());
	m_yourId = e.getYourId();
	for(int i = 0; i < e.getIds().size(); i++)
	{
		m_playerInfos[i].id = e.getIds()[i];
		m_playerInfos[i].heroType = e.getHeroTypes()[i];
	}

	switch(m_playerInfos[m_yourId].heroType)
	{
	case Hero::RED_KNIGHT:
		m_idleSound = createSoundHandle("red_knight/RedKnight_Idle_0.wav", false, false);
		m_attackSounds[0] = createSoundHandle("red_knight/RedKnight_Attack_0.wav", false, false);
		m_attackSounds[1] = createSoundHandle("red_knight/RedKnight_Attack_1.wav", false, false);
		m_attackSounds[2] = createSoundHandle("red_knight/RedKnight_Attack_2.wav", false, false);
		break;
	case Hero::ENGINEER:
		m_idleSound = createSoundHandle("Engineer_Idle_0.wav", false, false);
		m_attackSounds[0] = createSoundHandle("engineer/Engineer_Attack_0.wav", false, false);
		m_attackSounds[1] = createSoundHandle("engineer/Engineer_Attack_1.wav", false, false);
		m_attackSounds[2] = createSoundHandle("engineer/Engineer_Attack_2.wav", false, false);
		break;
	case Hero::THE_MENTALIST:
		m_idleSound = createSoundHandle("mentalist/Mentalist_Idle.wav", false, false);
		m_attackSounds[0] = createSoundHandle("mentalist/Mentalist_Attack_0.wav", false, false);
		m_attackSounds[1] = createSoundHandle("mentalist/Mentalist_Attack_1.wav", false, false);
		m_attackSounds[2] = createSoundHandle("mentalist/Mentalist_Attack_2.wav", false, false);
			break;
	case Hero::OFFICER:
		m_idleSound = createSoundHandle("officer/Officer_Death_1.wav", false, false);
		m_attackSounds[0] = createSoundHandle("officer/Officer_Attack_0.wav", false, false);
		m_attackSounds[1] = createSoundHandle("officer/Officer_Attack_1.wav", false, false);
		m_attackSounds[2] = createSoundHandle("officer/Officer_Attack_2.wav", false, false);
		break;
	case Hero::DOCTOR:
		m_idleSound = createSoundHandle("doctor/Doctor_Idle.wav", false, false);
		m_attackSounds[0] = createSoundHandle("doctor/Doctor_Attack_0.wav", false, false);
		m_attackSounds[1] = createSoundHandle("doctor/Doctor_Attack_1.wav", false, false);
		m_attackSounds[2] = createSoundHandle("doctor/Doctor_Attack_2.wav", false, false);
		break;
	}

	m_attackSoundTimer = 0.0f;
	m_idle = false;
	
	this->m_fpsText = g_graphicsEngine->createText("", INT2(300, 0), 40, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));
	this->m_hud = new HudMenu(this->m_network, m_playerInfos[m_yourId].heroType);
	this->m_clientEntityHandler = new ClientEntityHandler();

	g_graphicsEngine->getCamera()->set(FLOAT3(50.0f, 7.5f, 50.0f), FLOAT3(0.0f, -1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 1.0f), FLOAT3(1.0f, 0.0f, 0.0f));
	g_graphicsEngine->getCamera()->rotate(0.0f, -0.4f, 0.0f);

	g_graphicsEngine->createPointLight(FLOAT3(50.0f, 2.0f, 60.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, false);
	//g_graphicsEngine->createPointLight(FLOAT3(25.0f, 10.0f, 75.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 0.0f), FLOAT3(0.5f, 0.5f, 0.0f), 20.0f, false);
	//g_graphicsEngine->createPointLight(FLOAT3(25.0f, 10.0f, 25.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(0.0f, 1.0f, 1.0f), FLOAT3(0.0f, 0.5f, 0.5f), 20.0f, false);
	//g_graphicsEngine->createPointLight(FLOAT3(60.0f, 1.0f, 60.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 10.0f, false);
	//g_graphicsEngine->createDirectionalLight(FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(0.2f, 0.2f, 0.2f), FLOAT3(0.01f, 0.01f, 0.01f));
	g_graphicsEngine->createDirectionalLight(FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(0.5f, 0.5f, 0.5f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(0.01f, 0.01f, 0.01f));
	//g_graphicsEngine->createSpotLight(FLOAT3(60.0f, 5.0f, 60.0f), FLOAT3(1.0f, 1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT2(0.9f, 0.8f), 300.0f);
	//g_graphicsEngine->createSpotLight(FLOAT3(10.0f, 10.0f, 10.0f), FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT2(0.9f, 0.8f), 300.0f);
	//g_graphicsEngine->createSpotLight(FLOAT3(50.0f, 10.0f, 50.0f), FLOAT3(0.0f, 1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT2(0.9f, 0.8f), 300.0f);

	m_healthText = g_graphicsEngine->createText("No target acquired", INT2(500, 500), 30, D3DXCOLOR(1,1,1,1));
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_roads.size(); i++)
		g_graphicsEngine->removeRoad(m_roads[i]);
	for(int i = 0; i < m_ClientSkillEffects.size(); i++)
		delete m_ClientSkillEffects[i];
	for(int i = 0; i < GameState::NR_OF_ATTACK_SOUNDS; i++)
	{
		stopSound(m_attackSounds[i]);
		deactivateSound(m_attackSounds[i]);
	}

	if(m_minimap)
		delete this->m_minimap;
	//delete this->m_network;
	delete this->m_hud;
	delete this->m_clientEntityHandler;
	g_graphicsEngine->removeText(m_healthText);
}

void GameState::end()
{
	g_graphicsEngine->removeTerrain(this->m_terrain);
	
	delete this->m_clientEntityHandler;
	
	g_graphicsEngine->removeText(this->m_fpsText);

	this->setDone(true);
}

State::StateEnum GameState::nextState()
{
	return State::MAIN_MENU;
}

void GameState::update(float _dt)
{
	m_attackSoundTimer = max(m_attackSoundTimer-_dt, 0.0f);
	/*if(!isSoundPlaying(m_idleSound))
	{
		m_idleSoundTimer = max(m_idleSoundTimer-_dt, 0.0f);
		if(m_idleSoundTimer == 0.0f)
		{
			playSound(m_idleSound);
			m_idleSoundTimer = IDLE_SOUND_DELAY;
		}
	}*/

	// Update FRAMES PER SECOND (FPS) text
	static float lol = 0.0f;
	lol += _dt;
	if(lol > 1.0f)
	{
		stringstream ss;
		ss << "FPS: " << 1.0f/_dt << "            Dt*1000: " << _dt*1000.0f;
		this->m_fpsText->setString(ss.str());
		lol = -0.5f;
	}

	while(this->m_network->entityQueueEmpty() == false)
	{
		NetworkEntityMessage e = this->m_network->entityQueueFront();
		bool found = false;

		if(e.getEntityId() > 3)
		{
			int i = 0;
		}

		Entity* entity = this->m_clientEntityHandler->getEntity(e.getEntityId());

		if(entity != NULL)
		{
			if(e.getPosition().x == e.getPosition().x)
				entity->m_model->setPosition(e.getPosition());

			if(e.getRotation().x == e.getRotation().x)
				entity->m_model->setRotation(e.getRotation());
			entity->m_type = (ServerEntity::Type)e.getEntityType();
			entity->m_health = e.getHealth();

			if(e.getEntityId() == this->m_playerInfos[this->m_yourId].id)
			{
				this->m_hud->setHealth(e.getHealth());
			}
		}
		else
		{
			Model* model = g_graphicsEngine->createModel(this->m_modelIdHolder.getModel(e.getModelId()), FLOAT3(e.getPosition().x, 0.0, e.getPosition().z));
			model->setTextureIndex(m_modelIdHolder.getTexture(e.getModelId()));
			model->setGlowIndex(m_modelIdHolder.getGlowmap(e.getModelId()));

			if(this->m_modelIdHolder.getHat(e.getModelId()) != "")
			{
				model->SetHat(g_graphicsEngine->getMesh(this->m_modelIdHolder.getHat(e.getModelId())));
			}
			if(this->m_modelIdHolder.getRightHand(e.getModelId()) != "")
			{
				model->SetRightHand(g_graphicsEngine->getMesh(this->m_modelIdHolder.getRightHand(e.getModelId())));
			}
			if(this->m_modelIdHolder.getLeftHand(e.getModelId()) != "")
			{
				model->SetLeftHand(g_graphicsEngine->getMesh(this->m_modelIdHolder.getLeftHand(e.getModelId())));
			}
			if(model)
			{
				//this->m_entities.push_back(new Entity(model, e.getEntityId()));
				this->m_clientEntityHandler->addEntity(new Entity(model, e.getEntityId()));

				if(e.getEntityType() == ServerEntity::HeroType)
				{
					g_graphicsEngine->getCamera()->setX(e.getPosition().x);
					g_graphicsEngine->getCamera()->setZ(e.getPosition().z - 3.0f);
				}
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
		case Skill::MOVE:
			this->m_ClientSkillEffects.push_back(new RunClientSkillEffect(e.getSenderId()));
			break;
		case Skill::IDLE:
			this->m_ClientSkillEffects.push_back(new IdleClientSkillEffect(e.getSenderId()));
			m_idleSoundTimer = IDLE_SOUND_DELAY;
			m_idle = true;
			break;
		case Skill::DEATH:
			this->m_ClientSkillEffects.push_back(new DeathClientSkillEffect(e.getSenderId(), e.getPosition()));
			break;
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
		case Skill::ATTACK:
			m_ClientSkillEffects.push_back(new CloudOfDarknessClientSkillEffect(e.getPosition()));
			break;
		}
	}

	while(this->m_network->createActionTargetQueueEmpty() == false)
	{
		NetworkCreateActionTargetMessage e = this->m_network->createActionTargetQueueFront();
		
		switch(e.getActionId())
		{
		case Skill::RANGED_ATTACK:
			if(e.getTargetId() == m_playerInfos[m_yourId].id)
				m_ClientSkillEffects.push_back(new ArrowClientSkillEffect(e.getPosition(), e.getTargetId(), m_playerInfos[m_yourId].heroType));
			else
				m_ClientSkillEffects.push_back(new ArrowClientSkillEffect(e.getPosition(), e.getTargetId(), e.getSenderId()));
			break;
		case Skill::HEALING_TOUCH:
			m_ClientSkillEffects.push_back(new HealingTouchClientSkillEffect(e.getPosition()));
			break;
		case Skill::DEMONIC_PRESENCE:
			m_ClientSkillEffects.push_back(new DemonicPresenceClientSkillEffect(e.getTargetId()));
			break;
		case Skill::ENIGMATIC_PRESENCE:
			m_ClientSkillEffects.push_back(new EnigmaticPresenceClientSkillEffect(e.getTargetId()));
			break;
		case Skill::COURAGE_HONOR_VALOR:
			m_ClientSkillEffects.push_back(new CourageHonorValorClientSkillEffect(e.getTargetId()));
			break;
		case Skill::SIMONS_EVIL:
			m_ClientSkillEffects.push_back(new SimonsEvilClientSkillEffect(e.getTargetId()));
			break;
		case Skill::MELEE_ATTACK:
			this->m_ClientSkillEffects.push_back(new MeleeAttackClientSkillEffect(e.getSenderId(), e.getTargetId(), m_playerInfos[m_yourId]));
			break;
		}
	}

	while(this->m_network->skillBoughtQueueEmpty() == false)
	{
		NetworkSkillBoughtMessage e = this->m_network->skillBoughtQueueFront();
		
		// Do something!
		this->m_hud->addSkill(e.getActionId());
		this->m_hud->setResources(e.getResources());
	}

	while(this->m_network->removeActionTargetQueueEmpty() == false)
	{
		NetworkRemoveActionTargetMessage e = this->m_network->removeActionTargetQueueFront();
		
		switch(e.getActionId())
		{
		case Skill::DEMONIC_PRESENCE:
			{
				for(int i = 0; i < m_ClientSkillEffects.size(); i++)
				{
					if(typeid(DemonicPresenceClientSkillEffect) == typeid(*m_ClientSkillEffects[i]))
					{
						if(((DemonicPresenceClientSkillEffect*)m_ClientSkillEffects[i])->getMasterId() == e.getTargetId())
						{
							delete m_ClientSkillEffects[i];
							m_ClientSkillEffects.erase(m_ClientSkillEffects.begin()+i);
							i = m_ClientSkillEffects.size();
						}
					}
				}
			}
			break;
		case Skill::COURAGE_HONOR_VALOR:
			{
				for(int i = 0; i < m_ClientSkillEffects.size(); i++)
				{
					if(typeid(CourageHonorValorClientSkillEffect) == typeid(*m_ClientSkillEffects[i]))
					{
						if(((CourageHonorValorClientSkillEffect*)m_ClientSkillEffects[i])->getMasterId() == e.getTargetId())
						{
							delete m_ClientSkillEffects[i];
							m_ClientSkillEffects.erase(m_ClientSkillEffects.begin()+i);
							i = m_ClientSkillEffects.size();
						}
					}
				}
			}
			break;
		case Skill::ENIGMATIC_PRESENCE:
			{
				for(int i = 0; i < m_ClientSkillEffects.size(); i++)
				{
					if(typeid(EnigmaticPresenceClientSkillEffect) == typeid(*m_ClientSkillEffects[i]))
					{
						if(((EnigmaticPresenceClientSkillEffect*)m_ClientSkillEffects[i])->getMasterId() == e.getTargetId())
						{
							delete m_ClientSkillEffects[i];
							m_ClientSkillEffects.erase(m_ClientSkillEffects.begin()+i);
							i = m_ClientSkillEffects.size();
						}
					}
				}
			}
			break;
		}
	}

	while(this->m_network->skillUsedQueueEmpty() == false)
	{
		NetworkSkillUsedMessage e = this->m_network->skillUsedQueueFront();
		
		// Do something!
		this->m_hud->skillUsed(e.getActionIndex(), e.getActionId(), e.getCooldown());
	}

	while(this->m_network->removeEntityQueueEmpty() == false)
	{
		NetworkRemoveEntityMessage rem = this->m_network->removeEntityQueueFront();
		bool found = false;

		Entity* entity = this->m_clientEntityHandler->getEntity(rem.getEntityId());

		if(entity != NULL)
		{
			g_graphicsEngine->removeModel(entity->m_model);
			this->m_clientEntityHandler->removeEntity(entity);
		}
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

	static float CAMERA_SPEED = 12.0f;
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
		g_graphicsEngine->getCamera()->setZ(g_graphicsEngine->getCamera()->getPos().z-CAMERA_SPEED*_dt);
	}
	else if((g_mouse->getPos().y <= 10 || g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP))
	{
		g_graphicsEngine->getCamera()->setZ(g_graphicsEngine->getCamera()->getPos().z+CAMERA_SPEED*_dt);
	}
	
	if(g_keyboard->getKeyState('Q') == Keyboard::KEY_PRESSED)
	{
		// Calc some fucken pick ray out mofos
		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
		float dist;
		float k = (-pickOrig.y)/pickDir.y;
		D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;

		m_network->sendMessage(NetworkUseActionPositionMessage(Skill::DEATH_TOWER, FLOAT3(terrainPos.x, 0.0f, terrainPos.z)));
	}
	if(g_mouse->isLButtonPressed())
	{
		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());

		float k = (-pickOrig.y)/pickDir.y;
		D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;
	}
	if(g_mouse->isLButtonDown())
	{

	}
	else if(g_mouse->isLButtonReleased())
	{

	}
	if(g_mouse->isRButtonPressed() == true)
	{
		if(m_minimap->isMouseInMap(g_mouse->getPos()) == false)
		{
			bool validMove = true;
			
			D3DXVECTOR3 pickDir;
			D3DXVECTOR3 pickOrig;
			g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
			float dist;
			vector<Entity*> m_entities = m_clientEntityHandler->getEntities();
			for(int i = 0; i < m_entities.size(); i++)
			{
				if(m_entities[i]->m_type == ServerEntity::EnemyType && m_entities[i]->m_model->intersects(dist, pickOrig, pickDir))
				{
					this->m_network->sendMessage(NetworkUseActionTargetMessage(Skill::ATTACK, m_entities[i]->m_id));
					stringstream ss;
					ss << m_entities[i]->m_health;
					m_healthText->setString("Target health: " + ss.str());
					if(m_attackSoundTimer == 0.0f)
					{
						SpeechManager::speak(m_playerInfos[m_yourId].id, m_attackSounds[random(0, NR_OF_ATTACK_SOUNDS-1)]);
						m_attackSoundTimer = ATTACK_SOUND_DELAY;
					}
					validMove = false;
				}
			}

			if(validMove)
			{
				float k = (-pickOrig.y)/pickDir.y;
				D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;

				NetworkUseActionPositionMessage e = NetworkUseActionPositionMessage(Skill::MOVE, FLOAT3(terrainPos.x, 0.0f, terrainPos.z));
				this->m_network->sendMessage(e);
			}
		}
		else
		{
			FLOAT2 pos = m_minimap->getTerrainPos(g_mouse->getPos());

			NetworkUseActionPositionMessage e = NetworkUseActionPositionMessage(Skill::MOVE, FLOAT3(pos.x, 0.0f, pos.y));
			this->m_network->sendMessage(e);
		}
	}
	else if(g_mouse->isRButtonReleased())
	{

	}

	MeleeAttackClientSkillEffect::decreaseTimeBetweenDamageSounds(_dt);
	this->m_hud->Update(_dt, this->m_clientEntityHandler->getEntities());
	m_minimap->update(this->m_clientEntityHandler->getEntities(), g_graphicsEngine->getCamera()->getPos2D(), this->m_terrain->getWidth(), this->m_terrain->getHeight());
	//this->m_cursor.setPosition(g_mouse->getPos());
	SpeechManager::update();
}

void GameState::importMap(string _map)
{
	string path = "maps/" + _map + "/";

	FLOAT3 v1 = FLOAT3(0.0f, 0.0f, 0.0f);
	FLOAT3 v2 = FLOAT3(100.0f, 0.0f, 100.0f);

	vector<string> blendMaps = vector<string>(2);
	vector<string> textures;
	vector<string> normalMaps;
	vector<string> specularMaps;
	textures.push_back("textures\\1.png");
	textures.push_back("textures\\2.png");
	textures.push_back("textures\\3.png");
	textures.push_back("textures\\4.png");
	textures.push_back("textures\\5.png");
	textures.push_back("textures\\6.png");
	textures.push_back("textures\\7.png");
	textures.push_back("textures\\8.png");

	normalMaps.push_back("textures\\1_2_3_4_NM.png");
	normalMaps.push_back("textures\\1_2_3_4_NM.png");
	normalMaps.push_back("textures\\1_2_3_4_NM.png");
	normalMaps.push_back("textures\\1_2_3_4_NM.png");
	normalMaps.push_back("textures\\5_NM.png");
	normalMaps.push_back("textures\\6_NM.png");
	normalMaps.push_back("textures\\7_8_NM.png");
	normalMaps.push_back("textures\\7_8_NM.png");

	specularMaps.push_back("textures\\1_2_3_4_Specular.png");
	specularMaps.push_back("textures\\1_2_3_4_Specular.png");
	specularMaps.push_back("textures\\1_2_3_4_Specular.png");
	specularMaps.push_back("textures\\1_2_3_4_Specular.png");
	specularMaps.push_back("textures\\5_SM.png");
	specularMaps.push_back("textures\\6_SM.png");
	specularMaps.push_back("textures\\7_SM.png");
	specularMaps.push_back("textures\\8_SM.png");
	
	bool heightLoaded = false;
	bool widthLoaded = false;
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

			if(heightLoaded)
				g_graphicsEngine->initQuadTree(FLOAT2(v2.x, v2.z));
			else
				widthLoaded = true;
		}
		else if(strcmp(key, "height:") == 0)
		{
			int height;
			sscanf(buf, "height: %d", &height);
			v2.z = height;

			if(widthLoaded)
				g_graphicsEngine->initQuadTree(FLOAT2(v2.x, v2.z));
			else
				heightLoaded = true;
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
					float scale;
					sscanf(buf, "%f %f %f %f", &rot, &x, &z, &scale);
					rot = -rot * (D3DX_PI/180);

					m_roads.push_back(g_graphicsEngine->createRoad(texture, FLOAT3(x, 0.0f, -z), rot, scale));
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
					float scale;
					sscanf(buf, "%s %f %f %f %f %f %f %f", &in, &position.x, &position.y, &position.z, &rotation.y, &rotation.x, &rotation.z, &scale);

					position.z = -position.z;
					rotation.x *= -(D3DX_PI/180);
					rotation.y *= (D3DX_PI/180);
					rotation.z *= (D3DX_PI/180);
				
					Model *m = g_graphicsEngine->createModel(key, position, true);
					m->setRotation(rotation);
					m->setScale(scale, scale, scale);
				}
			}
		}
		else if(strcmp(key, "LIGHTS:") == 0)
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
					sscanf(buf, "%s", &in);

					if(strcmp(key, "AM") == 0)
					{
						FLOAT3 direction;
						FLOAT3 color;

						sscanf(buf, "AM %f %f %f %f %f %f", &direction.x, &direction.y, &direction.z, &color.x, &color.y, &color.z);
						g_graphicsEngine->createDirectionalLight(direction, FLOAT3(0.0f, 0.0f, 0.0f), color, color);
					}
					else if(strcmp(key, "PLS") == 0)
					{
						FLOAT3 position;
						FLOAT3 rotation;
						FLOAT3 color;
						float radius;
						sscanf(buf, "PLS %f %f %f %f %f %f %f %f %f %f", &position.x, &position.y, &position.z, &rotation.y, &rotation.x, &rotation.z, &color.x, &color.y, &color.z, &radius);

						position.z = -position.z;

						g_graphicsEngine->createPointLight(position, FLOAT3(0.0f, 0.0f, 0.0f), color, FLOAT3(1.0f, 1.0f, 1.0f), radius, false);
					}
					else if(strcmp(key, "PL") == 0)
					{
						FLOAT3 position;
						FLOAT3 rotation;
						FLOAT3 color;
						float radius;
						sscanf(buf, "PL %f %f %f %f %f %f %f %f %f %f", &position.x, &position.y, &position.z, &rotation.y, &rotation.x, &rotation.z, &color.x, &color.y, &color.z, &radius);

						position.z = -position.z;

						g_graphicsEngine->createPointLight(position, FLOAT3(0.0f, 0.0f, 0.0f), color, color, radius, false);
					}
					else if(strcmp(key, "SL") == 0)
					{
						FLOAT3 position;
						FLOAT3 direction;
						FLOAT3 color;
						sscanf(buf, "SL %f %f %f %f %f %f %f %f %f", &position.x, &position.y, &position.z, &direction.x, &direction.y, &direction.z, &color.x, &color.y, &color.z);

						position.z = position.z * -1;
						direction.y = -direction.y;

						g_graphicsEngine->createSpotLight(position, direction, FLOAT3(0.0f, 0.0f, 0.0f), color, color, FLOAT2(0.9f, 0.8f), 300.0f);
					}
				}
			}
		}
		else if(strcmp(key, "PARTICLESYSTEMS:") == 0)
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
					FLOAT3 position;
					FLOAT3 rotation;
					FLOAT3 color;

					sscanf(buf, "%s %f %f %f %f %f %f %f %f %f", key, &position.x, &position.y, &position.z, &rotation.x, &rotation.y, &rotation.z, &color.x, &color.y, &color.z);

					//Create particle system
					int lol = 0;
				}
			}
		}


		sscanf("bugfix", "%s", key);
	}
	stream.close();

	m_terrain = g_graphicsEngine->createTerrain(v1, v2, textures, blendMaps, normalMaps, specularMaps);
	m_minimap = new Minimap(path + minimap, m_terrain->getTopLeftCorner(), m_terrain->getBottomRightCorner(), g_graphicsEngine->getCamera()->getPos2D());
}