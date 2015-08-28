#ifndef __TYPES_PARSER_struct_normalized_specifier_H__
#define __TYPES_PARSER_struct_normalized_specifier_H__
/*
	Copyright 2015 Robert Elder Software Inc.  All rights reserved.

	This software is not currently available under any license, and unauthorized use
	or copying is not permitted.

	This software will likely be available under a common open source license in the
	near future.  Licensing is currently pending feedback from a lawyer.  If you have
	an opinion on this subject you can send it to recc [at] robertelder.org.

	This program comes with ABSOLUTELY NO WARRANTY.  In no event shall Robert Elder
	Software Inc. be liable for incidental or consequential damages in connection with
	use of this software.
*/


#ifndef __TYPES_PARSER_enum_normalized_specifier_type_H__
#include "enum_normalized_specifier_type.h"
#endif
#ifndef __TYPES_PARSER_struct_parser_node_H__
#include "struct_parser_node.h"
#endif

struct normalized_specifier{
	/*  
	    Used for abstracting away declaration_specifiers, type_specifier_list,
	    and qualifier_specifier_list
	*/
	struct parser_node * specifier;
	enum normalized_specifier_type type;
	unsigned int pad;
};

#endif
