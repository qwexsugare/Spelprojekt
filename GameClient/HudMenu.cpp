#include "HudMenu.h"
#include "ClientEntityHandler.h"
#include "SoundWrapper.h"
#include "TowerPlacer.h"
#include "Turrets.h"

HudMenu::HudMenu(Client *_network, Hero::HERO_TYPE _heroType, vector<PLAYER_INFO> m_playerInfos)
{
	this->m_network = _network;
	m_Chat = false;
	m_menuButton = new Button();
	m_menuButton->Init(FLOAT2(0.4f, 0.96f), FLOAT2(0.272916667f, 0.074074074f), "menu_textures\\SmallButton-MainMenu-MainMenu.png", "");
	m_leaveButton = new Button();
	m_leaveButton->Init(FLOAT2(0.4f, 0.88f), FLOAT2(0.272916667f, 0.074074074f), "menu_textures\\SmallButton-MainMenu-LeaveGame.png", "");
	m_leaveButton->setVisible(false);
	m_done = false;
	m_SkillHud.push_back(-1.5f);
	m_SkillHud.push_back(-1.5f);
	m_SkillHud.push_back(-1.5f);
	m_SkillHud.push_back(-1.5f);
	int graphics = g_configFile->getScreenSize().y;
	int windowed = g_configFile->getWindowed();
	m_graphicstext = "1080";
	m_changePosY	= 1.0f;
	m_fontsize		= 1.0f;
	if (graphics == 1080)
	{
		m_changePosY= 1.0f;
			m_graphicstext = "1080";
		if (windowed == 1)
		{
			m_fontsize = 1;
		}
		else
		{
			m_fontsize =1;
		}
	}
	if (graphics == 900)
	{
		m_changePosY= 0.833333333334f;
		m_graphicstext = "900";
		if (windowed == 1)
		{
			m_fontsize = 1;
		}
		else
		{
			m_fontsize =1;
		}
	}
	if (graphics == 720)
	{
		m_changePosY= 0.66666666666667f;
		m_graphicstext = "720";
		if (windowed == 1)
		{
			m_fontsize = 1;
		}
		else
		{
			m_fontsize =1;
		}
	}
	m_NumberOfSkills = 0;
	int TmpPos = m_NumberOfSkills * 98;

	m_Buy = false;
	m_Menu= false;
	m_Locked = true;
	m_hasTargetEnemy = false;
	m_health = 100;
	m_maxHealth = 100;

	m_DontChange.push_back(false);
	m_DontChange.push_back(false);
	m_DontChange.push_back(false);
	m_DontChange.push_back(false);

	m_Resources = 5000000;
	m_Chat = false;
	m_subTowerModel = NULL;
	m_towerModel = NULL;
	this->m_skillWaitingForTarget = -1;
	this->m_nrOfAttributesBought = 0;
	this->m_subTowerModel = NULL;
	this->m_towerModel = NULL;

	// Stats (Attributes)
	m_Attributes.push_back("");
	m_Attributes.push_back("");
	m_Attributes.push_back("");
	m_Attributes.push_back("");
	m_Attributes.push_back("");
	//health 5,6
	m_Attributes.push_back("400");
	m_Attributes.push_back("400");
	//Trait 7
	m_Attributes.push_back("Immune to physical");
	// Physical res and damage 8,9
	m_Attributes.push_back("50");
	m_Attributes.push_back("0-300");
	// Mental res and damage 10, 11
	m_Attributes.push_back("50");
	m_Attributes.push_back("0-400");

	m_heroType = _heroType;
	switch(_heroType)
	{
	case Hero::OFFICER:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-1.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),9));
		m_Attributes[7] = "Officer";
		break;
	case Hero::DOCTOR:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-4.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),9));
		m_Attributes[7] = "Doctor";
		break;
	case Hero::ENGINEER:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-3.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),9));
		m_Attributes[7] = "Engineer";
		break;
	case Hero::THE_MENTALIST:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-0.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),9));
		m_Attributes[7] = "The Mentalist";
		break;
	case Hero::RED_KNIGHT:
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-2.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),9));
		m_Attributes[7] = "Red Knight";
		break;
	}

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext +"\\HUD_Lower.png", FLOAT2(0,0),  FLOAT2(2,2),7));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext +"\\HUD_Minimap.png", FLOAT2(0,0),  FLOAT2(2,2),2));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Bar.png", FLOAT2(-0.35f,-0.84f),  FLOAT2(0.4625f,0.333333333f),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext +"\\HUD_Front.png", FLOAT2(0,0),  FLOAT2(2,2),9));

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Tower.png", FLOAT2(-0.56f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Strength.png", FLOAT2(-0.28f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Agility.png", FLOAT2(-0.0f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Wits.png", FLOAT2(0.28f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Fortitude.png", FLOAT2(0.56f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));

	this->m_LabelSprite.push_back(g_graphicsEngine->createSprite("menu_textures\\Label_1.png",FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*6)+0.46f, -1.5f),FLOAT2(0.103125f, 0.285185185f),8));	
	this->m_LabelSprite.push_back(g_graphicsEngine->createSprite("menu_textures\\Label_2.png",FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*5)+0.46f, -1.5f),FLOAT2(0.103125f, 0.285185185f),8));	
	this->m_LabelSprite.push_back(g_graphicsEngine->createSprite("menu_textures\\Label_3.png",FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*4)+0.46f, -1.5f),FLOAT2(0.103125f, 0.285185185f),8));	
	this->m_LabelSprite.push_back(g_graphicsEngine->createSprite("menu_textures\\Label_4.png",FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*3)+0.46f, -1.5f),FLOAT2(0.103125f, 0.285185185f),8));	
	
	m_enemyIcons[Enemy::EnemyType::IMP] = g_graphicsEngine->createSprite("menu_textures/Imp-2.png", FLOAT2(-0.94f,  0.88f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::IMP]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::SHADE] = g_graphicsEngine->createSprite("menu_textures/Imp-3.png", FLOAT2(-0.94f,  0.88f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::SHADE]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::FROST_DEMON] = g_graphicsEngine->createSprite("menu_textures/Imp-0.png", FLOAT2(-0.94f,  0.88f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::FROST_DEMON]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::SPITTING_DEMON] = g_graphicsEngine->createSprite("menu_textures/Imp-1.png", FLOAT2(-0.94f, 0.88f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::SPITTING_DEMON]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::BRUTE_STEED] = g_graphicsEngine->createSprite("menu_textures/Beast-2.png", FLOAT2(-0.94f,  0.88f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::BRUTE_STEED]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::HELLFIRE_STEED] = g_graphicsEngine->createSprite("menu_textures/Beast-3.png", FLOAT2(-0.94f,  0.88f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::HELLFIRE_STEED]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::SOUL_EATER_STEED] = g_graphicsEngine->createSprite("menu_textures/Beast-0.png", FLOAT2(-0.94f,  0.88f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::SOUL_EATER_STEED]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::THUNDERSTEED] = g_graphicsEngine->createSprite("menu_textures/Beast-1.png", FLOAT2(-0.94f,  0.88f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::THUNDERSTEED]->setVisible(false);
	m_enemyIcons[Enemy::EnemyType::BOSS] = g_graphicsEngine->createSprite("menu_textures/Beast-1.png", FLOAT2(-0.94f,  0.88f), FLOAT2(0.1f,  0.15625f), 9);
	m_enemyIcons[Enemy::EnemyType::BOSS]->setVisible(false);
	
	this->m_Buttons.resize(2);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(0.625f,0.856f),FLOAT2(0.057291667f,0.101851852f),"menu_textures\\Shop_1.png","",0,0,1,2,300);

	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(0.0f, 0.93f),FLOAT2(0.057291667f,0.101851852f),"menu_textures\\Shop.png","",0,0,1,9,100);

	this->m_SkillButtons.resize(6);
	this->m_SkillButtons[0] = new Skill_Buttons();
	this->m_SkillButtons[0]->Init(FLOAT2(-0.735f+(0.102083333f*1), -0.825f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,9,100,false);
	this->m_SkillButtons[0]->ChangAbleBind(false);
	this->m_SkillButtons[1] = new Skill_Buttons();
	this->m_SkillButtons[1]->Init(FLOAT2(-0.945f+(0.102083333f*2), -0.825f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,9,100,false);
	this->m_SkillButtons[2] = new Skill_Buttons();
	this->m_SkillButtons[2]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*0)+0.40f, -1.5f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,9,100,false);
	this->m_SkillButtons[3] = new Skill_Buttons();
	this->m_SkillButtons[3]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*1)+0.40f, -1.5f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE, 0,0,1,9,100,false);
	this->m_SkillButtons[4] = new Skill_Buttons();
	this->m_SkillButtons[4]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*2)+0.40f, -1.5f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,9,100,false);
	this->m_SkillButtons[5] = new Skill_Buttons();
	this->m_SkillButtons[5]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*3)+0.40f, -1.5f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,9,100,false);
	this->m_SkillButtons[0]->ChangAbleBind(false);
	this->m_SkillButtons[1]->ChangAbleBind(false);

	this->m_LabelInput = new TextInput("text4.png",INT2(1150*m_changePosY,1150),55*m_fontsize);
	this->m_ResourceLabel = new TextLabel("","text3.png",INT2(900*m_changePosY,1050),100*m_fontsize);
	string m_TempString = this->m_ResourceLabel->IntToString(m_Resources);
	this->m_ResourceLabel->setText(m_TempString);
	this->m_Chattext.resize(4);
	this->m_Chattext[0] = new TextLabel("","text2.png",INT2(1150*m_changePosY,1108),55*m_fontsize);
	this->m_Chattext[1] = new TextLabel("","text2.png",INT2(1150*m_changePosY,1084),55*m_fontsize);
	this->m_Chattext[2] = new TextLabel("","text2.png",INT2(1150*m_changePosY,1059),55*m_fontsize);
	this->m_Chattext[3] = new TextLabel("","text2.png",INT2(1150*m_changePosY,1036),55*m_fontsize);
	
	this->m_AttributeText.resize(8);
	this->m_AttributeText[0] = new TextLabel("","text5.png",INT2(90*m_changePosY, 987),55*m_fontsize);
	this->m_AttributeText[0]->setText(m_Attributes[0]);
	
	this->m_AttributeText[4] = new TextLabel("","text5.png",INT2(160*m_changePosY, 987),55*m_fontsize);
	this->m_AttributeText[4]->setText(m_Attributes[1]);
	
	this->m_AttributeText[5] = new TextLabel("","text5.png",INT2(230*m_changePosY, 987),55*m_fontsize);
	this->m_AttributeText[5]->setText(m_Attributes[2]);
	
	this->m_AttributeText[6] = new TextLabel("","text5.png",INT2(300*m_changePosY, 987),55*m_fontsize);
	this->m_AttributeText[6]->setText(m_Attributes[3]);
	
	this->m_AttributeText[7] = new TextLabel("","text5.png",INT2(370*m_changePosY, 987),55*m_fontsize);
	this->m_AttributeText[7]->setText(m_Attributes[4]);
	
	this->m_AttributeText[1] = new TextLabel("","text6.png",INT2(180*m_changePosY, 2),45*m_fontsize);
	this->m_AttributeText[1]->setText("  "+m_Attributes[5] +" / "+ m_Attributes[6]+ "_"+ m_Attributes[7]);
	
	this->m_AttributeText[2] = new TextLabel("","text6.png",INT2(505*m_changePosY, 2),45*m_fontsize);
	this->m_AttributeText[2]->setText(m_Attributes[8] +"  %"+"_"+ m_Attributes[9]);
	
	this->m_AttributeText[3] = new TextLabel("","text6.png",INT2(800*m_changePosY, 2),45*m_fontsize);
	this->m_AttributeText[3]->setText(m_Attributes[10] +" %"+ "_"+ m_Attributes[11]);

	this->m_waveText = new TextLabel("1","text6.png", INT2(g_graphicsEngine->getScreenSize().x - 45*m_changePosY, 60), 70*m_fontsize);
	this->m_livesRemaining = new TextLabel("", "text6.png", INT2(g_graphicsEngine->getScreenSize().x - 210*m_changePosY, 330), 55*m_fontsize);

	//}
	//Shop buttons
	for(int i = 0; i < 20; i++)
	{
		this->m_shopButtons.push_back(new Button());
	}

	this->m_shopButtons[0]->Init(FLOAT2(-0.62f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::TURRET_CONSTRUCTION),"100",0,0,1,12,100,0,INT2(422,80), false, Skill::TURRET_CONSTRUCTION,"menu_textures\\Skill_0.png");
	this->m_shopButtons[1]->Init(FLOAT2(-0.62f, 0.4f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::TURRET_DAMAGE),"3500",0,0,1,12,100,3500,INT2(422,324), false, Skill::TURRET_DAMAGE,"menu_textures\\Skill_1.png");
	this->m_shopButtons[2]->Init(FLOAT2(-0.34f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::STRENGTH),"100",0,0,1,12,100,0,INT2(692,80), false, Skill::STRENGTH, "menu_textures\\Skill_2.png");
	this->m_shopButtons[3]->Init(FLOAT2(-0.34f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::PHYSICAL_RESISTANCE),"900",0,0,1,12,100,900,INT2(692,200), false, Skill::PHYSICAL_RESISTANCE,"menu_textures\\Skill_3.png");
	this->m_shopButtons[4]->Init(FLOAT2(-0.34f, 0.4f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::LIFESTEALING_STRIKE),"2200",0,0,1,12,100,2200,INT2(692,324), false, Skill::LIFESTEALING_STRIKE,"menu_textures\\Skill_4.png");
	this->m_shopButtons[5]->Init(FLOAT2(-0.34f, 0.2f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::STUNNING_STRIKE),"2400",0,0,1,12,100,2400,INT2(692,440), false, Skill::STUNNING_STRIKE,"menu_textures\\Skill_5.png");
	this->m_shopButtons[6]->Init(FLOAT2(-0.34f, 0.0f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::DEMONIC_PRESENCE),"4000",0,0,1,12,100,4000, INT2(692,560), false, Skill::DEMONIC_PRESENCE,"menu_textures\\Skill_6.png");
	this->m_shopButtons[7]->Init(FLOAT2(-0.06f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::AGILITY),"100",0,0,1,12,100,0,INT2(1920/2,80), false, Skill::AGILITY,"menu_textures\\Skill_7.png");
	this->m_shopButtons[8]->Init(FLOAT2(-0.06f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::TELEPORT),"500",0,0,1,12,100,500,INT2(1920/2,200), false, Skill::TELEPORT,"menu_textures\\Skill_8.png");
	this->m_shopButtons[9]->Init(FLOAT2(-0.06f, 0.4f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::AIM),"1100",0,0,1,12,100,1100,INT2(1920/2,324), false, Skill::AIM,"menu_textures\\Skill_9.png");
	this->m_shopButtons[10]->Init(FLOAT2(-0.06f, 0.2f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::DEADLY_STRIKE),"2000",0,0,1,12,100,2000,INT2(1920/2,440), false, Skill::DEADLY_STRIKE,"menu_textures\\Skill_10.png");
	this->m_shopButtons[11]->Init(FLOAT2(0.22f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::WITS),"100",0,0,1,12,100,0,INT2(1228,80), false, Skill::WITS,"menu_textures\\Skill_11.png");
	this->m_shopButtons[12]->Init(FLOAT2(0.22f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::POISON_STRIKE),"1700",0,0,1,12,100,1700,INT2(1228,200), false, Skill::POISON_STRIKE,"menu_textures\\Skill_12.png");
	this->m_shopButtons[15]->Init(FLOAT2(0.22f, 0.4f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::HEALING_TOUCH),"1700",0,0,1,12,100,1700,INT2(1228,324), false, Skill::HEALING_TOUCH,"menu_textures\\Skill_19.png");
	this->m_shopButtons[13]->Init(FLOAT2(0.22f, 0.2f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::CHAIN_STRIKE),"2500",0,0,1,12,100,2500,INT2(1228,440), false, Skill::CHAIN_STRIKE,"menu_textures\\Skill_13.png");
	this->m_shopButtons[14]->Init(FLOAT2(0.22f, 0.0f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::CLOUD_OF_DARKNESS),"3500",0,0,1,12,100,3500,INT2(1228,560), false, Skill::CLOUD_OF_DARKNESS,"menu_textures\\Skill_14.png");
	this->m_shopButtons[16]->Init(FLOAT2(0.49f, 0.8f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::FORTITUDE),"100",0,0,1,12,100,0,INT2(1498,80), false, Skill::FORTITUDE,"menu_textures\\Skill_16.png");	
	this->m_shopButtons[17]->Init(FLOAT2(-0.62f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::GREED),"300",0,0,1,12,100,300,INT2(422,200), false, Skill::GREED,"menu_textures\\Skill_17.png");
	this->m_shopButtons[18]->Init(FLOAT2(0.49f, 0.6f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::MENTAL_RESISTANCE),"900",0,0,1,12,100,900,INT2(1498,200), false, Skill::MENTAL_RESISTANCE,"menu_textures\\Skill_18.png");
	this->m_shopButtons[19]->Init(FLOAT2(0.49f, 0.4f),FLOAT2(0.079166667f,0.140740741f),m_skillHolder.getSkill(Skill::WALL),"3000",0,0,1,12,100,3000,INT2(1498,324), false, Skill::WALL,"menu_textures\\Skill_20.png");

	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		this->m_disabledShopButtons.push_back(new Button());
		this->m_disabledShopButtons[i]->Init(this->m_shopButtons[i]->getPos(),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png",this->m_shopButtons[i]->getText(),0,0,1,12,100, 0, this->m_shopButtons[i]->getTextPos());
		this->m_disabledShopButtons[i]->setVisible(false);

		this->m_resourceImages.push_back(new Button());
		this->m_resourceImages[i]->Init(FLOAT2(this->m_shopButtons[i]->getPos().x + 0.12f, this->m_shopButtons[i]->getPos().y) ,FLOAT2(0.079166667f,0.140740741f), "menu_textures\\Button-Skill-Resource.png", "", 0,0,1,9,100,0,INT2(422,200));
		this->m_canAfford[i] = true;
	}

	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Tower.png", FLOAT2(-0.56f,0.3f),  FLOAT2(0.260416667f,1.451851852f),8));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Strength.png", FLOAT2(-0.28f,0.3f),  FLOAT2(0.260416667f,1.451851852f),8));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Agility.png", FLOAT2(-0.0f,0.3f),  FLOAT2(0.260416667f,1.451851852f),8));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Wits.png", FLOAT2(0.28f,0.3f),  FLOAT2(0.260416667f,1.451851852f),8));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Fortitude.png", FLOAT2(0.56f,0.3f),  FLOAT2(0.260416667f,1.451851852f),8));

	this->m_shopVisible = false;
	m_placingTower = false;
	this->displayShop(false);

	//Healthbar
	this->m_fullHealthPos = FLOAT2(-0.9375f, -0.200740741f);
	this->m_healthBar = g_graphicsEngine->createSpriteSheet("menu_textures\\HealthBar.dds", this->m_fullHealthPos, FLOAT2(0.079166667f, 0.755555556f), INT2(10,1),2);
	this->m_healthBar->playAnimation(INT2(0,0),INT2(9,0),true,10);

	//Towers
	int nrOfTowers = 4;
	for(int i = 0; i < nrOfTowers; i++)
	{
		this->m_towerButtons.push_back(new Button());
	}

	this->m_towerButtons[0]->Init(FLOAT2(0.011f,	-0.60f-0.004f), FLOAT2(0.079166667f/1.5f,0.140740741f/1.5f), this->m_skillHolder.getSkill(Skill::TESLA_CHAIN_TURRET), "", 0.0f, 0.0f, 1.0f, 7, 100, 0, INT2(0,0), false, Skill::TESLA_CHAIN_TURRET,"menu_textures\\Turret_Text_Tesla.png");
	this->m_towerButtons[1]->Init(FLOAT2(0.073f,	-0.67f-0.004f), FLOAT2(0.079166667f/1.5f,0.140740741f/1.5f), this->m_skillHolder.getSkill(Skill::FROST_TURRET), "", 0.0f, 0.0f, 1.0f, 7, 100, 0, INT2(0,0), false, Skill::FROST_TURRET,"menu_textures\\Turret_Text_Frost.png");
	this->m_towerButtons[2]->Init(FLOAT2(0.104f,	-0.79f-0.004f), FLOAT2(0.079166667f/1.5f,0.140740741f/1.5f), this->m_skillHolder.getSkill(Skill::POISON_TURRET), "", 0.0f, 0.0f, 1.0f, 7, 100, 0, INT2(0,0), false, Skill::POISON_TURRET,"menu_textures\\Turret_Text_Poison.png");
	this->m_towerButtons[3]->Init(FLOAT2(0.086f,	-0.90f-0.004f), FLOAT2(0.079166667f/1.5f,0.140740741f/1.5f), this->m_skillHolder.getSkill(Skill::DEATH_PULSE_TURRET), "", 0.0f, 0.0f, 1.0f, 7, 100, 0, INT2(0,0), false, Skill::DEATH_PULSE_TURRET,"menu_textures\\Turret_Text_Death.png");

	//Target
	this->m_placingTargetedSkill = false;
	this->m_targetModel = g_graphicsEngine->createModel("Target", FLOAT3(0.0f, 0.0f, 0.0f));
	this->m_targetModel->setAlpha(0.0f);
	this->m_targetModel->neutralize();
	this->m_targetModel->setShadow(false);

	// Sounds
	m_sellSkillsSound = createSoundHandle("buttons/CoinSell_Buy.wav", false, false);
}

