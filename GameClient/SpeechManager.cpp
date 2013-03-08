#include "SpeechManager.h"
#include "SoundWrapper.h"

map<unsigned int, int> SpeechManager::speeches;

void SpeechManager::init()
{

}

void SpeechManager::release()
{
	vector<map<unsigned int, int>::iterator> removeIndices;

	for(map<unsigned int, int>::iterator iter = SpeechManager::speeches.begin(); iter != SpeechManager::speeches.end(); iter++)
	{
		removeIndices.push_back(iter);
	}

	for(int i = 0; i < removeIndices.size(); i++)
	{
		stopSound(removeIndices[i]->second);
		SpeechManager::speeches.erase(removeIndices[i]);
	}
}

bool SpeechManager::speak(unsigned int _id, int _sound)
{
	bool success = true;
	for(map<unsigned int, int>::iterator iter = SpeechManager::speeches.begin(); iter != SpeechManager::speeches.end(); iter++)
	{
		if(iter->first == _id)
		{
			success = false;
			iter = SpeechManager::speeches.end();
			iter--;
		}
	}

	if(success)
	{
		SpeechManager::speeches[_id] = _sound;
		playSound(_sound);
	}

	return success;
}

void SpeechManager::speakUltimate(unsigned int _id, int _sound)
{
	bool replaced = false;
	for(map<unsigned int, int>::iterator iter = SpeechManager::speeches.begin(); iter != SpeechManager::speeches.end(); iter++)
	{
		if(iter->first == _id)
		{
			stopSound(iter->second);
			iter->second = _sound;
			iter = SpeechManager::speeches.end();
			iter--;
			replaced = true;
		}
	}

	if(!replaced)
	{
		SpeechManager::speeches[_id] = _sound;
	}
	
	playSound(_sound);
}

void SpeechManager::update()
{
	vector<map<unsigned int, int>::iterator> removeIndices;

	for(map<unsigned int, int>::iterator iter = SpeechManager::speeches.begin(); iter != SpeechManager::speeches.end(); iter++)
	{
		if(!isSoundPlaying(iter->second))
		{
			removeIndices.push_back(iter);
		}
	}

	for(int i = 0; i < removeIndices.size(); i++)
	{
		SpeechManager::speeches.erase(removeIndices[i]);
	}
}