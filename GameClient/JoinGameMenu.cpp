#include "JoinGameMenu.h"
#include "Graphics.h"


JoinGameMenu::JoinGameMenu(void)
{
	m_WriteIP		=	false;
	m_WriteName		=	false;
	m_WriteGame		=	false;
	int graphics = g_configFile->getScreenSize().y;
	int windowed = g_configFile->getWindowed();
	m_changePosY= 1.0f;
	m_fontsize = 1.0f;
	m_graphicstext = "1080";
	if (graphics == 1080)
	{
		m_changePosY= 1.0f;
		m_graphicstext = "1080";
		if (windowed == 1)
		{
			m_fontsize = 1;
		}
		else
		{
			m_fontsize =1;
		}
	}
	if (graphics == 900)
	{
		m_changePosY= 0.833333333334f;
		m_graphicstext = "900";
		if (windowed == 1)
		{
			m_fontsize = 1;
		}
		else
		{
			m_fontsize =0.833333333334f;
		}
	}
	if (graphics == 720)
	{
		m_changePosY= 0.66666666666667f;
		m_graphicstext = "720";
		if (windowed == 1)
		{
			m_fontsize = 1;
		}
		else
		{
			m_fontsize =0.66666666666667f;
		}
	}

	this->m_Label.push_back(new TextInput("text2.png", INT2(920*m_changePosY, 803), 100*m_fontsize));
	this->m_Label.push_back(new TextInput("text2.png", INT2(920*m_changePosY, 862), 100*m_fontsize));
	this->m_Label.push_back(new TextInput("text2.png", INT2(920*m_changePosY, 921), 100*m_fontsize, 10));
	this->m_Label[0]->setText("");
	this->m_Label[1]->setText("1337");
	this->m_Label[2]->setText(g_configFile->getPlayerName());
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-JoinGameMenu.png", FLOAT2(0,0),  FLOAT2(2,2),0));
	FLOAT2 m_size, m_side;
	m_size.x = 0;
	m_size.y = 0;
	m_side.x = 0;
	m_side.y = 0;
	m_size.x		=	1920;
	m_size.y		=	1080;
	m_side.x = (122.0f/m_size.x)*2.0f;
	m_side.y = (1920.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.png", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.png", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),3));
	m_side.x = (1920.0f/m_size.x)*2.0f;
	m_side.y = (122.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.png", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.png", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),4));
	this->m_Buttons.resize(5);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.140625f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-MainMenu-JoinGame.png","",0,0,1,5);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(0.140625f,  -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,1,5);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(0.2f,  -0.36f),FLOAT2(0.3125f*2,0.05555555f*1.5f),"menu_textures\\Button-Text.png","",0,0,1,5);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(0.2f,  -0.47f),FLOAT2(0.3125f*2,0.05555555f*1.5f),"menu_textures\\Button-Text.png","",0,0,1,5);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(0.2f,  -0.56f),FLOAT2(0.3125f*2,0.05555555f*1.5f),"menu_textures\\Button-Text.png","",0,0,1,5);
}
void JoinGameMenu::Update(float _dt)
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
	if (MainWriteGameIsDown() || m_WriteGame == true)
		this->m_Label[0]->update(_dt);
	if (MainWriteIPIsDown() || m_WriteIP == true)
		this->m_Label[1]->update(_dt);
	if (MainWriteNameIsDown() || m_WriteName == true)
		this->m_Label[2]->update(_dt);
}
bool JoinGameMenu::StartGameIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool JoinGameMenu::MainMenuGameIsDown()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool JoinGameMenu::MainWriteGameIsDown()
{
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		m_WriteIP		=	false;
		m_WriteName		=	false;
		m_WriteGame		=	true;
		return true;
	}
	return false;
}
bool JoinGameMenu::MainWriteIPIsDown()
{
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		m_WriteIP		=	true;
		m_WriteName		=	false;
		m_WriteGame		=	false;
		return true;
	}
	return false;
}
bool JoinGameMenu::MainWriteNameIsDown()
{
	if(this->m_Buttons[4]->Clicked() == 1)
	{
		m_WriteIP		=	false;
		m_WriteName		=	true;
		m_WriteGame		=	false;
		return true;
	}
	return false;
}

string JoinGameMenu::getIP()
{
	return this->m_Label[0]->getText();
}

string JoinGameMenu::getPort()
{
	return this->m_Label[1]->getText();
}

string JoinGameMenu::getPlayerName()
{
	return this->m_Label[2]->getText();
}

void JoinGameMenu::savePlayerName()
{
	g_configFile->setPlayerName(this->getPlayerName());
	g_configFile->save();
}

JoinGameMenu::~JoinGameMenu(void)
{
	for(int i = 0; i < m_Label.size();i++)
	{
		delete this->m_Label[i];
	}
}
