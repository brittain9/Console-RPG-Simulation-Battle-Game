#include "stdafx.h"
#include "Entity.h"

// Templates have to be in Main.cpp for ease

// Declarations, definitions at bottom
template <typename T>
T getInput(std::string message);

template<typename T>
up_entity_t createEntity(std::string n, float h, int a, int d, int ability);

up_entity_t createPlayer(float baseHealth, int baseAttack, int baseDefense);

void printWelcome()
{
	printf("Welcome to Alex's Console RPG Battle Simulation Game!\n ");
	while (true)
	{
		int option = getInput<int>("\nEnter 1 for more information.\nEnter 2 to begin: ");
		switch (option)
		{
		case 1:
			printf("\nmore information\n ");
			continue;

		case 2:
			break;
		default:
			printf("\nPlease enter either 1 for more information or 2 to begin: ");
		}
		break;
	}
}

int main()
{
	Timer t;
	printWelcome();
	up_entity_t player = createPlayer( 200, 1, 1);
	up_entity_t ent1 = createEntity<Human>("Humano", 250,3, 2,2);
	//up_entity_t ent2 = createEntity<Goblin>("Goblino", 200, 5, 5, 3);
	simulateSimulations(100, ent1.get(),	player.get(), false, true);


	std::cout << "\n\n\t" << t.elapsed();
	return 0;
}

template<typename T>
T getInput(std::string message)
{
	while (true)
	{
		printf("%s", message.c_str());
		T returning;
		cin >> returning;
		if (cin.fail())
		{
			printf("\nFailed to get input.\n");
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return returning;
	}

}

template<typename T>
up_entity_t createEntity(std::string n, float h, int a, int d, int ability)
{
	up_entity_t entityPtr = std::make_unique<T>(n, h, a, d, ability);
	return entityPtr;
}


up_entity_t createPlayer(float baseHealth, int baseAttack, int baseDefense)
{
	// Takes user input to create a custom player and returns unique_pointer to the dynamically allocated entity.

	int entityType = getInput<int>("Choose your entity type:\n0 for human.\n1 for goblin\nEntity Type: ");

	string name{};
	int healthUpgrade{ 0 };
	int attackUpgrade{ 0 };
	int defenseUpgrade{ 0 };

	bool loop{ true };

	while (loop)
	{

		printf("\nEnter your champions name: ");
		std::getline(cin, name);
		printf("\n\tName: %s | Health: %.0f | Attack: %i | Defense: %i\n\nYou have %i points to upgrade your player. 1 point = +1 attack, +1 defense, or +10 health\n", name.c_str(), baseHealth, baseAttack, baseDefense, MAX_POINTS);

		while (true)
		{
			int points = MAX_POINTS;

			healthUpgrade = getInput<int>("\nEnter the points to spend on health: ");
			if (healthUpgrade > points)
			{
				printf("\nYou spent too many points!\n");
				continue;
			}

			int pointsBuf1 = points - healthUpgrade;
			while (pointsBuf1 > 0)
			{
				points = pointsBuf1;
				printf("\nPoints Remaining: %i\n", points);
				attackUpgrade = getInput<int>("\nEnter the points to spend on attack: ");
				if (attackUpgrade > points)
				{
					printf("\nYou spent too many points!\n");
					continue;
				}
				int pointsBuf2 = pointsBuf1 - attackUpgrade;

				while (pointsBuf2 > 0)
				{
					points = pointsBuf2;
					printf("\nPoints Remaining: %i\n", points);
					defenseUpgrade = getInput<int>("\nEnter the points to spend on defense : ");
					if (defenseUpgrade > points)
					{
						printf("\nYou spent too many points!\n");
						continue;
					}
					points -= defenseUpgrade;
					break;
				}
				break;
			}
			break;
		}
		printf("\nYou have spent all your points!\n");

		printf("\nHere is your player:\n\n\tName: %s | Health: %.0f | Attack: %i | Defense: %i\n\nWould you like to restart creation? (1 for yes, 0 to continue): ", name.c_str(), baseHealth + 10.0 * healthUpgrade, baseAttack + attackUpgrade, baseDefense + defenseUpgrade);
		cin >> loop;
	}
	switch (entityType)
	{
	case 0: // Human
	{
		up_entity_t playerHumanPtr = createEntity<Human>(name, baseHealth + 10.0f * healthUpgrade, baseAttack + attackUpgrade, baseDefense + defenseUpgrade, 1);
		return playerHumanPtr;
	}
	case 1: // Goblin
	{
		up_entity_t playerGoblinPtr = createEntity<Goblin>(name, baseHealth + 10.0f * healthUpgrade, baseAttack + attackUpgrade, baseDefense + defenseUpgrade, 1);
		return playerGoblinPtr;
	}
	default:
		printf("\n\n\tYou entered an invalid entity type which I have not handled for yet...  Abort.\n\n");
		exit(1);
	}

}