bool HudMenu::isDone()const
{
	return m_done;
}

void HudMenu::Update(float _dt, const vector<Entity*>& _entities, unsigned int _heroId, vector<PLAYER_INFO> m_playerInfos, bool _yourHeroIsAlive)
{
	if(m_hasTargetEnemy)
	{
		Entity* currentTarget = ClientEntityHandler::getEntity(m_currentTargetEnemyId);
		if(!currentTarget)
		{
			m_hasTargetEnemy = false;
			m_enemyIcons[m_currentTargetType]->setVisible(false);
		}
	}
	if(m_Buy == false)
	{
		m_menuButton->Update();
	}
	for(int i = 0; i < this->m_towerButtons.size(); i++)
	{
		this->m_towerButtons[i]->Update();
	}
	
	bool switchedTower = false;
	for(int i = 0; i < this->m_towerButtons.size(); i++)
	{
		if(this->m_towerButtons[i]->isClicked())
		{
			if(m_towerModel)
			{
				g_graphicsEngine->removeModel(m_towerModel);
				m_towerModel = NULL;

				if(m_subTowerModel)
				{
					g_graphicsEngine->removeModel(m_subTowerModel);
					m_subTowerModel = NULL;
				}
			}
			
			this->m_towerId = this->m_towerButtons[i]->GetID();

			ModelIdHolder m;

			switch(this->m_towerId)
			{
			case Skill::DEATH_PULSE_TURRET:
				if(m_Resources >= DeathPulseTurret::COST)
				{
					this->m_towerModel = g_graphicsEngine->createModel(m.getModel(4), FLOAT3(0.0f, 0.0f, 0.0f));
					m_towerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
					this->m_towerModel->setAlpha(0.5f);
					this->m_placingTower = true;
					switchedTower = true;
				}
				break;
			case Skill::TESLA_CHAIN_TURRET:
				if(m_Resources >= TeslaChainTurret::COST)
				{
					this->m_towerModel = g_graphicsEngine->createModel(m.getModel(3), FLOAT3(0.0f, 0.0f, 0.0f));
					m_towerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
					this->m_towerModel->setAlpha(0.5f);
					this->m_placingTower = true;
					switchedTower = true;
				}
				break;
			case Skill::FROST_TURRET:
				if(m_Resources >= FrostTurret::COST)
				{
					this->m_towerModel = g_graphicsEngine->createModel(m.getModel(5), FLOAT3(0.0f, 0.0f, 0.0f));
					m_towerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
					this->m_towerModel->setAlpha(0.5f);
					m_subTowerModel = g_graphicsEngine->createModel(m.getModel(6), FLOAT3(0.0f, 0.0f, 0.0f));
					m_subTowerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
					m_subTowerModel->setAlpha(0.5f);
					this->m_placingTower = true;
					switchedTower = true;
				}
				break;
			case Skill::POISON_TURRET:
				if(m_Resources >= PoisonTurret::COST)
				{
					this->m_towerModel = g_graphicsEngine->createModel(m.getModel(2), FLOAT3(0.0f, 0.0f, 0.0f));
					m_towerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
					this->m_towerModel->setAlpha(0.5f);
					this->m_placingTower = true;
					switchedTower = true;
				}
				break;
			}
			
		}
	}

	if(g_keyboard->getKeyState('Z') == Keyboard::KEY_PRESSED)
	{
		if(m_Resources >= TeslaChainTurret::COST)
		{
			if(m_towerModel)
			{
				g_graphicsEngine->removeModel(m_towerModel);
				m_towerModel = NULL;

				if(m_subTowerModel)
				{
					g_graphicsEngine->removeModel(m_subTowerModel);
					m_subTowerModel = NULL;
				}
			}
		
			switchedTower = true;
			this->m_placingTower = true;
			this->m_towerId = this->m_towerButtons[0]->GetID();
			ModelIdHolder m;
			this->m_towerModel = g_graphicsEngine->createModel(m.getModel(3), FLOAT3(0.0f, 0.0f, 0.0f));
			m_towerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
			this->m_towerModel->setAlpha(0.5f);
		}
		else
		{
			if(m_towerModel)
			{
				g_graphicsEngine->removeModel(m_towerModel);
				m_towerModel = NULL;

				if(m_subTowerModel)
				{
					g_graphicsEngine->removeModel(m_subTowerModel);
					m_subTowerModel = NULL;
				}
			}

			m_placingTower = false;
		}
	}
	else if(g_keyboard->getKeyState('X') == Keyboard::KEY_PRESSED)
	{
		if(m_Resources >= FrostTurret::COST)
		{
			if(m_towerModel)
			{
				g_graphicsEngine->removeModel(m_towerModel);
				m_towerModel = NULL;

				if(m_subTowerModel)
				{
					g_graphicsEngine->removeModel(m_subTowerModel);
					m_subTowerModel = NULL;
				}
			}
		
			switchedTower = true;
			this->m_placingTower = true;
			this->m_towerId = this->m_towerButtons[1]->GetID();
			ModelIdHolder m;
			this->m_towerModel = g_graphicsEngine->createModel(m.getModel(5), FLOAT3(0.0f, 0.0f, 0.0f));
			m_towerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
			this->m_towerModel->setAlpha(0.5f);
			m_subTowerModel = g_graphicsEngine->createModel(m.getModel(6), FLOAT3(0.0f, 0.0f, 0.0f));
			m_subTowerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
			m_subTowerModel->setAlpha(0.5f);
		}
		else
		{
			if(m_towerModel)
			{
				g_graphicsEngine->removeModel(m_towerModel);
				m_towerModel = NULL;

				if(m_subTowerModel)
				{
					g_graphicsEngine->removeModel(m_subTowerModel);
					m_subTowerModel = NULL;
				}
			}

			m_placingTower = false;
		}
	}
	else if(g_keyboard->getKeyState('C') == Keyboard::KEY_PRESSED)
	{
		if(m_Resources >= PoisonTurret::COST)
		{
			if(m_towerModel)
			{
				g_graphicsEngine->removeModel(m_towerModel);
				m_towerModel = NULL;

				if(m_subTowerModel)
				{
					g_graphicsEngine->removeModel(m_subTowerModel);
					m_subTowerModel = NULL;
				}
			}
		
			switchedTower = true;
			this->m_placingTower = true;
			this->m_towerId = this->m_towerButtons[2]->GetID();
			ModelIdHolder m;
			this->m_towerModel = g_graphicsEngine->createModel(m.getModel(2), FLOAT3(0.0f, 0.0f, 0.0f));
			m_towerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
			this->m_towerModel->setAlpha(0.5f);
		}
		else
		{
			if(m_towerModel)
			{
				g_graphicsEngine->removeModel(m_towerModel);
				m_towerModel = NULL;

				if(m_subTowerModel)
				{
					g_graphicsEngine->removeModel(m_subTowerModel);
					m_subTowerModel = NULL;
				}
			}

			m_placingTower = false;
		}
	}
	else if(g_keyboard->getKeyState('V') == Keyboard::KEY_PRESSED)
	{
		if(m_Resources >= DeathPulseTurret::COST)
		{
			if(m_towerModel)
			{
				g_graphicsEngine->removeModel(m_towerModel);
				m_towerModel = NULL;

				if(m_subTowerModel)
				{
					g_graphicsEngine->removeModel(m_subTowerModel);
					m_subTowerModel = NULL;
				}
			}
		
			switchedTower = true;
			this->m_placingTower = true;
			this->m_towerId = this->m_towerButtons[3]->GetID();
			ModelIdHolder m;
			this->m_towerModel = g_graphicsEngine->createModel(m.getModel(4), FLOAT3(0.0f, 0.0f, 0.0f));
			m_towerModel->setColor(D3DXVECTOR4(0, 1, 1, 0.4f));
			this->m_towerModel->setAlpha(0.5f);
		}
		else
		{
			if(m_towerModel)
			{
				g_graphicsEngine->removeModel(m_towerModel);
				m_towerModel = NULL;

				if(m_subTowerModel)
				{
					g_graphicsEngine->removeModel(m_subTowerModel);
					m_subTowerModel = NULL;
				}
			}

			m_placingTower = false;
		}
	}

	this->m_AttributeText[0]->setText(m_Attributes[0]);
	
	this->m_AttributeText[4]->setText(m_Attributes[1]);
	
	this->m_AttributeText[5]->setText(m_Attributes[2]);
	
	this->m_AttributeText[6]->setText(m_Attributes[3]);
	
	this->m_AttributeText[7]->setText(m_Attributes[4]);
	if(m_Buy == false)
	{
		this->m_AttributeText[1]->setText("  "+m_Attributes[5] +" / "+ m_Attributes[6]+ "_"+ m_Attributes[7]);
	
		this->m_AttributeText[2]->setText(m_Attributes[8] +"  %"+"_"+ m_Attributes[9]);
	
		this->m_AttributeText[3]->setText(m_Attributes[10] +" %"+ "_"+ m_Attributes[11]);
	}
	else if(m_Buy == true)
	{
		this->m_AttributeText[1]->setText("");
	
		this->m_AttributeText[2]->setText("");
	
		this->m_AttributeText[3]->setText("");
	}
	if(this->m_placingTower && !switchedTower)
	{
		Entity* caster = ClientEntityHandler::getEntity(_heroId);
		bool heroWithinPlacingRange;
		if((caster->m_model->getPosition() - m_towerModel->getPosition()).length() <= TowerPlacer::PLACE_RANGE)
			heroWithinPlacingRange = true;
		else
			heroWithinPlacingRange = false;
		if(m_subTowerModel)
		{
			if(g_graphicsEngine->intersectsWithObject(*m_subTowerModel->getObb(), m_towerModel, m_subTowerModel) || !heroWithinPlacingRange)
			{
				m_towerModel->setTextureIndex("color1");
				m_subTowerModel->setTextureIndex("color1");
				this->m_towerModel->setAlpha(0.9f);
			}
			else
			{
				m_towerModel->setTextureIndex("color");
				m_subTowerModel->setTextureIndex("color");
				this->m_towerModel->setAlpha(0.5f);
				this->m_subTowerModel->setAlpha(0.5f);
			}
		}
		else if(g_graphicsEngine->intersectsWithObject(*m_towerModel->getObb(), m_towerModel) || !heroWithinPlacingRange)
		{
			m_towerModel->setTextureIndex("color1");
			this->m_towerModel->setAlpha(0.9f);
		}
		else
		{
			m_towerModel->setTextureIndex("color");
			this->m_towerModel->setAlpha(0.5f);
		}

		D3DXVECTOR3 pickDir;
		D3DXVECTOR3 pickOrig;
		g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());

		float k = (-pickOrig.y)/pickDir.y;
		D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;

		this->m_towerModel->setPosition(FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z));
		if(m_subTowerModel)
			m_subTowerModel->setPosition(FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z));

		if(g_mouse->isLButtonReleased())
		{
			g_graphicsEngine->removeModel(this->m_towerModel);
			m_towerModel = NULL;
			if(m_subTowerModel)
			{
				g_graphicsEngine->removeModel(this->m_subTowerModel);
				m_subTowerModel = NULL;
			}

			this->m_network->sendMessage(NetworkUseActionPositionMessage(this->m_towerId, FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z), 0));	
			this->m_placingTower = false;
		}
		else if(g_mouse->isRButtonPressed() == true)
		{
			g_graphicsEngine->removeModel(this->m_towerModel);
			m_towerModel = NULL;
			if(m_subTowerModel)
			{
				g_graphicsEngine->removeModel(this->m_subTowerModel);
				m_subTowerModel = NULL;
			}
			this->m_placingTower = false;
		}
	}
	else if(m_Chat == false)
	{
		// YOU MUST ADD ALL WAITING FOR TARGET SKILLS HERE TO NOT EQUAL IF YOU DONT WANT MULTIPLE ACTIONS TO HAPPEN AT THE SAME TIME.
		if(_yourHeroIsAlive && (g_keyboard->getKeyState('Q') != Keyboard::KEY_UP ||
		(m_skillWaitingForTarget != Skill::HEALING_TOUCH && g_mouse->isLButtonDown() &&
			m_Images[0]->intersects(FLOAT2(
			g_mouse->getPos().x/float(g_graphicsEngine->getRealScreenSize().x)*2.0f-1.0f,
			g_mouse->getPos().y/float(g_graphicsEngine->getRealScreenSize().y)*2.0f-1.0f)))))
		{
			// Find yourself in the entity vector
			for(int entityIndex = 0; entityIndex < _entities.size(); entityIndex++)
			{
				if(_entities[entityIndex]->m_id == _heroId && _entities[entityIndex]->m_health > 0)
				{
					g_graphicsEngine->getCamera()->set(_entities[entityIndex]->m_model->getPosition2DAsFloat2() - FLOAT2(0.0f, g_graphicsEngine->getCamera()->getZOffset()));

					entityIndex = _entities.size();
				}
			}
		}

		float max = -0.897916667f+0.001041667f+(0.102083333f*6)+0.025f;

		//Move the skill buttons
		for(int j = 0; j < m_DontChange.size(); j++)
		{
			float m_SkillHudMax = -0.804f;
			if(m_SkillHud[j] >= m_SkillHudMax && m_NumberOfSkills >= j+3 || m_DontChange[j] == false  && m_NumberOfSkills >= j+3)
			{
				m_SkillHud[j] += (_dt*2.0f)+0.005f;
				//this->m_Images[1]->setPosition(FLOAT2(-1.0f +((0.102083333f*(float)m_SkillHud)), -0.814814815f));

				this->m_SkillButtons[j+2]->setPosition(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*(j))+0.40f, m_SkillHud[j]));
				this->m_LabelSprite[j]->setPosition(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*(j))+0.40f, m_SkillHud[j]));

				if (m_SkillHud[j] >= m_SkillHudMax)
				{
					m_SkillHud[j] = m_SkillHudMax;

					//Set all skill buttons to the correct position in the end
					//this->m_Images[1]->setPosition(FLOAT2(-1.0f +((0.102083333f*(float)m_SkillHud)), -0.814814815f));
					this->m_SkillButtons[j+2]->setPosition(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*(j))+0.40f,  -0.829f));
					this->m_LabelSprite[j]->setPosition(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*(j))+0.40f,  -0.804f)); //-1.1782f +(0.102083333f*(((m_SkillHud+((m_NumberOfSkills-1)-(i-2)-(m_NumberOfSkills-5))))))+0.46f

					m_DontChange[j] = true;
				}
			}
		}

		if(this->m_skillWaitingForTarget > -1)
		{
			D3DXVECTOR3 pickDir;
			D3DXVECTOR3 pickOrig;
			g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());

			float k = (-pickOrig.y)/pickDir.y;
			D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;

			if(this->m_placingTargetedSkill == true)
			{
				this->m_targetModel->setPosition(FLOAT3(terrainPos.x, 0.1f, terrainPos.z));
			}

			if(g_mouse->isLButtonPressed() == true)
			{
				if(this->m_skillWaitingForTarget == Skill::CLOUD_OF_DARKNESS || this->m_skillWaitingForTarget == Skill::TELEPORT || this->m_skillWaitingForTarget == Skill::WALL || this->m_skillWaitingForTarget == Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE)
				{
					this->m_network->sendMessage(NetworkUseActionPositionMessage(this->m_skillWaitingForTarget, FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z), this->m_buttonIndex));		
					this->m_placingTargetedSkill = false;
					this->m_targetModel->setAlpha(0.0f);
				}
				else if(m_skillWaitingForTarget == Skill::HYPNOTIC_STARE || m_skillWaitingForTarget == Skill::CHAIN_STRIKE)
				{
					// Check if the target is the pic of the target down in the corner
					if(m_hasTargetEnemy && m_Images[m_currentTargetType]->intersects(FLOAT2(
						g_mouse->getPos().x/float(g_graphicsEngine->getRealScreenSize().x)*2.0f-1.0f, g_mouse->getPos().y/float(g_graphicsEngine->getRealScreenSize().y)*2.0f-1.0f)))
					{
						Entity* currentTarget = ClientEntityHandler::getEntity(m_currentTargetEnemyId);
						this->m_network->sendMessage(NetworkUseActionTargetMessage(m_skillWaitingForTarget, currentTarget->m_id, this->m_buttonIndex));
					}
					// Else the pick ray is out on the battlefield
					else
					{
						g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
						
						float dist;
						for(int entityIndex = 0; entityIndex < _entities.size(); entityIndex++)
						{
							if(_entities[entityIndex]->m_type == ServerEntity::EnemyType && _entities[entityIndex]->m_model->intersects(dist, pickOrig, pickDir))
							{
								this->m_network->sendMessage(NetworkUseActionTargetMessage(m_skillWaitingForTarget, _entities[entityIndex]->m_id, this->m_buttonIndex));
								entityIndex = _entities.size();
							}
						}
					}
				}
				else if(m_skillWaitingForTarget == Skill::HEALING_TOUCH)
				{
					// Check if the target is the pic of yourself down in the corner
					if(m_Images[0]->intersects(FLOAT2(
						g_mouse->getPos().x/float(g_graphicsEngine->getRealScreenSize().x)*2.0f-1.0f, g_mouse->getPos().y/float(g_graphicsEngine->getRealScreenSize().y)*2.0f-1.0f)))
					{
						// Find yourself in the entity vector
						for(int entityIndex = 0; entityIndex < _entities.size(); entityIndex++)
						{
							if(_entities[entityIndex]->m_id == _heroId)
							{
								this->m_network->sendMessage(NetworkUseActionTargetMessage(m_skillWaitingForTarget, _entities[entityIndex]->m_id, this->m_buttonIndex));
								entityIndex = _entities.size();
							}
						}
					}
					// Else the pick ray is out on the battlefield
					else
					{
						g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
						
						float dist;
						for(int entityIndex = 0; entityIndex < _entities.size(); entityIndex++)
						{
							if(_entities[entityIndex]->m_type == ServerEntity::HeroType && _entities[entityIndex]->m_model->intersects(dist, pickOrig, pickDir))
							{
								this->m_network->sendMessage(NetworkUseActionTargetMessage(m_skillWaitingForTarget, _entities[entityIndex]->m_id, this->m_buttonIndex));
								entityIndex = _entities.size();
							}
						}
					}
				}

				this->m_skillWaitingForTarget = -1;
				g_mouse->getCursor()->setPriority(1);
			}
			else if(g_mouse->isRButtonPressed() == true)
			{
				this->m_skillWaitingForTarget = -1;
				g_mouse->getCursor()->setPriority(1);
				this->m_placingTargetedSkill = false;
				this->m_targetModel->setAlpha(0.0f);
			}
		}

		for(int i = 2; i < m_NumberOfSkills; i++)
		{
			this->m_SkillButtons[i]->Update(_dt);
			
			if(g_keyboard->getKeyState('0' + i - 1) == Keyboard::KEY_PRESSED || this->m_SkillButtons[i]->Clicked() > 0)
			{
				if(m_SkillButtons[i]->getSkillId() == Skill::CLOUD_OF_DARKNESS || m_SkillButtons[i]->getSkillId() == Skill::HEALING_TOUCH || m_SkillButtons[i]->getSkillId() == Skill::TELEPORT || m_SkillButtons[i]->getSkillId() == Skill::HYPNOTIC_STARE
						|| m_SkillButtons[i]->getSkillId() == Skill::CHAIN_STRIKE || m_SkillButtons[i]->getSkillId() == Skill::WALL || m_SkillButtons[i]->getSkillId() == Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE)
				{
					this->m_skillWaitingForTarget = this->m_SkillButtons[i]->getSkillId();
					this->m_buttonIndex = i;

					switch(this->m_skillWaitingForTarget)
					{
					case Skill::CLOUD_OF_DARKNESS:
						{
							g_mouse->getCursor()->setFrame(Cursor::CLOUD_OF_DARKNESS, 3);
							Model *temp = g_graphicsEngine->createModel("CloudOfDarkness", FLOAT3());
							this->m_targetModel->setScale(temp->getBs()->Radius * 0.5f * 2, temp->getBs()->Radius * 0.5f * 2, temp->getBs()->Radius * 0.5f * 2);
							g_graphicsEngine->removeModel(temp);
							this->m_targetModel->setAlpha(0.999f);
							this->m_placingTargetedSkill = true;
						}
						break;
					case Skill::HEALING_TOUCH:
						g_mouse->getCursor()->setFrame(Cursor::HEALING_TOUCH, 3);
						break;
					case Skill::TELEPORT:
						g_mouse->getCursor()->setFrame(Cursor::TELEPORT, 3);
						break;
					case Skill::CHAIN_STRIKE:
						g_mouse->getCursor()->setFrame(Cursor::CHAIN_STRIKE, 3);
						break;
					case Skill::HYPNOTIC_STARE:
						g_mouse->getCursor()->setFrame(Cursor::HYPNOTIC_STARE, 3);
						break;
					case Skill::WALL:
						g_mouse->getCursor()->setFrame(Cursor::WALL, 3);
						break;
					case Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE:
						g_mouse->getCursor()->setFrame(Cursor::TARGET_ACQUIRED, 3);
						this->m_targetModel->setScale(TargetAcquiredPermissionToFire::RANGE * 2, TargetAcquiredPermissionToFire::RANGE * 2, TargetAcquiredPermissionToFire::RANGE * 2);
						this->m_targetModel->setAlpha(0.999f);
						this->m_placingTargetedSkill = true;
						break;
					}
				}
				else if(m_SkillButtons[i]->getSkillId() == Skill::STUNNING_STRIKE || m_SkillButtons[i]->getSkillId() == Skill::DEMONIC_PRESENCE || m_SkillButtons[i]->getSkillId() == Skill::SIMONS_EVIL ||
						m_SkillButtons[i]->getSkillId() == Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR || m_SkillButtons[i]->getSkillId() == Skill::TIME_IS_MONEY)
				{
					this->m_network->sendMessage(NetworkUseActionMessage(m_SkillButtons[i]->getSkillId(), i));
				}
			}
		}

		// Do the E skill
		this->m_SkillButtons[0]->Update(_dt);
		this->m_SkillButtons[1]->Update(_dt);

		if(this->m_SkillButtons.size() > 0 && (g_keyboard->getKeyState('E') == Keyboard::KEY_PRESSED || this->m_SkillButtons[1]->Clicked() > 0))
		{
			if(m_SkillButtons[1]->getSkillId() == Skill::CLOUD_OF_DARKNESS || m_SkillButtons[1]->getSkillId() == Skill::HEALING_TOUCH || m_SkillButtons[1]->getSkillId() == Skill::TELEPORT || m_SkillButtons[1]->getSkillId() == Skill::HYPNOTIC_STARE
					|| m_SkillButtons[1]->getSkillId() == Skill::CHAIN_STRIKE || m_SkillButtons[1]->getSkillId() == Skill::WALL || m_SkillButtons[1]->getSkillId() == Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE)
			{
				this->m_skillWaitingForTarget = this->m_SkillButtons[1]->getSkillId();
				this->m_buttonIndex = 1;

				switch(this->m_skillWaitingForTarget)
				{
				case Skill::CLOUD_OF_DARKNESS:
					g_mouse->getCursor()->setFrame(Cursor::CLOUD_OF_DARKNESS, 3);
					break;
				case Skill::HEALING_TOUCH:
					g_mouse->getCursor()->setFrame(Cursor::HEALING_TOUCH, 3);
					break;
				case Skill::TELEPORT:
					g_mouse->getCursor()->setFrame(Cursor::TELEPORT, 3);
					break;
				case Skill::CHAIN_STRIKE:
					g_mouse->getCursor()->setFrame(Cursor::CHAIN_STRIKE, 3);
					break;
				case Skill::HYPNOTIC_STARE:
					g_mouse->getCursor()->setFrame(Cursor::HYPNOTIC_STARE, 3);
					break;
				case Skill::WALL:
					g_mouse->getCursor()->setFrame(Cursor::WALL, 3);
					break;
				case Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE:
					g_mouse->getCursor()->setFrame(Cursor::TARGET_ACQUIRED, 3);
					this->m_targetModel->setScale(TargetAcquiredPermissionToFire::RANGE * 2, TargetAcquiredPermissionToFire::RANGE * 2, TargetAcquiredPermissionToFire::RANGE * 2);
					this->m_targetModel->setAlpha(0.999f);
					this->m_placingTargetedSkill = true;
					break;
				}
			}
			else if(m_SkillButtons[1]->getSkillId() == Skill::STUNNING_STRIKE || m_SkillButtons[1]->getSkillId() == Skill::DEMONIC_PRESENCE || m_SkillButtons[1]->getSkillId() == Skill::SIMONS_EVIL ||
					m_SkillButtons[1]->getSkillId() == Skill::SWIFT_AS_A_CAT_POWERFUL_AS_A_BEAR || m_SkillButtons[1]->getSkillId() == Skill::TIME_IS_MONEY)
			{
				this->m_network->sendMessage(NetworkUseActionMessage(m_SkillButtons[1]->getSkillId(), 1));
			}
		}

		for(int i = 0; i < m_Buttons.size(); i++)
		{
			this->m_Buttons[i]->Update();
		}
		if (m_Buy == true)
		{
			UpdateShop();

			if (BuyAllSkillIsDown())
			{
				this->displayShop(false);
				m_Buy = false;
			}
			else if(g_keyboard->getKeyState(VK_ESCAPE) == Keyboard::KEY_PRESSED)
			{
				this->displayShop(false);
				m_Buy = false;
				for(int i = 0; i < m_shopButtons.size(); i++)
				{
					m_shopButtons[i]->setAllSkillSprites(false);
				}
			}
		}
		else if(m_Buy == false)
		{				
			if (BuyAllSkillIsDown())
			{
				this->displayShop(true);
				m_Buy = true;
			}
		}

		if (g_keyboard->getKeyState(VK_RETURN) == Keyboard::KEY_PRESSED)
		{
			m_Chat = true;
			g_keyboard->setChatMode(m_Chat);
		}
	}
	else
	{
		this->m_LabelInput->update(_dt, true);

		if(g_keyboard->getKeyStateChatSuper(VK_RETURN) == Keyboard::KEY_PRESSED)
		{
			string m_String = "";
			m_String.erase(m_String.begin());
			m_String = this->m_LabelInput->getText();
			m_String.erase(m_String.end());
			
			this->m_network->sendMessage(NetworkTextMessage(m_String));
			this->m_LabelInput->setText(""); 
			this->m_Chattext[3]->setText("");
			m_Chat = false;
			g_keyboard->setChatMode(m_Chat);
		}
	}

	if(m_menuButton->isClicked() && m_Buy == false)
	{
		m_leaveButton->setVisible(!m_leaveButton->isVisible());
	}
	if(m_leaveButton->isVisible() && m_Buy ==false)
	{
		m_leaveButton->Update();
		if(m_leaveButton->isClicked())
			m_done = true;
	}
	while(!this->m_network->networkTextMessageQueueEmpty())
	{
		NetworkTextMessage e = this->m_network->networkTextMessageFront();
		for(int i = m_Chattext.size()-1; i > 0;i--)
		{
			m_Chattext[i]->setText(m_Chattext[i-1]->getText());
		}
		this->m_Chattext[0]->setText(e.getTxtMessage());
	}

	LockIsDown();
}
void HudMenu::UnInit(int _Type)
{

}
bool HudMenu::LockIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		if(m_NumberOfSkills > 2)
			playSound(m_sellSkillsSound);

		this->m_network->sendMessage(NetworkBuySkillMessage(Skill::SELL));
		m_NumberOfSkills = 2;
		m_SkillHud[0] = -1.5f;
		m_SkillHud[1] = -1.5f;
		m_SkillHud[2] = -1.5f;
		m_SkillHud[3] = -1.5f;
		for(int j =0; j< m_LabelSprite.size();j++)
		{
			this->m_LabelSprite[j]->setPosition(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*(j))+0.40f, -1.5f));
		}
		this->m_SkillButtons[5]->ChangeButton("30", false, 0);
		this->m_SkillButtons[4]->ChangeButton("30", false, 0);
		this->m_SkillButtons[3]->ChangeButton("30", false, 0);
		this->m_SkillButtons[2]->ChangeButton("30", false, 0);
		for(int i = 0; i < m_DontChange.size();i++)
		{
			m_DontChange[i] = false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool HudMenu::BuyAllSkillIsDown()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool HudMenu::MenuIsDown()
{
	if(this->m_Buttons[1]->Clicked() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

HudMenu::~HudMenu(void)
{
	stopSound(m_sellSkillsSound);
	deactivateSound(m_sellSkillsSound);
	delete m_menuButton;
	delete m_leaveButton;
	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		delete this->m_shopButtons[i];
		delete this->m_resourceImages[i];
		delete this->m_disabledShopButtons[i];
	}

	for(map<Enemy::EnemyType, Sprite*>::iterator iter = m_enemyIcons.begin(); iter != m_enemyIcons.end(); iter++)
		g_graphicsEngine->removeSprite(iter->second);

	for(int i = 0; i < this->m_shopBackground.size(); i++)
	{
		g_graphicsEngine->removeSprite(this->m_shopBackground[i]);
	}

	delete this->m_LabelInput;
	for(int i=0 ; i < this->m_Chattext.size();i++)
	{
		delete this->m_Chattext[i];
		this->m_Chattext[i] = NULL;
	}

	for(int i = 0; i < this->m_towerButtons.size(); i++)
	{
		delete this->m_towerButtons[i];
	}
	for(int i = 0; i < m_LabelSprite.size();i++)
	{
		g_graphicsEngine->removeSprite(this->m_LabelSprite[i]);
	}

	delete this->m_ResourceLabel;
	this->m_ResourceLabel = NULL;
	for(int i = 0 ; i < this->m_AttributeText.size();i++)
	{
		delete this->m_AttributeText[i];
		this->m_AttributeText[i] = NULL;
	}
	g_graphicsEngine->removeSpriteSheet(this->m_healthBar);
	
	if(m_towerModel)
		g_graphicsEngine->removeModel(m_towerModel);
	if(m_subTowerModel)
		g_graphicsEngine->removeModel(m_subTowerModel);

	delete this->m_livesRemaining;
	delete this->m_waveText;
}

void  HudMenu::UpdateShop()
{
	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		this->m_shopButtons[i]->Update();
		this->m_resourceImages[i]->Update();

		if(this->m_shopButtons[i]->Clicked() == 1)
		{
			this->m_network->sendMessage(NetworkBuySkillMessage(this->m_shopButtons[i]->GetID()));
		}
	}
}

void HudMenu::displayShop(bool _visible)
{
	this->m_shopVisible = _visible;
	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		if(this->m_canAfford[i] == true)
		{
			this->m_shopButtons[i]->setVisible(_visible);
		}
		else
		{
			this->m_disabledShopButtons[i]->setVisible(_visible);
		}

		this->m_resourceImages[i]->setVisible(_visible);
	}

	for(int i = 0; i < this->m_shopBackground.size(); i++)
	{
		this->m_shopBackground[i]->setVisible(_visible);
	}
}

