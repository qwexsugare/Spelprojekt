#include "LoreMenu.h"
#include "TextLabel.h"

LoreMenu::LoreMenu(void)
{
	ThisPage = 0;
	Change = false;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-LOREBOOK.png", FLOAT2(0,0),  FLOAT2(2,2),0));

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
bool LoreMenu::MainMenuGameIsDone()
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
		if(ThisPage == 0)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-LOREBOOK.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if(ThisPage == 1)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-Attributes.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if(ThisPage == 2)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-Skill-0.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if(ThisPage == 3)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-Skill-1.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 4)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-Engineer.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 5)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-Doctor.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 6)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-Officer.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 7)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-Mentalist.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		} 
		else if (ThisPage == 8)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-RedKnight.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 9)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-TeslaChainTurret.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 10)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-PoisonTurret.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 11)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-DeathPulseTurret.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 12)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-FrostTurret.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 13)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-FrostDemon.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 14)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-Imp.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 15)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-SpittingDemon.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
		else if (ThisPage == 16)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-LORE-ShadeFromTheUnderworld.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		}
	}
	Change = false;
}

LoreMenu::~LoreMenu(void)
{
}
