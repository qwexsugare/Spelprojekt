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

	bool TextureLowIsDown();
	bool TextureMediumIsDown();
	bool TextureHighIsDown();

	bool ShadowmapOFFIsDown();
	bool ShadowmapLOWIsDown();
	bool ShadowmapHIGHIsDown();

	bool EasyIsDown();
	bool NormalIsDown();
	bool HardIsDown();

	int GetValueContrast();
	int GetValueBrigtness();
private:
	Slider m_soundVolumeSlider;
	Slider m_musicVolumeSlider;
	Slider m_speechVolumeSlider;
	int m_Contrast,
		m_Brigtness,
		m_SoundVolume,
		m_MusicVolume,
		m_LevelMode,
		m_shadowmap,
		m_textureQuality;
	bool m_windowed,
		 m_DiffuseMode,
		 m_EmilMode,
		 m_SSAO;
	string m_graphicstext;
};

