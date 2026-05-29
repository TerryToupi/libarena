#define ORBIT_ARENA_IMPLEMENTATION
#include "../orb_arena.h"

int main()
{
	oa_arena *arena = oa_arena_alloc("global allocator");

	char *bytes = oa_push_array(arena, char, OA_MB(128));

	return 0;	
}