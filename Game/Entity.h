#pragma once
#include <string>
#include <iostream>

class Entity;

typedef std::unique_ptr<Entity> up_entity_t;

class Entity
{
	std::string m_name;
	bool m_isAlive = true;
	float m_max_health;
	float m_cur_health;
	int m_attack;
	int m_defense;
public:
	Entity(std::string n, float h, int a, int d) : m_name(n), m_max_health(h), m_cur_health(h), m_attack(a), m_defense(d)
	{
		std::cout << "Entity Acquired\n";
	}
	~Entity()
	{
		std::cout << "\nEntity Destroyed";
	}

	std::vector<float> getDamageStats();
	std::vector<float> getDefenseStats();

	void _attack(Entity* defender, bool printAllMessages, bool printImportantMessages);
	bool _checkIfAlive();
	inline std::string getName();
	//virtual void EntityFightAI(Entity* defender);

	void setHealth();

	void setAlive();


	

	
};

up_entity_t createEntity(std::string n, float h, int a, int d);

std::array<Entity*, 2> fight(Entity* ent1, Entity* ent2, bool printAllMessages, bool printImportantMessages);

Entity* simulate(int sims, Entity* ent1, Entity* ent2, bool printAllMessages = true, bool PrintImportantMessages = true);