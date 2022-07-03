#include "stdafx.h"
#include "rng.h"

unsigned int rng()
{
	std::random_device rd;

	std::mt19937::result_type seed = rd() ^ (
		(std::mt19937::result_type)
		std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()
			).count() +
		(std::mt19937::result_type)
		std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch()
			).count());

	std::mt19937 gen(seed);

	for (unsigned long j = 0; j < 100500; ++j)
	{
		std::mt19937::result_type n;
		// reject readings that would make n%6 non-uniformly distributed
		while ((n = gen()) > std::mt19937::max() -
			(std::mt19937::max() - 5) % 6)
		{ /* bad value retrieved so get next one */
		}

		return n;
	}
}

void testRandomNumberGeneration(int testSize, bool printNumbers)
{
	// Made this algorithm to test how well my random number generators perform after undergoing so many iterations of rng().
	// Current rng() function only produces ~236 duplicates per 1 million numbers in about 2-3 minutes. Pretty good.
	int dupes{ 0 };
	std::set<unsigned int> intSet;
	// use set because each element is unique
	for (int i{ 0 }; i < testSize; i++)
	{
		int sizeBeforeInsert = intSet.size();
		//get size before insert to compare with size after insert

		unsigned int a = rng();
		intSet.insert(a);
		// Insert into set
		if (sizeBeforeInsert == intSet.size())
			// if size is the same then the number was already in the set
			dupes++;

		// print numbers
		if(printNumbers)
		// if set to false decrease time by 1/4!
		{
			printf("%u\t", a);
			if (i % 5 == 0)
				// print newline every fifth number
				printf("\n");
		}
	}
	std::cout << "\nSize of set: " << intSet.size() << "\nDuplicates: " << dupes;
}

void testRandomNumberGenerationPercent(int testSize, int NumbersToTestPercentOf, bool printNumbers)
{
	// The other algorithm finds the number of duplicates. Created this algorithm to find
	// how evenly distributed the numbers will be when I modulo the rng() return by a specific number, NumbersToTestPercentOf.
	if (NumbersToTestPercentOf > testSize)
		throw "Test size must be greater than NumbersToTestPercentOf";
	if (NumbersToTestPercentOf > 10000)
		// Limit numbers to find percentage of to 10000
		throw "NumbersToTestPercentOf too large.";

	std::vector<unsigned int> intVec;
	for (int i{ 0 }; i < testSize; i++)
	{
		// add testSize numbers in range [0, NumbersToTestPercentOf - 1] to intVec
		unsigned int a = rng() % NumbersToTestPercentOf;
		intVec.push_back(a);

		if(printNumbers)
		// default is true, optional argument false to increase performance of algorithm
		{
			printf("%u\t", a);
			if (i % 5 == 0)
				printf("\n");
		}
	}
	// After the numbers are in the vector, we need to create another vector of size NumbersToTestPercentOf with the elements and 0 being the number of elements found
	std::vector<std::array<unsigned int, 2>> distributionVec;
	// resize vector to size of the memory of ints that will be taken up. 8 because the array has 2 ints
	for (int i{0}; i < NumbersToTestPercentOf; i++)
	{
		// add range [0 - NumbersToTestPercentOf - 1] to vector
		std::array<unsigned int, 2> arr1;
		arr1[0] = i;
		arr1[1] = 0;
		distributionVec.push_back(arr1);
	}

	// loop through 
	for (int i{ 0 }; i < intVec.size(); i++)
	{
		if (intVec[i] == distributionVec[intVec[i]][0])
		{
			distributionVec[intVec[i]][1]++;
		}
	}

	printf("\n\n");
	for (int i{ 0 }; i < distributionVec.size(); i++)
	{
		printf("Number:\t%u\t%.2f\t%%\n", distributionVec[i][0], ((float)distributionVec[i][1] / testSize) * 100.0);
	}
}

