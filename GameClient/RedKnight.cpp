#include "RedKnight.h"

RedKnight::RedKnight(int _playerId) : Hero(Hero::RED_KNIGHT, _playerId)
{
	m_modelId = 96;
	this->increaseStrength(5);
	this->increaseAgility(2);
	this->increaseWits(1);
	this->increaseFortitude(4);
	
	this->m_skills.push_back(new SwiftAsACatPowerfulAsABoar());
	this->m_skills.push_back(new CourageHonorValor());
}

RedKnight::~RedKnight()
{

}
