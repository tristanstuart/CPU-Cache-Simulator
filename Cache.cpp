#include "Cache.h"
#include <iostream>
#include <cmath>

// used to track the age of cache values, there's probably a better solution, but this works
static int modCount = 0;

Cache::Cache(int waySz, int numWys)
{
	waySize = waySz;
	numWays = numWys;
	tagShift = log2(waySize); // how many bits we need to shift over to get the tag (is just leftover after index is removed)
	cache = new Entry*[numWays];
	for(int i = 0; i < numWays; i++)
	{
		cache[i] = new Entry[waySize];
		for(int j = 0; j < waySize; j++)//initializing cache to empty so there arent any false positives
		{
			cache[i][j].tag = 0;
			cache[i][j].valid = false;
			cache[i][j].lastChanged = 0;
		}
	}
}

Cache::~Cache()
{
	for(int i = 0; i < numWays; i++)
		delete[] cache[i];
	delete[] cache;
}

bool Cache::getValueFromCache(int memLoc)
{
	int index = findIndex(memLoc);
	int tag = findTag(memLoc);
	for (int i = 0; i < numWays; i++) // check if value is cached and return hit if it is
		if (cache[i][index].valid && cache[i][index].tag == tag)
			return true;

	// we only get here if the value isnt cached, so we need to figure out which value is the oldest
	// so we can replace it with the new one
	int lastChanged = 0;// tracks the oldest value in the cache
	for (int i = 0; i < numWays; i++)
	{
		if (!cache[i][index].valid)// if there's an invalid entry, use that one first
		{
			lastChanged = i;
			break;
		}
		if(cache[i][index].lastChanged < cache[lastChanged][index].lastChanged) //track the oldest value at this index across all ways
			lastChanged = i;
	}

	//cache the new value based on where we calculated it to go
	cache[lastChanged][index].tag = tag;
	cache[lastChanged][index].valid = true;
	cache[lastChanged][index].lastChanged = ++modCount;

	return false;
}

int Cache::findTag(int memLoc)
{
	return memLoc >> tagShift;
}

int Cache::findIndex(int memLoc)
{
	return memLoc % waySize;
}