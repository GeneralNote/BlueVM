#include <BlueVM/bv_program.h>
#include <BlueVM/bv_stack.h>
#include <string.h>
#include <stdlib.h>

bv_program* bv_program_create(byte * mem)
{
	bv_program* ret = malloc(sizeof(bv_program));

	ret->header = bv_header_create(mem);
	ret->block = bv_block_create(mem + sizeof(ret->header));
	ret->functions = bv_function_create_array(ret->block->functions, mem);

	return ret;
}
void bv_program_delete(bv_program * prog)
{
	bv_function_delete_array(prog->functions, bv_program_get_function_count(prog));
	bv_block_delete(prog->block);

	free(prog);
}

u16 bv_program_get_function_count(bv_program * prog)
{
	return prog->block->functions->count;
}
bv_function* bv_program_get_function(bv_program* prog, const char* str)
{
	u16 func_count = bv_program_get_function_count(prog);

	for (u16 i = 0; i < func_count; i++)
		if (strcmp(prog->block->functions->names[i], str) == 0)
			return prog->functions[i];

	return 0;
}

bv_variable bv_program_call(bv_program* prog, bv_function* func)
{
	bv_stack stack = bv_stack_create();
	bv_variable rtrn;

	bv_constant_pool* cpool = prog->block->constants;
	byte* code = func->code;

	while ((code - func->code) < func->code_length) {
		bv_opcode op = bv_opcode_read(&code);

		if (op == bv_opcode_return)
			break;
		else if (op == bv_opcode_push_stack) {
			bv_type type = bv_type_read(&code);
			bv_stack_push(&stack, bv_variable_read(&code, type));
		}
		else if (op == bv_opcode_add) {
			if (stack.length < 2) // dont do anything if there is not enough arguments in stack
				continue;
			bv_variable var1 = bv_stack_penultimate(&stack);
			bv_variable var2 = bv_stack_top(&stack);

			if (var1.type == bv_type_float || var2.type == bv_type_float) {
				float sum = 0;

				if (var1.type == bv_type_float)
					sum += bv_variable_get_float(var1);
				else sum += bv_variable_get_uint(var1);
				if (var2.type == bv_type_float)
					sum += bv_variable_get_float(var2);
				else sum += bv_variable_get_uint(var2);

				bv_stack_pop(&stack);
				bv_stack_pop(&stack);

				bv_stack_push(&stack, bv_variable_create_float(sum));
			}
			else if (var1.type == bv_type_string && var2.type == bv_type_string) {
				string result = malloc(strlen(var1.value) + strlen(var2.value) + 1);
				strcpy(result, var1.value);
				strcpy(result+strlen(var1.value), var2.value);
				result[strlen(var1.value) + strlen(var2.value)] = 0;

				bv_stack_pop(&stack);
				bv_stack_pop(&stack);

				bv_stack_push(&stack, bv_variable_create_string(result));
				free(result);
			}
			else {
				u32 sum = bv_variable_get_uint(var1) + bv_variable_get_uint(var2);
				bv_type type = var1.type;

				bv_stack_pop(&stack);
				bv_stack_pop(&stack);

				bv_stack_push(&stack, bv_variable_create(type, sum));
			}
		} else if (op == bv_opcode_const_get) {
			bv_type type = bv_type_read(&code);
			u16 index = u16_read(&code);

			for (u8 i = 0; i < cpool->type_count; i++)
				if (cpool->val_type[i] == type) {
					if (index < cpool->val_count[i])
						bv_stack_push(&stack, bv_variable_copy(cpool->val[i][index]));
					break;
				}
		}
	}

	// get return value
	if (stack.length > 0)
		rtrn = bv_variable_copy(bv_stack_top(&stack)); // on return, make a copy of the return value
	else
		rtrn = bv_variable_create_int(0);

	bv_stack_delete(&stack);

	return rtrn;
}
