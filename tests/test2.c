#define ORBIT_ARENA_IMPLEMENTATION
#include "../orb_arena.h"

typedef struct kappa kappa;
struct kappa
{
	int k[4096];
};

int main()
{
	oa_arena *arena = oa_arena_alloc("");

	kappa *array = oa_push_array(arena, kappa, 32);
	oa_push_array(arena, kappa, 32);

	array[63].k[2] = 66667777;
	int will_it_be_good = array[63].k[2];

	oa_arena_clear(arena);
	return 0;	
}