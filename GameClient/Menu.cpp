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

	for(int i = 0; i < this->m_SkillButtons.size(); i++)
	{
		delete this->m_SkillButtons[i];
	}
	this->m_SkillButtons.clear();

	for(int i = 0; i < this->m_Images.size(); i++)
	{
		g_graphicsEngine->removeSprite(this->m_Images[i]);
	}
	this->m_Images.clear();
}
void Menu::deleteImages()
{
	for(int i = 0; i < this->m_Images.size(); i++)
	{
		g_graphicsEngine->removeSprite(this->m_Images[i]);
	}
	this->m_Images.clear();
}
