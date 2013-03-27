#include "CreditsMenu.h"


CreditsMenu::CreditsMenu(void)
{
	FLOAT2 m_size, m_side; 
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
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-Credits.png", FLOAT2(0,0),  FLOAT2(2,2),0));
	m_size.x		=	0;
	m_size.y		=	0;
	m_side.x		=	0;
	m_side.y		=	0;
	m_size.x		=	1920;
	m_size.y		=	1080;
	m_side.x		=	(122.0f/m_size.x)*2.0f;
	m_side.y		=	(1920.0f/m_size.y)*2.0f;

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.png", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),1));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.png", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),1));

	m_side.x		=	(1920.0f/m_size.x)*2.0f;
	m_side.y		=	(122.0f/m_size.y)*2.0f;

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.png", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),2));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.png", FLOAT2(0,-0.93f),  FLOAT2(-m_side.x,m_side.y),2));
	this->m_Buttons.resize(1);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(0,  -0.933333333f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,2);

}
void CreditsMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
}

bool CreditsMenu::MainMenuGameIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}


CreditsMenu::~CreditsMenu(void)
{
}
