#ifndef __TYPES_DATA_STRUCTURES_struct_unsigned_char_ptr_to_struct_linker_symbol_ptr_key_value_pair_H__
#define __TYPES_DATA_STRUCTURES_struct_unsigned_char_ptr_to_struct_linker_symbol_ptr_key_value_pair_H__
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

#ifndef __TYPES_LINKER_struct_linker_symbol_h__
#include "../../types/linker/struct_linker_symbol.h"
#endif

struct unsigned_char_ptr_to_struct_linker_symbol_ptr_key_value_pair{
	unsigned char * key;
	struct linker_symbol * value;
};

#endif
