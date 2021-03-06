#include "GameState.h"
#include "Input.h"
#include "Graphics.h"
#include "SoundWrapper.h"
#include "Skill.h"
#include "ClientSkillEffects.h"
#include "Path.h"
#include "MyAlgorithms.h"
#include "SpeechManager.h"
#include "Enemy.h"

GameState::GameState(Client *_network, string mapName)
{
	this->missionTimer=0.0f;
	this->missionCompletedSpriteB=0;
	this->missionCompletedSpriteC=0;
	this->missionFailedSpriteB=0;
	this->missionFailedSpriteC=0;
	this->missionStartedSpriteB=0;
	this->missionStartedSpriteC=0;

	this->missionStartedSpriteB = g_graphicsEngine->createSprite("./menu_textures/missionstartedB.png",FLOAT2(0.0,0.0),FLOAT2(0.520833333f,0.37037037f),3);
	this->missionStartedSpriteB->setVisible(false);
	this->missionStartedSpriteC = g_graphicsEngine->createSprite("./menu_textures/missionstartedC.png",FLOAT2(0.0,0.0),FLOAT2(0.520833333f,0.37037037f),3);
	this->missionStartedSpriteC->setVisible(false);
	this->missionCompletedSpriteB = g_graphicsEngine->createSprite("./menu_textures/missioncompleteB.png",FLOAT2(0.0,0.0),FLOAT2(0.520833333f,0.37037037f),3);
	this->missionCompletedSpriteB->setVisible(false);
	this->missionFailedSpriteB = g_graphicsEngine->createSprite("./menu_textures/missionfailedB.png",FLOAT2(0.0,0.0),FLOAT2(0.520833333f,0.37037037f),3);
	this->missionFailedSpriteB->setVisible(false);
	this->missionCompletedSpriteC = g_graphicsEngine->createSprite("./menu_textures/missioncompleteC.png",FLOAT2(0.0,0.0),FLOAT2(0.520833333f,0.37037037f),3);
	this->missionCompletedSpriteC->setVisible(false);
	this->missionFailedSpriteC = g_graphicsEngine->createSprite("./menu_textures/missionfailedC.png",FLOAT2(0.0,0.0),FLOAT2(0.520833333f,0.37037037f),3);
	this->missionFailedSpriteC->setVisible(false);

	m_missionButton = new Button();
	m_missionButton->Init(FLOAT2(0.0f, 0.0f), FLOAT2(0.520833333, 0.37037037), "menu_textures/LeaveGame_Button.png", "");
	m_missionButton->setVisible(false);
	m_missionButton->setKeep(1);

	this->m_network = _network;
	this->importMap(mapName);
	m_exitButton = NULL;
	//Create particle system
	testParticleSystem = NULL;//g_graphicsEngine->createParticleEngine(D3DXVECTOR4(0, 1, 0, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));

	//SSAO
	g_graphicsEngine->setSSAO(3, 0.01f, 0, 1);

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
		m_moveSounds[0] = createSoundHandle("red_knight/RedKnight_Click_0.wav", false, false);
		m_moveSounds[1] = createSoundHandle("red_knight/RedKnight_Click_1.wav", false, false);
		m_moveSounds[2] = createSoundHandle("red_knight/RedKnight_Click_2.wav", false, false);
		m_moveSounds[3] = createSoundHandle("red_knight/RedKnight_Click_3.wav", false, false);
		m_lowHealthSound = createSoundHandle("red_knight/RedKnight_LowHealth_0.wav", false, false);
		break;
	case Hero::ENGINEER:
		m_idleSound = createSoundHandle("engineer/Engineer_Idle_0.wav", false, false);
		m_attackSounds[0] = createSoundHandle("engineer/Engineer_Attack_0.wav", false, false);
		m_attackSounds[1] = createSoundHandle("engineer/Engineer_Attack_1.wav", false, false);
		m_attackSounds[2] = createSoundHandle("engineer/Engineer_Attack_2.wav", false, false);
		m_moveSounds[0] = createSoundHandle("engineer/Engineer_Click_0.wav", false, false);
		m_moveSounds[1] = createSoundHandle("engineer/Engineer_Click_1.wav", false, false);
		m_moveSounds[2] = createSoundHandle("engineer/Engineer_Click_2.wav", false, false);
		m_moveSounds[3] = createSoundHandle("engineer/Engineer_Click_3.wav", false, false);
		m_lowHealthSound = createSoundHandle("engineer/Engineer_LowHealth_0.wav", false, false);
		m_timeIsMoneySounds.push_back(createSoundHandle("skills/time_is_money0", false, false));
		m_timeIsMoneySounds.push_back(createSoundHandle("skills/time_is_money1", false, false));
		break;
	case Hero::THE_MENTALIST:
		m_idleSound = createSoundHandle("mentalist/Mentalist_Idle.wav", false, false);
		m_attackSounds[0] = createSoundHandle("mentalist/Mentalist_Attack_0.wav", false, false);
		m_attackSounds[1] = createSoundHandle("mentalist/Mentalist_Attack_1.wav", false, false);
		m_attackSounds[2] = createSoundHandle("mentalist/Mentalist_Attack_2.wav", false, false);
		m_moveSounds[0] = createSoundHandle("mentalist/Mentalist_Click_0.wav", false, false);
		m_moveSounds[1] = createSoundHandle("mentalist/Mentalist_Click_1.wav", false, false);
		m_moveSounds[2] = createSoundHandle("mentalist/Mentalist_Click_2.wav", false, false);
		m_moveSounds[3] = createSoundHandle("mentalist/Mentalist_Click_3.wav", false, false);
		m_lowHealthSound = createSoundHandle("mentalist/Mentalist_LowHealth_0.wav", false, false);
		break;
	case Hero::OFFICER:
		m_idleSound = createSoundHandle("officer/Officer_Idle_0.wav", false, false);
		m_attackSounds[0] = createSoundHandle("officer/Officer_Attack_0.wav", false, false);
		m_attackSounds[1] = createSoundHandle("officer/Officer_Attack_1.wav", false, false);
		m_attackSounds[2] = createSoundHandle("officer/Officer_Attack_2.wav", false, false);
		m_moveSounds[0] = createSoundHandle("officer/Officer_Click_0.wav", false, false);
		m_moveSounds[1] = createSoundHandle("officer/Officer_Click_1.wav", false, false);
		m_moveSounds[2] = createSoundHandle("officer/Officer_Click_2.wav", false, false);
		m_moveSounds[3] = createSoundHandle("officer/Officer_Click_3.wav", false, false);
		m_lowHealthSound = createSoundHandle("officer/Officer_LowHealth_0.wav", false, false);
		break;
	case Hero::DOCTOR:
		m_idleSound = createSoundHandle("doctor/Doctor_Idle_0.wav", false, false);
		m_attackSounds[0] = createSoundHandle("doctor/Doctor_Attack_0.wav", false, false);
		m_attackSounds[1] = createSoundHandle("doctor/Doctor_Attack_1.wav", false, false);
		m_attackSounds[2] = createSoundHandle("doctor/Doctor_Attack_2.wav", false, false);
		m_moveSounds[0] = createSoundHandle("doctor/Doctor_Click_0.wav", false, false);
		m_moveSounds[1] = createSoundHandle("doctor/Doctor_Click_1.wav", false, false);
		m_moveSounds[2] = createSoundHandle("doctor/Doctor_Click_2.wav", false, false);
		m_moveSounds[3] = createSoundHandle("doctor/Doctor_Click_3.wav", false, false);
		m_lowHealthSound = createSoundHandle("doctor/Doctor_LowHealth_0.wav", false, false);
		break;
	}
	m_churchSound = createSoundHandle("gameplay/churchBell1X.wav", false, false);
	
	m_attackSoundTimer = 0.0f;
	m_moveSoundTimer = 0.0f;
	m_idle = false;
	m_cameraFollowingHero = false;
	m_yourHeroLives = true;
	m_leaveGameSprite = NULL;
	
	this->m_fpsText = g_graphicsEngine->createText("", INT2(300, 40), 20, D3DXCOLOR(0.5f, 0.2f, 0.8f, 1.0f));
	this->m_hud = new HudMenu(this->m_network, m_playerInfos[m_yourId].heroType, m_playerInfos);
	this->m_clientEntityHandler = new ClientEntityHandler();

	g_graphicsEngine->getCamera()->set(FLOAT3(50.0f, 7.5f, 50.0f), FLOAT3(0.0f, -1.0f, 0.0f), FLOAT3(0.0f, 0.0f, 1.0f), FLOAT3(1.0f, 0.0f, 0.0f));
	g_graphicsEngine->getCamera()->rotate(0.0f, -0.4f, 0.0f);

	g_graphicsEngine->createPointLight(FLOAT3(60.0f, 1.0f, 60.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 10.0f, false, false);
	g_graphicsEngine->createPointLight(FLOAT3(50.0f, 2.0f, 60.0f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, false, false);
	g_graphicsEngine->createDirectionalLight(FLOAT3(0.0f, 1.0f, 0.25f), FLOAT3(0.1f, 0.1f, 0.1f), FLOAT3(0.01f, 0.01f, 0.01f), FLOAT3(0.0f, 0.0f, 0.0f));
	
	m_soundtracks[0] = createSoundHandle("music/everlasting_march.wav", true, false);
	m_soundtracks[1] = createSoundHandle("music/guitar_function.wav", true, false);
	m_soundtracks[2] = createSoundHandle("music/adv.wav", true, false);
	m_currentlyPlayingSoundtrack = 2; // This index will NEVER be played the first time due to how playRandomSoundtrack() works (it doesnt play the m_curr blalbla var soundtrack)
	playRandomSoundtrack();
}

GameState::~GameState()
{
	for(int i = 0; i < this->m_roads.size(); i++)
		g_graphicsEngine->removeRoad(m_roads[i]);
	for(int i = 0; i < m_ClientSkillEffects.size(); i++)
		delete m_ClientSkillEffects[i];
	if(m_minimap)
		delete this->m_minimap;
	delete this->m_hud;
	delete this->m_clientEntityHandler;
	if(this->testParticleSystem)
		g_graphicsEngine->removeParticleEngine(this->testParticleSystem);
	if(m_exitButton)
		delete m_exitButton;
	delete m_missionButton;
	g_graphicsEngine->removeSprite(this->missionCompletedSpriteB);
	g_graphicsEngine->removeSprite(this->missionCompletedSpriteC);
	g_graphicsEngine->removeSprite(this->missionFailedSpriteB);
	g_graphicsEngine->removeSprite(this->missionFailedSpriteC);
	g_graphicsEngine->removeSprite(this->missionStartedSpriteB);
	g_graphicsEngine->removeSprite(this->missionStartedSpriteC);
	// Release all sounds
	for(int i = 0; i < GameState::NR_OF_ATTACK_SOUNDS; i++)
	{
		stopSound(m_attackSounds[i]);
		deactivateSound(m_attackSounds[i]);
	}
	for(int i = 0; i < GameState::NR_OF_MOVE_SOUNDS; i++)
	{
		stopSound(m_moveSounds[i]);
		deactivateSound(m_moveSounds[i]);
	}
	for(int i = 0; i < m_timeIsMoneySounds.size(); i++)
	{
		stopSound(m_timeIsMoneySounds[i]);
		deactivateSound(m_timeIsMoneySounds[i]);
	}
	stopSound(m_lowHealthSound);
	deactivateSound(m_lowHealthSound);
	stopSound(m_churchSound);
	deactivateSound(m_churchSound);

	g_graphicsEngine->clear();
	
	// Release all music
	stopSound(m_soundtracks[m_currentlyPlayingSoundtrack]);
	for(int i = 0; i < NR_OF_SOUNDTRACKS; i++)
		deactivateSound(m_soundtracks[m_currentlyPlayingSoundtrack]);
	if(m_leaveGameSprite)
		g_graphicsEngine->removeSprite(m_leaveGameSprite);

	g_graphicsEngine->removeText(this->m_fpsText);
}

State::StateEnum GameState::nextState()
{
	return State::END;
}

void GameState::update(float _dt)
{
	while(m_network->endGameQueueEmpty() == false)
	{
		this->m_endMessage = m_network->endGameQueueFront();
		m_victory = this->m_endMessage.getVictory();
		m_exitButton = new Button();
		m_exitButton->Init(FLOAT2(0.0f, 0.0f), FLOAT2(0.520833333, 0.37037037), "menu_textures/LeaveGame_Button.png", "");
		if(m_victory == true)
		{
			m_leaveGameSprite = g_graphicsEngine->createSprite("menu_textures/LeaveGame_LevelCompleted.png",
				FLOAT2(0.0f, 0.0f), FLOAT2(0.520833333, 0.37037037), 1);
		}
		else
		{
			m_leaveGameSprite = g_graphicsEngine->createSprite("menu_textures/LeaveGame_LevelFailed.png",
				FLOAT2(0.0f, 0.0f), FLOAT2(0.520833333, 0.37037037), 1);
		}
	}

	if(this->m_exitButton != NULL)
	{
		m_exitButton->Update();
		if(m_exitButton->isClicked())
		{
			this->setDone(true);
		}
	}

	m_ambientSoundsManager.update(_dt);
	ClientEntityHandler::update(_dt);
	MeleeAttackClientSkillEffect::decreaseTimeBetweenDamageSounds(_dt);
	this->m_hud->Update(_dt, this->m_clientEntityHandler->getEntities(), m_playerInfos[m_yourId].id, m_playerInfos, m_yourHeroLives);
	m_minimap->update(this->m_clientEntityHandler->getEntities(), g_graphicsEngine->getCamera()->getPos2D(), this->m_terrain->getWidth(), this->m_terrain->getHeight(), this->m_playerInfos[this->m_yourId].id);
	SpeechManager::update();

	// Update sound timers
	m_lowHealthSoundDelayTimer = max(m_lowHealthSoundDelayTimer-_dt, 0.0f);
	m_attackSoundTimer = max(m_attackSoundTimer-_dt, 0.0f);
	m_moveSoundTimer = max(m_moveSoundTimer-_dt, 0.0f);
	if(m_idle)
	{
		if(m_idleSoundTimer > 0.0f)
		{
			m_idleSoundTimer = max(m_idleSoundTimer-_dt, 0.0f);
			if(m_idleSoundTimer == 0.0f)
			{
				SpeechManager::speak(m_playerInfos[m_yourId].id, m_idleSound);
				m_idle = false;
			}
		}
	}

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
			if(e.getXPos() == e.getXPos() && e.getZPos() == e.getZPos())
			{
				FLOAT3 p;
				p.x=e.getXPos();
				p.y=0;
				p.z=e.getZPos();
				entity->m_model->setPosition(p);
			}
			if(e.getYRot() == e.getYRot())
			{
				FLOAT3 rot;
				rot.x=e.getYRot();
				rot.y=0;
				rot.z=0;
				entity->m_model->setRotation(rot);

				FLOAT3 startPos,endPos;
				startPos.x=e.getStartX();
				startPos.y=0;
				startPos.z=e.getStartZ();
				endPos.x=e.getEndX();
				endPos.y=0;
				endPos.z=e.getEndZ();
				entity->m_startPos=startPos;
				entity->m_endPos=endPos;
				entity->movementSpeed=e.getMovementSpeed();
			}
		}
	}

	while(this->m_network->initEntityMessageEmpty()==false)
	{
		NetworkInitEntityMessage iem = this->m_network->initEntityMessageFront();
		bool found = false;

		Model* model = g_graphicsEngine->createModel(this->m_modelIdHolder.getModel(iem.getModelID()), FLOAT3(iem.getXPos(), 0.0, iem.getZPos()));
		model->setTextureIndex(m_modelIdHolder.getTexture(iem.getModelID()));
		model->setGlowIndex(m_modelIdHolder.getGlowmap(iem.getModelID()));
		model->setRotation(FLOAT3(iem.getYRot(), 0.0f, 0.0f));

		if(this->m_modelIdHolder.getHat(iem.getModelID()) != "")
		{
			model->SetHat(g_graphicsEngine->getMesh(this->m_modelIdHolder.getHat(iem.getModelID())));
			model->getAnimation()->PlayLoop("idle");
		}
		if(this->m_modelIdHolder.getRightHand(iem.getModelID(), iem.getWeaponType()) != "")
		{
			model->SetRightHand(g_graphicsEngine->getMesh(this->m_modelIdHolder.getRightHand(iem.getModelID(), iem.getWeaponType())));
		}
		if(this->m_modelIdHolder.getLeftHand(iem.getModelID(), iem.getWeaponType()) != "")
		{
			model->SetLeftHand(g_graphicsEngine->getMesh(this->m_modelIdHolder.getLeftHand(iem.getModelID(), iem.getWeaponType())));
		}
		if(model)
		{
			//this->m_entities.push_back(new Entity(model, e.getEntityId()));
			model->setScale(iem.getScale(),iem.getScale(),iem.getScale());
			Entity *e = new Entity(model, iem.getID(), (ServerEntity::Type)iem.getType(), iem.getSubtype());
			this->m_clientEntityHandler->addEntity(e);
			e->m_weapon = iem.getWeaponType();

			if(iem.getID() == m_playerInfos[m_yourId].id)
			{
				/*g_graphicsEngine->getCamera()->setX(iem.getXPos());
				g_graphicsEngine->getCamera()->setZ(iem.getZPos() - g_graphicsEngine->getCamera()->getZOffset());*/

				g_graphicsEngine->getCamera()->setX(max(
					min(iem.getXPos(), m_terrain->getWidth()-g_graphicsEngine->getCamera()->getXOffset()),
					g_graphicsEngine->getCamera()->getXOffset()));

				g_graphicsEngine->getCamera()->setZ(max(
					min(iem.getZPos() - g_graphicsEngine->getCamera()->getZOffset(), m_terrain->getHeight()-g_graphicsEngine->getCamera()->getZOffset()*2.0f),
					0.0f));
			}
		}
	}

	while(!this->m_network->updateEntityHealthEmpty())
	{
		NetworkUpdateEntityHealth ueh = this->m_network->updateEntityHealthFront();
		if(ueh.getId() == this->m_playerInfos[this->m_yourId].id)
		{
			if(ueh.getHealth() < 200 && m_lowHealthSoundDelayTimer == 0.0f)
			{
				SpeechManager::speak(m_playerInfos[m_yourId].id, m_lowHealthSound);
				m_lowHealthSoundDelayTimer = LOW_HEALTH_SOUND_DELAY;
			}
			this->m_hud->setHealth(ueh.getHealth());
		}

		Entity *e = ClientEntityHandler::getEntity(ueh.getId());

		if(e != NULL)
		{
			e->setHealth(ueh.getHealth());
		}
	}

	while(this->m_network->createActionQueueEmpty() == false)
	{
		NetworkCreateActionMessage e = this->m_network->createActionQueueFront();
		
		switch(e.getActionId())
		{
		case Skill::ENEMY_PURSUE:
			this->playPursueSound(e.getSenderId());
			break;
		case Skill::TIME_IS_MONEY:
			if(e.getSenderId() == m_playerInfos[m_yourId].id)
				playSound(m_timeIsMoneySounds[random(0, m_timeIsMoneySounds.size()-1)]);
			break;
		case Skill::STUNNING_STRIKE:
			m_ClientSkillEffects.push_back(new StunningStrikeClientSkillEffect(e.getSenderId(), e.getPosition()));
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
			if(e.getSenderId() == m_playerInfos[m_yourId].id)
			{
				m_yourHeroLives = false;
			}
			break;
		case Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR:
			this->m_ClientSkillEffects.push_back(new SwiftAsACatPowerfulAsABoarClientSkillEffect(e.getSenderId()));
			break;
		case Skill::RESPAWN:
			if(e.getSenderId() == m_playerInfos[m_yourId].id)
			{
				//g_graphicsEngine->getCamera()->set(FLOAT2(e.getPosition().x, e.getPosition().z-g_graphicsEngine->getCamera()->getZOffset()));

				g_graphicsEngine->getCamera()->setX(max(
					min(e.getPosition().x, m_terrain->getWidth()-g_graphicsEngine->getCamera()->getXOffset()),
					g_graphicsEngine->getCamera()->getXOffset()));

				g_graphicsEngine->getCamera()->setZ(max(
					min(e.getPosition().z - g_graphicsEngine->getCamera()->getZOffset(), m_terrain->getHeight()-g_graphicsEngine->getCamera()->getZOffset()*2.0f),
					0.0f));

				m_yourHeroLives = true;
			}
			break;
		case Skill::STUNNING_STRIKE_VICTIM:
			m_ClientSkillEffects.push_back(new StunningStrikeVictimClientSkillEffect(e.getSenderId()));
			break;
		case Skill::TURRET_CONSTRUCTION:
			this->m_hud->setTowerConstruction(e.getSenderId());
			break;
		case Skill::HEALING_FOUNTAIN:
			this->m_ClientSkillEffects.push_back(new HealingFountainClientSkillEffect(e.getSenderId()));
			break;
		case Skill::WAVE_UPDATE:
			this->m_hud->setWave(e.getSenderId());
			break;
		case Skill::LIVES_REMAINING:
			this->m_hud->setLivesRemaining(e.getSenderId());
			break;
		}
	}

	while(!this->m_network->missionQueueEmpty())
	{
		NetworkMissionStarted m = this->m_network->missionQueueFront();
	
		
		if(m.getStartOrEnd()=="start")
		{
			if(m.getMissionName()[0]=='I')
				this->missionStartedSpriteB->setVisible(true);
			if(m.getMissionName()[0]=='M')
				this->missionStartedSpriteC->setVisible(true);
			this->em.addMission(m.getMissionName(),"Running");
			this->m_missionButton->setVisible(true);
			this->m_missionButton->setKeep(0);
		}
		if(m.getStartOrEnd()=="failed")
		{
			if(m.getMissionName()[0]=='I')
				this->missionFailedSpriteB->setVisible(true);
			if(m.getMissionName()[0]=='M')
				this->missionFailedSpriteC->setVisible(true);
			this->em.setStatusForMission(m.getMissionName(),"Failed");
			this->m_missionButton->setVisible(true);
			this->m_missionButton->setKeep(0);
		}
		if(m.getStartOrEnd()=="completed")
		{
			if(m.getMissionName()[0]=='I')
				this->missionCompletedSpriteB->setVisible(true);
			if(m.getMissionName()[0]=='M')
				this->missionCompletedSpriteC->setVisible(true);
			this->em.setStatusForMission(m.getMissionName(),"Completed");
			this->m_missionButton->setVisible(true);
			this->m_missionButton->setKeep(0);
		}
		this->missionTimer=10.0f;
	}
	this->missionTimer-=_dt;
	if(this->missionTimer<0)
	{
		this->missionStartedSpriteB->setVisible(false);
		this->missionStartedSpriteC->setVisible(false);
		this->missionCompletedSpriteB->setVisible(false);
		this->missionFailedSpriteB->setVisible(false);
		this->missionCompletedSpriteC->setVisible(false);
		this->missionFailedSpriteC->setVisible(false);
		this->m_missionButton->setVisible(false);
		this->m_missionButton->setKeep(1);
	}

	m_missionButton->Update();
		if(m_missionButton->isClicked())
		{
			m_missionButton->setVisible(false);
			m_missionButton->setKeep(1);

		this->missionStartedSpriteB->setVisible(false);
		this->missionStartedSpriteC->setVisible(false);
		this->missionCompletedSpriteB->setVisible(false);
		this->missionFailedSpriteB->setVisible(false);
		this->missionCompletedSpriteC->setVisible(false);
		this->missionFailedSpriteC->setVisible(false);
		this->m_missionButton->setVisible(false);
		}

	while(this->m_network->createActionPositionQueueEmpty() == false)
	{
		NetworkCreateActionPositionMessage e = this->m_network->createActionPositionQueueFront();
		
		int sound; // a sound might be played and cant be declared inside switch
		switch(e.getActionId())
		{
		case Skill::CLOUD_OF_DARKNESS:
			m_ClientSkillEffects.push_back(new CloudOfDarknessClientSkillEffect(e.getSenderId(), e.getPosition()));
			break;
		case Skill::WALL:
			m_ClientSkillEffects.push_back(new WallClientSkillEffect(e.getSenderId(), e.getPosition()));
			break;
		case Skill::TESLA_CHAIN_TURRET:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("turrets/towerBuild.wav", false, true, e.getPosition());
				break;
			case 1:
				sound = createSoundHandle("turrets/towerBuildHammerSound.wav", false, true, e.getPosition());
				break;
			case 2:
				sound = createSoundHandle("turrets/towerBuildKlinkSound.wav", false, true, e.getPosition());
				break;
			}
			playSound(sound);
			deactivateSound(sound);
			break;
		case Skill::DEATH_PULSE_TURRET:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("turrets/towerBuild.wav", false, true, e.getPosition());
				break;
			case 1:
				sound = createSoundHandle("turrets/towerBuildHammerSound.wav", false, true, e.getPosition());
				break;
			case 2:
				sound = createSoundHandle("turrets/towerBuildKlinkSound.wav", false, true, e.getPosition());
				break;
			}
			playSound(sound);
			deactivateSound(sound);
			break;
		case Skill::FROST_TURRET:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("turrets/towerBuild.wav", false, true, e.getPosition());
				break;
			case 1:
				sound = createSoundHandle("turrets/towerBuildHammerSound.wav", false, true, e.getPosition());
				break;
			case 2:
				sound = createSoundHandle("turrets/towerBuildKlinkSound.wav", false, true, e.getPosition());
				break;
			}
			playSound(sound);
			deactivateSound(sound);
			break;
		case Skill::POISON_TURRET:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("turrets/towerBuild.wav", false, true, e.getPosition());
				break;
			case 1:
				sound = createSoundHandle("turrets/towerBuildHammerSound.wav", false, true, e.getPosition());
				break;
			case 2:
				sound = createSoundHandle("turrets/towerBuildKlinkSound.wav", false, true, e.getPosition());
				break;
			}
			playSound(sound);
			deactivateSound(sound);
			break;
		case Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE:
			m_ClientSkillEffects.push_back(new TargetAcquiredClientSkillEffect(e.getSenderId(), e.getPosition()));
			break;
		case Skill::TELEPORT:
			m_ClientSkillEffects.push_back(new TeleportClientSkillEffect(e.getSenderId(), e.getPosition()));
			break;
		}
	}

	while(this->m_network->createActionTargetQueueEmpty() == false)
	{
		NetworkCreateActionTargetMessage e = this->m_network->createActionTargetQueueFront();
		
		switch(e.getActionId())
		{
		case Skill::LIFESTEALING_STRIKE:
			this->m_ClientSkillEffects.push_back(new PassiveAttackClientSkillEffect(e.getSenderId(), e.getActionId()));
			break;
		case Skill::DEADLY_STRIKE:
			this->m_ClientSkillEffects.push_back(new PassiveAttackClientSkillEffect(e.getSenderId(), e.getActionId()));
			break;
		case Skill::POISON_STRIKE:
			this->m_ClientSkillEffects.push_back(new PassiveAttackClientSkillEffect(e.getSenderId(), e.getActionId()));
			break;
		case Skill::CHAIN_STRIKE:
			m_ClientSkillEffects.push_back(new ChainStrikeClientSkillEffect(e.getSenderId(), e.getTargetId(), e.getPosition()));
			break;
		case Skill::RANGED_ATTACK:
			m_ClientSkillEffects.push_back(new ArrowClientSkillEffect(e.getPosition(), e.getTargetId(), e.getSenderId(), e.getAnimationSpeed()));
			break;
		case Skill::FROST_TURRET_PROJECTILE:
			m_ClientSkillEffects.push_back(new FrostTurretProjectileClientSkillEffect(FLOAT3(e.getPosition().x, 0.5f, e.getPosition().z), e.getTargetId()));
			break;
		case Skill::POISON_TURRET_PROJECTILE:
			m_ClientSkillEffects.push_back(new PoisonTurretProjectileClientSkillEffect(FLOAT3(e.getPosition().x, 0.5f, e.getPosition().z), e.getTargetId()));
			break;
		case Skill::DEATH_PULSE_TURRET_PROJECTILE:
			m_ClientSkillEffects.push_back(new DeathPulseTurretClientSkillEffect(e.getTargetId(), e.getSenderId()));
			break;
		case Skill::HEALING_TOUCH:
			m_ClientSkillEffects.push_back(new HealingTouchClientSkillEffect(e.getPosition(), e.getSenderId(), e.getTargetId()));
			break;
		case Skill::HYPNOTIC_STARE:
			m_ClientSkillEffects.push_back(new HypnoticStareClientSkillEffect(e.getTargetId(), e.getSenderId(), e.getPosition().x));
			break;
		case Skill::DEMONIC_PRESENCE:
			m_ClientSkillEffects.push_back(new DemonicPresenceClientSkillEffect(e.getTargetId()));
			break;
		case Skill::ENIGMATIC_PRESENCE:
			m_ClientSkillEffects.push_back(new EnigmaticPresenceClientSkillEffect(e.getTargetId()));
			break;
		case Skill::COURAGE_HONOR_VALOR:
			for(int i = 0; i < m_playerInfos.size(); i++)
				if(m_playerInfos[i].heroType == Hero::RED_KNIGHT)
					m_ClientSkillEffects.push_back(new CourageHonorValorClientSkillEffect(e.getTargetId(), m_playerInfos[i].id));
			break;
		case Skill::SIMONS_EVIL:
			m_ClientSkillEffects.push_back(new SimonsEvilClientSkillEffect(e.getTargetId()));
			break;
		case Skill::MELEE_ATTACK:
			this->m_ClientSkillEffects.push_back(new MeleeAttackClientSkillEffect(e.getSenderId(), e.getTargetId(), m_playerInfos[m_yourId], e.getAnimationSpeed()));
			break;
		case Skill::AOE_MELEE_ATTACK:
			m_ClientSkillEffects.push_back(new MeleeAOEClientSkillEffect(e.getSenderId(), e.getTargetId(), m_playerInfos[m_yourId], e.getAnimationSpeed()));
			break;
		case Skill::CHURCH_PENETRATED:			
			m_ClientSkillEffects.push_back(new ChurchPenetratedClientSkillEffect(e.getSenderId(), e.getPosition()));		
			break;
		case Skill::CHURCH_REALLY_PENETRATED:
			playSound(m_churchSound);
			this->m_hud->setLivesRemaining(e.getTargetId());
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

							// Play sound
							Entity* ent = ClientEntityHandler::getEntity(e.getTargetId());
							if(ent)
							{
								int sound = createSoundHandle("skills/dpBreathingEnd.wav", false, true, ent->m_startPos);
								playSound(sound);
								deactivateSound(sound);
							}
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
		case Skill::WALL:
			this->playWallDeathSound(e.getPosition());
			break;
		}
	}

	while(this->m_network->skillUsedQueueEmpty() == false)
	{
		NetworkSkillUsedMessage e = this->m_network->skillUsedQueueFront();
		
		// Do something!
		this->m_hud->skillUsed(e.getActionIndex(), e.getActionId(), e.getCooldown());
	}

	while(this->m_network->entityAttributeQueueEmpty() == false)
	{
		NetworkEntityAttributeMessage e = this->m_network->entityAttributeFront();

		Entity *entity = ClientEntityHandler::getEntity(e.id);

		if(entity != NULL)
		{
			if(entity->m_type == ServerEntity::HeroType)
			{
				// Omfg its your attributes!!!11
				if(entity->m_id == m_playerInfos[m_yourId].id)
				{
					m_hud->setAgility(e.agility);
					m_hud->setFortitude(e.fortitude);
					m_hud->setWits(e.wits);
					m_hud->setStrength(e.strength);
					m_hud->setTowerConstruction(e.towerConstruction);
					m_hud->setMaxHealth(e.maxHealth);
					m_hud->setPhysicalDamage(e.physicalDamage);
					m_hud->setPhysicalResistance(e.physicalResistance);
					m_hud->setMentalDamage(e.mentalDamage);
					m_hud->setMentalResistance(e.mentalResistance);
				}
			}
			else if(entity->m_type == ServerEntity::TowerType) // Tower exception for lifetime bar
				entity->m_health = e.maxHealth;
			
			entity->m_maxHealth = e.maxHealth;
			entity->m_mentalDamage = e.mentalDamage;
			entity->m_physicalDamage = e.physicalDamage;
			entity->m_mentalResistance = e.mentalResistance;
			entity->m_physicalResistance = e.physicalResistance;
		}
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
	if(g_mouse->getPos().x >= g_graphicsEngine->getScreenSize().x-10 || g_keyboard->getKeyState('D') != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->setX(min(g_graphicsEngine->getCamera()->getPos().x+CAMERA_SPEED*_dt,
			m_terrain->getWidth()-g_graphicsEngine->getCamera()->getXOffset()));
	}
	else if(g_mouse->getPos().x <= 10 || g_keyboard->getKeyState('A') != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->setX(max(g_graphicsEngine->getCamera()->getPos().x-CAMERA_SPEED*_dt,
			g_graphicsEngine->getCamera()->getXOffset()));
	}
	if(g_mouse->getPos().y >= g_graphicsEngine->getScreenSize().y-10 || g_keyboard->getKeyState('S') != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->setZ(max(g_graphicsEngine->getCamera()->getPos().z-CAMERA_SPEED*_dt,
			0.0f));
	}
	else if(g_mouse->getPos().y <= 10 || g_keyboard->getKeyState('W') != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->setZ(min(g_graphicsEngine->getCamera()->getPos().z+CAMERA_SPEED*_dt,
			m_terrain->getHeight()-g_graphicsEngine->getCamera()->getZOffset()*2.0f));
	}

	D3DXVECTOR3 pickDir;
	D3DXVECTOR3 pickOrig;
	g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
	float dist;
	float k = (-pickOrig.y)/pickDir.y;
	D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;
	int mouseOverEnemy = -1;
	vector<Entity*> m_entities = m_clientEntityHandler->getEntities();
	for(int i = 0; i < m_entities.size(); i++)
	{
		if(m_entities[i]->m_type == ServerEntity::EnemyType && m_entities[i]->m_model->intersects(dist, pickOrig, pickDir))
		{
			mouseOverEnemy = i;
			i = m_entities.size();
			g_mouse->getCursor()->setFrame(Cursor::TARGET, 1);
		}
	}

	if(mouseOverEnemy == -1)
	{
		g_mouse->getCursor()->setFrame(Cursor::DEFAULT, 1);
	}
	
	if(g_mouse->isLButtonDown())
	{

	}
	else if(g_mouse->isLButtonReleased())
	{

	}
	if(g_mouse->isLButtonDown())
	{
		if(m_minimap->isMouseInMap(g_mouse->getPos()))
		{
			FLOAT2 pos = m_minimap->getTerrainPos(g_mouse->getPos());
			NetworkUseActionPositionMessage e = NetworkUseActionPositionMessage(Skill::MOVE, FLOAT3(pos.x, 0.0f, pos.y), -1);
			this->m_network->sendMessage(e);
			
			m_hud->removeTargetEnemy();
			m_idle = false;
		}
		else
		{
			if(mouseOverEnemy >= 0)
			{
				this->m_network->sendMessage(NetworkUseActionTargetMessage(Skill::ATTACK, m_entities[mouseOverEnemy]->m_id, -1));
				m_hud->setTargetEnemy(m_entities[mouseOverEnemy]->m_id);
				if(m_attackSoundTimer == 0.0f)
				{
					SpeechManager::speak(m_playerInfos[m_yourId].id, m_attackSounds[random(0, NR_OF_ATTACK_SOUNDS-1)]);
					m_attackSoundTimer = ATTACK_SOUND_DELAY;
				}
				m_idle = false;
			}
			else if(g_keyboard->getKeyState(VK_SHIFT) == Keyboard::KEY_UP)
			{
				float k = (-pickOrig.y)/pickDir.y;
				D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;
				NetworkUseActionPositionMessage e = NetworkUseActionPositionMessage(Skill::MOVE, FLOAT3(terrainPos.x, 0.0f, terrainPos.z), -1);
				this->m_network->sendMessage(e);
				m_hud->removeTargetEnemy();
				if(m_moveSoundTimer == 0.0f)
				{
					SpeechManager::speak(m_playerInfos[m_yourId].id, m_attackSounds[random(0, NR_OF_ATTACK_SOUNDS-1)]);
					m_moveSoundTimer = MOVE_SOUND_DELAY;
				}
				SpeechManager::speak(m_playerInfos[m_yourId].id, m_moveSounds[random(0, NR_OF_MOVE_SOUNDS-1)]);
				m_idle = false;
			}
		}
	}
	else if(g_mouse->isRButtonReleased())
	{

	}
	if(g_keyboard->getKeyState('Q') == Keyboard::KEY_PRESSED && g_keyboard->getKeyState(VK_SHIFT) != Keyboard::KEY_UP)
	{
		m_cameraFollowingHero = !m_cameraFollowingHero;
	}
	if(m_cameraFollowingHero && m_yourHeroLives)
	{
		g_graphicsEngine->getCamera()->setX(ClientEntityHandler::getEntity(m_playerInfos[m_yourId].id)->m_model->getPosition().x);
		g_graphicsEngine->getCamera()->setZ(ClientEntityHandler::getEntity(m_playerInfos[m_yourId].id)->m_model->getPosition().z-g_graphicsEngine->getCamera()->getZOffset());
	}
	else if(m_playerInfos.size() > 0 && g_keyboard->getKeyState(VK_TAB) != Keyboard::KEY_UP)
	{
		// Find closest hero
		float closestDistance = 9000.0f;
		float closestIndex = -1;
		for(int i = 0; i < m_playerInfos.size(); i++)
		{
			if(i != m_yourId)
			{
				Entity* hero = ClientEntityHandler::getEntity(m_playerInfos[i].id);
				if(hero)
				{
					float dist = (ClientEntityHandler::getEntity(m_playerInfos[m_yourId].id)->m_model->getPosition() - ClientEntityHandler::getEntity(m_playerInfos[i].id)->m_model->getPosition()).length();
					if(dist < closestDistance)
					{
						closestIndex = i;
						closestDistance = dist;
					}
				}
			}
		}
		if(closestIndex != -1)
		{
			g_graphicsEngine->getCamera()->setX(ClientEntityHandler::getEntity(m_playerInfos[closestIndex].id)->m_model->getPosition().x);
			g_graphicsEngine->getCamera()->setZ(ClientEntityHandler::getEntity(m_playerInfos[closestIndex].id)->m_model->getPosition().z-g_graphicsEngine->getCamera()->getZOffset());
		}
	}
	/*if(g_keyboard->getKeyState(VK_DOWN) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveY(min(_dt, 9.0f - g_graphicsEngine->getCamera()->getPos().y));
	}
	if(g_keyboard->getKeyState(VK_UP) != Keyboard::KEY_UP)
	{
		g_graphicsEngine->getCamera()->moveY(max(-_dt, 7.5f - g_graphicsEngine->getCamera()->getPos().y));
	}*/
	if(m_hud->isDone())
	{
		this->setDone(true);
		this->m_endMessage = NetworkEndGameMessage(false, -1, -1, -1, vector<StatisticsPlayer>());
	}

	if(!isSoundPlaying(m_soundtracks[m_currentlyPlayingSoundtrack]))
	{
		this->playRandomSoundtrack();
	}
}

