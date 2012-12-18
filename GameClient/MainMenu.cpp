#include "MainMenu.h"
extern Menu::WorldState g_MState;

MainMenu::MainMenu() : Menu()
{
}

void MainMenu::Init()
{
	g_MState = WorldState::Main;
	this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-MainBack.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-MainFront.png", INT2(1920/2, 1080/2), INT2(1920, 1080),2));

	this->m_Buttons.resize(6);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(INT2(1920*0.5f-700,  1080*0.5+200),INT2(262,77),"Button-MainMenu-CreateGame.png","",0,0,1);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(INT2(1920*0.5f-700,  1080*0.5+100),INT2(262,77),"Button-MainMenu-JoinGame.png","",0,0,1);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(INT2(1920*0.5f-700,  1080*0.5),INT2(262,77),"Button-MainMenu-Settings.png","",0,0,1);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(INT2(1920*0.5f-700,  1080*0.5-100),INT2(262,77),"Button-MainMenu-Lore.png","",0,0,1);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(INT2(1920*0.5f-700,  1080*0.5-200),INT2(262,77),"Button-MainMenu-Credits.png","",0,0,1);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(INT2(1920*0.5f-700,  1080*0.5-300),INT2(262,77),"Button-MainMenu-ExitGame.png","",0,0,1);
}
void MainMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
	ChangeStates();
}
bool MainMenu::CreateGameIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;

}
bool MainMenu::JoinGameIsDone()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool MainMenu::SettingsIsDone()
{
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool MainMenu::LoreIsDone()
{
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool MainMenu::CreditsIsDone()
{
	if(this->m_Buttons[4]->Clicked() == 1)
	{
		return true;
	}
	return false;
} 
bool MainMenu::ExitIsDone()
{
	if(this->m_Buttons[5]->Clicked() == 1)
	{
		return true;
	}
	return false;
}

void MainMenu::ChangeStates()
{
	if(CreateGameIsDown())
	{
		g_MState = WorldState::Create;
	}
	else if(JoinGameIsDone())
	{
		g_MState = WorldState::Join;
	}
	else if(SettingsIsDone())
	{
		g_MState = WorldState::Settings;
	}
	else if(LoreIsDone())
	{
		g_MState = WorldState::Lore;
	}
	else if(CreditsIsDone())
	{
		g_MState = WorldState::Credits;
	}
	else if(ExitIsDone())
	{
		g_MState = WorldState::Exit;
	}
}

MainMenu::~MainMenu()
{

	
}