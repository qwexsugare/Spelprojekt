#include "MainMenu.h"

MainMenu::MainMenu() : Menu()
{
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-MainBack.png", FLOAT2(0, 0),  FLOAT2(2, 2),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-MainFront.png", FLOAT2(0, 0),  FLOAT2(2, 2),2));

	this->m_Buttons.resize(6);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(INT2(1920*0.5f-700,  1080*0.5+200),INT2(262,77),"menu_textures\\Button-MainMenu-CreateGame.png","",0,0,1);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(INT2(1920*0.5f-700,  1080*0.5+100),INT2(262,77),"menu_textures\\Button-MainMenu-JoinGame.png","",0,0,1);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(INT2(1920*0.5f-700,  1080*0.5),INT2(262,77),"menu_textures\\Button-MainMenu-Settings.png","",0,0,1);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(INT2(1920*0.5f-700,  1080*0.5-100),INT2(262,77),"menu_textures\\Button-MainMenu-Lore.png","",0,0,1);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(INT2(1920*0.5f-700,  1080*0.5-200),INT2(262,77),"menu_textures\\Button-MainMenu-Credits.png","",0,0,1);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(INT2(1920*0.5f-700,  1080*0.5-300),INT2(262,77),"menu_textures\\Button-MainMenu-ExitGame.png","",0,0,1);
}

void MainMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
}

MainMenu::~MainMenu()
{

}

bool MainMenu::createGameIsDown()
{
	if(this->m_Buttons[0]->Clicked() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}