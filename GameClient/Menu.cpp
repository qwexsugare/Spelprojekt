#include "Menu.h"

Menu::Menu()
{
}

void Menu::Init()
{

}

void Menu::Update()
{

}
Menu::~Menu()
{
	for(int i = 0; i < this->m_Buttons.size(); i++)
	{
		delete this->m_Buttons[i];
	}

	this->m_Buttons.clear();

	for(int i = 0; i < this->m_Images.size(); i++)
	{
		g_graphicsEngine->removeSprite(this->m_Images[i]);
	}

	this->m_Images.clear();
}
