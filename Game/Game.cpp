#include "stdafx.h"
#include "Entity.h"

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


template <typename T>
up_entity_t createPlayer(int points, float baseHealth, int baseAttack, int baseDefense)
{
	// Takes user input to create a custom player and returns unique_pointer to the dynamically allocated entity.
	// Apparently templates cannot be put in seperate CPP files :(
	string name{};
	int healthUpgrade{ 0 };
	int attackUpgrade{ 0 };
	int defenseUpgrade{ 0 };

	const int initialPoints{ points };
	bool loop{ true };

	while (loop)
	{
		points = initialPoints;

		name = getInput<string>("\nPlease enter your name: ");
		printf("\n\tName: %s | Health: %.0f | Attack: %i | Defense: %i\n\nYou have %i points to upgrade your player. 1 point = +1 attack, +1 defense, or +10 health\n", name.c_str(), baseHealth, baseAttack, baseDefense, points);

		while (true)
		{
			points = initialPoints;

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
	up_entity_t playerPtr = std::make_unique<T>(name, baseHealth + 10.0f * healthUpgrade, baseAttack + attackUpgrade, baseDefense + defenseUpgrade);
	return playerPtr;
}


void printWelcome()
{
	printf("Welcome to Alex's Console RPG Battle Simulation Game!\n ");
	while (true)
	{
		int option = getInput<int>("\nEnter 1 for more information.\nEnter 2 to begin : ");
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
	//printWelcome();
	//up_entity_t player = createPlayer<Entity>(10, 100, 1, 1);
	//up_entity_t entity1 = createEntity("Alex", 120, 3, 6);
	//up_entity_t entity2 = createEntity("Alexander", 150, 4, 3);

	Timer t;

	try
	{
		testRandomNumberGenerationPercent(1000000, 100, false);
	}
	catch (const char* error)
	{
		std::cerr << "Error(" << error << ")";
	}

	cout << "\nTime elapsed: " << t.elapsed();
	
	return 0;
}
