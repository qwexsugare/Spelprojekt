#include "CreditsMenu.h"


CreditsMenu::CreditsMenu(void)
{
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-Credits.png", FLOAT2(0,0),  FLOAT2(2,2),0));

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
