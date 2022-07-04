#include "stdafx.h"
#include "Entity.h"

std::vector<float> Entity::getDamageStats()
{
	// Returns Vector: 0 = Attack multi, 1 = attack Max, 2 = CritChance

	float attackMulti = BASE_ATTACK_MULTIPLIER + (LEVEL_ATT_MULT * m_attack);
	float attackMax = BASE_ATTACK_MAX + (LEVEL_ATT_MAX * m_attack);
	float critChance = CRITICAL_HIT_CHANCE + (LEVEL_CRIT_CHANCE * m_attack);
	std::vector<float> DamVec = { attackMulti, attackMax, critChance };

	return DamVec;
}

std::vector<float> Entity::getDefenseStats()
{
	// Returns Vector: 0 = multi, 1 = Max, 2 = Chance
	float defenseMulti = BASE_DEFENSE_MUTLIPLIER + (LEVEL_DEF_MULT * m_defense);
	float defenseMax = BASE_DEFENSE_DAMAGE_MAX + (LEVEL_DEF_MAX * m_defense);
	float reflectChance = REFLECT_DAMAGE_CHANCE + (LEVEL_REFLECT_CHANCE * m_defense);
	std::vector<float> DamVec = { defenseMulti, defenseMax, reflectChance };

	return DamVec;
}

up_entity_t createEntity(std::string n, float h, int a, int d)
{
	up_entity_t entityPtr = std::make_unique<Entity>(n, h, a, d);
	return entityPtr;
}

Entity* simulate(int sims, Entity* ent1, Entity* ent2, bool printAllMessages, bool PrintImportantMessages)
{
	int ent1Score{ 0 };
	int ent2Score{ 0 };
	int drawScore{ 0 };

	for (int i{ 0 }; i < sims; i++)
	{
		std::array<Entity*, 2> winLoss = fight(ent1, ent2, printAllMessages, PrintImportantMessages);
		if (winLoss[0] == ent1)
			ent1Score++;
		else if (winLoss[0] == ent2)
			ent2Score++;
		else if (winLoss[0] == nullptr)
			drawScore++;
		else
			std::cerr << "Should never happen";
	}
	printf("\n\n|\t%s Score: %i\t\t%s Score: %i\t\tDraws: %i\t|\n\n",ent1->getName().c_str(), ent1Score, ent2->getName().c_str(), ent2Score, drawScore);
	if (ent1Score > ent2Score)
		printf("%s is the champion! He will be moving to the next round!", ent1->getName().c_str(), sims, ent2->getName().c_str());
	else
		printf("%s is the champion! He will be moving to the next round!", ent2->getName().c_str(), sims, ent1->getName().c_str());

	return ent1Score > ent2Score ? ent1 : ent2;
}

std::array<Entity*, 2> fight(Entity* ent1, Entity* ent2, bool printAllMessages, bool printImportantMessages)
{
	// Make two entities fight. First person starts randomly. Returns array of entities: index[0] = winner, index[1] = loser.
	
	// Switch to make it 50% for who starts first. First person obviously has advantage.
	ent1->setHealth();
	ent1->setAlive();
	ent2->setHealth();
	ent2->setAlive();

	switch (rng() % 2)
	{
	case 0:
		// ent1 starts first.
		while(ent1->_checkIfAlive() && ent2->_checkIfAlive())
		{
			ent1->_attack(ent2,printAllMessages, printImportantMessages);
			if (ent2->_checkIfAlive())
				ent2->_attack(ent1, printAllMessages, printImportantMessages);
		}
		break;
	case 1:
		// ent2 starts first.
		while (ent1->_checkIfAlive() && ent2->_checkIfAlive())
		{
			ent2->_attack(ent1, printAllMessages, printImportantMessages);
			if (ent1->_checkIfAlive())
				ent1->_attack(ent2, printAllMessages, printImportantMessages);
		}
		break;
	}
	if (ent1->_checkIfAlive())
	{
		std::array<Entity*, 2> WinLossVec = { ent1, ent2 };
		printf("\n%s has defeated %s in battle!\n", ent1->getName().c_str(), ent2->getName().c_str());
		return WinLossVec;
	}
	else if (ent2->_checkIfAlive())
	{
		std::array<Entity*, 2> WinLossVec = { ent2, ent1 };
		printf("\n%s has defeated %s in battle!\n", ent2->getName().c_str(), ent1->getName().c_str());
		return WinLossVec;
	}
	else
	{
		printf("\nEveryone has died in battle\nWar never changes.\n");
		std::array<Entity*, 2> WinLossVec = { nullptr };
	}

}

