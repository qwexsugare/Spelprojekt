#include "IntroMenu.h"


IntroMenu::IntroMenu(void)
{
	firstRun	=	true;
	secondRun	=	false;
	thirdRun	=	false;
	forthRun	=	false;
	m_time		=	0;
	m_counter	=	1;
	int graphics = g_configFile->getScreenSize().y;
	m_graphicstext = "1080";
	if (graphics == 1080)
	{
		m_graphicstext = "1080";
	}
	if (graphics == 900)
	{
		m_graphicstext = "900";
	}
	if (graphics == 720)
	{
		m_graphicstext = "720";
	}
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-INTRO-0.png", FLOAT2(0,  0),  FLOAT2(2, 2),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-INTRO-1.png", FLOAT2(0,  0),  FLOAT2(2, 2),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-INTRO-2.png", FLOAT2(0,  0),  FLOAT2(2, 2),0));
	this->m_Images[0]->setVisible(false);
	this->m_Images[1]->setVisible(false);
	this->m_Images[2]->setVisible(false);
}
void IntroMenu::Update(float _dt)
{
	m_time += _dt;
	if(firstRun == true && m_counter < m_time)
	{
		m_counter	=	m_time*2;
		firstRun	=	false;
		secondRun	=	true;
		thirdRun	=	false;
		this->m_Images[0]->setVisible(true);
		this->m_Images[1]->setVisible(false);
		this->m_Images[2]->setVisible(false);
	}
	if(secondRun == true && m_counter < m_time)
	{
		m_counter	= m_time*2;
		firstRun	=	false;
		secondRun	=	false;
		thirdRun	=	true;
		this->m_Images[0]->setVisible(false);
		this->m_Images[1]->setVisible(true);
		this->m_Images[2]->setVisible(false);
	}
	if(thirdRun == true && m_counter < m_time)
	{
		m_counter	=  m_time*2;
		firstRun	=	false;
		secondRun	=	false;
		thirdRun	=	false;
		forthRun	=	true;
		this->m_Images[0]->setVisible(false);
		this->m_Images[1]->setVisible(false);
		this->m_Images[2]->setVisible(true);
	}
}
bool IntroMenu::MainMenuGameIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
IntroMenu::~IntroMenu(void)
{

}
