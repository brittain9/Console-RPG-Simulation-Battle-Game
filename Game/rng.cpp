#include "stdafx.h"
#include "rng.h"

// I tested all of my random number generators for fun with my own algorithms. Each test ran had testSize = 1m. NumbersForPercentage = 1k. printNumbers = false.

// Tested the two top contenders, the first two functions,
// Function 1: 10 Million Test Cases. 23, 163 duplicates.Perfect distrubution. 48.03 seconds. 4 LINES OF CODE!
// Function 2: 10 Million Test Cases. 23,289 duplicates. Perfect distribution. 49.5 seconds.

unsigned int rng()
{
	// 238 duplicates. Very evenly distributed. 4.3 seconds. 4 lines of code. Stopping all tests. This is the one.
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 42949672957); // distribution in range MAX_UNSIGNED_INT
	return dist(rng);
}

//unsigned int rng1()
//{
//  // Top contender function. Slightly slower. Much longer and more complex.
//	// Only 226 duplicates in 1 million test size. Very evenly distributed. Both tests ran in 4.9 seconds.
//	std::random_device rd;
//
//	std::mt19937::result_type seed = rd() ^ (
//		(std::mt19937::result_type)
//		std::chrono::duration_cast<std::chrono::seconds>(
//			std::chrono::system_clock::now().time_since_epoch()
//			).count() +
//		(std::mt19937::result_type)
//		std::chrono::duration_cast<std::chrono::microseconds>(
//			std::chrono::high_resolution_clock::now().time_since_epoch()
//			).count());
//
//	std::mt19937 gen(seed);
//
//	for (unsigned long j = 0; j < 100500; ++j)
//	{
//		std::mt19937::result_type n;
//		// reject readings that would make n%6 non-uniformly distributed
//		while ((n = gen()) > std::mt19937::max() -
//			(std::mt19937::max() - 5) % 6)
//		{ /* bad value retrieved so get next one */
//		}
//
//		return n;
//	}
//}

//unsigned int rng()
//{
//	// This was my first self thought of random number generator. Cast a dynamically located object memory address unsigned int and return
//	// Garbage results. 999979 duplicates per 1 million test case. Only 21 unique numbers were generated with fairly even distribution amoung them.
//	// Really fast: .5 seconds using default constructor and destructor. The addresses on heap aren't as random I thought they would be.
//	std::unique_ptr<Entity> justWantAddress = std::make_unique<Entity>();
//	return (unsigned int)(justWantAddress.get());
//}

//unsigned int rng()	
//{
//	// This was my second iteration of random number generator. Use a dynamically located object memroy address as the seed for srand().
//	// Even worse than first one. 999980 duplicates. Only 20 unique numbers with fairly even distribution. Slower at .6 seconds.
//	std::unique_ptr<Entity> justWantAddress = std::make_unique<Entity>();
//	srand((unsigned int)justWantAddress.get());
//	return rand();
//}

//unsigned int rng()
//{
//	// Simple rng() function I found on StackOverflow just wanted to test.
//	// Feel bad for this one. It generates a random number each time the program is run. Thats it. Only 1 result in set. Fastest time though at .15 seconds.
//	srand((unsigned)time(NULL));
//	return rand();
//}

bool cmp(int a, int b)
{
	return a == b ? true : false;
}


void testRandomNumberGeneration(int testSize, bool printNumbers)
{
	// Made this algorithm to test how well my random number generators perform after undergoing so many iterations of rng().
	std::unique_ptr<std::set<unsigned int>> intSetPtr = std::make_unique<std::set<unsigned int>>();
	// use set because each element is unique. Dynamically allocate so I can use more memory.
	for (int i{ 0 }; i < testSize; i++)
	{
		unsigned int a = rng();
		intSetPtr->insert(a);

		if(printNumbers)
		 //if set to false decrease time by 1/4!
		{
			printf("%u\t", a);
			if (i % 5 == 0)
				printf("\n");
		}
	}
	printf("\n\tSize of set: %i\tDuplicates: %i\n", intSetPtr->size(), testSize - intSetPtr->size());
}

void testRandomNumberGenerationPercent(int testSize, int NumbersToTestPercentOf, bool printNumbers)
{
	// The other algorithm finds the number of duplicates. Created this algorithm to find
	// how evenly distributed the numbers will be when I modulo the rng() return by a specific number, NumbersToTestPercentOf.
	if (NumbersToTestPercentOf > testSize)
	{
		printf("testSize must be larger than NumberPercantage.");
		return;
	}

	if (NumbersToTestPercentOf > 10000)
	{
		printf("NumberPercantage too large.");
		return;
	}

	std::unique_ptr<std::vector<unsigned int>> intVecPtr = std::make_unique<std::vector<unsigned int>>();
	for (int i{ 0 }; i < testSize; i++)
	{
		// add testSize numbers in range [0, NumbersToTestPercentOf - 1] to intVec
		unsigned int a = rng() % NumbersToTestPercentOf;
		intVecPtr->push_back(a);

		if (printNumbers)
			// default is true, optional argument false to increase performance of algorithm
		{
			printf("%u\t", a);
			if (i % 5 == 0)
				printf("\n");
		}
	}
	// After the numbers are in the vector, we need to create another vector of size NumbersToTestPercentOf with the elements and 0 being the number of elements found
	std::vector<std::array<unsigned int, 2>> distribVec;

	for (int i{ 0 }; i < NumbersToTestPercentOf; i++)
	{
		// add range [0 - NumbersToTestPercentOf - 1] to vector
		std::array<unsigned int, 2> arr1;
		arr1[0] = i;
		arr1[1] = 0;
		distribVec.push_back(arr1);
	}

	// loop through 
	for (int i{ 0 }; i < intVecPtr->size(); i++)
	{
		if (intVecPtr->at(i) == distribVec[intVecPtr->at(i)][0])
		{
			distribVec[intVecPtr->at(i)][1]++;
		}
	}
	printf("\n\n");

	for (int i{ 0 }; i < distribVec.size(); i++)
	{
		printf("\tNumber:\t%u\t%.2f\t%%\n", distribVec[i][0], ((float)distribVec[i][1] / testSize) * 100.0);
	}
}