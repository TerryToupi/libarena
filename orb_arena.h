#ifndef ORBIT_ARENA_
#define ORBIT_ARENA_

/*-----------------------------------------------------------------------*/
/*---------------------------DEFAULT-OPTIONS-----------------------------*/
/*-----------------------------------------------------------------------*/
#ifndef OA_BUILD_STATIC
	#define OA_BUILD_STATIC 1
#endif

#ifndef OA_BUILD_DYNAMIC
	#define OA_BUILD_DYNAMIC 0
#endif

/*---------------------------------------------------------------------*/
/*---------------------------STANDAR-TYPES-----------------------------*/
/*---------------------------------------------------------------------*/
#if defined(__cplusplus)
extern "C"
{
#endif

#if defined(__cplusplus)
	#define OA_EXTERN extern "C"
#else
	#define OA_EXTERN extern
#endif

#if defined(_WIN32) || defined(_WIN64)
	#define OA_DLL_EXPORT OA_EXTERN __declspec(dllexport)
	#define OA_DLL_IMPORT OA_EXTERN __declspec(dllimport)
#else
	#define OA_DLL_EXPORT OA_EXTERN __attribute__((visibility("default")))
	#define OA_DLL_IMPORT OA_EXTERN
#endif

#ifndef OA_DEF
	#if OA_BUILD_STATIC
		#define OA_DEF static
	#elif OA_BUILD_DYNAMIC
		#define OA_DEF OA_DLL_EXPORT
	#else
		#define OA_DEF OA_DLL_IMPORT
	#endif
#endif

#ifndef OA_INTERNAL
	#define OA_INTERNAL static
#endif

#if defined(_WIN32) || defined(_WIN64)
	#ifndef OA_OS_WINDOWS
	#define OA_OS_WINDOWS 1
	#endif
#elif defined(__APPLE__) && defined(__MACH__)
	#ifndef OA_OS_OSX
	#define OA_OS_OSX 1
	#endif
#elif defined(__unix__)
	#ifndef OA_OS_UNIX
	#define OA_OS_UNIX 1
	#endif
	#if defined(__linux__)
		#ifndef OA_OS_LINUX
		#define OA_OS_LINUX 1
		#endif
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		#ifndef OA_OS_FREEBSD
		#define OA_OS_FREEBSD 1
		#endif
	#else
		#error Unsupported UNIX operating system!
	#endif
#else
	#error Unsupported operating system!
#endif

#if defined(_MSC_VER)
	#ifndef OA_COMPILER_MSVC
	#define OA_COMPILER_MSVC 1
	#endif
#endif
#if defined(__clang__)
	#ifndef OA_COMPILER_CLANG
	#define OA_COMPILER_CLANG 1
	#endif
#endif
#if defined(__GNUC__)
	#ifndef OA_COMPILER_GCC
	#define OA_COMPILER_GCC 1
	#endif
#endif

#if !defined(OA_COMPILER_MSVC) && \
	!defined(OA_COMPILER_CLANG) && \
	!defined(OA_COMPILER_GCC)
	#error Unsupported compiler!
#endif

#if defined(OA_COMPILER_MSVC)
	#define oa__alignof(T) __alignof(T)
#elif defined(OA_COMPILER_CLANG)
	#define oa__alignof(T) __alignof(T)
#elif defined(OA_COMPILER_GCC)
	#define oa__alignof(T) __alignof__(T)
#else
	#error AlignOf not defined for this compiler.
#endif

#ifndef OA_STATIC_ASSERT
	#define OA_ASSERT_NAME_CONCAT_(a, b) a##b
	#define OA_ASSERT_NAME_CONCAT(a, b) OA_ASSERT_NAME_CONCAT_(a, b)

	#define OA_STATIC_ASSERT_MESSAGE(cond, name) \
		typedef char OA_ASSERT_NAME_CONCAT(static_assertion_, name)[(!!(cond)) * 2 - 1]

	#define OA_STATIC_ASSERT_LINE_COUNT(cond, line, count) \
		OA_STATIC_ASSERT_MESSAGE( \
			cond, \
			OA_ASSERT_NAME_CONCAT( \
				OA_ASSERT_NAME_CONCAT(at_count_, count), \
				OA_ASSERT_NAME_CONCAT(_at_line_, line) \
			) \
		)

	#define OA_STATIC_ASSERT(cond) \
		OA_STATIC_ASSERT_LINE_COUNT(cond, __LINE__, __COUNTER__)
#endif

#if defined(OA_COMPILER_MSVC)
#define oa__trap() __debugbreak()
#elif defined(OA_COMPILER_CLANG) || defined(OA_COMPILER_GCC)
#define oa__trap() __builtin_trap()
#else
#error Unknown trap intrinsic for this compiler.
#endif

#ifndef OA_ASSERT
#define OA_ASSERT(x) do{if(!(x)) {oa__trap();}}while(0)
#endif

#if defined(OA_COMPILER_MSVC)
	#define OA_FORCE_INLINE __forceinline
#elif defined(OA_COMPILER_CLANG) || defined(OA_COMPILER_GCC)
	#define OA_FORCE_INLINE __attribute__((always_inline))
#endif

#if defined(_WIN32) && !defined(__MINGW32__)
	#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
	#endif
#endif

#if defined(OA_OS_UNIX)
	#define _GNU_SOURCE
	#define _LARGEFILE64_SOURCE
#endif

#include <stddef.h>
#include <stdarg.h>
#include <string.h>

#if defined(OA_OS_WINDOWS)
	#if _MSC_VER < 1300
	typedef unsigned char    oa__u8;
	typedef   signed char    oa__i8;
	typedef unsigned short   oa__u16;
	typedef   signed short   oa__i16;
	typedef unsigned int     oa__u32;
	typedef   signed int     oa__i32;
	#else
	typedef unsigned __int8   oa__u8;
	typedef   signed __int8   oa__i8;
	typedef unsigned __int16  oa__u16;
	typedef   signed __int16  oa__i16;
	typedef unsigned __int32  oa__u32;
	typedef   signed __int32  oa__i32;
	#endif
	typedef unsigned __int64 oa__u64;
	typedef   signed __int64 oa__i64;
#else
	#include <stdint.h>
	typedef uint8_t   oa__u8;
	typedef  int8_t   oa__i8;
	typedef uint16_t  oa__u16;
	typedef  int16_t  oa__i16;
	typedef uint32_t  oa__u32;
	typedef  int32_t  oa__i32;
	typedef uint64_t  oa__u64;
	typedef  int64_t  oa__i64;
#endif

OA_STATIC_ASSERT(sizeof(oa__u8)  == sizeof(oa__i8));
OA_STATIC_ASSERT(sizeof(oa__u16) == sizeof(oa__i16));
OA_STATIC_ASSERT(sizeof(oa__u32) == sizeof(oa__i32));
OA_STATIC_ASSERT(sizeof(oa__u64) == sizeof(oa__i64));

OA_STATIC_ASSERT(sizeof(oa__u8)  == 1);
OA_STATIC_ASSERT(sizeof(oa__u16) == 2);
OA_STATIC_ASSERT(sizeof(oa__u32) == 4);
OA_STATIC_ASSERT(sizeof(oa__u64) == 8);

typedef size_t 		oa__usize;
typedef ptrdiff_t 	oa__isize;

OA_STATIC_ASSERT(sizeof(oa__usize) == sizeof(oa__isize));

#if defined(_WIN64)
	typedef signed   __int64  oa__intptr;
	typedef unsigned __int64  oa__uintptr;
#elif defined(_WIN32)
	#ifndef _W64
		#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
			#define _W64 __w64
		#else
			#define _W64
		#endif
	#endif

	typedef _W64   signed int  oa__intptr;
	typedef _W64 unsigned int  oa__uintptr;
#else
	typedef uintptr_t  oa__uintptr;
	typedef  intptr_t  oa__intptr;
#endif

OA_STATIC_ASSERT(sizeof(oa__uintptr) == sizeof(oa__intptr));

typedef float  oa__f32;
typedef double oa__f64;

OA_STATIC_ASSERT(sizeof(oa__f32) == 4);
OA_STATIC_ASSERT(sizeof(oa__f64) == 8);

typedef oa__i8 	oa__b8;
typedef oa__i16 oa__b16;
typedef oa__i32 oa__b32;

#ifndef NULL
	#if defined(__cplusplus)
		#if __cplusplus >= 201103L
			#define NULL nullptr
		#else
			#define NULL 0
		#endif
	#else
		#define NULL ((void *)0)
	#endif
#endif

#if defined(__cplusplus)
	#define oa__struct_initializer() {}
#else
	#define oa__struct_initializer() {0}
#endif

#define OA_KB(n)  			(((oa__u64)(n)) << 10)
#define OA_MB(n)  			(((oa__u64)(n)) << 20)
#define OA_GB(n)  			(((oa__u64)(n)) << 30)
#define OA_TB(n)  			(((oa__u64)(n)) << 40)
#define OA_Thousand(n)   	((n)*1000)
#define OA_Million(n)    	((n)*1000000)
#define OA_Billion(n)    	((n)*1000000000)

#define OA_MIN(A,B) 		(((A)<(B))?(A):(B))
#define OA_MAX(A,B) 		(((A)>(B))?(A):(B))
#define OA_CLAMP_TOP(A,X) 	OA_MIN(A,X)
#define OA_CLAMP_BOT(X,B) 	OA_MAX(X,B)
#define OA_CLAMP(A,X,B) 	(((X)<(A))?(A):((X)>(B))?(B):(X))
#define OA_ALIGN_POW2(x,b)	(((x) + (b) - 1)&(~((b) - 1)))

/*------------------------------------------------------------------*/
/*---------------------------DEFINITION-----------------------------*/
/*------------------------------------------------------------------*/
#define OA_ARENA_HEADER_SIZE 128

#define OA_DEFAULT_RESERVE_SIZE 			OA_MB(64)
#define OA_DEFAULT_COMMIT_SIZE  			OA_KB(64)
#define OA_DEFAULT_FLAGS 					0
#define OA_DEFAULT_BACKING_BUFFER 			NULL
#define OA_DEFAULT_ALLOCATION_SITE_FILE		__FILE__
#define OA_DEFAULT_ALLOCATION_SITE_LINE		__LINE__



typedef oa__u64 oa_arena_flags_kind;
enum
{
	OA_ARENA_FLAG_NO_CHAIN = (1<<1),
};



typedef struct oa__arena_desc oa_arena_desc;
struct oa__arena_desc
{
	oa_arena_flags_kind  flags;
	oa__u64 			 reserve_size;
	oa__u64 			 commit_size;
	void 				*optional_backing_buffer;
	const char			*allocation_site_file;
	oa__u32				 allocation_site_line;
	const char 			*name;
};



typedef struct oa__arena oa_arena;
struct oa__arena
{
	oa_arena 			*prev;
	oa_arena 			*current;
	oa_arena_flags_kind  flags;
	oa__u64 			 cmt_size;
	oa__u64 			 res_size;
	oa__u64 			 base_pos;
	oa__u64 			 pos;
	oa__u64 			 cmt;
	oa__u64 			 res;
	const char 			*allocation_site_file;
	oa__u32 			 allocation_site_line;
	const char 			*name;
};
OA_STATIC_ASSERT(sizeof(oa_arena) <= OA_ARENA_HEADER_SIZE);



typedef struct oa__temp oa_temp;
struct oa__temp
{
	oa_arena *arena;
	oa__u64   pos;
};



OA_DEF oa_arena *oa_arena_allocate(oa_arena_desc *desc);



OA_DEF oa_arena *oa_arena_alloc(const char *name);

		

OA_DEF void oa_arena_release(oa_arena *arena);



OA_DEF void *oa_arena_push(oa_arena *arena, oa__u64 size, oa__u64 align, oa__b32 zero);
#define oa_push_array_no_zero_aligned(a, T, c, align) (T *)oa_arena_push((a), sizeof(T)*(c), align, (0))
#define oa_push_array_aligned(a, T, c, align) 		  (T *)oa_arena_push((a), sizeof(T)*(c), align, (1))
#define oa_push_array_no_zero(a, T, c)	oa_push_array_no_zero_aligned(a, T, c, OA_MAX(8, oa__alignof(T)))
#define oa_push_array(a, T, c)			oa_push_array_aligned(a, T, c, OA_MAX(8, oa__alignof(T)))



OA_DEF oa__u64 oa_arena_pos(oa_arena *arena);



OA_DEF void oa_arena_pop_to(oa_arena *arena, oa__u64 pos);



OA_DEF void oa_arena_clear(oa_arena *arena);



OA_DEF void oa_arena_pop(oa_arena *arena, oa__u64 amt);



OA_DEF oa_temp oa_arena_temp_begin(oa_arena *arena);



OA_DEF void oa_arena_temp_end(oa_temp tmp);



#if defined(__cplusplus)
}
#endif

