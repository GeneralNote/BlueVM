#ifndef __BLUEVM_FUNCTION_H__
#define __BLUEVM_FUNCTION_H__

#include <BlueVM/types.h>
#include <BlueVM/bv_type.h>
#include <BlueVM/bv_function_pool.h>
#include <BlueVM/bv_variable.h>

typedef bv_variable (*bv_external_function)(u8, bv_variable*);

typedef struct bv_function_s
{
	u8 args;
	u32 code_length;
	byte* code;
} bv_function;

bv_function* bv_function_create(byte* mem);
void bv_function_delete(bv_function* func);
bv_function** bv_function_create_array(bv_function_pool* funcs, byte* mem);
void bv_function_delete_array(bv_function** data, u16 len);

#endif