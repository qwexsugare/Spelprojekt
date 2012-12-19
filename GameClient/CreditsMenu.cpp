#include "CreditsMenu.h"

CreditsMenu::CreditsMenu(): Menu()
{
	this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-Credits.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));

	this->m_Buttons.resize(1);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(INT2(1920*0.5f,  1080*0.5-504),INT2(262,77),"Button-LobbyMenu-MainMenu.png","",0,0,1);
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

CreditsMenu::~CreditsMenu()
{

}
