#include "LobbyMenu.h"
extern Menu::WorldState g_MState;

LobbyMenu::LobbyMenu(void) : Menu()
{
}


LobbyMenu::~LobbyMenu(void)
{

}
void LobbyMenu::Init()
{
	this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LobbyMenu-Background.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LobbyMenu-Middleground.png", INT2(1920/2, 1080/2), INT2(1920, 1080),1));
	this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LobbyMenu-Foreground.png", INT2(1920/2, 1080/2), INT2(1920, 1080),4));

	this->m_Buttons.resize(12);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(INT2(1920*0.5f-700,  1080*0.5+28),INT2(262,77),"Button-LobbyMenu-Chat.png","",0,0,1);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(INT2(1920*0.5f-700,  1080*0.5-60),INT2(262,77),"Button-LobbyMenu-Store.png","",0,0,1);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(INT2(1920*0.5f-700,  1080*0.5-148),INT2(262,77),"Button-LobbyMenu-MainMenu.png","",0,0,1);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(INT2(1920*0.5f+700,  1080*0.5+28),INT2(262,77),"Button-LobbyMenu-CharacterInformation.png","",0,0,1);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(INT2(1920*0.5f+700,  1080*0.5-60),INT2(262,77),"Button-LobbyMenu-LevelInformation.png","",0,0,1);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(INT2(1920*0.5f+700,  1080*0.5-148),INT2(262,77),"Button-LobbyMenu-Ready.png","",0,0,1);
	this->m_Buttons[6] = new Button();
	this->m_Buttons[6]->Init(INT2(1920*0.5f+360,  1080*0.5-280),INT2(73,73),"Button-LobbyMenu-CloseCombat.png","",0,0,1);
	this->m_Buttons[7] = new Button();
	this->m_Buttons[7]->Init(INT2(1920*0.5f+680,  1080*0.5-280),INT2(73,73),"Button-LobbyMenu-RangeCombat.png","",0,0,1);
	
	// Player buttons
	this->m_Buttons[8] = new Button();
	this->m_Buttons[8]->Init(INT2(1920*0.5f+700,  1080*0.5+330),INT2(262,77),"Button-LobbyMenu-Player1.png","",0,0,1);
	this->m_Buttons[9] = new Button();
	this->m_Buttons[9]->Init(INT2(1920*0.5f+700,  1080*0.5+260),INT2(262,77),"Button-LobbyMenu-Player2.png","",0,0,1);
	this->m_Buttons[10] = new Button();
	this->m_Buttons[10]->Init(INT2(1920*0.5f+700,  1080*0.5+190),INT2(262,77),"Button-LobbyMenu-Player3.png","",0,0,1);
	this->m_Buttons[11] = new Button();
	this->m_Buttons[11]->Init(INT2(1920*0.5f+700,  1080*0.5+120),INT2(262,77),"Button-LobbyMenu-Player4.png","",0,0,1);
}
void LobbyMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
	ChangeStates();
}
bool LobbyMenu::ChatIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::StoreIsDone()
{
	if(this->m_Buttons[1]->Clicked()== 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::MainMenuIsDone()
{
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::CharacterInformationIsDone()
{
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::LevelInformationIsDone()
{
	if(this->m_Buttons[4]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::StartGameIsDone()
{
	if(this->m_Buttons[5]->Clicked()== 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::RangeCombatIsDone()
{
	if(this->m_Buttons[6]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LobbyMenu::CloseCombatIsDone()
{
	if(this->m_Buttons[7]->Clicked()== 1)
	{
		return true;
	}
	return false;
}
void LobbyMenu::ChangeStates()
{
	if(StartGameIsDone())
	{
		g_MState = WorldState::InGame;
	}
	else if(MainMenuIsDone())
	{
		g_MState = WorldState::Main;
	}
}