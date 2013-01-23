#include "MainMenu.h"

MainMenu::MainMenu() : Menu()
{
	FLOAT2 m_size, m_side; 
	m_size.x = 0;
	m_size.y = 0;
	m_side.x = 0;
	m_side.y = 0;
	m_size.x = g_graphicsEngine->getRealScreenSize().x;
	m_size.y = g_graphicsEngine->getRealScreenSize().y;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-MainBack.dds", FLOAT2(0,0),  FLOAT2(2,2),0));
	m_side.x = (122.0f/m_size.x)*2;
	m_side.y = (1920.0f/m_size.y)*2;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.dds", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.dds", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),4));
	m_side.x = (1920.0f/m_size.x)*2;
	m_side.y = (122.0f/m_size.y)*2;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.dds", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),5));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.dds", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),6));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-MainFront.dds", FLOAT2(0,0), FLOAT2(2,2),2));


	this->m_Buttons.resize(6);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.729166667f,  0.37037037f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-CreateGame.dds","",0,0,2);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.729166667f,	0.185185185f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-JoinGame.dds","",0,0,2);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(-0.729166667f,	0.0f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-Settings.dds","",0,0,2);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.729166667f,  -0.185185185f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-Lore.dds","",0,0,2);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(-0.729166667f,  -0.37037037f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-Credits.dds","",0,0,2);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(-0.729166667f,	-0.555555556f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-ExitGame.dds","",0,0,2);
}

void MainMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
}

MainMenu::~MainMenu()
{

}

bool MainMenu::createGameIsDown()
{
	if(this->m_Buttons[0]->Clicked() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool MainMenu::JoinGameIsDown()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool MainMenu::SettingsIsDown()
{
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool MainMenu::LoreIsDown()
{
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool MainMenu::CreditsIsDown()
{
	if(this->m_Buttons[4]->Clicked() == 1)
	{
		return true;
	}
	return false;
} 
bool MainMenu::ExitIsDown()
{
	if(this->m_Buttons[5]->Clicked() == 1)
	{
		return true;
	}
	return false;
}