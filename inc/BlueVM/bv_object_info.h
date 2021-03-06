#ifndef __BLUEVM_OBJECT_INFO_H__
#define __BLUEVM_OBJECT_INFO_H__

#include <BlueVM/types.h>
#include <BlueVM/bv_header.h>
#include <BlueVM/bv_name_list.h>
#include <BlueVM/bv_function.h>

typedef struct bv_function_pool_s bv_function_pool;
typedef struct bv_variable_s bv_variable;

typedef bv_variable(*bv_external_method)(bv_program*, bv_object*, u8, bv_variable*);
typedef void(*bv_object_info_on_delete)(bv_object*);
typedef void* (*bv_object_info_on_copy)(void*);

typedef struct bv_object_info_s {
	bv_string name;			// class type/object name (eg "Vehicle", "Animal", etc...)

	bv_name_list props;		// property names

	bv_function_pool* method_info;
	bv_function** methods;	// method data

	u16 ext_method_count;
	bv_external_method* ext_methods;
	bv_string* ext_method_names;

	bv_object_info_on_delete on_delete; // so that user can delete some allocated data stored under user_data
	bv_object_info_on_copy on_copy; // so that user can copy some allocated data stored under user_data
} bv_object_info;

bv_object_info* bv_object_info_create(const bv_string name);
bv_object_info* bv_object_info_read(bv_header header, byte** mem, byte* orig_mem);
void bv_object_info_delete(bv_object_info* info);

void bv_object_info_add_property(bv_object_info* info, const bv_string name);
void bv_object_info_add_ext_method(bv_object_info* info, const bv_string name, bv_external_method method);

#endif