//void Entity::EntityFightAI(Entity* defender)
//{
//	// Called by object to attack the other entity. Will use decision structure to decide if to attack or stay back and heal or use ability if implemented.
//	while(this->_checkIfAlive() && defender->_checkIfAlive())
//	{
//		this->_attack(defender, true, true);
//		if (defender->_checkIfAlive())
//			defender->_attack(this, true, true);
//	}
//}

void Entity::_attack(Entity* defender, bool printAllMessages, bool printImportantMessages)
{
	// Helper function for attacking used in AI
	std::vector<float> attackerStats = this->getDamageStats();
	std::vector<float> defenderStats = defender->getDefenseStats();
	
	int firstAttackerDamage = rng() % (int)attackerStats[1];
	int firstDefenderDamage = rng() % (int)defenderStats[1];

	float secondAttackerDamage =  (float)firstAttackerDamage * attackerStats[0];
	float secondDefenderDamage= (float)firstDefenderDamage * defenderStats[0];

	if(printAllMessages)
		printf("\n%s is attacking %s. ", this->m_name.c_str(), defender->m_name.c_str());

	if(rng() % 10000 < (int)(attackerStats[2] * 1000))
		// If attacker critical hit
	{
		secondAttackerDamage *= 1 + CRITICAL_HIT_DAMAGE_MULTI;
		defender->m_cur_health -= secondAttackerDamage;
		defender->m_isAlive = defender->_checkIfAlive();
		if(printImportantMessages)
			printf("\n%s critically strikes %s for %.0f damage!\nHe takes no damage in the masterful attack.\n", this->m_name.c_str(), defender->m_name.c_str(), secondAttackerDamage );
	}
	else if (rng() % 10000 < (int)(defenderStats[2] * 1000))
		// If defender reflect damage
	{
		float defenderTotalDamage = secondDefenderDamage + secondAttackerDamage * REFLECT_DAMAGE_MULTI;
		this->m_cur_health -= defenderTotalDamage;
		this->m_isAlive = this->_checkIfAlive();
		if (printImportantMessages)
			printf("\n%s parries %s dealing %.0f damage and reflecting %.0f damage back to the attacker!\nHe takes no damage in the masterful defense.\n", defender->m_name.c_str(), this->m_name.c_str(), secondDefenderDamage, secondAttackerDamage * REFLECT_DAMAGE_MULTI);
	}
	else
	{
		// If no critical hits or reflects.
		this->m_cur_health -= secondDefenderDamage + 1;
		defender->m_cur_health -= secondAttackerDamage + 1;
		defender->m_isAlive = defender->_checkIfAlive();
		this->m_isAlive = this->_checkIfAlive();
		if(printAllMessages)
			printf("\n%s attacks %s for %.0f damage.\n%s takes %.0f damage in the attack.\n", this->m_name.c_str(), defender->m_name.c_str(), secondAttackerDamage, this->m_name.c_str() ,secondDefenderDamage);
	}
}

bool Entity::_checkIfAlive()
{
	// Return true if alive, false if dead
	if (this->m_cur_health <= 0.0)
		m_isAlive = false;

	if (!this->m_isAlive)
		return false;

	if(this->m_isAlive)
		return true;
}

inline std::string Entity::getName()
{
	return m_name;
}

void Entity::setHealth()
{
	m_cur_health = m_max_health;
}

void Entity::setAlive()
{
	m_isAlive = true;
}