#include "HudMenu.h"


HudMenu::HudMenu(void)
{
	m_Time = 0;
	m_Delay = 0;
	m_DelayTime = 10;
	m_SkillHud = -1.0f;
	m_NumberOfSkills = 1;
	m_SkillValue = -4;
	int TmpPos = m_NumberOfSkills * 98;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Doctor.dds", FLOAT2(-0.9375f, -0.633333333f),  FLOAT2(0.083333333f,0.148148148f),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Main_Buttons_SkillBar.dds", FLOAT2(-1+(0.102083333f*(m_NumberOfSkills-1)),  -0.814814815f),  FLOAT2(1.03125f, 0.344444444f),1));

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Menu_Hud_Back.dds", FLOAT2(0,0),  FLOAT2(2,2),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Menu_Hud_Front.dds", FLOAT2(0,0),  FLOAT2(2,2),3));
	this->m_Sprite.push_back(g_graphicsEngine->createSpriteSheet("menu_textures\\HealthBar.dds",FLOAT2(-0.9375f,  -0.240740741f),FLOAT2(0.079166667f, 0.755555556f),INT2(10,1),2));

	this->m_Buttons.resize(6);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*1)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button_Skills.dds","",0,0,3);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*2)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button_Skills.dds","",0,0,3);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*3)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button_Skills.dds","",0,0,3);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*4)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button_Skills.dds","",0,0,3);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*5)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button_Skills.dds","",0,0,3);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(-0.897916667f+0.001041667f+(0.102083333f*6)+0.025f, -0.883333333f-0.004f),FLOAT2(0.079166667f,0.140740741f),"menu_textures\\Button_Skills.dds","",0,0,3);

	m_Sprite[0]->playAnimation(INT2(0,0),INT2(9,0),true,10);
}
void HudMenu::Update(float _dt)
{
	if(::GetAsyncKeyState('0'))
	{
		m_NumberOfSkills = 0;
		m_SkillValue =-5;
	}
	if(::GetAsyncKeyState('1'))
	{
		m_NumberOfSkills = 1;
		m_SkillValue = -4;
	}
	if(::GetAsyncKeyState('2'))
	{
		m_NumberOfSkills = 2;
		m_SkillValue = -3;
	}
	if(::GetAsyncKeyState('3'))
	{
		m_NumberOfSkills = 3;
		m_SkillValue = -2;
	}
	if(::GetAsyncKeyState('4'))
	{
		m_NumberOfSkills = 4;
		m_SkillValue = -1;
	}
	if(::GetAsyncKeyState('5'))
	{
		m_NumberOfSkills = 5;
		m_SkillValue = 0;
	}
	if(::GetAsyncKeyState('6'))
	{
		m_NumberOfSkills = 6;
		m_SkillValue = 1;
	}
	float max = -0.897916667f+0.001041667f+(0.102083333f*6)+0.025f;
	if (m_SkillHud <= m_NumberOfSkills-1)
	{
		m_SkillHud += _dt*2;
	}
	m_Delay = 0;
	this->m_Images[1]->setPosition(FLOAT2(-1.0f +((0.102083333f*(float)m_SkillHud)), -0.814814815f));
	for(int i=0 ; i < m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->setPosition(FLOAT2(-1.1782f +(0.102083333f*(((m_SkillHud+((m_NumberOfSkills-1)-i-m_SkillValue))))),  -0.883333333f-0.004f));
	}

	if (m_SkillHud >= m_NumberOfSkills-1)
	{
		m_SkillHud = m_NumberOfSkills-1;
	}
	
	for(int i =m_NumberOfSkills-1; i >=0; i--)
	{
		this->m_Buttons[i]->Update();
	}
}

HudMenu::~HudMenu(void)
{
}
