#ifndef recc_implementation_DIR_asm_functions_DOT_h
#define recc_implementation_DIR_asm_functions_DOT_h
/*
    Copyright 2016 Robert Elder Software Inc.
    
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

#ifndef recc_implementation_DIR_asm_DOT_h
#include "asm.h"
#endif
unsigned int undo_basic_asm_operation(struct asm_state *, enum asm_operation_type);
void create_asm_state(struct asm_state *, struct memory_pool_collection *);
void destroy_asm_state(struct asm_state *);
void print_aggregate_type_specifier(struct asm_state *, struct unsigned_char_list *, struct aggregate_type_specifier_id);
void print_simple_type_specifier(struct asm_state *, struct unsigned_char_list *, struct simple_type_specifier_id);
void print_simple_type_qualifier(struct asm_state *, struct unsigned_char_list *, struct simple_type_qualifier_id);
void print_simple_storage_class_specifier(struct asm_state *, struct unsigned_char_list *, struct simple_storage_class_specifier_id);
void print_specifier_or_qualifier(struct asm_state *, struct unsigned_char_list *, struct specifier_or_qualifier_id);
void print_specifier_or_qualifier_list_item(struct asm_state *, struct unsigned_char_list *, struct specifier_or_qualifier_list_item_id);
void print_parameter_list(struct asm_state *, struct unsigned_char_list *, struct parameter_list_id);
void print_initializer(struct asm_state *, struct unsigned_char_list *, struct initializer_id);
void print_declarator_part(struct asm_state *, struct unsigned_char_list *, struct declarator_part_id);
void print_any_statement_list_item(struct asm_state *, struct unsigned_char_list *, struct any_statement_list_item_id);
void print_anonymous_tag_definition(struct asm_state *, struct unsigned_char_list *, struct anonymous_tag_definition_id);
void print_named_tag_predeclaration(struct asm_state *, struct unsigned_char_list *, struct named_tag_predeclaration_id);
void print_named_tag_definition(struct asm_state *, struct unsigned_char_list *, struct named_tag_definition_id);
void print_tag_definition(struct asm_state *, struct unsigned_char_list *, struct tag_definition_id);
void print_struct_or_union_member_list_item(struct asm_state *, struct unsigned_char_list *, struct struct_or_union_member_list_item_id);
void print_enum_member_list_item(struct asm_state *, struct unsigned_char_list *, struct enum_member_list_item_id);
void print_enum_member(struct asm_state *, struct unsigned_char_list *, struct enum_member_id);
void print_struct_or_union_member(struct asm_state *, struct unsigned_char_list *, struct struct_or_union_member_id);
void print_layout_flag_list_item(struct asm_state *, struct unsigned_char_list *, struct layout_flag_list_item_id);
void print_layout_flag(struct asm_state *, struct unsigned_char_list *, struct layout_flag_id);
void print_initializer_list_item(struct asm_state *, struct unsigned_char_list *, struct initializer_list_item_id);
void print_expression_list_item(struct asm_state *, struct unsigned_char_list *, struct expression_list_item_id);
void print_declarator_part_list_item(struct asm_state *, struct unsigned_char_list *, struct declarator_part_list_item_id);
void print_pointer_part(struct asm_state *, struct unsigned_char_list *, struct pointer_part_id);
void print_function_part(struct asm_state *, struct unsigned_char_list *, struct function_part_id);
void print_array_part(struct asm_state *, struct unsigned_char_list *, struct array_part_id);
void print_general_type(struct asm_state *, struct unsigned_char_list *, struct general_type_id);
void print_typedef_entry(struct asm_state *, struct unsigned_char_list *, struct typedef_entry_id);
void print_general_type_list_item(struct asm_state *, struct unsigned_char_list *, struct general_type_list_item_id);
void print_postfix_expression_part_list_item(struct asm_state *, struct unsigned_char_list *, struct postfix_expression_part_list_item_id);
void print_postfix_expression_part(struct asm_state *, struct unsigned_char_list *, struct postfix_expression_part_id);
void print_unscoped_tag_specifier(struct asm_state *, struct unsigned_char_list *, struct unscoped_tag_specifier_id);
void print_scoped_typename_specifier(struct asm_state *, struct unsigned_char_list *, struct scoped_typename_specifier_id);
void print_scoped_tag_specifier(struct asm_state *, struct unsigned_char_list *, struct scoped_tag_specifier_id);
void print_unscoped_union_specifier(struct asm_state *, struct unsigned_char_list *, struct unscoped_union_specifier_id);
void print_unscoped_struct_specifier(struct asm_state *, struct unsigned_char_list *, struct unscoped_struct_specifier_id);
void print_unscoped_enum_specifier(struct asm_state *, struct unsigned_char_list *, struct unscoped_enum_specifier_id);
void print_bitfield(struct asm_state *, struct unsigned_char_list *, struct bitfield_id);
void print_jump_statement(struct asm_state *, struct unsigned_char_list *, struct jump_statement_id);
void print_switch_statement(struct asm_state *, struct unsigned_char_list *, struct switch_statement_id);
void print_if_statement(struct asm_state *, struct unsigned_char_list *, struct if_statement_id);
void print_while_statement(struct asm_state *, struct unsigned_char_list *, struct while_statement_id);
void print_for_statement(struct asm_state *, struct unsigned_char_list *, struct for_statement_id);
void print_code_statement(struct asm_state *, struct unsigned_char_list *, struct code_statement_id);
void print_labeled_statement(struct asm_state *, struct unsigned_char_list *, struct labeled_statement_id);
void print_postfix_expression(struct asm_state *, struct unsigned_char_list *, struct postfix_expression_id);
void print_primary_expression(struct asm_state *, struct unsigned_char_list *, struct primary_expression_id);
void print_any_statement(struct asm_state *, struct unsigned_char_list *, struct any_statement_id);
void print_scoped_statement(struct asm_state *, struct unsigned_char_list *, struct scoped_statement_id);
void print_declaration_statement(struct asm_state *, struct unsigned_char_list *, struct declaration_statement_id);
void print_function_definition(struct asm_state *, struct unsigned_char_list *, struct function_definition_id);
void print_simple_declaration(struct asm_state *, struct unsigned_char_list *, struct simple_declaration_id);
void print_expression(struct asm_state *, struct unsigned_char_list *, struct expression_id);
void print_cast_expression(struct asm_state *, struct unsigned_char_list *, struct cast_expression_id);
void print_unary_expression(struct asm_state *, struct unsigned_char_list *, struct unary_expression_id);
void print_binary_expression(struct asm_state *, struct unsigned_char_list *, struct binary_expression_id);
void print_ternary_expression(struct asm_state *, struct unsigned_char_list *, struct ternary_expression_id);
void print_constant_description(struct asm_state *, struct unsigned_char_list *, struct constant_description_id);
void print_data_package(struct asm_state *, struct unsigned_char_list *, struct data_package_id);
void print_error_node(struct asm_state *, struct unsigned_char_list *, struct error_node_id);
void print_byte_package(struct asm_state *, struct unsigned_char_list *, struct byte_package_id);
void print_hword_package(struct asm_state *, struct unsigned_char_list *, struct hword_package_id);
void print_word_package(struct asm_state *, struct unsigned_char_list *, struct word_package_id);
void print_qword_package(struct asm_state *, struct unsigned_char_list *, struct qword_package_id);
void print_dword_package(struct asm_state *, struct unsigned_char_list *, struct dword_package_id);
void print_string_package(struct asm_state *, struct unsigned_char_list *, struct string_package_id);
void print_identifier(struct asm_state *, struct unsigned_char_list *, struct identifier_id);
void print_scope_guid(struct asm_state *, struct unsigned_char_list *, struct scope_guid_id);
void print_anonymous_instance(struct asm_state *, struct unsigned_char_list *, struct anonymous_instance_id);
struct aggregate_type_specifier_id make_aggregate_type_specifier_simple_type_specifier(struct asm_state *, struct simple_type_specifier_id);
struct aggregate_type_specifier_id make_aggregate_type_specifier_tag_specifier(struct asm_state *, struct scoped_tag_specifier_id);
struct aggregate_type_specifier_id make_aggregate_type_specifier_typename_specifier(struct asm_state *, struct scoped_typename_specifier_id);
struct simple_type_specifier_id make_simple_type_specifier_void(struct asm_state *);
struct simple_type_specifier_id make_simple_type_specifier_char(struct asm_state *);
struct simple_type_specifier_id make_simple_type_specifier_short(struct asm_state *);
struct simple_type_specifier_id make_simple_type_specifier_int(struct asm_state *);
struct simple_type_specifier_id make_simple_type_specifier_long(struct asm_state *);
struct simple_type_specifier_id make_simple_type_specifier_float(struct asm_state *);
struct simple_type_specifier_id make_simple_type_specifier_double(struct asm_state *);
struct simple_type_specifier_id make_simple_type_specifier_signed(struct asm_state *);
struct simple_type_specifier_id make_simple_type_specifier_unsigned(struct asm_state *);
struct simple_type_qualifier_id make_simple_type_qualifier_const(struct asm_state *);
struct simple_type_qualifier_id make_simple_type_qualifier_volatile(struct asm_state *);
struct simple_storage_class_specifier_id make_simple_storage_class_specifier_typedef(struct asm_state *);
struct simple_storage_class_specifier_id make_simple_storage_class_specifier_extern(struct asm_state *);
struct simple_storage_class_specifier_id make_simple_storage_class_specifier_static(struct asm_state *);
struct simple_storage_class_specifier_id make_simple_storage_class_specifier_auto(struct asm_state *);
struct simple_storage_class_specifier_id make_simple_storage_class_specifier_register(struct asm_state *);
struct specifier_or_qualifier_id make_specifier_or_qualifier_simple_storage_class_specifier(struct asm_state *, struct simple_storage_class_specifier_id);
struct specifier_or_qualifier_id make_specifier_or_qualifier_simple_type_qualifier(struct asm_state *, struct simple_type_qualifier_id);
struct specifier_or_qualifier_id make_specifier_or_qualifier_aggregate_type_specifier(struct asm_state *, struct aggregate_type_specifier_id);
struct specifier_or_qualifier_list_item_id make_specifier_or_qualifier_list_item_specifier_or_qualifier(struct asm_state *, struct specifier_or_qualifier_list_item_id, struct specifier_or_qualifier_id);
struct specifier_or_qualifier_list_item_id make_specifier_or_qualifier_list_item_list_start(struct asm_state *);
struct parameter_list_id make_parameter_list_variadic(struct asm_state *, struct general_type_list_item_id);
struct parameter_list_id make_parameter_list_non_variadic(struct asm_state *, struct general_type_list_item_id);
struct initializer_id make_initializer_initializer_list(struct asm_state *, struct initializer_list_item_id);
struct initializer_id make_initializer_expression(struct asm_state *, struct expression_id);
struct declarator_part_id make_declarator_part_function(struct asm_state *, struct function_part_id);
struct declarator_part_id make_declarator_part_pointer(struct asm_state *, struct pointer_part_id);
struct declarator_part_id make_declarator_part_array(struct asm_state *, struct array_part_id);
struct any_statement_list_item_id make_any_statement_list_item_any_statement(struct asm_state *, struct any_statement_list_item_id, struct any_statement_id);
struct any_statement_list_item_id make_any_statement_list_item_list_start(struct asm_state *);
struct anonymous_tag_definition_id make_anonymous_tag_definition_anonymous(struct asm_state *, struct tag_definition_id, struct scope_guid_id, struct anonymous_instance_id);
struct named_tag_predeclaration_id make_named_tag_predeclaration_named(struct asm_state *, struct scope_guid_id, struct identifier_id);
struct named_tag_definition_id make_named_tag_definition_named(struct asm_state *, struct tag_definition_id, struct scope_guid_id, struct identifier_id);
struct tag_definition_id make_tag_definition_enum(struct asm_state *, struct enum_member_list_item_id);
struct tag_definition_id make_tag_definition_struct(struct asm_state *, struct struct_or_union_member_list_item_id);
struct tag_definition_id make_tag_definition_union(struct asm_state *, struct struct_or_union_member_list_item_id);
struct struct_or_union_member_list_item_id make_struct_or_union_member_list_item_member(struct asm_state *, struct struct_or_union_member_list_item_id, struct struct_or_union_member_id);
struct struct_or_union_member_list_item_id make_struct_or_union_member_list_item_list_start(struct asm_state *);
struct enum_member_list_item_id make_enum_member_list_item_member(struct asm_state *, struct enum_member_list_item_id, struct enum_member_id);
struct enum_member_list_item_id make_enum_member_list_item_list_start(struct asm_state *);
struct enum_member_id make_enum_member_member(struct asm_state *, struct identifier_id, struct expression_id);
struct struct_or_union_member_id make_struct_or_union_member_member(struct asm_state *, struct general_type_id, struct layout_flag_list_item_id, struct identifier_id);
struct layout_flag_list_item_id make_layout_flag_list_item_layout_flag(struct asm_state *, struct layout_flag_list_item_id, struct layout_flag_id);
struct layout_flag_list_item_id make_layout_flag_list_item_list_start(struct asm_state *);
struct layout_flag_id make_layout_flag_struct(struct asm_state *);
struct layout_flag_id make_layout_flag_union(struct asm_state *);
struct initializer_list_item_id make_initializer_list_item_initializer(struct asm_state *, struct initializer_list_item_id, struct initializer_id);
struct initializer_list_item_id make_initializer_list_item_list_start(struct asm_state *);
struct expression_list_item_id make_expression_list_item_expression(struct asm_state *, struct expression_list_item_id, struct expression_id);
struct expression_list_item_id make_expression_list_item_list_start(struct asm_state *);
struct declarator_part_list_item_id make_declarator_part_list_item_declarator_part(struct asm_state *, struct declarator_part_list_item_id, struct declarator_part_id);
struct declarator_part_list_item_id make_declarator_part_list_item_list_start(struct asm_state *);
struct pointer_part_id make_pointer_part_pointer(struct asm_state *, struct specifier_or_qualifier_list_item_id);
struct function_part_id make_function_part_prototype(struct asm_state *, struct parameter_list_id);
struct function_part_id make_function_part_k_and_r_c(struct asm_state *, struct parameter_list_id);
struct array_part_id make_array_part_expression(struct asm_state *, struct expression_id);
struct array_part_id make_array_part_flexible(struct asm_state *);
struct general_type_id make_general_type_general_type(struct asm_state *, struct specifier_or_qualifier_list_item_id, struct declarator_part_list_item_id, struct bitfield_id);
struct typedef_entry_id make_typedef_entry_typedef(struct asm_state *, struct identifier_id, struct scope_guid_id, struct general_type_id);
struct general_type_list_item_id make_general_type_list_item_general_type(struct asm_state *, struct general_type_list_item_id, struct general_type_id);
struct general_type_list_item_id make_general_type_list_item_list_start(struct asm_state *);
struct postfix_expression_part_list_item_id make_postfix_expression_part_list_item_postfix_expression_part(struct asm_state *, struct postfix_expression_part_list_item_id, struct postfix_expression_part_id);
struct postfix_expression_part_list_item_id make_postfix_expression_part_list_item_list_start(struct asm_state *);
struct postfix_expression_part_id make_postfix_expression_part_array_dereference(struct asm_state *, struct expression_id);
struct postfix_expression_part_id make_postfix_expression_part_struct_dot_dereference(struct asm_state *, struct identifier_id);
struct postfix_expression_part_id make_postfix_expression_part_struct_arrow_dereference(struct asm_state *, struct identifier_id);
struct postfix_expression_part_id make_postfix_expression_part_function_dereference(struct asm_state *, struct expression_list_item_id);
struct postfix_expression_part_id make_postfix_expression_part_inc(struct asm_state *);
struct postfix_expression_part_id make_postfix_expression_part_dec(struct asm_state *);
struct unscoped_tag_specifier_id make_unscoped_tag_specifier_struct_specifier(struct asm_state *, struct unscoped_struct_specifier_id);
struct unscoped_tag_specifier_id make_unscoped_tag_specifier_union_specifier(struct asm_state *, struct unscoped_union_specifier_id);
struct unscoped_tag_specifier_id make_unscoped_tag_specifier_enum_specifier(struct asm_state *, struct unscoped_enum_specifier_id);
struct scoped_typename_specifier_id make_scoped_typename_specifier_scoped_typename(struct asm_state *, struct scope_guid_id, struct identifier_id);
struct scoped_tag_specifier_id make_scoped_tag_specifier_scoped_tag_specifier(struct asm_state *, struct scope_guid_id, struct unscoped_tag_specifier_id);
struct unscoped_union_specifier_id make_unscoped_union_specifier_named_union(struct asm_state *, struct identifier_id);
struct unscoped_union_specifier_id make_unscoped_union_specifier_anonymous_union(struct asm_state *, struct anonymous_instance_id);
struct unscoped_struct_specifier_id make_unscoped_struct_specifier_named_struct(struct asm_state *, struct identifier_id);
struct unscoped_struct_specifier_id make_unscoped_struct_specifier_anonymous_struct(struct asm_state *, struct anonymous_instance_id);
struct unscoped_enum_specifier_id make_unscoped_enum_specifier_named_enum(struct asm_state *, struct identifier_id);
struct unscoped_enum_specifier_id make_unscoped_enum_specifier_anonymous_enum(struct asm_state *, struct anonymous_instance_id);
struct bitfield_id make_bitfield_no_bitfield(struct asm_state *);
struct bitfield_id make_bitfield_constant_bitfield(struct asm_state *, struct expression_id);
struct jump_statement_id make_jump_statement_return_expression(struct asm_state *, struct expression_id);
struct jump_statement_id make_jump_statement_return_no_expression(struct asm_state *);
struct jump_statement_id make_jump_statement_break(struct asm_state *);
struct jump_statement_id make_jump_statement_continue(struct asm_state *);
struct jump_statement_id make_jump_statement_goto(struct asm_state *, struct identifier_id);
struct switch_statement_id make_switch_statement_switch(struct asm_state *, struct expression_id, struct any_statement_id);
struct if_statement_id make_if_statement_just_if(struct asm_state *, struct any_statement_id, struct expression_id);
struct if_statement_id make_if_statement_if_else(struct asm_state *, struct any_statement_id, struct expression_id, struct any_statement_id);
struct while_statement_id make_while_statement_do_while(struct asm_state *, struct expression_id, struct any_statement_id);
struct while_statement_id make_while_statement_while(struct asm_state *, struct expression_id, struct any_statement_id);
struct for_statement_id make_for_statement_for(struct asm_state *, struct expression_list_item_id, struct expression_list_item_id, struct expression_list_item_id);
struct code_statement_id make_code_statement_labeled_statement(struct asm_state *, struct labeled_statement_id);
struct code_statement_id make_code_statement_compound_statement(struct asm_state *, struct any_statement_list_item_id);
struct code_statement_id make_code_statement_expression_statement(struct asm_state *, struct expression_list_item_id);
struct code_statement_id make_code_statement_for_statement(struct asm_state *, struct for_statement_id);
struct code_statement_id make_code_statement_while_statement(struct asm_state *, struct while_statement_id);
struct code_statement_id make_code_statement_if_statement(struct asm_state *, struct if_statement_id);
struct code_statement_id make_code_statement_switch_statement(struct asm_state *, struct switch_statement_id);
struct code_statement_id make_code_statement_jump_statement(struct asm_state *, struct jump_statement_id);
struct labeled_statement_id make_labeled_statement_goto_label(struct asm_state *, struct any_statement_id);
struct labeled_statement_id make_labeled_statement_case_label(struct asm_state *, struct any_statement_id, struct expression_id);
struct labeled_statement_id make_labeled_statement_default_label(struct asm_state *, struct any_statement_id);
struct postfix_expression_id make_postfix_expression_postfix_expression(struct asm_state *, struct primary_expression_id, struct postfix_expression_part_list_item_id);
struct primary_expression_id make_primary_expression_constant_description(struct asm_state *, struct constant_description_id);
struct primary_expression_id make_primary_expression_identifier(struct asm_state *, struct identifier_id);
struct primary_expression_id make_primary_expression_expression(struct asm_state *, struct expression_id);
struct any_statement_id make_any_statement_declaration_statement(struct asm_state *, struct declaration_statement_id);
struct any_statement_id make_any_statement_scoped_statement(struct asm_state *, struct scoped_statement_id);
struct any_statement_id make_any_statement_code_statement(struct asm_state *, struct code_statement_id);
struct scoped_statement_id make_scoped_statement_function_scope(struct asm_state *, struct any_statement_list_item_id, struct scope_guid_id);
struct scoped_statement_id make_scoped_statement_block_scope(struct asm_state *, struct any_statement_list_item_id, struct scope_guid_id);
struct scoped_statement_id make_scoped_statement_file_scope(struct asm_state *, struct any_statement_list_item_id, struct scope_guid_id);
struct declaration_statement_id make_declaration_statement_simple_declaration(struct asm_state *, struct simple_declaration_id);
struct declaration_statement_id make_declaration_statement_function_definition(struct asm_state *, struct function_definition_id);
struct function_definition_id make_function_definition_prototyped(struct asm_state *, struct general_type_id, struct any_statement_list_item_id, struct any_statement_list_item_id, struct identifier_id);
struct function_definition_id make_function_definition_k_and_r_c(struct asm_state *, struct general_type_id, struct any_statement_list_item_id, struct any_statement_list_item_id, struct identifier_id);
struct simple_declaration_id make_simple_declaration_simple_declaration(struct asm_state *, struct general_type_id, struct identifier_id, struct initializer_id);
struct expression_id make_expression_cast_expression(struct asm_state *, struct cast_expression_id);
struct expression_id make_expression_binary_expression(struct asm_state *, struct binary_expression_id);
struct expression_id make_expression_ternary_expression(struct asm_state *, struct ternary_expression_id);
struct cast_expression_id make_cast_expression_has_cast(struct asm_state *, struct cast_expression_id, struct general_type_id);
struct cast_expression_id make_cast_expression_no_cast(struct asm_state *, struct unary_expression_id);
struct unary_expression_id make_unary_expression_sizeof_expression(struct asm_state *, struct expression_id);
struct unary_expression_id make_unary_expression_postfix_expression(struct asm_state *, struct postfix_expression_id);
struct unary_expression_id make_unary_expression_sizeof_type(struct asm_state *, struct general_type_id);
struct unary_expression_id make_unary_expression_inc(struct asm_state *, struct expression_id);
struct unary_expression_id make_unary_expression_dec(struct asm_state *, struct expression_id);
struct unary_expression_id make_unary_expression_address(struct asm_state *, struct expression_id);
struct unary_expression_id make_unary_expression_point_to(struct asm_state *, struct expression_id);
struct unary_expression_id make_unary_expression_positive(struct asm_state *, struct expression_id);
struct unary_expression_id make_unary_expression_negative(struct asm_state *, struct expression_id);
struct unary_expression_id make_unary_expression_bitwise_not(struct asm_state *, struct expression_id);
struct unary_expression_id make_unary_expression_logical_not(struct asm_state *, struct expression_id);
struct binary_expression_id make_binary_expression_plus(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_minus(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_divide(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_multiply(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_exclusive_or(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_modulus(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_bitwise_or(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_logical_or(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_bitwise_and(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_logical_and(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_lt(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_gt(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_le(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_ge(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_eq(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_assign(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_add_assign(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_sub_assign(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_div_assign(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_mul_assign(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_and_assign(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_or_assign(struct asm_state *, struct expression_id, struct expression_id);
struct binary_expression_id make_binary_expression_mod_assign(struct asm_state *, struct expression_id, struct expression_id);
struct ternary_expression_id make_ternary_expression_ternary_operator(struct asm_state *, struct expression_id, struct expression_id, struct expression_id);
struct constant_description_id make_constant_description_constant_description(struct asm_state *, struct general_type_id, struct data_package_id);
struct data_package_id make_data_package_error(struct asm_state *, struct error_node_id);
struct data_package_id make_data_package_byte(struct asm_state *, struct byte_package_id);
struct data_package_id make_data_package_hword(struct asm_state *, struct hword_package_id);
struct data_package_id make_data_package_word(struct asm_state *, struct word_package_id);
struct data_package_id make_data_package_dword(struct asm_state *, struct dword_package_id);
struct data_package_id make_data_package_qword(struct asm_state *, struct qword_package_id);
struct data_package_id make_data_package_string(struct asm_state *, struct string_package_id);
struct error_node_id make_error_node_error(struct asm_state *);
struct byte_package_id make_byte_package_byte(struct asm_state *, unsigned char);
struct hword_package_id make_hword_package_hword(struct asm_state *, unsigned char, unsigned char);
struct word_package_id make_word_package_word(struct asm_state *, unsigned int);
struct qword_package_id make_qword_package_qword(struct asm_state *, unsigned int, unsigned int, unsigned int, unsigned int);
struct dword_package_id make_dword_package_dword(struct asm_state *, unsigned int, unsigned int);
struct string_package_id make_string_package_string(struct asm_state *, unsigned int, unsigned char *);
struct identifier_id make_identifier_identifier(struct asm_state *, struct c_lexer_token *);
struct scope_guid_id make_scope_guid_block_scope(struct asm_state *);
struct scope_guid_id make_scope_guid_file_scope(struct asm_state *);
struct scope_guid_id make_scope_guid_function_scope(struct asm_state *);
struct anonymous_instance_id make_anonymous_instance_anonymous_entry(struct asm_state *);
#endif
