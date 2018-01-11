#ifndef __BLUEVM_FUNCTION_POOL_H__
#define __BLUEVM_FUNCTION_POOL_H__

#include <BlueVM/types.h>

typedef struct bv_function_pool {
	u16 count;
	string* names;
	u32* address;
} bv_function_pool;

bv_function_pool* bv_function_pool_create(byte* mem);
u32 bv_function_pool_get_address(bv_function_pool* pool, string str);
u32 bv_function_pool_length(bv_function_pool* pool);
void bv_function_pool_delete(bv_function_pool* pool);

#endif