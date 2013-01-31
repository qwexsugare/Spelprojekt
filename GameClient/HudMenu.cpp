#include "HudMenu.h"


HudMenu::HudMenu(Client *_network)
{
	this->m_network = _network;
	m_Chat = false;
	m_Time = 0;
	m_Delay = 0;
	m_DelayTime = 10;
	m_SkillHud = -1.0f;
	m_NumberOfSkills = 0;
	int TmpPos = m_NumberOfSkills * 98;
	m_DontChange = false;
	m_Buy = false;
	m_Menu= false;
	m_Locked = true;
	m_DontChange = false;
	m_OncePerBuy = false;
	m_Resources = 200000;
	m_First = 0;
	m_DelayTime = 500;
	m_Chat = false;
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-0.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),5));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-1.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),5));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-3.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),6));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-3.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),5));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-4.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),5));
	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Main_Buttons_SkillBar.png", FLOAT2(-1+(0.102083333f*(m_NumberOfSkills-1)),  -0.814814815f),  FLOAT2(1.03125f, 0.344444444f),2));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\GUI-Map.png",FLOAT2(0.79f,  0.6f),FLOAT2(0.421875f, 0.796296296f),5));

	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\GUI-Map.png", FLOAT2(0,0),  FLOAT2(2,2),3));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\LowerHud-Bar.png", FLOAT2(-0.5f,-0.88f),  FLOAT2(1.030208333f,0.272222222f),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\GUI-HealtbarHud.png", FLOAT2(-0.876f,-0.3293f),  FLOAT2(0.245833333f,1.344f),5));
	this->m_Sprite.push_back(g_graphicsEngine->createSpriteSheet("menu_textures\\HealthBar.dds",FLOAT2(-0.9375f,  -0.240740741f),FLOAT2(0.079166667f, 0.755555556f),INT2(10,1),2));

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Tower.png", FLOAT2(-0.56f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Strength.png", FLOAT2(-0.28f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Agility.png", FLOAT2(-0.0f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Wits.png", FLOAT2(0.28f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Fortitude.png", FLOAT2(0.56f,1.8f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\GUI-HealtbarHud.png", FLOAT2(-0.876f,-0.3293f),  FLOAT2(0.245833333f,1.344f),5));

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Chain_Lower.png",FLOAT2(0.0f,  -1.0f),FLOAT2(2.0f, 0.092592593f),6));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Chain_Side.png",FLOAT2(-1.0f,  0.0f),FLOAT2(0.052083333f, 3.555555556f),6));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Resourcehud.png",FLOAT2(0.0f,  -0.85f),FLOAT2(0.260416667f,  0.42962963f),5));	

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\ChatWindow-Hud.png",FLOAT2(0.5f,  -0.91f),FLOAT2(0.973958333f,  0.32962963f),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.15f,  -1.0f),FLOAT2(0.375f/3,  0.666666667f/3),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.43f,  -0.98f),FLOAT2(0.375f/2, 0.666666667f/2),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.0f,  -0.855f),FLOAT2(0.375f/1.3f,  0.666666667f/1.3f),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.265f,  -0.90f),FLOAT2(0.375f/2,  0.666666667f/2),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.85f,  -0.79f),FLOAT2(0.375f/1.2f,  0.666666667f/1.2f),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.6f,  -0.90f),FLOAT2(0.375f/2,  0.666666667f/2),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Gear.png",FLOAT2(-0.6f,  -0.90f),FLOAT2(0.375f/1.4f,  0.666666667f/1.4f),1));	
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Color-Test.png",FLOAT2(0,0),FLOAT2(2,2),12));	

	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Tower.png", FLOAT2(-0.56f,1.6f),  FLOAT2(0.260416667f,1.451851852f),10));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Strength.png", FLOAT2(-0.28f,1.6f),  FLOAT2(0.260416667f,1.451851852f),10));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Agility.png", FLOAT2(-0.0f,1.6f),  FLOAT2(0.260416667f,1.451851852f),10));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Wits.png", FLOAT2(0.28f,1.6f),  FLOAT2(0.260416667f,1.451851852f),10));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Fortitude.png", FLOAT2(0.56f,1.6f),  FLOAT2(0.260416667f,1.451851852f),10));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-0.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f*1.5f,0.148148148f*1.5f),5));

	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Beast-0.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f,0.148148148f),5));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Beast-1.png", FLOAT2(-0.938f, -0.64f),  FLOAT2(0.083333333f,0.148148148f),6));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Beast-2.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f,0.148148148f),5));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Beast-3.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f,0.148148148f),5));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-0.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f,0.148148148f),5));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-1.png", FLOAT2(-0.938f, -0.64f),  FLOAT2(0.083333333f,0.148148148f),6));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-2.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f,0.148148148f),5));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-3.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f,0.148148148f),5));
	//this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Character-4.png", FLOAT2(-0.91f, -0.85f),  FLOAT2(0.083333333f,0.148148148f),5));
	
	this->m_Buttons.resize(2);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.95f,-0.50f),FLOAT2(0.033333333f,0.059259259f),"menu_textures\\Button-Unlock.png","",0,0,1,11,300);
	
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.94f,0.94f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_All.png","",0,0,1,11,100);	
/*
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.56f,0.94f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Tower.png","",0,0,1,11,100);	
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(-0.28f,0.94f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Strength.png","",0,0,1,11,100);	
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.0f,0.94f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Agility.png","",0,0,1,11,100);	
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(0.28f,0.94f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Wits.png","",0,0,1,11,100);	
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(0.56f,0.94f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Fortitude.png","",0,0,1,11,100);*/	

	this->m_SkillButtons.resize(6);
	this->m_SkillButtons[0] = new Skill_Buttons();
	this->m_SkillButtons[0]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*1)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[0]->ChangAbleBind(false);
	this->m_SkillButtons[1] = new Skill_Buttons();
	this->m_SkillButtons[1]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*2)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[2] = new Skill_Buttons();
	this->m_SkillButtons[2]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*3)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[3] = new Skill_Buttons();
	this->m_SkillButtons[3]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*4)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE, 0,0,1,4,100,false);
	this->m_SkillButtons[4] = new Skill_Buttons();
	this->m_SkillButtons[4]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*5)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[5] = new Skill_Buttons();
	this->m_SkillButtons[5]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*6)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",Skill::MOVE,0,0,1,4,100,false);
	this->m_SkillButtons[0]->ChangAbleBind(false);
	this->m_SkillButtons[1]->ChangAbleBind(false);
	m_Sprite[0]->playAnimation(INT2(0,0),INT2(9,0),true,10);
	m_DontChange = false;

	this->m_LabelInput = new TextInput("text4.png",INT2(1100,1150),55);
	this->m_ResourceLabel = new TextLabel("","text3.png",INT2(925,1100),100);
	string m_TempString = this->m_ResourceLabel->IntToString(m_Resources);
	this->m_ResourceLabel->setText(m_TempString);
	this->m_Chattext.resize(4);
	this->m_Chattext[0] = new TextLabel("","text2.png",INT2(1100,1120),55);
	this->m_Chattext[1] = new TextLabel("","text2.png",INT2(1100,1090),55);
	this->m_Chattext[2] = new TextLabel("","text2.png",INT2(1100,1060),55);
	this->m_Chattext[3] = new TextLabel("","text2.png",INT2(1100,1030),55);

	for(int i = 0; i < 20; i++)
	{
		this->m_shopButtons.push_back(new Button());
		this->m_resourceImages.push_back(new Button());
	}

	this->m_shopButtons[0]->Init(FLOAT2(-0.62f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-0.png","0",0,0,1,12,100,0,INT2(422,80), false, Skill::TOWER);
	this->m_shopButtons[1]->Init(FLOAT2(-0.62f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-12.png","3500",0,0,1,12,100,3500,INT2(422,200), false, Skill::TURRET_LIFE);
	this->m_shopButtons[2]->Init(FLOAT2(-0.34f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-1.png","0",0,0,1,12,100,0,INT2(692,80), false, Skill::STRENGTH);
	this->m_shopButtons[3]->Init(FLOAT2(-0.34f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-7.png","900",0,0,1,12,100,900,INT2(692,200), false, Skill::PHYSICAL_RESISTANCE);
	this->m_shopButtons[4]->Init(FLOAT2(-0.34f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-9.png","2200",0,0,1,12,100,2200,INT2(692,324), false, Skill::LIFESTEALING_STRIKE);
	this->m_shopButtons[5]->Init(FLOAT2(-0.34f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-13.png","2400",0,0,1,12,100,2400,INT2(692,440), false, Skill::STUNNING_STRIKE);
	this->m_shopButtons[6]->Init(FLOAT2(-0.34f, 0.0f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-16.png","4000",0,0,1,12,100,4000, INT2(692,560), false, Skill::DEMONIC_PRESENCE);
	this->m_shopButtons[7]->Init(FLOAT2(-0.06f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-2.png","0",0,0,1,12,100,0,INT2(1920/2,80), false, Skill::AGILITY);
	this->m_shopButtons[8]->Init(FLOAT2(-0.06f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-18.png","500",0,0,1,12,100,500,INT2(1920/2,200), false, Skill::TELEPORT);
	this->m_shopButtons[9]->Init(FLOAT2(-0.06f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-5.png","1100",0,0,1,12,100,1100,INT2(1920/2,324), false, Skill::AIM);
	this->m_shopButtons[10]->Init(FLOAT2(-0.06f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-11.png","2000",0,0,1,12,100,2000,INT2(1920/2,440), false, Skill::DEADLY_STRIKE);
	this->m_shopButtons[11]->Init(FLOAT2(0.22f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-3.png","0",0,0,1,12,100,0,INT2(1228,80), false, Skill::WITS);
	this->m_shopButtons[12]->Init(FLOAT2(0.22f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-10.png","1700",0,0,1,12,100,1700,INT2(1228,200), false, Skill::POISON_STRIKE);
	this->m_shopButtons[13]->Init(FLOAT2(0.22f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-14.png","2500",0,0,1,12,100,2500,INT2(1228,324), false, Skill::CHAIN_STRIKE);
	this->m_shopButtons[14]->Init(FLOAT2(0.22f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-17.png","3500",0,0,1,12,100,3500,INT2(1228,440), false, Skill::CLOUD_OF_DARKNESS);
	this->m_shopButtons[15]->Init(FLOAT2(0.22f, 0.0f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-19.png","1700",0,0,1,12,100,1700,INT2(1228,560), false, Skill::HEALING_TOUCH);
	this->m_shopButtons[16]->Init(FLOAT2(0.49f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-4.png","0",0,0,1,12,100,0,INT2(1498,80), false, Skill::FORTITUDE);
	this->m_shopButtons[17]->Init(FLOAT2(0.49f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-6.png","700",0,0,1,12,100,700,INT2(1498,200), false, Skill::GREED);
	this->m_shopButtons[18]->Init(FLOAT2(0.49f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-8.png","900",0,0,1,12,100,900,INT2(1498,324), false, Skill::MENTAL_RESISTANCE);
	this->m_shopButtons[19]->Init(FLOAT2(0.49f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-20.png","3000",0,0,1,12,100,3000,INT2(1498,440), false, Skill::WALL);

	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		this->m_disabledShopButtons.push_back(new Button());
		this->m_disabledShopButtons[i]->Init(this->m_shopButtons[i]->getPos(),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png",this->m_shopButtons[i]->getText(),0,0,1,12,100, 0, this->m_shopButtons[i]->getTextPos());
		this->m_disabledShopButtons[i]->setVisible(false);

		this->m_resourceImages.push_back(new Button());
		this->m_resourceImages[i]->Init(FLOAT2(this->m_shopButtons[i]->getPos().x + 0.12f, this->m_shopButtons[i]->getPos().y) ,FLOAT2(0.079166667f,0.140740741f), "menu_textures\\Button-Skill-Resource.png", "", 0,0,1,12,100,0,INT2(422,200));
		this->m_canAfford[i] = true;
	}

	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Tower.png", FLOAT2(-0.56f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Strength.png", FLOAT2(-0.28f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Agility.png", FLOAT2(-0.0f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Wits.png", FLOAT2(0.28f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));
	this->m_shopBackground.push_back(g_graphicsEngine->createSprite("menu_textures\\Upgradebar_Fortitude.png", FLOAT2(0.56f,0.3f),  FLOAT2(0.260416667f,1.451851852f),10));

	this->displayShop(false);
}
void HudMenu::Update(float _dt, const vector<Entity*>& _entities)
{
	if(m_Chat == false)
	{
			float max = -0.897916667f+0.001041667f+(0.102083333f*6)+0.025f;
			m_Delay += 1;

			if(m_DontChange == false)
			{
				if (m_SkillHud <= m_NumberOfSkills-1)
				{
					m_SkillHud += _dt*2;
					m_Delay = 0;
				}

				this->m_Images[1]->setPosition(FLOAT2(-1.0f +((0.102083333f*(float)m_SkillHud)), -0.814814815f));
				for(int i=0 ; i < m_SkillButtons.size(); i++)
				{
					this->m_SkillButtons[i]->setPosition(FLOAT2(-1.1782f +(0.102083333f*(((m_SkillHud+((m_NumberOfSkills-1)-i-(m_NumberOfSkills-5)))))),  -0.883333333f-0.004f));
				}

				if (m_SkillHud >= m_NumberOfSkills-1)
				{
					m_SkillHud = m_NumberOfSkills-1;
					m_DontChange = true;
				}
			}
			for(int i = 0; i < m_NumberOfSkills; i++)
			{
				this->m_SkillButtons[i]->Update();

				if(g_keyboard->getKeyState('0' + i + 1) == Keyboard::KEY_PRESSED || this->m_SkillButtons[i]->Clicked() > 0)
				{
					if(m_SkillButtons[i]->getSkillId() == Skill::CLOUD_OF_DARKNESS || m_SkillButtons[i]->getSkillId() == Skill::TELEPORT)
					{
						D3DXVECTOR3 pickDir;
						D3DXVECTOR3 pickOrig;
						g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());

						float k = (-pickOrig.y)/pickDir.y;
						D3DXVECTOR3 terrainPos = pickOrig + pickDir*k;
						this->m_network->sendMessage(NetworkUseActionPositionMessage(m_SkillButtons[i]->getSkillId(), FLOAT3(terrainPos.x, terrainPos.y, terrainPos.z)));
					}
					else if(m_SkillButtons[i]->getSkillId() == Skill::STUNNING_STRIKE || m_SkillButtons[i]->getSkillId() == Skill::DEMONIC_PRESENCE)
					{
						this->m_network->sendMessage(NetworkUseActionMessage(m_SkillButtons[i]->getSkillId()));
					}
					else if(m_SkillButtons[i]->getSkillId() == Skill::HEALING_TOUCH || m_SkillButtons[i]->getSkillId() == Skill::CHAIN_STRIKE)
					{
						D3DXVECTOR3 pickDir;
						D3DXVECTOR3 pickOrig;
						g_graphicsEngine->getCamera()->calcPick(pickDir, pickOrig, g_mouse->getPos());
						
						float dist;
						for(int entityIndex = 0; entityIndex < _entities.size(); entityIndex++)
						{
							if(_entities[entityIndex]->m_type == ServerEntity::HeroType && _entities[entityIndex]->m_model->intersects(dist, pickOrig, pickDir))
							{
								this->m_network->sendMessage(NetworkUseActionTargetMessage(m_SkillButtons[i]->getSkillId(), _entities[entityIndex]->m_id));
								entityIndex = _entities.size();
							}
						}
					}
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
			}
			else if(m_Buy == false)
			{				
				if (BuyAllSkillIsDown())
				{
					this->displayShop(true);
					m_Buy = true;
				}
			}

			if (g_keyboard->getKeyState(VK_RETURN) == Keyboard::KEY_PRESSED && m_Chat == false)
			{
				m_Chat = true;
			}
	}
	else
	{
		this->m_LabelInput->update(_dt);

		if(g_keyboard->getKeyState(VK_RETURN) == Keyboard::KEY_PRESSED)
		{
			string m_String = "";
			m_String.erase(m_String.begin());
			for(int i = m_Chattext.size()-1; i > 0;i--)
			{
				m_Chattext[i]->setText(m_Chattext[i-1]->getText());
			}
			m_String = this->m_LabelInput->getText();
			m_String.erase(m_String.end());
			this->m_Chattext[0]->setText(m_String);
			this->m_LabelInput->setText(""); 
			this->m_Chattext[3]->setText("");
			m_Chat = false;
		}
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
		m_NumberOfSkills = 2;
		m_SkillHud = 0;
		this->m_SkillButtons[5]->ChangeButton("30", false, 0);
		this->m_SkillButtons[4]->ChangeButton("30", false, 0);
		this->m_SkillButtons[3]->ChangeButton("30", false, 0);
		this->m_SkillButtons[2]->ChangeButton("30", false, 0);
		m_DontChange = false;
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
	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		delete this->m_shopButtons[i];
		delete this->m_resourceImages[i];
		delete this->m_disabledShopButtons[i];
	}

	delete this->m_LabelInput;
	for(int i=0 ; i < this->m_Chattext.size();i++)
	{
		delete this->m_Chattext[i];
		this->m_Chattext[i] = NULL;
	}
	delete this->m_ResourceLabel;
	this->m_ResourceLabel = NULL;
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
int HudMenu::ButtonClicked()
{
	return 0;
}
int HudMenu::SkilledBougth()
{
	return SkillID;
}
int  HudMenu::ReturnID()
{
	return 0;
}

void HudMenu::displayShop(bool _visible)
{
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
	for(int i = 0; i < this->m_shopButtons.size(); i++)
	{
		if(this->m_shopButtons[i]->GetID() == _skillId)
		{
			this->m_SkillButtons[this->m_NumberOfSkills]->ChangeButton(this->m_shopButtons[i]->getTextureName(), true, _skillId);
			this->m_NumberOfSkills++;
			this->m_DontChange = false;
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
		}
		else
		{
			this->m_canAfford[i] = true;
		}
	}
}