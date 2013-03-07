#pragma once

class AmbientSoundsManager
{
private:
	static const int THUNDER_SOUNDS_DELAY = 45;
	static const int NR_OF_THUNDER_SOUNDS = 5;
	int m_thunderSounds[NR_OF_THUNDER_SOUNDS];
	float m_thunderSoundsTimer;
	
	static const int SCREAM_SOUNDS_DELAY = 30;
	static const int SCREAM_SOUNDS_PLAY_CHANCE = 50;
	static const int NR_OF_SCREAM_SOUNDS = 5;
	int m_screamSounds[NR_OF_SCREAM_SOUNDS];
	float m_screamSoundsTimer;

	int m_music;
public:
	AmbientSoundsManager();
	~AmbientSoundsManager();

	void update(float _dt);
};

