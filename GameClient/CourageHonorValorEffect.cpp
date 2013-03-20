#include "CourageHonorValorEffect.h"
#include "EntityHandler.h"

const float CourageHonorValorEffect::MOVEMENT_SPEED_BASE = 0.05f;
const float CourageHonorValorEffect::MOVEMENT_SPEED_FACTOR = 0.01f;
const float CourageHonorValorEffect::MENTAL_RESISTANCE_FACTOR = -0.01f;
const float CourageHonorValorEffect::MENTAL_RESISTANCE_BASE = -0.05f;
const float CourageHonorValorEffect::MENTAL_DAMAGE_FACTOR = 1.5f;
const float CourageHonorValorEffect::MENTAL_DAMAGE_BASE = 4.0f;

CourageHonorValorEffect::CourageHonorValorEffect(unsigned int _caster)
{
	m_caster = _caster;

	this->m_obb = NULL;
	FLOAT3 pos = EntityHandler::getServerEntity(_caster)->getPosition();
	this->m_bs = new BoundingSphere(XMFLOAT3(0,0,0), 0.0001f);
	m_visible = false;
	m_timer = 0.0f;
	m_type = OtherType;
	
	ServerEntity* caster = EntityHandler::getServerEntity(m_caster);
	if(caster)
	{
		vector<ServerEntity*> heroes = EntityHandler::getAllHeroes();
		for(int i = 0; i < heroes.size(); i++)
		{
			bool alreadyAffected = false;
			for(int j = 0; j < m_affectedGuys.size(); j++)
			{
				if(heroes[i]->getId() == m_affectedGuys[j].id)
				{
					alreadyAffected = true;
					j = m_affectedGuys.size();
				}
			}

			if(!alreadyAffected)
			{
				if((caster->getPosition()-heroes[i]->getPosition()).length() <= AOE)
				{
					int mentalDamageChange = MENTAL_DAMAGE_BASE+((UnitEntity*)caster)->getWits()*MENTAL_DAMAGE_FACTOR;
					float movementChange = MOVEMENT_SPEED_BASE+((UnitEntity*)caster)->getWits()*MOVEMENT_SPEED_FACTOR;
					float mentalResistanceChange = MENTAL_RESISTANCE_BASE+((UnitEntity*)caster)->getWits()*MENTAL_RESISTANCE_FACTOR;
					m_affectedGuys.push_back(AffectedGuy(heroes[i]->getId(), mentalResistanceChange, movementChange, mentalDamageChange));
					((UnitEntity*)heroes.at(i))->alterMovementSpeed(movementChange);
					((UnitEntity*)heroes.at(i))->alterMentalResistance(mentalResistanceChange);
					((UnitEntity*)heroes.at(i))->alterMentalDamage(mentalDamageChange);
					this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::COURAGE_HONOR_VALOR, 0, heroes[i]->getId(), heroes[i]->getPosition()));
				}
			}
		}
	}
}

CourageHonorValorEffect::~CourageHonorValorEffect()
{

}

void CourageHonorValorEffect::update(float _dt)
{
	ServerEntity* caster = EntityHandler::getServerEntity(m_caster);

	if(caster)
	{
		// Check if any of the affected guys have died or escaped the aura area.
		for(int i = 0; i < m_affectedGuys.size(); i++)
		{
			// Dont mind the caster, he is taken care of elsewhere i hope(?).
			if(m_affectedGuys[i].id != m_caster)
			{
				ServerEntity* se = EntityHandler::getServerEntity(m_affectedGuys[i].id);
				// Check if the affected guy has died recently then remove it.
				if(!se)
				{
					m_affectedGuys.erase(m_affectedGuys.begin()+i);
					i--;
				}
				// Else the affected guys is still alive and might have escaped the aura area and needs to be taken down!
				else if((caster->getPosition()-se->getPosition()).length() > AOE)
				{
					((UnitEntity*)se)->alterMovementSpeed(-m_affectedGuys[i].movementChange);
					((UnitEntity*)se)->alterMentalResistance(-m_affectedGuys[i].mentalResistanceChange);
					((UnitEntity*)se)->alterMentalDamage(-m_affectedGuys[i].mentalDamageChange);
					m_affectedGuys.erase(m_affectedGuys.begin()+i);
					i--;
					this->m_messageQueue->pushOutgoingMessage(new RemoveActionTargetMessage(Skill::COURAGE_HONOR_VALOR, 0, se->getId()));
				}
			}
		}

		// Check if any newcomers want to join in on the oral (aural) fun.
		vector<ServerEntity*> heroes = EntityHandler::getAllHeroes();
		for(int i = 0; i < heroes.size(); i++)
		{
			if(heroes[i]->getId() != m_caster)
			{
				bool alreadyAffected = false;
				for(int j = 0; j < m_affectedGuys.size(); j++)
				{
					if(heroes[i]->getId() == m_affectedGuys[j].id)
					{
						alreadyAffected = true;
						j = m_affectedGuys.size();
					}
				}

				if(!alreadyAffected)
				{
					if((caster->getPosition()-heroes[i]->getPosition()).length() <= AOE)
					{
						int mentalDamageChange = MENTAL_DAMAGE_BASE+((UnitEntity*)caster)->getWits()*MENTAL_DAMAGE_FACTOR;
						float movementChange = MOVEMENT_SPEED_BASE+((UnitEntity*)caster)->getWits()*MOVEMENT_SPEED_FACTOR;
						float mentalResistanceChange = MENTAL_RESISTANCE_BASE+((UnitEntity*)caster)->getWits()*MENTAL_RESISTANCE_FACTOR;
						m_affectedGuys.push_back(AffectedGuy(heroes[i]->getId(), mentalResistanceChange, movementChange, mentalDamageChange));
						((UnitEntity*)heroes.at(i))->alterMovementSpeed(movementChange);
						((UnitEntity*)heroes.at(i))->alterMentalResistance(mentalResistanceChange);
						((UnitEntity*)heroes.at(i))->alterMentalDamage(mentalDamageChange);
						this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::COURAGE_HONOR_VALOR, 0, heroes[i]->getId(), heroes[i]->getPosition()));
					}
				}
			}
		}
	}
}