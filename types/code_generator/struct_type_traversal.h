#ifndef TYPES_CODE_GENERATOR_struct_type_traversal_H__
#define TYPES_CODE_GENERATOR_struct_type_traversal_H__
/*
    Copyright 2015 Robert Elder Software Inc.
    
    Licensed under the Apache License, Version 2.0 (the "License"); you may not 
    use this file except in compliance with the License.  You may obtain a copy 
    of the License at
    
        http://www.apache.org/licenses/LICENSE-2.0
    
    Unless required by applicable law or agreed to in writing, software 
    distributed under the License is distributed on an "AS IS" BASIS, WITHOUT 
    WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the 
    License for the specific language governing permissions and limitations 
    under the License.
*/

#ifndef TYPES_PARSER_enum_type_class_H__
#include "../../types/parser/enum_type_class.h"
#endif
#ifndef TYPES_PARSER_struct_type_description_H__
#include "../../types/parser/struct_type_description.h"
#endif
#ifndef TYPES_DATA_STRUCTURES_struct_type_traversal_ptr_list_H__
#include "../../types/data-structures/struct_struct_type_traversal_ptr_list.h"
#endif

struct type_traversal{
	struct type_description * type_description;
	struct struct_type_traversal_ptr_list children;
	unsigned int arity; /* For arrays */
	unsigned int arrays_as_pointers; /* For arrays */
	unsigned char * parent_tag_name; /* structs, enums, unions */
	unsigned char * member_name; /* for structs, enums */
	enum type_class type_class;
	unsigned int pad;
};

#endif