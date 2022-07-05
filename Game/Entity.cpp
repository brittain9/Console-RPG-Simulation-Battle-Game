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


up_entity_t createHuman(std::string n, float h, int a, int d, int potions)
{
	up_entity_t humanPtr = std::make_unique<Human>(n, h, a, d, potions);
	return humanPtr;
}
up_entity_t createGoblin(std::string n, float h, int a, int d, int coins)
{
	up_entity_t goblinPtr = std::make_unique<Goblin>(n, h, a, d, coins);
	return goblinPtr;
}


Entity* simulateSimulations(int sims, Entity* ent1, Entity* ent2, bool printAllMessages, bool PrintImportantMessages)
{
	if(sims > 10000)
	{
		printf("If you want to do this change the number in the function. That is over 100 Million simulations.");
		return nullptr;
	}

	int ent1Score{ 0 };
	int ent2Score{ 0 };
	int drawScore{ 0 };

	for (int i{ 0 }; i < sims; i++)
	{
		Entity* winner = simulate(sims, ent1, ent2, printAllMessages, PrintImportantMessages);
		if (winner == ent1)
			ent1Score++;
		else if (winner == ent2)
			ent2Score++;
		else
			drawScore++;
	}
	printf("\n\nIn %i sims of %i sims!\t||\t%s Score: %i\t\t%s Score: %i\t\tDraws: %i\t||\n\n", sims, sims, ent1->getName().c_str(), ent1Score, ent2->getName().c_str(), ent2Score, drawScore);
	if (ent1Score > ent2Score)
		printf("%s is the champion! He will be moving to the next round!", ent1->getName().c_str(), sims, ent2->getName().c_str());
	else
		printf("%s is the champion! He will be moving to the next round!", ent2->getName().c_str(), sims, ent1->getName().c_str());

	return ent1Score > ent2Score ? ent1 : ent2;
}

Entity* simulate(int sims, Entity* ent1, Entity* ent2, bool printAllMessages, bool printImportantMessages)
{
	int ent1Score{ 0 };
	int ent2Score{ 0 };
	int drawScore{ 0 };

	for (int i{ 0 }; i < sims; i++)
	{
		std::array<Entity*, 2> winLoss = fight(ent1, ent2, printAllMessages, printImportantMessages);
		if (winLoss[0] == ent1)
			ent1Score++;
		else if (winLoss[0] == ent2)
			ent2Score++;
		else if (winLoss[0] == nullptr)
			drawScore++;
		else
			std::cerr << "Should never happen";
	}
	if (printImportantMessages)
		printf("\n\n|\t%s Score: %i\t\t%s Score: %i\t\tDraws: %i\t|\n\n",ent1->getName().c_str(), ent1Score, ent2->getName().c_str(), ent2Score, drawScore);
	if (ent1Score > ent2Score)
		if (printImportantMessages)
			printf("%s is the champion! He will be moving to the next round!", ent1->getName().c_str(), sims, ent2->getName().c_str());
	else
		if (printImportantMessages)
			printf("%s is the champion! He will be moving to the next round!", ent2->getName().c_str(), sims, ent1->getName().c_str());

	return ent1Score > ent2Score ? ent1 : ent2;
}

std::array<Entity*, 2> fight(Entity* ent1, Entity* ent2, bool printAllMessages, bool printImportantMessages)
{
	// Make two entities fight. First person starts randomly. Returns array of entities: index[0] = winner, index[1] = loser.
	
	// Switch to make it 50% for who starts first. First person obviously has advantage.
	ent1->setMaxHealth();
	ent1->setAlive();
	ent2->setMaxHealth();
	ent2->setAlive();

	switch (rng() % 2)
	{
	case 0:
		// ent1 starts first.
		while(ent1->_checkIfAlive() && ent2->_checkIfAlive())
		{
			ent1->EntityFightAI(ent2, printAllMessages, printImportantMessages);
			if(ent2->_checkIfAlive())
				// if second attacker isnt already dead.
				ent2->EntityFightAI(ent1, printAllMessages, printImportantMessages);
		}
		break;
	case 1:
		// ent2 starts first.
		while (ent1->_checkIfAlive() && ent2->_checkIfAlive())
		{
			ent2->EntityFightAI(ent1, printAllMessages, printImportantMessages);
			if (ent1->_checkIfAlive())
				ent1->EntityFightAI(ent2, printAllMessages, printImportantMessages);
		}
		break;
	}

	if (ent1->_checkIfAlive())
	{
		std::array<Entity*, 2> WinLossVec = { ent1, ent2 };
		if(printImportantMessages)
			printf("\n%s has defeated %s in battle!\n", ent1->getName().c_str(), ent2->getName().c_str());
		return WinLossVec;
	}
	else if (ent2->_checkIfAlive())
	{
		std::array<Entity*, 2> WinLossVec = { ent2, ent1 };
		if (printImportantMessages)
			printf("\n%s has defeated %s in battle!\n", ent2->getName().c_str(), ent1->getName().c_str());
		return WinLossVec;
	}
	else
	{
		if (printImportantMessages)
			printf("\nEveryone has died in battle\nWar never changes.\n");
		std::array<Entity*, 2> WinLossVec = { nullptr };
	}

}

