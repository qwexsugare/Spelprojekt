#include "AmbientSoundsManager.h"
#include "SoundWrapper.h"
#include "MyAlgorithms.h"

AmbientSoundsManager::AmbientSoundsManager()
{
	m_thunderSounds[0] = createSoundHandle("ambient/thunder0.wav", false, false);
	m_thunderSounds[1] = createSoundHandle("ambient/thunder1.wav", false, false);
	m_thunderSounds[2] = createSoundHandle("ambient/thunder2.wav", false, false);
	m_thunderSounds[3] = createSoundHandle("ambient/thunder3.wav", false, false);
	m_thunderSounds[4] = createSoundHandle("ambient/thunder4.wav", false, false);
	m_thunderSoundsTimer = THUNDER_SOUNDS_DELAY;
	
	m_screamSounds[0] = createSoundHandle("ambient/CPUScream0.wav", false, false);
	m_screamSounds[1] = createSoundHandle("ambient/CPUScream1.wav", false, false);
	m_screamSounds[2] = createSoundHandle("ambient/scream0.wav", false, false);
	m_screamSounds[3] = createSoundHandle("ambient/scream1.wav", false, false);
	m_screamSounds[4] = createSoundHandle("ambient/scream2.wav", false, false);
	m_screamSoundsTimer = SCREAM_SOUNDS_DELAY;
}

AmbientSoundsManager::~AmbientSoundsManager()
{
	for(int i = 0; i < NR_OF_THUNDER_SOUNDS; i++)
	{
		stopSound(m_thunderSounds[i]);
		deactivateSound(m_thunderSounds[i]);
	}
	for(int i = 0; i < NR_OF_SCREAM_SOUNDS; i++)
	{
		stopSound(m_screamSounds[i]);
		deactivateSound(m_screamSounds[i]);
	}
}

void AmbientSoundsManager::update(float _dt)
{
	m_thunderSoundsTimer = max(m_thunderSoundsTimer-_dt, 0.0f);
	if(m_thunderSoundsTimer == 0.0f)
	{
		playSound(m_thunderSounds[random(0, NR_OF_THUNDER_SOUNDS-1)]);
		m_thunderSoundsTimer = THUNDER_SOUNDS_DELAY;
	}
	
	m_screamSoundsTimer = max(m_screamSoundsTimer-_dt, 0.0f);
	if(m_screamSoundsTimer == 0.0f)
	{
		if(random(1, 100) <= SCREAM_SOUNDS_PLAY_CHANCE)
			playSound(m_screamSounds[random(0, NR_OF_SCREAM_SOUNDS-1)]);
		m_screamSoundsTimer = SCREAM_SOUNDS_DELAY;
	}
}