#include "SettingsMenu.h"
#include "Graphics.h"
#include "SoundWrapper.h"

SettingsMenu::SettingsMenu()
{
	m_windowed = g_configFile->getWindowed();
	FLOAT2 m_size, m_side; 
	m_size.x = 0;
	m_size.y = 0;
	m_side.x = 0;
	m_side.y = 0;
	m_size.x = 1920;
	m_size.y = 1080;

	int graphics = g_configFile->getScreenSize().y;
	m_DiffuseMode = g_configFile->getDiffuseMode();
	m_SSAO = g_configFile->getSSAO();
	m_EmilMode = g_configFile->getEmilMode();
	m_textureQuality = g_configFile->getTextureQuality();
	m_LevelMode = g_configFile->getLevelMode();
	m_shadowmap = g_configFile->getShadowmap();
	m_graphicstext = "1080";
	if (graphics == 1080)
	{
		m_graphicstext = "1080";
	}
	if (graphics == 900)
	{
		m_graphicstext = "900";
	}
	if (graphics == 720)
	{
		m_graphicstext = "720";
	}

	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-Settings.png", FLOAT2(0,0),  FLOAT2(2,2),0));
	m_side.x = (122.0f/m_size.x)*2.0f;
	m_side.y = (1920.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.png", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.png", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),3));
	m_side.x = (1920.0f/m_size.x)*2.0f;
	m_side.y = (122.0f/m_size.y)*2.0f;
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.png", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),4));
	this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.png", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),4));
	this->m_Buttons.resize(22);
	this->m_Buttons[0] = new Button();
	this->m_Buttons[0]->Init(FLOAT2(-0.65, 0.265f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\720p.png","",0,0,1,5);
	this->m_Buttons[1] = new Button();
	this->m_Buttons[1]->Init(FLOAT2(-0.55, 0.265f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\900p.png","",0,0,1,5);
	this->m_Buttons[2] = new Button();
	this->m_Buttons[2]->Init(FLOAT2(-0.45, 0.265f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\1080p.png","",0,0,1,5);

	/*this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.55, 0.26f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\800p.png","",0,0,1,5);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(-0.45, 0.26f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\1050p.png","",0,0,1,5);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(-0.35, 0.26f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\1200p.png","",0,0,1,5);*/

	this->m_Buttons[3] = new Button();
	this->m_Buttons[3]->Init(FLOAT2(-0.15625f, -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-LobbyMenu-MainMenu.png","",0,0,1,5);
	this->m_Buttons[4] = new Button();
	this->m_Buttons[4]->Init(FLOAT2(0.15625f, -0.875f),FLOAT2(0.272916667f,0.142592593f),"menu_textures\\Button-SettingsMenu-SaveChanges.png","",0,0,1,5);

	//this->m_Buttons[5] = new Button();
	//this->m_Buttons[5]->Init(FLOAT2(-0.708333333f, 0.262962963f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0,0.4f,2,1);
	this->m_Buttons[5] = new Button();
	this->m_Buttons[5]->Init(FLOAT2(-0.55, 0.138888889f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\RadioButton.png","",0,0.4f,2,1);
	this->m_Buttons[6] = new Button();
	this->m_Buttons[6]->Init(FLOAT2(-0.45, 0.138888889f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\RadioButton.png","",0,0.4f,2,1);

	// Texture map quality
	this->m_Buttons[7] = new Button();
	this->m_Buttons[7]->Init(FLOAT2(-0.65, 0.0f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\Button_LOW.png","",0,0,1,5);
	this->m_Buttons[8] = new Button();
	this->m_Buttons[8]->Init(FLOAT2(-0.55, 0.0f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\Button_MEDIUM.png","",0,0,1,5);
	this->m_Buttons[9] = new Button();
	this->m_Buttons[9]->Init(FLOAT2(-0.45, 0.0f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\Button_HIGH.png","",0,0,1,5);

	// Shadowmap
	this->m_Buttons[10] = new Button();
	this->m_Buttons[10]->Init(FLOAT2(-0.65, -0.27f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\RadioButton.png","",0,0.4f,2,1);
	this->m_Buttons[11] = new Button();
	this->m_Buttons[11]->Init(FLOAT2(-0.55, -0.27f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\Button_LOW.png","",0,0,1,5);
	this->m_Buttons[12] = new Button();
	this->m_Buttons[12]->Init(FLOAT2(-0.45, -0.27f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\Button_HIGH.png","",0,0,1,5);

	// SSAO
	this->m_Buttons[13] = new Button();
	this->m_Buttons[13]->Init(FLOAT2(-0.55, -0.138888889f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\RadioButton.png","",0,0.4f,2,1);
	this->m_Buttons[14] = new Button();
	this->m_Buttons[14]->Init(FLOAT2(-0.45, -0.138888889f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\RadioButton.png","",0,0.4f,2,1);

	// Diffuse mode
	this->m_Buttons[15] = new Button();
	this->m_Buttons[15]->Init(FLOAT2(-0.55, -0.4f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\RadioButton.png","",0,0.4f,2,1);
	this->m_Buttons[16] = new Button();
	this->m_Buttons[16]->Init(FLOAT2(-0.45, -0.4f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\RadioButton.png","",0,0.4f,2,1);

	// Level difficulty
	this->m_Buttons[17] = new Button();
	this->m_Buttons[17]->Init(FLOAT2(0.0f, -0.22f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\Button_EASY.png","",0,0,1,5);
	this->m_Buttons[18] = new Button();
	this->m_Buttons[18]->Init(FLOAT2(0.1f, -0.22f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\Button_NORMAL.png","",0,0,1,5);
	this->m_Buttons[19] = new Button();
	this->m_Buttons[19]->Init(FLOAT2(0.2f, -0.22f),FLOAT2(0.086458333f,0.033333333f),"menu_textures\\Button_HARD.png","",0,0,1,5);

	// Emil mode
	this->m_Buttons[20] = new Button();
	this->m_Buttons[20]->Init(FLOAT2(0.1f, -0.4f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\RadioButton.png","",0,0.4f,2,1);
	this->m_Buttons[21] = new Button();
	this->m_Buttons[21]->Init(FLOAT2(0.2f, -0.4f),FLOAT2(0.026041667f,0.051851852f),"menu_textures\\RadioButton.png","",0,0.4f,2,1);

	if(m_windowed == 1)
	{
		m_Buttons[5]->SetTextBoxValue(true);
		m_Buttons[6]->SetTextBoxValue(false);
	}
	else
	{
		m_Buttons[5]->SetTextBoxValue(false);
		m_Buttons[6]->SetTextBoxValue(true);
	}
	if(m_DiffuseMode == 1)
	{
		m_Buttons[15]->SetTextBoxValue(true);
		m_Buttons[16]->SetTextBoxValue(false);
	}
	else
	{
		m_Buttons[15]->SetTextBoxValue(false);
		m_Buttons[16]->SetTextBoxValue(true);
	}
	if(m_EmilMode == 1)
	{
		m_Buttons[20]->SetTextBoxValue(true);
		m_Buttons[21]->SetTextBoxValue(false);
	}
	else
	{
		m_Buttons[20]->SetTextBoxValue(false);
		m_Buttons[21]->SetTextBoxValue(true);
	}
	if(m_SSAO == 1)
	{
		m_Buttons[13]->SetTextBoxValue(true);
		m_Buttons[14]->SetTextBoxValue(false);
	}
	else
	{
		m_Buttons[13]->SetTextBoxValue(false);
		m_Buttons[14]->SetTextBoxValue(true);
	}
	if(m_textureQuality == 0)
	{
		m_Buttons[7]->SetTextBoxValue(true);
		m_Buttons[8]->SetTextBoxValue(false);
		m_Buttons[9]->SetTextBoxValue(false);
	}
	else if(m_textureQuality == 1)
	{
		m_Buttons[7]->SetTextBoxValue(false);
		m_Buttons[8]->SetTextBoxValue(true);
		m_Buttons[9]->SetTextBoxValue(false);
	}
	else if(m_textureQuality == 2)
	{
		m_Buttons[7]->SetTextBoxValue(false);
		m_Buttons[8]->SetTextBoxValue(false);
		m_Buttons[9]->SetTextBoxValue(true);
	}
	if(m_shadowmap == 0)
	{
		m_Buttons[10]->SetTextBoxValue(true);
		m_Buttons[11]->SetTextBoxValue(false);
		m_Buttons[12]->SetTextBoxValue(false);
	}
	else if(m_shadowmap == 1)
	{
		m_Buttons[10]->SetTextBoxValue(false);
		m_Buttons[11]->SetTextBoxValue(true);
		m_Buttons[12]->SetTextBoxValue(false);
	}
	else if(m_shadowmap == 2)
	{
		m_Buttons[10]->SetTextBoxValue(false);
		m_Buttons[11]->SetTextBoxValue(false);
		m_Buttons[12]->SetTextBoxValue(true);
	}
	if(m_LevelMode == 0)
	{
		m_Buttons[17]->SetTextBoxValue(true);
		m_Buttons[18]->SetTextBoxValue(false);
		m_Buttons[19]->SetTextBoxValue(false);
	}
	else if(m_LevelMode == 1)
	{
		m_Buttons[17]->SetTextBoxValue(false);
		m_Buttons[18]->SetTextBoxValue(true);
		m_Buttons[19]->SetTextBoxValue(false);
	}
	else if(m_LevelMode == 2)
	{
		m_Buttons[17]->SetTextBoxValue(false);
		m_Buttons[18]->SetTextBoxValue(false);
		m_Buttons[19]->SetTextBoxValue(true);
	}
	/*this->m_soundVolumeSlider.Init(FLOAT2(-0.177083333f+g_configFile->getSoundVolume()*0.4f, 0.262962963f),FLOAT2(0.026041667f,0.051851852f),
		"menu_textures\\Arrow-Up.png","",-g_configFile->getSoundVolume()*0.4f,0.4f-g_configFile->getSoundVolume()*0.4f,2,1);
	this->m_musicVolumeSlider.Init(FLOAT2(-0.177083333f+g_configFile->getMusicVolume()*0.4f, 0.138888889f),FLOAT2(0.026041667f,0.051851852f),
		"menu_textures\\Arrow-Up.png","",-g_configFile->getMusicVolume()*0.4f,0.4f-g_configFile->getMusicVolume()*0.4f,2,1);*/

	this->m_soundVolumeSlider.Init(FLOAT2(-0.177083333f, 0.262962963f), g_configFile->getSoundVolume()*0.4f,FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0.0f,0.4f,2,1);
	this->m_musicVolumeSlider.Init(FLOAT2(-0.177083333f, 0.138888889f), g_configFile->getMusicVolume()*0.4f, FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0.0f,0.4f,2,1);
	this->m_speechVolumeSlider.Init(FLOAT2(-0.177083333f, 0.014f), g_configFile->getSpeechVolume()*0.4f, FLOAT2(0.026041667f,0.051851852f),"menu_textures\\Arrow-Up.png","",0.0f,0.4f,2,1);
	
	if (graphics == 720)
	{
		this->m_Buttons[0]->SetTextBoxValue(true);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(false);
		//this->m_Buttons[3]->SetTextBoxValue(false);
		//this->m_Buttons[4]->SetTextBoxValue(false);
		//this->m_Buttons[5]->SetTextBoxValue(false);
	}
	if (graphics == 900)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(true);
		this->m_Buttons[2]->SetTextBoxValue(false);
		//this->m_Buttons[3]->SetTextBoxValue(false);
		//this->m_Buttons[4]->SetTextBoxValue(false);
		//this->m_Buttons[5]->SetTextBoxValue(false);
	}
	if (graphics == 1080)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(true);
		//this->m_Buttons[3]->SetTextBoxValue(false);
		//this->m_Buttons[4]->SetTextBoxValue(false);
		//this->m_Buttons[5]->SetTextBoxValue(false);

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
	// Windowed Mode clicked
	if(m_Buttons[5]->isClicked())
	{
		m_Buttons[5]->SetTextBoxValue(true);
		m_Buttons[6]->SetTextBoxValue(false);
		m_windowed = true;
	}
	// Fullscreen mode
	if(m_Buttons[6]->isClicked())
	{
		m_Buttons[5]->SetTextBoxValue(false);
		m_Buttons[6]->SetTextBoxValue(true);
		m_windowed = false;
	}

	// SSAO ON
	if(m_Buttons[13]->isClicked())
	{
		m_Buttons[13]->SetTextBoxValue(true);
		m_Buttons[14]->SetTextBoxValue(false);
		m_SSAO = true;
	}
	// SSAO OFF
	if(m_Buttons[14]->isClicked())
	{
		m_Buttons[13]->SetTextBoxValue(false);
		m_Buttons[14]->SetTextBoxValue(true);
		m_SSAO = false;
	}

	// DIFFUSE MODE ON
	if(m_Buttons[15]->isClicked())
	{
		m_Buttons[15]->SetTextBoxValue(true);
		m_Buttons[16]->SetTextBoxValue(false);
		m_DiffuseMode = true;
	}
	// DIFFUSE MODE OFF
	if(m_Buttons[16]->isClicked())
	{
		m_Buttons[15]->SetTextBoxValue(false);
		m_Buttons[16]->SetTextBoxValue(true);
		m_DiffuseMode = false;
	}

	// EMIL MODE ON
	if(m_Buttons[20]->isClicked())
	{
		m_Buttons[20]->SetTextBoxValue(true);
		m_Buttons[21]->SetTextBoxValue(false);
		m_EmilMode = 1;
	}
	// EMIL MODE OFF
	if(m_Buttons[21]->isClicked())
	{
		m_Buttons[20]->SetTextBoxValue(false);
		m_Buttons[21]->SetTextBoxValue(true);
		m_EmilMode = 0;
	}
	m_soundVolumeSlider.Update();
	m_musicVolumeSlider.Update();
	m_speechVolumeSlider.Update();
	LowIsDownS();
	MediumIsDownS();
	HighIsDownS();

	TextureLowIsDown();
	TextureMediumIsDown();
	TextureHighIsDown();

	ShadowmapOFFIsDown();
	ShadowmapLOWIsDown();
	ShadowmapHIGHIsDown();

	EasyIsDown();
	NormalIsDown();
	HardIsDown();

	/*LowIsDown();
	MediumIsDown();
	HighIsDown();*/
	setMusicVolume(this->m_musicVolumeSlider.GetValue());
	setSoundVolume(this->m_soundVolumeSlider.GetValue());
	setSpeechVolume(this->m_speechVolumeSlider.GetValue());
	if(SaveSettingsIsDown())
	{
		int graphics = g_configFile->getScreenSize().y;
		if (graphics == 1080)
		{
			g_configFile->setScreenSize(INT2(1920, 1080));
		}
		if (graphics == 900)
		{
			g_configFile->setScreenSize(INT2(1600, 900));
		}
		if (graphics == 720)
		{
			g_configFile->setScreenSize(INT2(1280, 720));
		}
		g_configFile->setMusicVolume(m_musicVolumeSlider.GetValue());
		g_configFile->setSoundVolume(m_soundVolumeSlider.GetValue());
		g_configFile->setSpeechVolume(m_speechVolumeSlider.GetValue());
		g_configFile->setWindowed(m_windowed);
		g_configFile->setLevelMode(m_LevelMode);
		g_configFile->setDiffuseMode(m_DiffuseMode);
		g_configFile->setEmilMode(m_EmilMode);
		g_configFile->setShadowmap(m_shadowmap);
		g_configFile->setSSAO(m_SSAO);
		g_configFile->setTextureQuality(m_textureQuality);
		g_configFile->save();
		g_graphicsEngine->setSsaoEnabled(m_SSAO);
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
		//this->m_Buttons[3]->SetTextBoxValue(false);
		//this->m_Buttons[4]->SetTextBoxValue(false);
		//this->m_Buttons[5]->SetTextBoxValue(false);
		deleteImages();
		g_configFile->setScreenSize(INT2(1280, 720));
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-Settings.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		FLOAT2 m_size, m_side; 
		m_size.x = 0;
		m_size.y = 0;
		m_side.x = 0;
		m_side.y = 0;
		m_size.x = 1920;
		m_size.y = 1080;
		m_side.x = (122.0f/m_size.x)*2.0f;
		m_side.y = (1920.0f/m_size.y)*2.0f;
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.png", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.png", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),3));
		m_side.x = (1920.0f/m_size.x)*2.0f;
		m_side.y = (122.0f/m_size.y)*2.0f;
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.png", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),4));
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.png", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),4));
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
		//this->m_Buttons[3]->SetTextBoxValue(false);
		//this->m_Buttons[4]->SetTextBoxValue(false);
		//this->m_Buttons[5]->SetTextBoxValue(false);
		deleteImages();
		g_configFile->setScreenSize(INT2(1600, 900));
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-Settings.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		FLOAT2 m_size, m_side; 
		m_size.x = 0;
		m_size.y = 0;
		m_side.x = 0;
		m_side.y = 0;
		m_size.x = 1920;
		m_size.y = 1080;
		m_side.x = (122.0f/m_size.x)*2.0f;
		m_side.y = (1920.0f/m_size.y)*2.0f;
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.png", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.png", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),3));
		m_side.x = (1920.0f/m_size.x)*2.0f;
		m_side.y = (122.0f/m_size.y)*2.0f;
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.png", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),4));
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.png", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),4));
		return true;
	}
	return false;
}
bool SettingsMenu::HighIsDownS()
{
	// 1920 x 1080
	if(this->m_Buttons[2]->Clicked() == 1)
	{
		this->m_Buttons[0]->SetTextBoxValue(false);
		this->m_Buttons[1]->SetTextBoxValue(false);
		this->m_Buttons[2]->SetTextBoxValue(true);
		//this->m_Buttons[3]->SetTextBoxValue(false);
		//this->m_Buttons[4]->SetTextBoxValue(false);
		//this->m_Buttons[5]->SetTextBoxValue(false);
		deleteImages();
		g_configFile->setScreenSize(INT2(1920, 1080));
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\"+m_graphicstext+"\\MENU-Settings.png", FLOAT2(0,0),  FLOAT2(2,2),0));
		FLOAT2 m_size, m_side; 
		m_size.x = 0;
		m_size.y = 0;
		m_side.x = 0;
		m_side.y = 0;
		m_size.x = 1920;
		m_size.y = 1080;
		m_side.x = (122.0f/m_size.x)*2.0f;
		m_side.y = (1920.0f/m_size.y)*2.0f;
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Left.png", FLOAT2(-0.94f,0),  FLOAT2(m_side.x,m_side.y),3));
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Right.png", FLOAT2(0.94f,0),  FLOAT2(m_side.x,-m_side.y),3));
		m_side.x = (1920.0f/m_size.x)*2.0f;
		m_side.y = (122.0f/m_size.y)*2.0f;
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_UP.png", FLOAT2(0,0.89f),  FLOAT2(m_side.x,m_side.y),4));
		this->m_Images.push_back(g_graphicsEngine->createSprite("menu_textures\\Frame_Bottom.png", FLOAT2(0,-0.89f),  FLOAT2(-m_side.x,m_side.y),4));
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
		//g_configFile->setScreenSize(INT2(1280, 800));
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
		//g_configFile->setScreenSize(INT2(1680, 1050));
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
		//g_configFile->setScreenSize(INT2(1920, 1200));
		return true;
	}
	return false;
}
bool SettingsMenu::TextureLowIsDown()
{
	if(this->m_Buttons[7]->Clicked() == 1)
	{
		this->m_Buttons[7]->SetTextBoxValue(true);
		this->m_Buttons[8]->SetTextBoxValue(false);
		this->m_Buttons[9]->SetTextBoxValue(false);
		m_textureQuality = 0;
		return true;
	}
	return false;
}
bool SettingsMenu::TextureMediumIsDown()
{
	if(this->m_Buttons[8]->Clicked() == 1)
	{
		this->m_Buttons[7]->SetTextBoxValue(false);
		this->m_Buttons[8]->SetTextBoxValue(true);
		this->m_Buttons[9]->SetTextBoxValue(false);
		m_textureQuality = 1;
		return true;
	}
	return false;
}
bool SettingsMenu::TextureHighIsDown()
{
	if(this->m_Buttons[9]->Clicked() == 1)
	{
		this->m_Buttons[7]->SetTextBoxValue(false);
		this->m_Buttons[8]->SetTextBoxValue(false);
		this->m_Buttons[9]->SetTextBoxValue(true);
		m_textureQuality = 2;
		return true;
	}
	return false;
}

bool SettingsMenu::ShadowmapOFFIsDown()
{
	if(this->m_Buttons[10]->Clicked() == 1)
	{
		this->m_Buttons[10]->SetTextBoxValue(true);
		this->m_Buttons[11]->SetTextBoxValue(false);
		this->m_Buttons[12]->SetTextBoxValue(false);
		m_shadowmap = 0;
		return true;
	}
	return false;
}
bool SettingsMenu::ShadowmapLOWIsDown()
{
	if(this->m_Buttons[11]->Clicked() == 1)
	{
		this->m_Buttons[10]->SetTextBoxValue(false);
		this->m_Buttons[11]->SetTextBoxValue(true);
		this->m_Buttons[12]->SetTextBoxValue(false);
		m_shadowmap = 1;
		return true;
	}
	return false;
}
bool SettingsMenu::ShadowmapHIGHIsDown()
{
	if(this->m_Buttons[12]->Clicked() == 1)
	{
		this->m_Buttons[10]->SetTextBoxValue(false);
		this->m_Buttons[11]->SetTextBoxValue(false);
		this->m_Buttons[12]->SetTextBoxValue(true);
		m_shadowmap = 2;
		return true;
	}
	return false;
}

bool SettingsMenu::EasyIsDown()
{
	if(this->m_Buttons[17]->Clicked() == 1)
	{
		this->m_Buttons[17]->SetTextBoxValue(true);
		this->m_Buttons[18]->SetTextBoxValue(false);
		this->m_Buttons[19]->SetTextBoxValue(false);
		m_LevelMode = 0;
		return true;
	}
	return false;
}
bool SettingsMenu::NormalIsDown()
{
	if(this->m_Buttons[18]->Clicked() == 1)
	{
		this->m_Buttons[17]->SetTextBoxValue(false);
		this->m_Buttons[18]->SetTextBoxValue(true);
		this->m_Buttons[19]->SetTextBoxValue(false);
		m_LevelMode = 1;
		return true;
	}
	return false;
}
bool SettingsMenu::HardIsDown()
{
	if(this->m_Buttons[19]->Clicked() == 1)
	{
		this->m_Buttons[17]->SetTextBoxValue(false);
		this->m_Buttons[18]->SetTextBoxValue(false);
		this->m_Buttons[19]->SetTextBoxValue(true);
		m_LevelMode = 2;
		return true;
	}
	return false;
}

bool SettingsMenu::MainMenuIsDown()
{
	if(this->m_Buttons[3]->Clicked() == 1)
	{
		return true;
	}
	return false;
}
bool SettingsMenu::SaveSettingsIsDown()
{
	if(this->m_Buttons[4]->Clicked() == 1)
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
