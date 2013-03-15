#include "Room.h"


Room::Room(int _index, int _charId, string _roomDiffuse, string _roomGlow, FLOAT3 _pos, float _roomWidth)
{
	float x = -1.4f;
	float y =  -0.5f;
	float z = 6;
	float inLightZ = -0.5;
	float inLightY = 2.3f;
	float frontLightZ = -1.7f;
	float frontLightY = 1.8f;
	this->m_width = _roomWidth;


	this->m_character = g_graphicsEngine->createModel(m_modelIdHolder.getModel(_charId), FLOAT3(_pos.x + (_roomWidth*_index), _pos.y, _pos.z), false, m_modelIdHolder.getTexture(_charId));
	this->m_character->setGlowIndex("");
	this->m_character->SetHat(g_graphicsEngine->getMesh(m_modelIdHolder.getHat(_charId)));
	this->m_window = g_graphicsEngine->createModel("windowGlow", FLOAT3(_pos.x + (_roomWidth*_index), _pos.y, _pos.z), false, "color");

	this->m_room = g_graphicsEngine->createModel("rum", FLOAT3(_pos.x + (_roomWidth*_index), _pos.y, _pos.z), false, m_modelIdHolder.getTexture(_charId));
	this->m_room->setGlowIndex("");
	
	this->m_door = g_graphicsEngine->createModel("Door", FLOAT3(_pos.x + (_roomWidth*_index), _pos.y, _pos.z), false, "color");
	this->m_door->getAnimation()->PlayLoop("ClosedIdle");
	
	
	

	this->m_inLight =	NULL;// g_graphicsEngine->createPointLight(FLOAT3(x + (_roomWidth * _index), y + inLightY, z - 0.5f), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 2.5f, false, false);
	this->m_frontLight = g_graphicsEngine->createPointLight(FLOAT3(x + (_roomWidth * _index), y + frontLightY, z + frontLightZ), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 3.0f, true, false);
	
	this->m_fire = g_graphicsEngine->createParticleEngine("fire", D3DXVECTOR4(_pos.x + (_roomWidth*_index) + 1.13f, _pos.y + 0.5f, _pos.z - 1.29f, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
}

Room::Room(int _index, string _roomDiffuse, FLOAT3 _pos, float _roomWidth)
{
	float x = -1.4f;
	float y =  -0.5f;
	float z = 6;
	float inLightZ = -0.5;
	float inLightY = 1.6f;
	float frontLightZ = -0.5f;
	float frontLightY = 0.5f;
	this->m_width = _roomWidth;

	this->m_backLight = NULL;
	this->m_character = NULL;
	this->m_window = NULL;

	this->m_room = g_graphicsEngine->createModel("rum", FLOAT3(_pos.x + (_roomWidth*_index), _pos.y, _pos.z), false, _roomDiffuse);	
	this->m_room->setGlowIndex("");

	this->m_door = NULL;

	this->m_inLight = NULL;// = g_graphicsEngine->createPointLight(FLOAT3(x + (_roomWidth * _index), y + inLightY, z), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, true, false);
	this->m_frontLight = NULL;// g_graphicsEngine->createPointLight(FLOAT3(x + (_roomWidth * _index), y + frontLightY, z + frontLightZ), FLOAT3(0.0f, 0.0f, 0.0f), FLOAT3(1.0f, 1.0f, 1.0f), FLOAT3(1.0f, 1.0f, 1.0f), 5.0f, false, false);
}


Room::~Room()
{
	g_graphicsEngine->removeModel(m_character);
	g_graphicsEngine->removeModel(m_window);
	g_graphicsEngine->removeModel(m_room);
	g_graphicsEngine->removeModel(m_door);
	g_graphicsEngine->removePointLight(m_frontLight);
	g_graphicsEngine->removePointLight(m_inLight);
	g_graphicsEngine->removePointLight(m_backLight);
	g_graphicsEngine->removeParticleEngine(m_fire);
}
