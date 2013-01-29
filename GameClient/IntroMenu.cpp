#include "IntroMenu.h"


IntroMenu::IntroMenu(void)
{
	firstRun = true;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-INTRO-0.png", FLOAT2(0,  0),  FLOAT2(2, 2),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-INTRO-1.png", FLOAT2(0,  0),  FLOAT2(2, 2),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-INTRO-2.png", FLOAT2(0,  0),  FLOAT2(2, 2),0));
}
void IntroMenu::Update(float _dt)
{

	if(firstRun == true)
	{
		m_counter = _dt*10;
		firstRun = false;
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
