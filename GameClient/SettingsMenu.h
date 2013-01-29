#pragma once
#include "menu.h"
class SettingsMenu :
	public Menu
{
public:
	SettingsMenu(void);
	~SettingsMenu(void);
	
	void Update();
	bool MainMenuIsDown();
	bool SaveSettingsIsDown();
	bool LowIsDownS();
	bool MediumIsDownS();
	bool HighIsDownS();
	bool LowIsDown();
	bool MediumIsDown();
	bool HighIsDown();
	int GetValueContrast();
	int GetValueBrigtness();
	int GetValueSoundVolume();
	int GetValueMusicVolume();
private:
	int m_Contrast,
		m_Brigtness,
		m_SoundVolume,
		m_MusicVolume;
};

