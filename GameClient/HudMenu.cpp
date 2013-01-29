#include "HudMenu.h"


HudMenu::HudMenu(void)
{
	m_Chat = false;
	m_Time = 0;
	m_Delay = 0;
	m_DelayTime = 10;
	m_SkillHud = -1.0f;
	m_NumberOfSkills = 2;
	m_SkillValue = -3;
	int TmpPos = m_NumberOfSkills * 98;
	m_DontChange = false;
	m_Buy = false;
	m_Buy_Tower = false;
	m_Buy_Strength = false;
	m_Buy_Agility = false;
	m_Buy_Wits = false;
	m_Buy_Fortitude = false;
	m_Menu= false;
	m_Locked = true;
	m_Init_All = false;
	m_Init_Tower = false;
	m_Init_Strength = false;
    m_Init_Agility = false;
	m_Init_Wits = false;
	m_Init_Fortitude = false;
	m_DontChange = false;
	m_OncePerBuy = false;
	m_Resources = 200000;
	m_First = 0;
	m_First_Tower = 0;
	m_First_Strength = 0;
	m_First_Agility = 0;
	m_First_Wits = 0;
	m_First_Fortitude = 0;
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
	
	this->m_Buttons.resize(7);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.95f,-0.50f),FLOAT2(0.033333333f,0.059259259f),"menu_textures\\Button-Unlock.png","",0,0,1,11,300);
	
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.94f,0.94f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Tower.png","",0,0,1,11,100);	
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(-0.94f,0.82f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Strength.png","",0,0,1,11,100);	
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.94f,0.70f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Agility.png","",0,0,1,11,100);	
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(-0.94f,0.58f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Wits.png","",0,0,1,11,100);	
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(-0.94f,0.46f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_Fortitude.png","",0,0,1,11,100);	
	this->m_Buttons[6] = new Button();
	this->m_Buttons[6]->Init(FLOAT2(-0.94f,0.34f),FLOAT2(0.061458333f,0.111111111f),"menu_textures\\Upgradebar_Buy_All.png","",0,0,1,11,100);	
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
	this->m_SkillButtons[0]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*1)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","1",".png",0,0,1,4,100,false);
	this->m_SkillButtons[0]->ChangAbleBind(false);

	this->m_SkillButtons[1] = new Skill_Buttons();
	this->m_SkillButtons[1]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*2)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","2",".png",0,0,1,4,100,true);
	this->m_SkillButtons[2] = new Skill_Buttons();
	this->m_SkillButtons[2]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*3)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",0,0,1,4,100,false);
	this->m_SkillButtons[3] = new Skill_Buttons();
	this->m_SkillButtons[3]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*4)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",0,0,1,4,100,true);
	this->m_SkillButtons[4] = new Skill_Buttons();
	this->m_SkillButtons[4]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*5)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",0,0,1,4,100,false);
	this->m_SkillButtons[5] = new Skill_Buttons();
	this->m_SkillButtons[5]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*6)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-","30",".png",0,0,1,4,100,false);
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
}
void HudMenu::Update(float _dt)
{
	if(m_Chat == false)
	{
			float max = -0.897916667f+0.001041667f+(0.102083333f*6)+0.025f;
			m_Delay += 1;

			if (m_DontChange == false)
			{
				if (m_SkillHud <= m_NumberOfSkills-1)
				{
					m_SkillHud += _dt*2;
					m_Delay = 0;
				}

				this->m_Images[1]->setPosition(FLOAT2(-1.0f +((0.102083333f*(float)m_SkillHud)), -0.814814815f));
				for(int i=0 ; i < m_SkillButtons.size(); i++)
				{
					this->m_SkillButtons[i]->setPosition(FLOAT2(-1.1782f +(0.102083333f*(((m_SkillHud+((m_NumberOfSkills-1)-i-m_SkillValue))))),  -0.883333333f-0.004f));
				}

				if (m_SkillHud >= m_NumberOfSkills-1)
				{
					m_SkillHud = m_NumberOfSkills-1;
					m_DontChange = true;
				}
			}
			for(int i =m_NumberOfSkills-1; i >=0; i--)
			{
				this->m_SkillButtons[i]->Update();
			}

			for(int i = 0; i < m_Buttons.size(); i++)
			{
				this->m_Buttons[i]->Update();
			}
			if (m_Buy == false)
			{
				if (BuyTowerSkillIsDown())
				{
					m_Delay = 0;
					m_Buy_Tower = false;
					m_Buy = true;
				}
				if (BuyStrengthSkillIsDown())
				{
					m_Delay = 0;
					m_Buy_Strength = false;
					m_Buy = true;
				}
				if (BuyAgilitySkillIsDown())
				{
					m_Delay = 0;
					m_Buy_Agility = false;
					m_Buy = true;
				}
				if (BuyWitsSkillIsDown())
				{
					m_Delay = 0;
					m_Buy_Wits = false;
					m_Buy = true;
				}
				if (BuyFortitudeSkillIsDown())
				{
					m_Delay = 0;
					m_Buy_Fortitude = false;
					m_Buy = true;
				}
				if (BuyAllSkillIsDown())
				{
					m_Delay = 0;
					m_Init_Tower = 1;
					m_Buy_Tower = false;
					m_Init_Strength = 1;
					m_Buy_Strength = false;
					m_Init_Agility = 1;
					m_Buy_Agility = false;
					m_Init_Wits = 1;
					m_Buy_Wits = false;
					m_Init_Fortitude = 1;
					m_Buy_Fortitude = false;
					m_Buy = true;
				}
			}
			else if(m_Buy == true)
			{
				if (BuyTowerSkillIsDown())
				{
					m_Delay = 0;
					m_Init_Tower = 1;
					m_Buy_Tower = true;
					m_Buy = false;
				}
				if (BuyStrengthSkillIsDown())
				{
					m_Delay = 0;
					m_Init_Strength = 1;
					m_Buy_Strength = true;
					m_Buy = false;
				}
				if (BuyAgilitySkillIsDown())
				{
					m_Delay = 0;
					m_Init_Agility = 1;
					m_Buy_Agility = true;
					m_Buy = false;
				}
				if (BuyWitsSkillIsDown())
				{
					m_Delay = 0;
					m_Init_Wits = 1;
					m_Buy_Wits = true;
					m_Buy = false;
				}
				if (BuyFortitudeSkillIsDown())
				{
					m_Delay = 0;
					m_Init_Fortitude = 1;
					m_Buy_Fortitude = true;
					m_Buy = false;
				}
				if (BuyAllSkillIsDown())
				{
					m_Delay = 0;
					m_Init_Tower = 1;
					m_Buy_Tower = true;
					m_Init_Strength = 1;
					m_Buy_Strength = true;
					m_Init_Agility = 1;
					m_Buy_Agility = true;
					m_Init_Wits = 1;
					m_Buy_Wits = true;
					m_Init_Fortitude = 1;
					m_Buy_Fortitude = true;
					m_Buy = false;
				}
			}
			BuyHud();
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
		m_SkillValue = -3;
		m_SkillHud = 0;
		this->m_SkillButtons[5]->ChangeButton("30", false);
		this->m_SkillButtons[4]->ChangeButton("30", false);
		this->m_SkillButtons[3]->ChangeButton("30", false);
		this->m_SkillButtons[2]->ChangeButton("30", false);
		m_DontChange = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool HudMenu::BuyTowerSkillIsDown()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	else
	{
		return 0;
	}
}
bool HudMenu::BuyStrengthSkillIsDown()
{
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool HudMenu::BuyAgilitySkillIsDown()
{
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool HudMenu::BuyWitsSkillIsDown()
{
	if(this->m_Buttons[4]->Clicked() == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool HudMenu::BuyFortitudeSkillIsDown()
{
	if(this->m_Buttons[5]->Clicked() == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool HudMenu::BuyAllSkillIsDown()
{
	if(this->m_Buttons[6]->Clicked() == 1)
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
	if(this->m_Buttons[6]->Clicked() > 0)
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
	for(int i = 0; i < BuyButtonTower.size();i++)
	{
		delete this->BuyButtonTower[i];
	}
	this->BuyButtonTower.clear();

	for(int i = 0; i < BuyButtonStrength.size();i++)
	{
		delete this->BuyButtonStrength[i];
	}
	this->BuyButtonStrength.clear();

	for(int i = 0; i < BuyButtonAgility.size();i++)
	{
		delete this->BuyButtonAgility[i];
	}
	this->BuyButtonAgility.clear();

	for(int i = 0; i < BuyButtonWits.size();i++)
	{
		delete this->BuyButtonWits[i];
	}
	this->BuyButtonWits.clear();

	for(int i = 0; i < BuyButtonFortitude.size();i++)
	{
		delete this->BuyButtonFortitude[i];
	}
	this->BuyButtonFortitude.clear();

	for(int i = 0; i < BuyAttributes.size();i++)
	{
		delete this->BuyAttributes[i];
	}
	this->BuyAttributes.clear();
	delete this->m_LabelInput;
	for(int i=0 ; i < this->m_Chattext.size();i++)
	{
		delete this->m_Chattext[i];
		this->m_Chattext[i] = NULL;
	}
	delete this->m_ResourceLabel;
	this->m_ResourceLabel = NULL;
}
void HudMenu::BuyHud()
{
	m_LoseMoney = 0;
	UpdateShop();
	if (m_LoseMoney == 1)
	{
		string m_TempString = this->m_ResourceLabel->IntToString(m_Resources);
		this->m_ResourceLabel->setText(m_TempString);
		if(m_Buy_Tower == true && BuyButtonTower.size() > 0)
		{
			m_Init_Tower = 1;
			for(int i = 0; i < this->BuyButtonTower.size();i++)
			{
				this->BuyButtonTower[i]->RemoveSprite();
				delete this->BuyButtonTower[i];
			}
			this->BuyButtonTower.clear();
		}
		if(m_Buy_Strength == true && BuyButtonStrength.size() > 0)
		{
			m_Init_Strength = 1;
			for(int i = 0; i < this->BuyButtonStrength.size();i++)
			{
				this->BuyButtonStrength[i]->RemoveSprite();
				delete this->BuyButtonStrength[i];
			}
			this->BuyButtonStrength.clear();
		}
		if(m_Buy_Agility == true && BuyButtonAgility.size() > 0)
		{
			m_Init_Agility = 1;
			for(int i = 0; i < this->BuyButtonAgility.size();i++)
			{
				this->BuyButtonAgility[i]->RemoveSprite();
				delete this->BuyButtonAgility[i];
			}
			this->BuyButtonAgility.clear();
		}
		if(m_Buy_Wits == true && BuyButtonWits.size() > 0)
		{
			m_Init_Wits = 1;
			for(int i = 0; i < this->BuyButtonWits.size();i++)
			{
				this->BuyButtonWits[i]->RemoveSprite();
				delete this->BuyButtonWits[i];
			}
			this->BuyButtonWits.clear();
		}
		if(m_Buy_Fortitude == true && BuyButtonFortitude.size() > 0)
		{
			m_Init_Fortitude = 1;
			for(int i = 0; i < this->BuyButtonFortitude.size();i++)
			{
				this->BuyButtonFortitude[i]->RemoveSprite();
				delete this->BuyButtonFortitude[i];
			}
			this->BuyButtonFortitude.clear();
		}
		m_LoseMoney = 0;
		UpdateShop();
	}
}
void  HudMenu::UpdateShop()
{
	if(m_Buy_Tower == true)
	{
		if (m_Init_Tower == 1 && BuyButtonTower.size() == 0)
		{
			this->m_Images[5]->setPosition(FLOAT2(-0.56f,0.3f));
			this->BuyButtonTower.resize(4);
			if(m_Resources >= 0)
			{
				this->BuyButtonTower[0] = new Button();
				this->BuyButtonTower[0]->Init(FLOAT2(-0.62f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-0.png","0",0,0,1,12,100,0,INT2(422,80));
				this->BuyButtonTower[0]->SetID(0);
			}
			else
			{
				this->BuyButtonTower[0] = new Button();
				this->BuyButtonTower[0]->Init(FLOAT2(-0.62f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","0",0,0,1,12,100,0,INT2(422,80));
				this->BuyButtonTower[0]->SetID(30);
			}
			if(m_Resources >= 3500)
			{
				this->BuyButtonTower[1] = new Button();
				this->BuyButtonTower[1]->Init(FLOAT2(-0.62f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-12.png","3500",0,0,1,12,100,3500,INT2(422,200));
				this->BuyButtonTower[1]->SetID(12);
			}
			else
			{
				this->BuyButtonTower[1] = new Button();
				this->BuyButtonTower[1]->Init(FLOAT2(-0.62f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","3500",0,0,1,12,100,0,INT2(422,200));
				this->BuyButtonTower[1]->SetID(30);
			}
			this->BuyButtonTower[2] = new Button();
			this->BuyButtonTower[2]->Init(FLOAT2(-0.50f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,80));

			this->BuyButtonTower[3] = new Button();
			this->BuyButtonTower[3]->Init(FLOAT2(-0.50f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));

			m_Init_Tower = 0;
		}
		for(int i = 0; i < 2; i++)
		{
			this->BuyButtonTower[i]->Update();
			if(this->BuyButtonTower[i]->Clicked() == true)
			{
				if(i !=0)
				{
					if(m_NumberOfSkills <  6)
					{
						string type;
						type = this->BuyButtonTower[i]->GetID();
						if (type != "30")
						{
							m_NumberOfSkills++;
							m_SkillValue += 1;
							m_DontChange = false;
							this->m_SkillButtons[m_NumberOfSkills-1]->ChangeButton(type, true);

							m_Resources = this->BuyButtonTower[i]->LoseAmountOfResources(m_Resources);
							m_LoseMoney = 1;
							if (m_SkillValue >= 1)
							{
								m_SkillValue = 1;
							}
						}
					}
					if(m_NumberOfSkills >= 6)
					{
						m_DontChange = false;
						m_NumberOfSkills = 6;
						m_SkillValue = 1;
					}
				}
				else
				{
				}
			}
		}
	}
	else if(m_Buy_Tower == false && BuyButtonTower.size() > 0)
	{
		this->m_Images[5]->setPosition(FLOAT2(-0.56f,1.8f));
		for(int i = 0; i < this->BuyButtonTower.size();i++)
		{
			this->BuyButtonTower[i]->RemoveSprite();
			delete this->BuyButtonTower[i];
		}
		this->BuyButtonTower.clear();
	}
	if( m_Buy_Strength == true)
	{
		if (m_Init_Strength == 1 && BuyButtonStrength.size() == 0)
		{
			this->m_Images[6]->setPosition(FLOAT2(-0.28f,0.3f));
			this->BuyButtonStrength.resize(10);
			if(m_Resources >= 0)
			{
				this->BuyButtonStrength[0] = new Button();
				this->BuyButtonStrength[0]->Init(FLOAT2(-0.34f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-1.png","0",0,0,1,12,100,0,INT2(692,80));
				this->BuyButtonStrength[0]->SetID(1);
			}
			else
			{
				this->BuyButtonStrength[0] = new Button();
				this->BuyButtonStrength[0]->Init(FLOAT2(-0.34f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","0",0,0,1,12,100,0,INT2(692,80));
				this->BuyButtonStrength[0]->SetID(30);
			}
			if(m_Resources >= 900)
			{
				this->BuyButtonStrength[1] = new Button();
				this->BuyButtonStrength[1]->Init(FLOAT2(-0.34f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-7.png","900",0,0,1,12,100,900,INT2(692,200));
				this->BuyButtonStrength[1]->SetID(7);
			}
			else
			{
				this->BuyButtonStrength[1] = new Button();
				this->BuyButtonStrength[1]->Init(FLOAT2(-0.34f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","900",0,0,1,12,100,0,INT2(692,200));
				this->BuyButtonStrength[1]->SetID(30);
			}
			if(m_Resources >= 2200)
			{
				this->BuyButtonStrength[2] = new Button();
				this->BuyButtonStrength[2]->Init(FLOAT2(-0.34f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-9.png","2200",0,0,1,12,100,2200,INT2(692,324));
				this->BuyButtonStrength[2]->SetID(9);
			}
			else
			{
				this->BuyButtonStrength[2] = new Button();
				this->BuyButtonStrength[2]->Init(FLOAT2(-0.34f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","2200",0,0,1,12,100,0,INT2(692,324));
				this->BuyButtonStrength[2]->SetID(30);
			}
			if(m_Resources >= 2400)
			{
				this->BuyButtonStrength[3] = new Button();
				this->BuyButtonStrength[3]->Init(FLOAT2(-0.34f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-13.png","2400",0,0,1,12,100,2400,INT2(692,440));
				this->BuyButtonStrength[3]->SetID(13);
			}
			else
			{
				this->BuyButtonStrength[3] = new Button();
				this->BuyButtonStrength[3]->Init(FLOAT2(-0.34f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","2400",0,0,1,12,100,0,INT2(692,440));
				this->BuyButtonStrength[3]->SetID(30);
			}
			if(m_Resources >= 4000)
			{
				this->BuyButtonStrength[4] = new Button();
				this->BuyButtonStrength[4]->Init(FLOAT2(-0.34f, 0.0f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-16.png","4000",0,0,1,12,100,4000, INT2(692,560));
				this->BuyButtonStrength[4]->SetID(16);
			}
			else
			{
				this->BuyButtonStrength[4] = new Button();
				this->BuyButtonStrength[4]->Init(FLOAT2(-0.34f, 0.0f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","4000",0,0,1,12,100,0,INT2(692,560));
				this->BuyButtonStrength[4]->SetID(30);
			}
			this->BuyButtonStrength[5] = new Button();
			this->BuyButtonStrength[5]->Init(FLOAT2(-0.22f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,80));

			this->BuyButtonStrength[6] = new Button();
			this->BuyButtonStrength[6]->Init(FLOAT2(-0.22f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));

			this->BuyButtonStrength[7] = new Button();
			this->BuyButtonStrength[7]->Init(FLOAT2(-0.22f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,80));

			this->BuyButtonStrength[8] = new Button();
			this->BuyButtonStrength[8]->Init(FLOAT2(-0.22f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));

			this->BuyButtonStrength[9] = new Button();
			this->BuyButtonStrength[9]->Init(FLOAT2(-0.22f, 0.0f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));
			m_Init_Strength = 0;
		}
		for(int i = 0; i < 5; i++)
		{
			this->BuyButtonStrength[i]->Update();
			if(this->BuyButtonStrength[i]->Clicked() == true)
			{
				if(i !=0)
				{
					if(m_NumberOfSkills < 6)
					{
						string type;
						type = this->BuyButtonStrength[i]->GetID();
						if (type != "30")
						{
							m_NumberOfSkills++;
							m_SkillValue += 1;
							m_DontChange = false;
							this->m_SkillButtons[m_NumberOfSkills-1]->ChangeButton(type, true);

							m_Resources = this->BuyButtonStrength[i]->LoseAmountOfResources(m_Resources);
							m_LoseMoney = 1;
							if (m_SkillValue >= 1)
							{
								m_SkillValue = 1;
							}
						}
					}
					if(m_NumberOfSkills >= 6)
					{
						m_DontChange = false;
						m_NumberOfSkills = 6;
						m_SkillValue = 1;
					}
				}
				else
				{

				}
			}
		}
	}
	else if( m_Buy_Strength == false && BuyButtonStrength.size() > 0)
	{
		this->m_Images[6]->setPosition(FLOAT2(-0.28f,1.8f));
		for(int i = 0; i < this->BuyButtonStrength.size();i++)
		{
			this->BuyButtonStrength[i]->RemoveSprite();
			delete this->BuyButtonStrength[i];
		}
		this->BuyButtonStrength.clear();
	}
	if (m_Buy_Agility == true)
	{	
		if (m_Init_Agility == 1 && BuyButtonAgility.size() == 0)
		{
			this->m_Images[7]->setPosition(FLOAT2(-0.0f,0.3f));
			this->BuyButtonAgility.resize(8);
			if(m_Resources >= 0)
			{
				this->BuyButtonAgility[0] = new Button();
				this->BuyButtonAgility[0]->Init(FLOAT2(-0.06f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-2.png","0",0,0,1,12,100,0,INT2(1920/2,80));
				this->BuyButtonAgility[0]->SetID(2);
			}
			else
			{
				this->BuyButtonAgility[0] = new Button();
				this->BuyButtonAgility[0]->Init(FLOAT2(-0.06f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","0",0,0,1,12,100,0,INT2(1920/2,80));
				this->BuyButtonAgility[0]->SetID(30);
			}
			if(m_Resources >= 500)
			{
				this->BuyButtonAgility[1] = new Button();
				this->BuyButtonAgility[1]->Init(FLOAT2(-0.06f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-18.png","500",0,0,1,12,100,500,INT2(1920/2,200));
				this->BuyButtonAgility[1]->SetID(18);
			}
			else
			{
				this->BuyButtonAgility[1] = new Button();
				this->BuyButtonAgility[1]->Init(FLOAT2(-0.06f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","500",0,0,1,12,100,0,INT2(1920/2,200));
				this->BuyButtonAgility[1]->SetID(30);
			}
			if(m_Resources >= 1100)
			{
				this->BuyButtonAgility[2] = new Button();
				this->BuyButtonAgility[2]->Init(FLOAT2(-0.06f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-5.png","1100",0,0,1,12,100,1100,INT2(1920/2,324));
				this->BuyButtonAgility[2]->SetID(5);
			}
			else
			{
				this->BuyButtonAgility[2] = new Button();
				this->BuyButtonAgility[2]->Init(FLOAT2(-0.06f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","1100",0,0,1,12,100,0,INT2(1920/2,324));
				this->BuyButtonAgility[2]->SetID(30);
			}
			if(m_Resources >= 2000)
			{
				this->BuyButtonAgility[3] = new Button();
				this->BuyButtonAgility[3]->Init(FLOAT2(-0.06f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-11.png","2000",0,0,1,12,100,2000,INT2(1920/2,440));
				this->BuyButtonAgility[3]->SetID(11);
			}
			else
			{
				this->BuyButtonAgility[3] = new Button();
				this->BuyButtonAgility[3]->Init(FLOAT2(-0.06f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","2000",0,0,1,12,100,0,INT2(1920/2,440));
				this->BuyButtonAgility[3]->SetID(30);
			}
			this->BuyButtonAgility[4] = new Button();
			this->BuyButtonAgility[4]->Init(FLOAT2(0.06f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,80));

			this->BuyButtonAgility[5] = new Button();
			this->BuyButtonAgility[5]->Init(FLOAT2(0.06f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));

			this->BuyButtonAgility[6] = new Button();
			this->BuyButtonAgility[6]->Init(FLOAT2(0.06f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,80));

			this->BuyButtonAgility[7] = new Button();
			this->BuyButtonAgility[7]->Init(FLOAT2(0.06f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));

			m_Init_Agility = 0;
		}
		for(int i = 0; i < 4; i++)
		{
			this->BuyButtonAgility[i]->Update();
			if(this->BuyButtonAgility[i]->Clicked() == true)
			{
				if(i !=0)
				{
					if(m_NumberOfSkills  < 6)
					{
						string type;
						type = this->BuyButtonAgility[i]->GetID();
						if (type != "30")
						{
							m_NumberOfSkills++;
							m_SkillValue += 1;
							m_DontChange = false;
							this->m_SkillButtons[m_NumberOfSkills-1]->ChangeButton(type, true);
	
							m_Resources = this->BuyButtonAgility[i]->LoseAmountOfResources(m_Resources);
							m_LoseMoney = 1;
							if (m_SkillValue >= 1)
							{
								m_SkillValue = 1;
							}
						}
					}
					if(m_NumberOfSkills  >= 6)
					{
						m_DontChange = false;
						m_NumberOfSkills = 6;
						m_SkillValue = 1;
					}
				}
				else
				{
				}
			}
		}
	}
	else if (m_Buy_Agility == false && BuyButtonAgility.size() > 0)
	{	
		this->m_Images[7]->setPosition(FLOAT2(0.0f,1.8f));
		for(int i = 0; i < this->BuyButtonAgility.size();i++)
		{
			this->BuyButtonAgility[i]->RemoveSprite();
			delete this->BuyButtonAgility[i];
		}
		this->BuyButtonAgility.clear();
	}
	if (m_Buy_Wits == true)
	{
		if (m_Init_Wits == 1 &&  BuyButtonWits.size() == 0)
		{
			this->m_Images[8]->setPosition(FLOAT2(0.28f,0.3f));
			this->BuyButtonWits.resize(8);
			if(m_Resources >= 0)
			{
				this->BuyButtonWits[0] = new Button();
				this->BuyButtonWits[0]->Init(FLOAT2(0.22f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-3.png","0",0,0,1,12,100,0,INT2(1228,80));
				this->BuyButtonWits[0]->SetID(3);
			}
			else
			{
				this->BuyButtonWits[0] = new Button();
				this->BuyButtonWits[0]->Init(FLOAT2(0.22f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","0",0,0,1,12,100,0,INT2(1228,80));
				this->BuyButtonWits[0]->SetID(30);
			}
			if(m_Resources >= 1700)
			{
				this->BuyButtonWits[1] = new Button();
				this->BuyButtonWits[1]->Init(FLOAT2(0.22f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-10.png","1700",0,0,1,12,100,1700,INT2(1228,200));
				this->BuyButtonWits[1]->SetID(10);
			}
			else
			{
				this->BuyButtonWits[1] = new Button();
				this->BuyButtonWits[1]->Init(FLOAT2(0.22f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","1700",0,0,1,12,100,0,INT2(1228,200));
				this->BuyButtonWits[1]->SetID(30);
			}
			if(m_Resources >= 2500)
			{
				this->BuyButtonWits[2] = new Button();
				this->BuyButtonWits[2]->Init(FLOAT2(0.22f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-14.png","2500",0,0,1,12,100,2500,INT2(1228,324));
				this->BuyButtonWits[2]->SetID(14);
			}
			else
			{
				this->BuyButtonWits[2] = new Button();
				this->BuyButtonWits[2]->Init(FLOAT2(0.22f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","2500",0,0,1,12,100,0,INT2(1228,324));
				this->BuyButtonWits[2]->SetID(30);
			}
			if(m_Resources >= 3500)
			{
				this->BuyButtonWits[3] = new Button();
				this->BuyButtonWits[3]->Init(FLOAT2(0.22f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-17.png","3500",0,0,1,12,100,3500,INT2(1228,440));
				this->BuyButtonWits[3]->SetID(17);
			}
			else
			{
				this->BuyButtonWits[3] = new Button();
				this->BuyButtonWits[3]->Init(FLOAT2(0.22f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","3500",0,0,1,12,100,0,INT2(1228,440));
				this->BuyButtonWits[3]->SetID(30);
			}

			this->BuyButtonWits[4] = new Button();
			this->BuyButtonWits[4]->Init(FLOAT2(0.34f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,80));

			this->BuyButtonWits[5] = new Button();
			this->BuyButtonWits[5]->Init(FLOAT2(0.34f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));

			this->BuyButtonWits[6] = new Button();
			this->BuyButtonWits[6]->Init(FLOAT2(0.34f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,80));

			this->BuyButtonWits[7] = new Button();
			this->BuyButtonWits[7]->Init(FLOAT2(0.34f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));
			m_Init_Wits = 0;
		}
		for(int i = 0; i < 4; i++)
		{
			this->BuyButtonWits[i]->Update();
			if(this->BuyButtonWits[i]->Clicked() == true)
			{
				if(i !=0)
				{
					if(m_NumberOfSkills < 6)
					{
						string type;
						type = this->BuyButtonWits[i]->GetID();
						if (type != "30")
						{
							m_NumberOfSkills++;
							m_SkillValue += 1;
							m_DontChange = false;
							this->m_SkillButtons[m_NumberOfSkills-1]->ChangeButton(type, true);

							m_Resources = this->BuyButtonWits[i]->LoseAmountOfResources(m_Resources);
							m_LoseMoney = 1;
						}
						if (m_SkillValue >= 1)
						{
							m_SkillValue = 1;
						}
					}
					if(m_NumberOfSkills >= 6)
					{
						m_DontChange = false;
						m_NumberOfSkills = 6;
						m_SkillValue = 1;
					}
				}
								else
				{
				}
			}
		}
	}
	else if (m_Buy_Wits == false && BuyButtonWits.size() > 0)
	{
		this->m_Images[8]->setPosition(FLOAT2(0.28f,1.8f));
		for(int i = 0; i < this->BuyButtonWits.size();i++)
		{
			this->BuyButtonWits[i]->RemoveSprite();
			delete this->BuyButtonWits[i];
		}
		this->BuyButtonWits.clear();
	}
	if (m_Buy_Fortitude == true)
	{
		if (m_Init_Fortitude == 1 && BuyButtonFortitude.size() == 0)
		{
			this->m_Images[9]->setPosition(FLOAT2(0.56f,0.3f));
			this->BuyButtonFortitude.resize(8);
			if(m_Resources >= 0)
			{
				this->BuyButtonFortitude[0] = new Button();
				this->BuyButtonFortitude[0]->Init(FLOAT2(0.49f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-4.png","0",0,0,1,12,100,0,INT2(1498,80));
				this->BuyButtonFortitude[0]->SetID(4);
			}
			else
			{
				this->BuyButtonFortitude[0] = new Button();
				this->BuyButtonFortitude[0]->Init(FLOAT2(0.49f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","0",0,0,1,12,100,0,INT2(1498,80));
				this->BuyButtonFortitude[0]->SetID(30);
			}
			if(m_Resources >= 700)
			{
				this->BuyButtonFortitude[1] = new Button();
				this->BuyButtonFortitude[1]->Init(FLOAT2(0.49f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-6.png","700",0,0,1,12,100,700,INT2(1498,200));
				this->BuyButtonFortitude[1]->SetID(6);
			}
			else
			{
				this->BuyButtonFortitude[1] = new Button();
				this->BuyButtonFortitude[1]->Init(FLOAT2(0.49f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","700",0,0,1,12,100,0,INT2(1498,200));
				this->BuyButtonFortitude[1]->SetID(30);
			}
			if(m_Resources >= 900)
			{
				this->BuyButtonFortitude[2] = new Button();
				this->BuyButtonFortitude[2]->Init(FLOAT2(0.49f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-8.png","900",0,0,1,12,100,900,INT2(1498,324));
				this->BuyButtonFortitude[2]->SetID(8);
			}
			else
			{
				this->BuyButtonFortitude[2] = new Button();
				this->BuyButtonFortitude[2]->Init(FLOAT2(0.49f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","900",0,0,1,12,100,0,INT2(1498,324));
				this->BuyButtonFortitude[2]->SetID(30);
			}
			if(m_Resources >= 3000)
			{
				this->BuyButtonFortitude[3] = new Button();
				this->BuyButtonFortitude[3]->Init(FLOAT2(0.49f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-20.png","3000",0,0,1,12,100,3000,INT2(1498,440));
				this->BuyButtonFortitude[3]->SetID(20);
			}
			else
			{
				this->BuyButtonFortitude[3] = new Button();
				this->BuyButtonFortitude[3]->Init(FLOAT2(0.49f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-30.png","3000",0,0,1,12,100,0,INT2(1498,440));
				this->BuyButtonFortitude[3]->SetID(30);
			}
			this->BuyButtonFortitude[4] = new Button();
			this->BuyButtonFortitude[4]->Init(FLOAT2(0.61f, 0.8f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,80));

			this->BuyButtonFortitude[5] = new Button();
			this->BuyButtonFortitude[5]->Init(FLOAT2(0.61f, 0.6f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));

			this->BuyButtonFortitude[6] = new Button();
			this->BuyButtonFortitude[6]->Init(FLOAT2(0.61f, 0.4f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,80));

			this->BuyButtonFortitude[7] = new Button();
			this->BuyButtonFortitude[7]->Init(FLOAT2(0.61f, 0.2f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button-Skill-Resource.png","",0,0,1,12,100,0,INT2(422,200));
			m_Init_Fortitude = 0;
		}
		for(int i = 0; i < 4; i++)
		{
			this->BuyButtonFortitude[i]->Update();
			if(this->BuyButtonFortitude[i]->Clicked() == true)
			{
				if(i !=0)
				{
					if(m_NumberOfSkills < 6)
					{
						string type;
						type = this->BuyButtonFortitude[i]->GetID();
						if (type != "30")
						{
							m_NumberOfSkills++;
							m_SkillValue += 1;
							m_DontChange = false;
							this->m_SkillButtons[m_NumberOfSkills-1]->ChangeButton(type, true);

							m_Resources = this->BuyButtonFortitude[i]->LoseAmountOfResources(m_Resources);
							m_LoseMoney = 1;
							if (m_SkillValue >= 1)
							{
								m_SkillValue = 1;
							}
						}
					}
					if(m_NumberOfSkills >= 6)
					{
						m_DontChange = false;
						m_NumberOfSkills = 6;
						m_SkillValue = 1;
					}
				}
				else
				{
				}
			}
		}
	}
	else if (m_Buy_Fortitude == false && BuyButtonFortitude.size() > 0)
	{
		this->m_Images[9]->setPosition(FLOAT2(0.56f,1.8f));
		for(int i = 0; i < this->BuyButtonFortitude.size();i++)
		{
			this->BuyButtonFortitude[i]->RemoveSprite();
			delete this->BuyButtonFortitude[i];
		}
		this->BuyButtonFortitude.clear();
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
