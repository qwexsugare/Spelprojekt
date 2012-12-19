#include "HudMenu.h"

HudMenu::HudMenu(): Menu()
{
	this->m_Time = 0;
	this->m_Delay = 0;
	this->m_DelayTime = 70;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Doctor.png", INT2(1920*0.5f-900,  1080*0.5-340),  INT2(80, 80),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Menu_Hud_Front.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),0));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Menu_Hud_Front.png", INT2(1920/2,  1080/2),  INT2(1920, 1080),3));
	this->m_Buttons.resize(1);
	this->m_Sprite.push_back(g_graphicsEngine->createSpriteSheet("menu_textures\\HealthBar.png",INT2(1920*0.5f-900,  1080*0.5-130),INT2(76, 408),INT2(10,1),2));

	this->m_Sprite[0]->playAnimation(INT2(0, 0), INT2(9, 0), true, 10);
}

void HudMenu::Update()
{

}

HudMenu::~HudMenu()
{

}
