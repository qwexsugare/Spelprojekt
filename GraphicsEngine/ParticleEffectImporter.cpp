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
		else if(strcmp(key, "Scale") == 0)
		{
			float scale;
			sscanf(buff, "Scale %f", &scale);
			pe->scale = scale;
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
		else if(strcmp(key, "EmitRate") == 0)
		{
			float emitRate;
			sscanf(buff, "EmitRate %f", &emitRate);
			pe->emitRate = emitRate;
		}
		else if(strcmp(key, "LifeTime") == 0)
		{
			float lifeTime;
			sscanf(buff, "LifeTime %f", &lifeTime);
			pe->lifeTime = lifeTime;
		}
		else if(strcmp(key, "Speed") == 0)
		{
			float speed;
			sscanf(buff, "Speed %f", &speed);
			pe->speed = speed;
		}
		else if(strcmp(key, "Offset") == 0)
		{
			float offset;
			sscanf(buff, "Offset %f", &offset);
			pe->offset = offset;
		}
	}

	stream.close();
	
	return pe;
}