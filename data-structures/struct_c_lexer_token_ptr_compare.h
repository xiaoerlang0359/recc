#ifndef struct_c_lexer_token_ptr_compare__H__DEFINED__
#define struct_c_lexer_token_ptr_compare__H__DEFINED__
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

#ifndef TYPES_LEXER_struct_c_lexer_token_H__
#include "../types/lexer/struct_c_lexer_token.h"
#endif

int struct_c_lexer_token_ptr_compare(struct c_lexer_token *, struct c_lexer_token *);

#endif