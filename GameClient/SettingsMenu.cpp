#include "SettingsMenu.h"


SettingsMenu::SettingsMenu(void)
{
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-Settings.png", FLOAT2(0,0),  FLOAT2(2,2),0));
	this->m_Buttons.resize(8);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.15625f, -0.933333333f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,2);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(0.15625f, -0.933333333f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-SettingsMenu-SaveChanges.png","",0,0,2);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(-0.708333333f, 0.262962963f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,0);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.708333333f, 0.138888889f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,0);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(-0.708333333f, 0.018518519f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,0);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(-0.177083333f, 0.262962963f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,0);
	this->m_Buttons[6] = new Button();
	this->m_Buttons[6]->Init(FLOAT2(-0.177083333f, 0.138888889f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,0);
	this->m_Buttons[7] = new Button();
	this->m_Buttons[7]->Init(FLOAT2(-0.177083333f,  1),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,385,2,0);
}
void SettingsMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
}
bool SettingsMenu::MainMenuGameIsDone()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool SettingsMenu::SaveSettingsIsDone()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}


SettingsMenu::~SettingsMenu(void)
{
}