void HudMenu::addSkill(unsigned int _skillId)
{
	if(this->m_skillHolder.getSkill(_skillId) != "")
	{
		if(_skillId == Skill::STRENGTH || _skillId == Skill::AGILITY || _skillId == Skill::WITS || _skillId == Skill::FORTITUDE || _skillId == Skill::TURRET_CONSTRUCTION)
		{
			this->m_nrOfAttributesBought++;
			int cost = 100 * (pow(1.12f, this->m_nrOfAttributesBought));
			if (cost >= 5000)
			{
				cost = 5000;
			}
			stringstream ss;
			ss << cost;
			this->m_shopButtons[0]->setText(ss.str());
			this->m_shopButtons[2]->setText(ss.str());
			this->m_shopButtons[7]->setText(ss.str());
			this->m_shopButtons[11]->setText(ss.str());
			this->m_shopButtons[16]->setText(ss.str());

			this->m_disabledShopButtons[0]->setText(ss.str());
			this->m_disabledShopButtons[2]->setText(ss.str());
			this->m_disabledShopButtons[7]->setText(ss.str());
			this->m_disabledShopButtons[11]->setText(ss.str());
			this->m_disabledShopButtons[16]->setText(ss.str());
		}
		else
		{
			this->m_SkillButtons[this->m_NumberOfSkills]->ChangeButton(this->m_skillHolder.getSkill(_skillId), this->m_skillHolder.getActive(_skillId), _skillId,this->m_skillHolder.getDescription(_skillId));

			if(this->m_NumberOfSkills >= 2)
			{
				this->m_DontChange[m_NumberOfSkills - 2] = false;
				m_SkillHud[m_NumberOfSkills - 2] = -1.5f;
				bool checkActive = true;
				checkActive = this->m_SkillButtons[this->m_NumberOfSkills]->getActiveorPassive();

				if (checkActive == false)
				{
					//int numbers = this->m_NumberOfSkills-1;
					//stringstream ss;
					//ss << numbers;
					g_graphicsEngine->removeSprite(m_LabelSprite[m_NumberOfSkills-2]);
					this->m_LabelSprite[m_NumberOfSkills-2] = (g_graphicsEngine->createSprite("menu_textures\\Label_P.png",FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*(m_NumberOfSkills-2))+0.46f, -1.5f),FLOAT2(0.103125f, 0.285185185f),8));	
				}
				else
				{
					stringstream ss;
					ss<<"menu_textures\\Label_"<<m_NumberOfSkills-1<<".png";
					g_graphicsEngine->removeSprite(m_LabelSprite[m_NumberOfSkills-2]);
					this->m_LabelSprite[m_NumberOfSkills-2] = (g_graphicsEngine->createSprite(ss.str(),FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*(m_NumberOfSkills-2))+0.46f, -1.5f),FLOAT2(0.103125f, 0.285185185f),8));	
				}
			}

			this->m_NumberOfSkills++;
		}
	}
}

