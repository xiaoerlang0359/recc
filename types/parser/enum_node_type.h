#ifndef TYPES_PARSER_enum_node_type_H__
#define TYPES_PARSER_enum_node_type_H__
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

enum node_type{
	TERMINAL,
	EPSILON,
	PRIMARY_EXPRESSION,
	POSTFIX_EXPRESSION,
	POSTFIX_EXPRESSION_REST,
	UNARY_EXPRESSION,
	UNARY_OPERATOR,
	CAST_EXPRESSION,
	MULTIPLICATIVE_EXPRESSION,
	MULTIPLICATIVE_EXPRESSION_REST,
	ADDITIVE_EXPRESSION,
	ADDITIVE_EXPRESSION_REST,
	SHIFT_EXPRESSION,
	SHIFT_EXPRESSION_REST,
	RELATIONAL_EXPRESSION,
	RELATIONAL_EXPRESSION_REST,
	EQUALITY_EXPRESSION,
	EQUALITY_EXPRESSION_REST,
	AND_EXPRESSION,
	AND_EXPRESSION_REST,
	EXCLUSIVE_OR_EXPRESSION,
	EXCLUSIVE_OR_EXPRESSION_REST,
	INCLUSIVE_OR_EXPRESSION,
	INCLUSIVE_OR_EXPRESSION_REST,
	LOGICAL_AND_EXPRESSION,
	LOGICAL_AND_EXPRESSION_REST,
	LOGICAL_OR_EXPRESSION,
	LOGICAL_OR_EXPRESSION_REST,
	CONDITIONAL_EXPRESSION,
	ASSIGNMENT_EXPRESSION,
	ASSIGNMENT_OPERATOR,
	EXPRESSION_REST,
	EXPRESSION,
	CONSTANT_EXPRESSION,
	EXPRESSION_STATEMENT,
	LABELED_STATEMENT,
	SELECTION_STATEMENT,
	ITERATION_STATEMENT,
	JUMP_STATEMENT,
	STATEMENT,
	STATEMENT_LIST,
	STATEMENT_LIST_REST,
	COMPOUND_STATEMENT,
	TYPE_QUALIFIER,
	TYPE_QUALIFIER_LIST,
	TYPE_QUALIFIER_LIST_REST,
	STORAGE_CLASS_SPECIFIER,
	TYPE_SPECIFIER,
	ENUM_SPECIFIER,
	DECLARATION_SPECIFIERS,
	DECLARATION,
	DECLARATION_LIST,
	DECLARATION_LIST_REST,
	DIRECT_DECLARATOR_REST,
	DIRECT_DECLARATOR,
	DIRECT_ABSTRACT_DECLARATOR,
	DIRECT_ABSTRACT_DECLARATOR_REST,
	TYPE_NAME,
	ABSTRACT_DECLARATOR,
	DECLARATOR,
	INIT_DECLARATOR,
	INIT_DECLARATOR_LIST,
	INIT_DECLARATOR_LIST_REST,
	INITIALIZER,
	INITIALIZER_LIST,
	INITIALIZER_LIST_REST,
	IDENTIFIER_LIST,
	IDENTIFIER_LIST_REST,
	POINTER,
	STRUCT_OR_UNION,
	STRUCT_DECLARATOR,
	STRUCT_DECLARATOR_LIST,
	STRUCT_DECLARATOR_LIST_REST,
	STRUCT_DECLARATION,
	STRUCT_DECLARATION_LIST,
	STRUCT_DECLARATION_LIST_REST,
	STRUCT_OR_UNION_SPECIFIER,
	SPECIFIER_QUALIFIER_LIST,
	PARAMETER_DECLARATION,
	ARGUMENT_EXPRESSION_LIST,
	ARGUMENT_EXPRESSION_LIST_REST,
	PARAMETER_LIST,
	PARAMETER_LIST_REST,
	PARAMETER_TYPE_LIST,
	ENUMERATOR_LIST,
	ENUMERATOR_LIST_REST,
	ENUMERATOR,
	TRANSLATION_UNIT,
	TRANSLATION_UNIT_REST,
	EXTERNAL_DECLARATION,
	FUNCTION_DEFINITION
};

#endif