#include "stdafx.h"
#include "Entity.h"

up_entity_t createEntity(std::string n, float h, int a, int d)
{
	up_entity_t entityPtr = std::make_unique<Entity>(n, h, a, d);
	return entityPtr;
}

//std::vector<up_entity_t> fight(up_entity_t ent1, up_entity_t ent2)
//{
//	// Make two entities fight. First person starts randomly. Returns vector of entities: index[0] = winner, index[1] = loser.
//}
//
//void Entity::EntityFightAI(up_entity_t defender)
//{
//	// Called by object to attack the other entity. Will use decision structure to decide if to attack or stay back and heal or use ability if implemented.
//}
//
//void Entity::_attack(up_entity_t defender)
//{
//	// Helper function for attacking used in AI
//
//}
