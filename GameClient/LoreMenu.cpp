#include "LoreMenu.h"
#include "TextLabel.h"

LoreMenu::LoreMenu(void)
{
	ThisPage = 0;
	Change = false;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-0.png", FLOAT2(0,0),  FLOAT2(2,2),0));

	this->m_Buttons.resize(3);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(0.208333333f,-0.933333333f),FLOAT2(0.053125f,0.103703704f),"menu_textures\\Arrow-Right.png","",0,0,2);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.208333333f,-0.933333333f),FLOAT2(0.053125f,0.103703704f),"menu_textures\\Arrow-Left.png","",0,0,2);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(0,-0.933333333f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,2);

}
void LoreMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
	ChangeStates();
}
bool LoreMenu::Plus()
{
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LoreMenu::Minus()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool LoreMenu::MainMenuIsDown()
{
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
void LoreMenu::ChangeStates()
{
	if(Plus())
	{
		ThisPage += 1;
		Change = true;
		if (ThisPage > 16)
		{
			ThisPage = 0;
		}

	}
	else if(Minus())
	{
		ThisPage -= 1;
		Change = true;
		if(ThisPage < 0)
		{
			ThisPage = 16;
		}
	}

	if (Change == true)
	{
		stringstream ss;
		ss << ThisPage;

		g_graphicsEngine->removeSprite( m_Images[0]);
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-" +ss.str()+ ".png", FLOAT2(0,0),  FLOAT2(2,2),0));
	}
	Change = false;
}

LoreMenu::~LoreMenu(void)
{
}
