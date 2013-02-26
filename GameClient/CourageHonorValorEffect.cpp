#include "CourageHonorValorEffect.h"
#include "EntityHandler.h"

const float CourageHonorValorEffect::MOVEMENT_SPEED = 0.2f;
const float CourageHonorValorEffect::PHYSICAL_RESISTANCE = -0.15f;
const float CourageHonorValorEffect::MENTAL_DAMAGE = 100.0f;
vector<unsigned int> CourageHonorValorEffect::m_affectedGuys;

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
				if(heroes[i]->getId() == m_affectedGuys[j])
				{
					alreadyAffected = true;
					j = m_affectedGuys.size();
				}
			}

			if(!alreadyAffected)
			{
				if((caster->getPosition()-heroes[i]->getPosition()).length() <= AOE)
				{
					m_affectedGuys.push_back(heroes[i]->getId());
					((UnitEntity*)heroes.at(i))->alterMovementSpeed(MOVEMENT_SPEED);
					((UnitEntity*)heroes.at(i))->alterPhysicalResistance(PHYSICAL_RESISTANCE);
					((UnitEntity*)heroes.at(i))->alterMentalDamage(MENTAL_DAMAGE);
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
			if(m_affectedGuys[i] != m_caster)
			{
				ServerEntity* se = EntityHandler::getServerEntity(m_affectedGuys[i]);
				// Check if the affected guy has died recently then remove it.
				if(!se)
				{
					m_affectedGuys.erase(m_affectedGuys.begin()+i);
					i--;
					this->m_messageQueue->pushOutgoingMessage(new RemoveActionTargetMessage(Skill::COURAGE_HONOR_VALOR, 0, se->getId()));
				}
				// Else the affected guys is still alive and might have escaped the aura area and needs to be taken down!
				else if((caster->getPosition()-se->getPosition()).length() > AOE)
				{
					((UnitEntity*)se)->alterMovementSpeed(-MOVEMENT_SPEED);
					((UnitEntity*)se)->alterPhysicalResistance(-PHYSICAL_RESISTANCE);
					((UnitEntity*)se)->alterMentalDamage(-MENTAL_DAMAGE);
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
					if(heroes[i]->getId() == m_affectedGuys[j])
					{
						alreadyAffected = true;
						j = m_affectedGuys.size();
					}
				}

				if(!alreadyAffected)
				{
					if((caster->getPosition()-heroes[i]->getPosition()).length() <= AOE)
					{
						m_affectedGuys.push_back(heroes[i]->getId());
						((UnitEntity*)heroes.at(i))->alterMovementSpeed(MOVEMENT_SPEED);
						((UnitEntity*)heroes.at(i))->alterPhysicalResistance(PHYSICAL_RESISTANCE);
						((UnitEntity*)heroes.at(i))->alterMentalDamage(MENTAL_DAMAGE);
						this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::COURAGE_HONOR_VALOR, 0, heroes[i]->getId(), heroes[i]->getPosition()));
					}
				}
			}
		}
	}
}