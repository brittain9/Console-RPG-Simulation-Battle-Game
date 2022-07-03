#pragma once
#include <string>
#include <iostream>

class Entity;

typedef std::unique_ptr<Entity> up_entity_t;

class Entity
{
	std::string m_name;
	bool m_isAlive = true;
	float m_health;
	int m_attack;
	int m_defense;
public:
	Entity(std::string n, float h, int a, int d) : m_name(n), m_health(h), m_attack(a), m_defense(d)
	{
		std::cout << "Entity Acquired\n";
	}
	~Entity()
	{
		std::cout << "Entity Destroyed";
	}

	//virtual void EntityFightAI(up_entity_t defender);
	//virtual void _attack(up_entity_t defender);
	
};

up_entity_t createEntity(std::string n, float h, int a, int d);

//std::vector<up_entity_t> fight(up_entity_t ent1, up_entity_t ent2);
