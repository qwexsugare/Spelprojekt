#pragma once
#include "menu.h"
#include "Slider.h"
class SettingsMenu :
	public Menu
{
public:
	SettingsMenu();
	~SettingsMenu();
	
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
private:
	Slider m_soundVolumeSlider;
	Slider m_musicVolumeSlider;

	int m_Contrast,
		m_Brigtness,
		m_SoundVolume,
		m_MusicVolume;
	bool m_windowed;
	string m_graphicstext;
};

