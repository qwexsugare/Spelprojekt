#include "SettingsMenu.h"
#include "Graphics.h"
#include "SoundWrapper.h"

SettingsMenu::SettingsMenu(void)
{
	FLOAT2 m_size, m_side; 
	m_size.x = 0;
	m_size.y = 0;
	m_side.x = 0;
	m_side.y = 0;
	m_size.x = 1920;
	m_size.y = 1080;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\MENU-Settings.png", FLOAT2(0,0),  FLOAT2(2,2),0));
	m_side.x = (122.0f/m_size.x)*2.0f;
	m_side.y = (1920.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.png", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.png", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),3));
	m_side.x = (1920.0f/m_size.x)*2.0f;
	m_side.y = (122.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.png", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.png", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),4));
	this->m_Buttons.resize(5);
	/*this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.55, 0.3f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\720p.png","",0,0,1,5);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.45, 0.3f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\900p.png","",0,0,1,5);*/
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.35, 0.3f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\1080p.png","",0,0,1,5);
	/*this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.55, 0.26f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\800p.png","",0,0,1,5);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(-0.45, 0.26f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\1050p.png","",0,0,1,5);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(-0.35, 0.26f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\1200p.png","",0,0,1,5);*/
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.15625f, -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,1,5);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(0.15625f, -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-SettingsMenu-SaveChanges.png","",0,0,1,5);
	//this->m_Buttons[5] = new Button();
	//this->m_Buttons[5]->Init(FLOAT2(-0.708333333f, 0.262962963f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,1);
	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.708333333f, 0.138888889f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,1);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(-0.708333333f, 0.018518519f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,1);
	
	/*this->m_soundVolumeSlider.Init(FLOAT2(-0.177083333f+g_configFile->getSoundVolume()*0.4f, 0.262962963f),FLOAT2(0.026041667f,0.051851852f),
		"menu_textures\\Arrow-Up.png","",-g_configFile->getSoundVolume()*0.4f,0.4f-g_configFile->getSoundVolume()*0.4f,2,1);
	this->m_musicVolumeSlider.Init(FLOAT2(-0.177083333f+g_configFile->getMusicVolume()*0.4f, 0.138888889f),FLOAT2(0.026041667f,0.051851852f),
		"menu_textures\\Arrow-Up.png","",-g_configFile->getMusicVolume()*0.4f,0.4f-g_configFile->getMusicVolume()*0.4f,2,1);*/
	this->m_soundVolumeSlider.Init(FLOAT2(-0.177083333f, 0.262962963f), g_configFile->getSoundVolume()*0.4f,FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0.0f,0.4f,2,1);
	this->m_musicVolumeSlider.Init(FLOAT2(-0.177083333f, 0.138888889f), g_configFile->getMusicVolume()*0.4f, FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0.0f,0.4f,2,1);

	int graphics = g_configFile->getScreenSize().y;
	/*if (graphics == 720)
	{
		this->m_Buttons[0]->SetTextBoxValue(true);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(false);
	}
	if (graphics == 900)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(true);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(false);
	}*/
	if (graphics == 1080)
	{
		/*this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(true);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(false);*/

		this->m_Buttons[0]->SetTextBoxValue(true);
	}
	/*if (graphics == 800)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(true);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(false);

	}
	if (graphics == 1050)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(true);
		this->m_Buttons[5]->SetTextBoxValue(false);
	}
	if (graphics == 1200)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(true);
	}*/
	/*this->m_Buttons[7] = new Button();
	this->m_Buttons[7]->Init(FLOAT2(-0.177083333f,  1),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,1);*/
}
void SettingsMenu::Update()
{
	for(int i=0; i < this->m_Buttons.size(); i++)
	{
		this->m_Buttons[i]->Update();
	}
	m_soundVolumeSlider.Update();
	m_musicVolumeSlider.Update();
	/*LowIsDownS();
	MediumIsDownS();*/
	HighIsDownS();
	/*LowIsDown();
	MediumIsDown();
	HighIsDown();*/
	setMusicVolume(this->m_musicVolumeSlider.GetValue());
	setSoundVolume(this->m_soundVolumeSlider.GetValue());
	if(SaveSettingsIsDown())
	{
		g_configFile->setMusicVolume(m_musicVolumeSlider.GetValue());
		g_configFile->setSoundVolume(m_soundVolumeSlider.GetValue());
		g_configFile->save();
	}
}
bool SettingsMenu::LowIsDownS()
{
	// 1280 x 720
	if(this->m_Buttons[0]->Clicked() == 1)
	{
		this->m_Buttons[0]->SetTextBoxValue(true);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(false);
		g_configFile->setScreenSize(INT2(1280, 720));
		return true;
	}
	return false;
}
bool SettingsMenu::MediumIsDownS()
{
	// 1600 x 900
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(true);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(false);
		g_configFile->setScreenSize(INT2(1600, 900));
		return true;
	}
	return false;
}
bool SettingsMenu::HighIsDownS()
{
	// 1920 x 1080
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		/*this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(true);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(false);*/
		g_configFile->setScreenSize(INT2(1920, 1080));
		return true;
	}
	return false;
}
bool SettingsMenu::LowIsDown()
{
	// 1280 x 800
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(true);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(false);
		g_configFile->setScreenSize(INT2(1280, 800));
		return true;
	}
	return false;
}
bool SettingsMenu::MediumIsDown()
{
	// 1680 x 1050
	if(this->m_Buttons[4]->Clicked() == 1)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(true);
		this->m_Buttons[5]->SetTextBoxValue(false);
		g_configFile->setScreenSize(INT2(1680, 1050));
		return true;
	}
	return false;
}
bool SettingsMenu::HighIsDown()
{
	// 1920 x 1200
	if(this->m_Buttons[5]->Clicked() == 1)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(false);
		this->m_Buttons[3]->SetTextBoxValue(false);
		this->m_Buttons[4]->SetTextBoxValue(false);
		this->m_Buttons[5]->SetTextBoxValue(true);
		g_configFile->setScreenSize(INT2(1920, 1200));
		return true;
	}
	return false;
}
bool SettingsMenu::MainMenuIsDown()
{
	if(this->m_Buttons[1]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool SettingsMenu::SaveSettingsIsDown()
{
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
int SettingsMenu::GetValueContrast()
{
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		m_Contrast = this->m_Buttons[3]->GetValue();
		return m_Contrast;
	}
	return m_Contrast;
}
int SettingsMenu::GetValueBrigtness()
{
	if(this->m_Buttons[4]->Clicked() == 1)
	{
		m_Brigtness = this->m_Buttons[4]->GetValue();
		return m_Brigtness;
	}
	return m_Brigtness;
}

SettingsMenu::~SettingsMenu(void)
{
}