void GameState::importMap(string _map)
{
	string path = _map;
	string reversedPath;
	bool save=false;
	for(int i=_map.size()-1;i>=0;i--)
	{
		if(_map[i]=='/')
		{
			save=true;
		}
		if(save)
		{
			reversedPath+=_map[i];
		}
	}
	string tmppath;
	while(reversedPath.size()>0)
	{
		tmppath+=reversedPath.back();
		reversedPath.pop_back();
	}
	path=tmppath;
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
	stream.open(_map);
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
					//rotation = FLOAT3(0,0,0);
				
					if(key[0]=='S'&&key[1]=='P'&&key[2]=='A'&&key[3]=='W'&&key[4]=='N')
					{
					}
					else
					{
						Model *m = g_graphicsEngine->createModel(key, position, true);
						m->setRotation(rotation);
						m->setScale(scale, scale, scale);
					}
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
						position = position - FLOAT3(0.33f, 0.0f, 0.33f);
						g_graphicsEngine->createPointLight(position, FLOAT3(0.0f, 0.0f, 0.0f), color, FLOAT3(1.0f, 1.0f, 1.0f), radius, false, true);
					}
					else if(strcmp(key, "PL") == 0)
					{
						FLOAT3 position;
						FLOAT3 rotation;
						FLOAT3 color;
						float radius;
						sscanf(buf, "PL %f %f %f %f %f %f %f %f %f %f", &position.x, &position.y, &position.z, &rotation.y, &rotation.x, &rotation.z, &color.x, &color.y, &color.z, &radius);

						position.z = -position.z;

						g_graphicsEngine->createPointLight(position, FLOAT3(0.0f, 0.0f, 0.0f), color, color, radius, false, true);
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

void GameState::playPursueSound(unsigned int _speakerId)
{
	Entity* speaker = ClientEntityHandler::getEntity(_speakerId);
	if(speaker)
	{
		int sound;
		switch(speaker->m_subtype)
		{
		case Enemy::IMP:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Monster_Imp_Attack_0.wav", false, true, speaker->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("enemy/Monster_Imp_Attack_1.wav", false, true, speaker->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("enemy/Monster_Imp_Attack_2.wav", false, true, speaker->m_startPos);
				break;
			}
			break;
		case Enemy::SHADE:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Monster_Shade_Attack_0.wav", false, true, speaker->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("enemy/Monster_Shade_Attack_1.wav", false, true, speaker->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("enemy/Monster_Shade_Attack_2.wav", false, true, speaker->m_startPos);
				break;
			}
			break;
		case Enemy::FROST_DEMON:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Monster_Frost_Attack_0.wav", false, true, speaker->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("enemy/Monster_Frost_Attack_1.wav", false, true, speaker->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("enemy/Monster_Frost_Attack_2.wav", false, true, speaker->m_startPos);
				break;
			}
			break;
		case Enemy::SPITTING_DEMON:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Monster_Spitting_Attack_0.wav", false, true, speaker->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("enemy/Monster_Spitting_Attack_1.wav", false, true, speaker->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("enemy/Monster_Spitting_Attack_2.wav", false, true, speaker->m_startPos);
				break;
			}
			break;
		case Enemy::HELLFIRE_STEED:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Beast_Attack_0.wav", false, true, speaker->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("enemy/Beast_Attack_1.wav", false, true, speaker->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("enemy/Beast_Attack_2.wav", false, true, speaker->m_startPos);
				break;
			}
			break;
		case Enemy::SOUL_EATER_STEED:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Beast_Attack_0.wav", false, true, speaker->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("enemy/Beast_Attack_1.wav", false, true, speaker->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("enemy/Beast_Attack_2.wav", false, true, speaker->m_startPos);
				break;
			}
			break;
		case Enemy::THUNDERSTEED:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Beast_Attack_0.wav", false, true, speaker->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("enemy/Beast_Attack_1.wav", false, true, speaker->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("enemy/Beast_Attack_2.wav", false, true, speaker->m_startPos);
				break;
			}
			break;
		case Enemy::BRUTE_STEED:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Beast_Attack_0.wav", false, true, speaker->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("enemy/Beast_Attack_1.wav", false, true, speaker->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("enemy/Beast_Attack_2.wav", false, true, speaker->m_startPos);
				break;
			}
			break;
		case Enemy::BOSS:
			switch(random(0, 2))
			{
			case 0:
				sound = createSoundHandle("enemy/Beast_Attack_0.wav", false, true, speaker->m_startPos);
				break;
			case 1:
				sound = createSoundHandle("enemy/Beast_Attack_1.wav", false, true, speaker->m_startPos);
				break;
			case 2:
				sound = createSoundHandle("enemy/Beast_Attack_2.wav", false, true, speaker->m_startPos);
				break;
			}
		}

		SpeechManager::speak(_speakerId, sound);
		deactivateSound(sound);
	}
}

void GameState::playRandomSoundtrack()
{
	vector<int> possibleSoundtracks;
	for(int i = 0; i < NR_OF_SOUNDTRACKS; i++)
	{
		if(m_currentlyPlayingSoundtrack != i)
			possibleSoundtracks.push_back(i);
	}
	m_currentlyPlayingSoundtrack = possibleSoundtracks[random(0, possibleSoundtracks.size()-1)];
	playSound(m_soundtracks[m_currentlyPlayingSoundtrack]);
}

void GameState::playWallDeathSound(FLOAT3 _position)
{
	int sound = createSoundHandle("skills/wallEnd.wav", false, true, _position);
	playSound(sound);
	deactivateSound(sound);
}

NetworkEndGameMessage GameState::getEndGameMessage()
{
	return this->m_endMessage;
}
MissionEndMessage GameState::getMissionEndMessage()
{
	return this->em;
}