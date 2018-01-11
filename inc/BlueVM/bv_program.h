#ifndef __BLUEVM_PROGRAM_H__
#define __BLUEVM_PROGRAM_H__

#include <BlueVM/bv_header.h>
#include <BlueVM/bv_block.h>
#include <BlueVM/bv_function.h>
#include <BlueVM/bv_variable.h>

typedef struct bv_program {
	bv_header header;
	bv_block* block;
	bv_function** functions;
} bv_program;

bv_program* bv_program_create(byte* mem);
void bv_program_delete(bv_program* program);

u16 bv_program_get_function_count(bv_program* prog);
bv_function* bv_program_get_function(bv_program* prog, const char* str);

bv_variable bv_program_call(bv_program* prog, bv_function* func);

#endif