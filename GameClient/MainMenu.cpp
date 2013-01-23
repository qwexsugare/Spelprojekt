#include "MainMenu.h"

MainMenu::MainMenu() : Menu()
{
	FLOAT2 m_size, m_side; 
	m_size.x = 0;
	m_size.y = 0;
	m_side.x = 0;
	m_side.y = 0;
	//m_size.x = g_graphicsEngine->getRealScreenSize().x;
	//m_size.y = g_graphicsEngine->getRealScreenSize().y;
	m_size.x = 1920;
	m_size.y = 1080;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-MainBack.png", FLOAT2(0,0),  FLOAT2(2,2),0));
	m_side.x = (122.0f/m_size.x)*2.0f;
	m_side.y = (1920.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.png", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.png", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),3));
	m_side.x = (1920.0f/m_size.x)*2.0f;
	m_side.y = (122.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.png", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.png", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-MainFront.dds", FLOAT2(0,0), FLOAT2(2,2),2));


	this->m_Buttons.resize(6);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.28125f*2.5f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-CreateGame.png","",0,0,2,5);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.28125f*1.5f,	-0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-JoinGame.png","",0,0,2,5);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(-0.140625f,	-0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-Settings.png","",0,0,2,5);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(0.140625f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-Lore.png","",0,0,2,5);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(0.28125f*1.5f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-Credits.png","",0,0,2,5);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(0.28125f*2.5f,	-0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-ExitGame.png","",0,0,2,5);
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
	if(this->m_Buttons[0]->Clicked() == 1)
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