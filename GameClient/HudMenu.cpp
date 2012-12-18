#include "HudMenu.h"
extern Menu::WorldState g_MState;

HudMenu::HudMenu(): Menu()
{
}

void HudMenu::Init()
{
	m_Time = 0;
	m_Delay = 0;
	m_DelayTime = 70;
	this->m_Images.push_back(g_graphicsEngine->createSprite("Doctor.png", INT2(1920*0.5f-900,  1080*0.5-340),  INT2(80, 80),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("Menu_Hud_Front.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("Menu_Hud_Front.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),3));
	this->m_Buttons.resize(1);
	this->m_Sprite.push_back(g_graphicsEngine->createSpriteSheet("HealthBar.png",INT2(1920*0.5f-900,  1080*0.5-130),INT2(76, 408),INT2(10,1),2));
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(INT2(1920*0.5f-700,  1080*0.5+200),INT2(262,77),"Button-MainMenu-CreateGame.png","",0,0,1);

}
void HudMenu::Update()
{
	m_Delay++;
	if(m_Delay > m_DelayTime)
	{
		m_Time++;
		m_Delay = 0;
		if (m_Time > 9)
			m_Time = 0;
	}
	m_Sprite[0]->setCurrentFrame(INT2(m_Time,0));
}
HudMenu::~HudMenu()
{

}
void HudMenu::ChangeStates()
{
}
