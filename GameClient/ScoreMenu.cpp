#include "ScoreMenu.h"


ScoreMenu::ScoreMenu(void)
{

	FLOAT2 m_size, m_side; 
	m_size.x = 0;
	m_size.y = 0;
	m_side.x = 0;
	m_side.y = 0;
	m_size.x = g_graphicsEngine->getRealScreenSize().x;
	m_size.y = g_graphicsEngine->getRealScreenSize().y;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-Settings.png", FLOAT2(0,0),  FLOAT2(2,2),0));
	m_side.x = (122.0f/m_size.x)*2.0f;
	m_side.y = (1920.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.dds", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.dds", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),3));
	m_side.x = (1920.0f/m_size.x)*2.0f;
	m_side.y = (122.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.dds", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.dds", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),4));
	this->m_Buttons.resize(1);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.140625f,  -0.933333333f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,2);
}
void ScoreMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
}
bool ScoreMenu::MainMenuGameIsDown()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}

ScoreMenu::~ScoreMenu(void)
{
}