#endif // ORBIT_ARENA_



///////////////////////////////////////////////////////////////////////////////////////////////////
/*										IMPLEMENTATION 										     */
///////////////////////////////////////////////////////////////////////////////////////////////////



#ifdef ORBIT_ARENA_IMPLEMENTATION
#undef ORBIT_ARENA_IMPLEMENTATION

#if OA_OS_OSX || OA_OS_UNIX
    #include <sys/mman.h>
    #include <sys/types.h>
#elif OA_OS_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

#if OA_OS_WINDOWS && OA_COMPILER_MSVC
    #include <intrin.h>
	#pragma comment(lib, "kernel32.lib")
#endif

OA_INTERNAL volatile oa__u32 oa__atomic_os_page_size = 0;

OA_INTERNAL oa__u32
oa__atomic_u32_ptr_eval(volatile oa__u32 *ptr)
{
#if OA_COMPILER_MSVC
    return (oa__u32)_InterlockedCompareExchange((volatile long *)ptr, 0, 0);

#elif OA_COMPILER_CLANG || OA_COMPILER_GCC
    return __atomic_load_n(ptr, __ATOMIC_ACQUIRE);

#else
    #error Atomic intrinsics not defined for this compiler.
#endif
}

OA_INTERNAL oa__b32
oa__atomic_u32_ptr_cond_assign(volatile oa__u32 *ptr, oa__u32 e, oa__u32 v)
{
#if OA_COMPILER_MSVC
    return _InterlockedCompareExchange((volatile long *)ptr, (long)v, (long)e) == (long)e;

#elif OA_COMPILER_CLANG || OA_COMPILER_GCC
    oa__u32 expected = e;
    return __atomic_compare_exchange_n(
        ptr,
        &expected,
        v,
        0,
        __ATOMIC_RELEASE,
        __ATOMIC_ACQUIRE
    );

#else
    #error Atomic intrinsics not defined for this compiler.
#endif
}

