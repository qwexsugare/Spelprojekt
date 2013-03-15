#pragma once

#include "Graphics.h"
#include "ModelIdHolder.h"

class Room
{
private:
	Model* m_room;
	Model* m_character;
	Model* m_window;
	Model* m_door;
	PointLight* m_frontLight;
	PointLight* m_inLight;
	PointLight* m_backLight;
	ModelIdHolder m_modelIdHolder;
	float m_width;
	ParticleEngine* m_fire;
public:
	Room(int _index, int _charId, string _roomDiffuse, string _roomGlow, FLOAT3 _pos, float roomWidth);
	Room(int _index, string _roomDiffuse, FLOAT3 _pos, float _roomWidth);
	~Room();
	float getWidth(){return m_width;}
	Model* getRoom(){return this->m_room;}
	Model* getCharacter(){return this->m_character;}
	Model* getDoor(){return this->m_door;}
};