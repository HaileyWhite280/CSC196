#include "Random.h"
#include <stdlib.h>

namespace nc
{
	void SeedRandom(unsigned int seed)
	{
		srand(seed);
	}

	float Random()
	{
		return rand() / static_cast<float>(RAND_MAX);
	}

	float RandomRange(float min, float max)
	{
		return min + (max - min) * Random();
	}

	int randomInt()
	{
		return rand();
	}

	int randomRangeInt(int min, int max)
	{
		return min + rand() % (max - min);
	}
}