OA_INTERNAL void *
oa__os_reserve(oa__u64 reserve_size)
{
#if OA_OS_OSX || OA_OS_UNIX
	void *result = mmap(0, reserve_size, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (result == MAP_FAILED)
	{
		result = 0;
	}
	return result;
#elif OA_OS_WINDOWS
	void *result = VirtualAlloc(0, reserve_size, MEM_RESERVE, PAGE_READWRITE);
	return result;
#else
	#error No supproted OS for os reserve!
#endif	
}

OA_INTERNAL oa__b32
oa__os_commit(void *ptr, oa__u64 commit_size)
{
#if OA_OS_OSX || OA_OS_UNIX
	oa__b32 result = (mprotect(ptr, commit_size, PROT_READ|PROT_WRITE) != 0);
	return retult;
#elif OA_OS_WINDOWS
	oa__b32 result = (VirtualAlloc(ptr, commit_size, MEM_COMMIT, PAGE_READWRITE) != 0);
	return result;
#else
	#error No supproted OS for os commit!
#endif	
}

OA_INTERNAL void
oa__os_release(void *ptr, oa__u64 release_size)
{
#if OA_OS_OSX || OA_OS_UNIX
	munmap(ptr, release_size);
#elif OA_OS_WINDOWS
	(void)release_size;
	VirtualFree(ptr, 0, MEM_RELEASE);
#else
	#error No supproted OS for os release!
#endif
}

OA_INTERNAL oa__u64
oa__os_page_size(void)
{
	oa__u32 result = oa__atomic_u32_ptr_eval(&oa__atomic_os_page_size);

    if (result == 0)
    {
#if OA_OS_OSX || OA_OS_UNIX
        long page_size = sysconf(_SC_PAGESIZE);
        result = (page_size > 0) ? (oa__u32)page_size : 4096;
#elif OA_OS_WINDOWS
        SYSTEM_INFO info;
        GetSystemInfo(&info);
        result = (oa__u32)info.dwPageSize;
#else
        #error No supported OS for os page size!
#endif
        if (!oa__atomic_u32_ptr_cond_assign(&oa__atomic_os_page_size, 0, result))
        {
            result = oa__atomic_u32_ptr_eval(&oa__atomic_os_page_size);
        }
    }

    return result;
}

OA_DEF oa_arena *
oa_arena_allocate(oa_arena_desc *desc)
{
	oa__u64 reserve_size = desc->reserve_size;
	oa__u64 commit_size = desc->commit_size;

	void *base = desc->optional_backing_buffer;
	if (base == 0)
	{
		reserve_size = OA_ALIGN_POW2(reserve_size, oa__os_page_size());
		commit_size = OA_ALIGN_POW2(commit_size, oa__os_page_size());
		base = oa__os_reserve(reserve_size);
		oa__os_commit(base, commit_size);
	}

	oa_arena *arena = (oa_arena *)base;
	arena->current = arena;
	arena->prev = 0;
	arena->flags = desc->flags;
	arena->cmt_size = desc->commit_size;
	arena->res_size = desc->reserve_size;
	arena->base_pos = 0;
	arena->pos = OA_ARENA_HEADER_SIZE;
	arena->cmt = commit_size;
	arena->res = reserve_size;
	arena->allocation_site_file = desc->allocation_site_file;
	arena->allocation_site_line = desc->allocation_site_line;
	arena->name = desc->name;
	return arena;
}

OA_DEF oa_arena *
oa_arena_alloc(const char *name)
{
	oa_arena_desc desc = oa__struct_initializer();
	desc.reserve_size = OA_DEFAULT_RESERVE_SIZE;
	desc.commit_size = OA_DEFAULT_COMMIT_SIZE;
	desc.flags = OA_DEFAULT_FLAGS;
	desc.allocation_site_file = OA_DEFAULT_ALLOCATION_SITE_FILE;
	desc.allocation_site_line = OA_DEFAULT_ALLOCATION_SITE_LINE;
	desc.name = name;
	oa_arena *arena = oa_arena_allocate(&desc);
	return arena;
}

OA_DEF void *
oa_arena_push(oa_arena *arena, oa__u64 size, oa__u64 align, oa__b32 zero)
{
	oa_arena *current = arena->current;
	oa__u64 pos_pre = OA_ALIGN_POW2(current->pos, align);
	oa__u64 pos_pst = pos_pre + size;

	oa__u64 size_to_zero = 0;
	if (zero)
	{
		size_to_zero = OA_MIN(current->cmt, pos_pst) - pos_pre;
	}

	if (current->res < pos_pst && !(current->flags & OA_ARENA_FLAG_NO_CHAIN))
	{
		oa_arena 	*new_block = 0;
		oa__u64		 res_size = current->res_size;
		oa__u64 	 cmt_size = current->cmt_size;
		if (size + OA_ARENA_HEADER_SIZE > res_size)
		{
			res_size = OA_ALIGN_POW2(size + OA_ARENA_HEADER_SIZE, align);
			cmt_size = OA_ALIGN_POW2(size + OA_ARENA_HEADER_SIZE, align);
		}

		oa_arena_desc desc = oa__struct_initializer();
		desc.reserve_size 	= res_size;
		desc.commit_size 	= cmt_size;
		desc.flags 			= current->flags;
		desc.allocation_site_file = current->allocation_site_file;
		desc.allocation_site_line = current->allocation_site_line;
		new_block = oa_arena_allocate(&desc);

		new_block->base_pos = current->base_pos + current->res;
		new_block->prev = arena->current;
		arena->current = new_block;
		current = new_block;
		pos_pre = OA_ALIGN_POW2(current->pos, align);
		pos_pst = pos_pre + size;
	}

	if (current->cmt < pos_pst)
	{
		oa__u64 cmt_pst_aligned = pos_pst + current->cmt_size - 1;
		cmt_pst_aligned -= cmt_pst_aligned % current->cmt_size;
		oa__u64 cmt_pst_clamped = OA_CLAMP_TOP(cmt_pst_aligned, current->res);
		oa__u64 cmt_size = cmt_pst_clamped - current->cmt;
		oa__u8 *cmt_ptr = (oa__u8 *)current + current->cmt;
		oa__os_commit(cmt_ptr, cmt_size);
		current->cmt = cmt_pst_clamped;
	}

	void *result = 0;
	if (current->cmt >= pos_pst)
	{
		result 		 = (oa__u8 *)current + pos_pre;
		current->pos = pos_pst;
		memset(result, 0, size_to_zero);
	}

	return result;
}

OA_DEF void
oa_arena_release(oa_arena *arena)
{
	for (oa_arena *n = arena->current, *prev = 0; n != 0; n = prev)	
	{
		prev = n->prev;
		oa__os_release(n, n->res);
	}
}

OA_DEF oa__u64
oa_arena_pos(oa_arena *arena)
{
	oa_arena *current = arena->current;
	oa__u64 pos = current->base_pos + current->pos;	
	return pos;
}

OA_DEF void
oa_arena_pop_to(oa_arena *arena, oa__u64 pos)
{
	oa__u64 big_pos = OA_CLAMP_BOT(OA_ARENA_HEADER_SIZE, pos);
	oa_arena *current = arena->current;

	for (oa_arena *prev = 0; current->base_pos >= big_pos; current = prev)
	{
		prev = current->prev;
		oa__os_release(current, current->res);
	}
	arena->current = current;
	oa__u64 new_pos = big_pos - current->base_pos;
	OA_ASSERT(new_pos <= current->pos);
	current->pos = new_pos;
}

OA_DEF void
oa_arena_clear(oa_arena *arena)
{
	oa_arena_pop_to(arena, 0);
}


OA_DEF void
oa_arena_pop(oa_arena *arena, oa__u64 amt)
{
	oa__u64 pos_old = oa_arena_pos(arena);
	oa__u64 pos_new = pos_old;
	if (amt < pos_old)
	{
		pos_new = pos_old - amt;
	}
	oa_arena_pop_to(arena, pos_new);
}

OA_DEF oa_temp
oa_arena_temp_begin(oa_arena *arena)
{
	oa__u64 pos = oa_arena_pos(arena);
	oa_temp temp = {arena, pos};
	return temp;
}

OA_DEF void
oa_arena_temp_end(oa_temp tmp)
{
	oa_arena_pop_to(tmp.arena, tmp.pos);
}

#endif
