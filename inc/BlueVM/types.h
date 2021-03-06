#ifndef __BLUEVM_TYPES_H__
#define __BLUEVM_TYPES_H__

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned int u32;
typedef signed int s32;

//typedef char* bv_string;
#define bv_string char*

typedef unsigned char byte;

u8 u8_read(byte** mem);
s8 s8_read(byte** mem);
u16 u16_read(byte** mem);
s16 s16_read(byte** mem);
u32 u32_read(byte** mem);
s32 s32_read(byte** mem);
float float_read(byte** mem);
bv_string string_read(byte** mem);

bv_string bv_itoa(s32 val, s32 base);
bv_string bv_ftoa(float val, u8 dec);

#endif