void Human::EntityFightAI(Entity* defender, bool printAllMessages, bool printImportantMessages)
{
	// Called by object to attack the other entity. Will use decision structure to decide if to attack or stay back and heal or use ability if implemented.
	if (this->getCurHealth() < this->getMaxHealth() / 4 && this->getPotions() > 0 && rng() % 100 < 75)
	{
		// If current health is 1/4 max health and has potions and 75% chance
		this->setHealth(getCurHealth() + (this->getMaxHealth() * HUMAN_POTION_RATE));
		//used a potion
		this->m_healthPotions -= 1;
		if(printImportantMessages)
			printf("\n%s used a health potion and healed for %.0f points. His new health is %.0f!\n", this->getName().c_str(), this->getMaxHealth() * HUMAN_POTION_RATE, this->getCurHealth());

	}else if (this->getCurHealth() < SIT_BACK_HEALTH_MAX_ALL * this->getMaxHealth() && rng() % 100 < (int)(HUMAN_SIT_BACK_RATE * 100) )
	{
		int healAmount = rng() % SIT_BACK_HEAL_AMOUNT_MAX;
		this->setHealth(getCurHealth() + (float)healAmount);
		if(printAllMessages)
			printf("\n%s has decided to sit back and heal. They healed for %.0f health!\n", this->getName().c_str(), (float)healAmount);
	}
	else
		this->_attack(defender, printAllMessages, printImportantMessages);
}

void Goblin::EntityFightAI(Entity* defender, bool printAllMessages, bool printImportantMessages)
{
	// Called by object to attack the other entity. Will use decision structure to decide if to attack or stay back and heal or use ability if implemented.

	if (this->getCoins() > 0 && rng() % 100 < (int)(GOBLIN_BRIBE_RATE * 100))
	{
		// If has coins and Goblin Bribe Rate
		if (printImportantMessages)
			printf("\n%s is attempting to bribe %s. He offers him a shiny coin of solid gold!\n", this->getName().c_str(), defender->getName().c_str());
		if(rng() % 100 < (int)(GOBLIN_BRIBE_CHANCE * 100))
		{
			// If successful bribe
			// Make goblin win
			defender->setHealth(0);
			defender->_checkIfAlive();
			printf("\n%s has taken the gold coin and ran away. %s wins!\n", defender->getName().c_str(), this->getName().c_str());
		}
		// used a coin
		this->m_goldCoin -= 1;
	}
	else if (this->getCurHealth() < SIT_BACK_HEALTH_MAX_ALL * this->getMaxHealth() && rng() % 100 < (int)(GOBLIN_SIT_BACK_RATE * 100))
	{
		int healAmount = rng() % SIT_BACK_HEAL_AMOUNT_MAX;
		this->setHealth(getCurHealth() + (float)healAmount);
		if (printAllMessages)
			printf("\n%s has decided to sit back and heal. They healed for %.0f health!\n", this->getName().c_str(), (float)healAmount);
	}
	else
		this->_attack(defender, printAllMessages, printImportantMessages);

}

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
			printf("%s critically strikes %s for %.0f damage!\nHe takes no damage in the masterful attack.\n", this->m_name.c_str(), defender->m_name.c_str(), secondAttackerDamage );
	}
	else if (rng() % 10000 < (int)(defenderStats[2] * 1000))
		// If defender reflect damage
	{
		float defenderTotalDamage = secondDefenderDamage + secondAttackerDamage * REFLECT_DAMAGE_MULTI;
		this->m_cur_health -= defenderTotalDamage;
		this->m_isAlive = this->_checkIfAlive();
		if (printImportantMessages)
			printf("%s parries %s dealing %.0f damage and reflecting %.0f damage back to the attacker!\nHe takes no damage in the masterful defense.\n", defender->m_name.c_str(), this->m_name.c_str(), secondDefenderDamage, secondAttackerDamage * REFLECT_DAMAGE_MULTI);
	}
	else
	{
		// If no critical hits or reflects.
		this->m_cur_health -= secondDefenderDamage + 1;
		defender->m_cur_health -= secondAttackerDamage + 1;
		defender->m_isAlive = defender->_checkIfAlive();
		this->m_isAlive = this->_checkIfAlive();
		if(printAllMessages)
			printf("%s attacks %s for %.0f damage.\n%s takes %.0f damage in the attack.\n", this->m_name.c_str(), defender->m_name.c_str(), secondAttackerDamage, this->m_name.c_str() ,secondDefenderDamage);
	}
}

bool Entity::_checkIfAlive()
{
	// Return true if alive, false if dead
	if (this->m_cur_health <= 0.0)
		m_isAlive = false;

	if (!this->m_isAlive)
		return false;

	return true;
}


inline void Entity::setMaxHealth()
{
	m_cur_health = m_max_health;
}

inline void Entity::setHealth(float health)
{
	m_cur_health = health;
}


inline void Entity::setAlive()
{
	m_isAlive = true;
}