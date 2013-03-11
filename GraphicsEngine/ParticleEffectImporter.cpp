#include "ParticleEffectImporter.h"

ParticleEffect*  ParticleEffectImporter::loadParticleEffect(string _filename)
{
	string filepath = "./particles/effects/";

	ParticleEffect* pe = new ParticleEffect();

	ifstream stream;
	stream.open(filepath +_filename+".gzp");

	if(!stream.is_open())
	{
		string eMsg = filepath + _filename + " could not be found :(";
		MessageBox(NULL, eMsg.c_str(), "Error: ParticleEffectImporter", 0);
		return NULL;
	}

	string line;
	while(!stream.eof())
	{
		char buff[1024];
		char key[100];
		stream.getline(buff, 1024);
		sscanf(buff, "%s", key);

		if(strcmp(key, "#") == 0)
		{
		}
		else if(strcmp(key, "First") == 0)
		{
			float time;
			int behavior;
			sscanf(buff, "First %i %f", &behavior, &time);
			pe->startBehavior = behavior;
			pe->startBehaviorTime = time;
		}
		else if(strcmp(key, "Second") == 0)
		{
			float time;
			int behavior;
			sscanf(buff, "Second %i %f", &behavior, &time);
			pe->behavior = behavior;
			pe->behaviorTime = time;
		}
		else if(strcmp(key, "Last") == 0)
		{
			int behavior;
			sscanf(buff, "Last %i", &behavior);
			pe->endBehavior = behavior;
		}
		else if(strcmp(key, "Textures") == 0)
		{
			bool isDone = false;
			while(!isDone)
			{
				stream.getline(buff, 1024);
				sscanf(buff, "%s", key);
				
				if(strcmp(key, "End") == 0)
				{
					isDone = true;
				}
				else
				{
					pe->textures.push_back(key);
				}
			}
		}
	}

	stream.close();
	
	return pe;
}