#pragma once

static_assert(sizeof(char) == 1, "unexpected size");
static_assert(sizeof(short) == 2, "unexpected size");
static_assert(sizeof(int) == 4, "unexpected size");
static_assert(sizeof(long long) == 8, "unexpected size");

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned long long vu64;

typedef volatile signed char vs8;
typedef volatile short vs16;
typedef volatile int vs32;
typedef volatile long long vs64;

typedef float f32;
typedef double f64;

union relocPointer
{
	u32 resolvedPointer;
	struct
	{
		u16 nextPointer;
		u16 pointer;
	};
};