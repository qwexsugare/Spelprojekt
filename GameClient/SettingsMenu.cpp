#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(): Menu()
{
	this->m_Images.push_back(g_graphicsEngine->createSprite("MENU-Settings.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
	this->m_Buttons.resize(8);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(INT2(1920*0.5f+150,  1080*0.5-504),INT2(262,77),"Button-LobbyMenu-MainMenu.png","",0,0,1);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(INT2(1920*0.5f-150,  1080*0.5-504),INT2(262,77),"Button-SettingsMenu-SaveChanges.png","",0,0,1);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(INT2(1920*0.5f-680,  1080*0.5+142),INT2(25,28),"Arrow-Up.png","",0,385,1,0);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(INT2(1920*0.5f-680,  1080*0.5+75),INT2(25,28),"Arrow-Up.png","",0,385,1,0);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(INT2(1920*0.5f-680,  1080*0.5+10),INT2(25,28),"Arrow-Up.png","",0,385,1,0);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(INT2(1920*0.5f-170,  1080*0.5+142),INT2(25,28),"Arrow-Up.png","",0,385,1,0);
	this->m_Buttons[6] = new Button();
	this->m_Buttons[6]->Init(INT2(1920*0.5f-170,  1080*0.5+75),INT2(25,28),"Arrow-Up.png","",0,385,1,0);
	this->m_Buttons[7] = new Button();
	this->m_Buttons[7]->Init(INT2(1920*0.5f-100,  1080*0.5-300),INT2(25,28),"Arrow-Up.png","",0,385,1,0);
}

void SettingsMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
}

SettingsMenu::~SettingsMenu()
{

}