// source: https://en.wikipedia.org/wiki/Xorshift 

#include <ctime>

static bool initialized = false;
static unsigned int seed;  // 100% random seed value

unsigned int random()
{
	if (!initialized)
	{
		seed = time(0);
		initialized = true;
	}
	
	seed ^= seed << 13; // left shift
	seed ^= seed >> 17; // right shift
	seed ^= seed << 5;  // left shift
	return seed;
}
/* 
0000 0000 0000 0000 0000 0000 0000 0111 seed = 7

0000 0000 0000 0000 1110 0000 0000 0000 seed lshift 13
0000 0000 0000 0000 0000 0000 0000 0111 seed xor(^)
---------------------------------------
0000 0000 0000 0000 1110 0000 0000 0111
*/