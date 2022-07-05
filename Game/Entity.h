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
		std::cout << "Entity Created\n";
	}
	~Entity()
	{
		std::cout << "\nEntity Deleted";
	}

	virtual const char* printClass() { return "Entity"; }

	std::vector<float> getDamageStats();
	std::vector<float> getDefenseStats();

	void _attack(Entity* defender, bool printAllMessages, bool printImportantMessages);
	bool _checkIfAlive();

	virtual void EntityFightAI(Entity* defender, bool printAllMessages, bool printImportantMessages) = 0;

	// Getters
	std::string getName() { return m_name; }
	bool getisAlive() { return m_isAlive; }
	float getCurHealth() { return m_cur_health; }
	float getMaxHealth() { return m_max_health; }
	int getAttack() { return m_attack; }
	int getDefense() { return m_defense; }

	// Setters
	inline void setMaxHealth(); // Sets Entity back to max health;
	inline void setHealth(float health);

	inline void setAlive();

};

class Human : public Entity
{
	// Has health potions that can heal them when they are below a certain health
	int m_healthPotions;
public:
	Human(std::string n, float h, int a, int d, int hPo) : Entity(n,h,a,d), m_healthPotions(hPo) {}

	const char* printClass() { return "Human"; }

	int getPotions() { return m_healthPotions; }

	void EntityFightAI(Entity* defender, bool printAllMessages, bool printImportantMessages) override;
};

class Goblin : public Entity
{
	// Uses a turn to attempt to bribe the opponent to forfeit
	int m_goldCoin;
public:
	Goblin(std::string n, float h, int a, int d, int g) : Entity(n, h, a, d),m_goldCoin(g) {}

	const char* printClass() { return "Goblin"; }

	int getCoins() { return m_goldCoin; }

	void EntityFightAI(Entity* defender, bool printAllMessages, bool printImportantMessages) override;
};

up_entity_t createHuman(std::string n, float h, int a, int d, int potions);
up_entity_t createGoblin(std::string n, float h, int a, int d, int coins);

std::array<Entity*, 2> fight(Entity* ent1, Entity* ent2, bool printAllMessages, bool printImportantMessages);

Entity* simulate(int sims, Entity* ent1, Entity* ent2, bool printAllMessages = true, bool PrintImportantMessages = true);

Entity* simulateSimulations(int sims, Entity* ent1, Entity* ent2, bool printAllMessages = true, bool PrintImportantMessages = true);