void HudMenu::removeTargetEnemy()
{
	if(m_hasTargetEnemy)
	{
		Entity* currentUnit = ClientEntityHandler::getEntity(m_currentTargetEnemyId);
		if(currentUnit)
		{
			m_enemyIcons[Enemy::EnemyType(currentUnit->m_subtype)]->setVisible(false);
			m_hasTargetEnemy = false;
		}
	}
}

void HudMenu::setResources(unsigned int _resources)
{
	stringstream ss;
	ss<<_resources;

	this->m_Resources = _resources;
	this->m_ResourceLabel->setText(ss.str());

	//Update the buttons in the shop
	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		if(this->m_shopButtons[i]->getCost() > this->m_Resources)
		{
			this->m_canAfford[i] = false;
			this->m_shopButtons[i]->setVisible(false);
		}
		else
		{
			this->m_canAfford[i] = true;
			this->m_disabledShopButtons[i]->setVisible(false);
		}
	}

	if(this->m_shopVisible == true)
	{
		this->displayShop(true);
	}
}

void HudMenu::skillUsed(unsigned int index, unsigned int actionId, float cooldown)
{
	if(this->m_SkillButtons[index]->getSkillId() == actionId)
	{
		this->m_SkillButtons[index]->setCooldown(cooldown);
	}
}

