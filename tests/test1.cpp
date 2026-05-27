#define ORBIT_ARENA_IMPLEMENTATION
#include "../orb_arena.h"

int main()
{
	oa_arena *arena = oa_arena_alloc("global allocator");
	return 0;	
}