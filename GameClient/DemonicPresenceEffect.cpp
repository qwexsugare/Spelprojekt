#include "DemonicPresenceEffect.h"
#include "EntityHandler.h"

const float DemonicPresenceEffect::ATTACK_SPEED_BOOST = 0.75f;
const float DemonicPresenceEffect::MOVEMENT_SPEED_BOOST = 2.0f;//0.5f;
vector<unsigned int> DemonicPresenceEffect::m_affectedGuys;

DemonicPresenceEffect::DemonicPresenceEffect(unsigned int _caster)
{
	m_caster = _caster;

	this->m_obb = NULL;
	FLOAT3 pos = EntityHandler::getServerEntity(_caster)->getPosition();
	this->m_bs = new BoundingSphere(XMFLOAT3(pos.x, 0.0f, pos.z), AOE);
	m_visible = false;
	m_timer = 0.0f;
	m_type = OtherType;
	
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
			if(heroes[i]->contains(*m_bs) != ContainmentType::DISJOINT)
			{
				m_affectedGuys.push_back(heroes[i]->getId());
				((UnitEntity*)heroes.at(i))->alterMovementSpeed(MOVEMENT_SPEED_BOOST);
				((UnitEntity*)heroes.at(i))->alterAttackSpeed(ATTACK_SPEED_BOOST);
				this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::DEMONIC_PRESENCE, 0, heroes[i]->getId(), heroes[i]->getPosition()));
			}
		}
	}
}

DemonicPresenceEffect::~DemonicPresenceEffect()
{
	for(int i = 0; i < m_affectedGuys.size(); i++)
	{
		ServerEntity* se = EntityHandler::getServerEntity(m_affectedGuys[i]);
		if(se)
		{
			((UnitEntity*)se)->alterMovementSpeed(-MOVEMENT_SPEED_BOOST);
			((UnitEntity*)se)->alterAttackSpeed(-ATTACK_SPEED_BOOST);
		}
	}
}

void DemonicPresenceEffect::update(float _dt)
{
	ServerEntity* caster = EntityHandler::getServerEntity(m_caster);

	if(caster)
	{
		m_timer += _dt;

		// If the spell duration has expired, remove all affected dudes and buffs.
		if(m_timer > LIFETIME)
		{
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
		}
		else
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
						this->m_messageQueue->pushOutgoingMessage(new RemoveActionTargetMessage(Skill::DEMONIC_PRESENCE, 0, se->getId()));
					}
					// Else the affected guys is still alive and might have escaped the aura area and needs to be taken down!
					else if((caster->getPosition()-se->getPosition()).length() > AOE)
					{
						((UnitEntity*)se)->alterMovementSpeed(-MOVEMENT_SPEED_BOOST);
						((UnitEntity*)se)->alterAttackSpeed(-ATTACK_SPEED_BOOST);
						m_affectedGuys.erase(m_affectedGuys.begin()+i);
						i--;
						this->m_messageQueue->pushOutgoingMessage(new RemoveActionTargetMessage(Skill::DEMONIC_PRESENCE, 0, se->getId()));
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
						if(heroes[i]->contains(*m_bs) != ContainmentType::DISJOINT)
						{
							m_affectedGuys.push_back(heroes[i]->getId());
							((UnitEntity*)heroes.at(i))->alterMovementSpeed(MOVEMENT_SPEED_BOOST);
							((UnitEntity*)heroes.at(i))->alterAttackSpeed(ATTACK_SPEED_BOOST);
							this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::DEMONIC_PRESENCE, 0, heroes[i]->getId(), heroes[i]->getPosition()));
						}
					}
				}
			}
		}
	}
}