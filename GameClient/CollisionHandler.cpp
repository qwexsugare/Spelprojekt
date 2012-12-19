#include "CollisionHandler.h"

CollisionHandler::CollisionHandler()
{

}

CollisionHandler::~CollisionHandler()
{

}

void CollisionHandler::addCollision(ServerEntity *_ent1, ServerEntity *_ent2)
{
	CollisionMessage* newMsg1 = new CollisionMessage();
	newMsg1->type = Message::Collision;
	newMsg1->reciverId = _ent1->getMessageQueue()->getId();
	newMsg1->affectedDudeId = _ent2->getId();
	this->m_myMessages->pushOutgoingMessage(newMsg1);

	CollisionMessage* newMsg2 = new CollisionMessage();
	newMsg2->type = Message::Collision;
	newMsg2->reciverId = _ent2->getMessageQueue()->getId();
	this->m_myMessages->pushOutgoingMessage(newMsg2);
}

void CollisionHandler::update()
{
	vector<ServerEntity*> ents = EntityHandler::getEntities();
	for(int i = 0; i < ents.size(); i++)
	{
		for(int j = i+1; j < ents.size(); j++)
		{
			// If the first entity has a bounding sphere, collide the second entity with it
			if(ents[i]->getBoundingSphere())
			{
				// If the second entity has a bounding sphere, collide the first entity with it
				if(ents[j]->getBoundingSphere())
				{
					if(ents[i]->getBoundingSphere()->Intersects(*ents[j]->getBoundingSphere()) || ents[i]->getBoundingSphere()->Contains(*ents[j]->getBoundingSphere()))
					{
						this->addCollision(ents[i], ents[j]);
					}
				}
				// If the second entity has a bounding oriented box, collide the first entity with it
				else if(ents[j]->getObb())
				{
					if(ents[i]->getBoundingSphere()->Intersects(*ents[j]->getObb()) || ents[i]->getBoundingSphere()->Contains(*ents[j]->getObb()))
					{
						this->addCollision(*ents[i], *ents[j]);
					}
				}
			}
			// If the first entity has a bounding oriented box, collide the second entity with it
			else if(ents[i]->getObb())
			{
				// If the second entity has a bounding sphere, collide the first entity with it
				if(ents[j]->getBoundingSphere())
				{
					if(ents[i]->getObb()->Intersects(*ents[j]->getBoundingSphere()) || ents[i]->getObb()->Contains(*ents[j]->getBoundingSphere()))
					{
						this->addCollision(*ents[i], *ents[j]);
					}
				}
				// If the second entity has a bounding oriented box, collide the first entity with it
				else if(ents[j]->getObb())
				{
					if(ents[i]->getObb()->Intersects(*ents[j]->getObb()) || ents[i]->getObb()->Contains(*ents[j]->getObb()))
					{
						this->addCollision(*ents[i], *ents[j]);
					}
				}
			}
		}
	}
}

