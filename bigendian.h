#pragma once


void changeEndianness(unsigned char* c, u32 n)
{
	static unsigned char temp[64];
	for (int i = 0; i < n; temp[i] = c[i], i++);
	for (int i = 0; i < n; c[i] = temp[n - 1 - i], i++);
}

typedef unsigned char u8;

struct u16 {
	unsigned short value;
	operator unsigned short() const {
		return (value << 8) | (value >> 8);
	}
};

struct u32 {
	unsigned long value;
	operator unsigned long() const {
		unsigned long out = value;
		changeEndianness((unsigned char*)&out, 4);
		return out;
	}
};

struct u64 {
	unsigned long long value;
	operator unsigned long long() const {
		unsigned long long out = value;
		changeEndianness((unsigned char*)&out, 8);
		return out;
	}
};

typedef char s8;

struct s16 {
	short value;
	operator short() const {
		return (value << 8) | (value >> 8);
	}
};

struct s32 {
	long value;
	operator long() const {
		long out = value;
		changeEndianness((unsigned char*)&out, 4);
		return out;
	}
};

struct s64 {
	long long value;
	operator long long() const {
		long long out = value;
		changeEndianness((unsigned char*)&out, 8);
		return out;
	}
};

typedef float f32;
typedef double f64;