void HudMenu::setHealth(int _health)
{
	if(_health > 0)
	{
		stringstream ss;
		ss << _health;
		m_Attributes[5] = ss.str();
	}
	else
		m_Attributes[5] = "0";

	this->m_health = _health;
	float h = (1.0f - (float)this->m_health / (float)this->m_maxHealth);
	h = min(1.0f, max(h, 0.0f));
	this->m_healthBar->setPosition(FLOAT2(this->m_fullHealthPos.x, this->m_fullHealthPos.y - h * 0.495555556f));
}

void HudMenu::setMaxHealth(int _maxHealth)
{
	stringstream ss;
	ss << _maxHealth;
	m_Attributes[6] = ss.str();

	this->m_maxHealth = _maxHealth;
	float h = (1.0f - (float)this->m_health / (float)this->m_maxHealth);
	h = min(1.0f, max(h, 0.0f));
	this->m_healthBar->setPosition(FLOAT2(this->m_fullHealthPos.x, this->m_fullHealthPos.y - h * 0.495555556f));
}

void HudMenu::setTargetEnemy(unsigned int _currentTargetEnemyId)
{
	if(m_hasTargetEnemy)
	{
		Entity* currentUnit = ClientEntityHandler::getEntity(m_currentTargetEnemyId);
		if(currentUnit != NULL)
		{
			m_enemyIcons[Enemy::EnemyType(currentUnit->m_subtype)]->setVisible(false);
		}
	}
	else
	{
		m_hasTargetEnemy = true;
	}

	Entity* targetUnit = ClientEntityHandler::getEntity(_currentTargetEnemyId);
	m_currentTargetType = Enemy::EnemyType(targetUnit->m_subtype);
	m_enemyIcons[m_currentTargetType]->setVisible(true);

	m_currentTargetEnemyId = _currentTargetEnemyId;
}

