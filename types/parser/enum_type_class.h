#ifndef TYPES_PARSER_enum_type_class_H__
#define TYPES_PARSER_enum_type_class_H__
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

enum type_class{
	TYPE_CLASS_CHAR,
	TYPE_CLASS_SHORT,
	TYPE_CLASS_INT,
	TYPE_CLASS_LONG,
	TYPE_CLASS_LONG_LONG,
	TYPE_CLASS_FLOAT,
	TYPE_CLASS_DOUBLE,
	TYPE_CLASS_LONG_DOUBLE,
	TYPE_CLASS_VOID,
	TYPE_CLASS_POINTER,
	TYPE_CLASS_ARRAY,
	TYPE_CLASS_FUNCTION,
	TYPE_CLASS_ENUM,
	TYPE_CLASS_STRUCT,
	TYPE_CLASS_UNION
};

#endif