#ifndef __BLUEVM_STACK_H__
#define __BLUEVM_STACK_H__

#include <BlueVM/bv_variable.h>

typedef struct bv_stack {
	bv_variable* data;
	u32 length;
} bv_stack;

bv_stack bv_stack_create();
void bv_stack_delete(bv_stack* stack);

bv_variable bv_stack_top(bv_stack* stack);
void bv_stack_pop(bv_stack* stack);
void bv_stack_push(bv_stack* stack, bv_variable var);

#endif