void HudMenu::setLivesRemaining(int livesRemaing)
{
	stringstream ss;
	ss<<livesRemaing;
	this->m_livesRemaining->setText(ss.str());
}

void HudMenu::setStrength(int _strength)
{
	this->m_strength = _strength;
	stringstream ss;
	ss<<this->m_strength;
	this->m_Attributes[1] = ss.str();
}

void HudMenu::setAgility(int _agility)
{
	this->m_agility = _agility;
	stringstream ss;
	ss<<this->m_agility;
	this->m_Attributes[2] = ss.str();
}

void HudMenu::setWits(int _wits)
{
	this->m_wits = _wits;
	stringstream ss;
	ss<<this->m_wits;
	this->m_Attributes[3] = ss.str();
}

void HudMenu::setFortitude(int _fortitude)
{
	this->m_fortitude = _fortitude;
	stringstream ss;
	ss<<this->m_fortitude;
	this->m_Attributes[4] = ss.str();
}

void HudMenu::setMentalDamage(int _md)
{
	stringstream ss;
	ss << _md;
	m_Attributes[11] = ss.str();
}

void HudMenu::setMentalResistance(float _mr)
{
	_mr = (1.0f-_mr)*100;
	stringstream ss;
	ss << _mr;
	m_Attributes[10] = ss.str() + " o/o";
}

void HudMenu::setPhysicalDamage(int _pd)
{
	stringstream ss;
	ss << _pd;
	m_Attributes[9] = ss.str();
}

void HudMenu::setPhysicalResistance(float _pr)
{
	_pr = (1.0f-_pr)*100;
	stringstream ss;
	ss << _pr;
	m_Attributes[8] = ss.str() + " o/o";
}

void HudMenu::setTowerConstruction(int _towerConstruction)
{
	this->m_towerConstruction = _towerConstruction;
	stringstream ss;
	ss<<this->m_towerConstruction;
	this->m_Attributes[0] = ss.str();
}

void HudMenu::setWave(int _wave)
{
	stringstream ss;
	ss<<_wave;
	this->m_waveText->setText(ss.str());
}