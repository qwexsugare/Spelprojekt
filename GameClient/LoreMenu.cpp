#include "LoreMenu.h"

LoreMenu::LoreMenu() : Menu()
{
	this->m_thisPage = 0;
	this->m_change = false;
	this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-World.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));

	this->m_Buttons.resize(3);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(INT2(1920*0.5f+200,  1080*0.5-504),INT2(51,56),"Arrow-Right.png","",0,0,1);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(INT2(1920*0.5f-200,  1080*0.5-504),INT2(51,56),"Arrow-Left.png","",0,0,1);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(INT2(1920*0.5f,  1080*0.5-504),INT2(262,77),"Button-LobbyMenu-MainMenu.png","",0,0,1);
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

LoreMenu::~LoreMenu()
{

}
void LoreMenu::ChangeStates()
{
	if(this->Plus())
	{
		this->m_thisPage += 1;
		this->m_change = true;
		if (this->m_thisPage > 15)
		{
			this->m_thisPage = 0;
		}

	}
	else if(Minus())
	{
		this->m_thisPage -= 1;
		this->m_change = true;

		if(this->m_thisPage < 0)
		{
			this->m_thisPage = 15;
		}
	}

	if (this->m_change == true)
	{
		if(this->m_thisPage == 0)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-World.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if(this->m_thisPage == 1)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-Attributes.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if(this->m_thisPage == 2)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-Skill-0.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if(this->m_thisPage == 3)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-Skill-1.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 4)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-Engineer.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 5)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-Doctor.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 6)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-Officer.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 7)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-Mentalist.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		} 
		else if (this->m_thisPage == 8)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-RedKnight.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 9)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-TeslaChainTurret.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 10)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-PoisonTurret.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 11)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-DeathPulseTurret.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 12)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-FrostTurret.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 13)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-FrostDemon.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 14)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-Imp.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}
		else if (this->m_thisPage == 15)
		{
			g_graphicsEngine->removeSprite( m_Images[0]);
			this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-LORE-SpittingDemon.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
		}

		this->m_change = false;
	}
}
