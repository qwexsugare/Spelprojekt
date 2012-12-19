#include "CreateGameMenu.h"

CreateGameMenu::CreateGameMenu(): Menu()
{
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-CreateGameMenu.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));

	this->m_Buttons.resize(2);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(INT2(1920*0.5f+135,  1080*0.5-504),INT2(262,77),"menu_textures\\Button-CharacterMenu-StartGame.png","",0,0,1);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(INT2(1920*0.5f-135,  1080*0.5-504),INT2(262,77),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,1);
}

void CreateGameMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
}
bool CreateGameMenu::StartGameIsDown()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool CreateGameMenu::MainMenuGameIsDown()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
CreateGameMenu::~CreateGameMenu()
{

}