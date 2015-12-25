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
#include "lexer.h"

#define SHOW_LEXER_TOKENS 0

static const char * c_token_type_names[90] = {
	"SPACE",
	"NEWLINE",
	"COMMENT",
	"AUTO",
	"BREAK",
	"CASE",
	"CHAR",
	"CONST",
	"CONTINUE",
	"DEFAULT",
	"DO",
	"DOUBLE",
	"ELSE",
	"ENUM",
	"EXTERN",
	"FLOAT",
	"FOR",
	"GOTO",
	"IF",
	"INT",
	"LONG",
	"REGISTER",
	"RETURN",
	"SHORT",
	"SIGNED",
	"SIZEOF",
	"STATIC",
	"STRUCT",
	"SWITCH",
	"TYPEDEF",
	"UNION",
	"UNSIGNED",
	"VOID",
	"VOLATILE",
	"WHILE",
	"IDENTIFIER",
	"CONSTANT_HEX",
	"CONSTANT_EXPONENT",
	"CONSTANT_FLOAT_SMALL",
	"CONSTANT_FLOAT_LARGE",
	"CONSTANT_DECIMAL",
	"CONSTANT_CHARACTER",
	"STRING_LITERAL",
	"ELLIPSIS",
	"RIGHT_ASSIGN",
	"LEFT_ASSIGN",
	"ADD_ASSIGN",
	"SUB_ASSIGN",
	"MUL_ASSIGN",
	"DIV_ASSIGN",
	"MOD_ASSIGN",
	"AND_ASSIGN",
	"XOR_ASSIGN",
	"OR_ASSIGN",
	"RIGHT_OP",
	"LEFT_OP",
	"INC_OP",
	"DEC_OP",
	"PTR_OP",
	"AND_OP",
	"OR_OP",
	"LE_OP",
	"GE_OP",
	"EQ_OP",
	"NE_OP",
	"SEMICOLON_CHAR",
	"OPEN_BRACE_CHAR",
	"CLOSE_BRACE_CHAR",
	"OPEN_SQUARE_BRACKET_CHAR",
	"CLOSE_SQUARE_BRACKET_CHAR",
	"COMMA_CHAR",
	"COLON_CHAR",
	"EQUALS_CHAR",
	"OPEN_PAREN_CHAR",
	"CLOSE_PAREN_CHAR",
	"DOT_CHAR",
	"AMPERSAND_CHAR",
	"EXCLAMATION_MARK_CHAR",
	"TILDE_CHAR",
	"MINUS_CHAR",
	"PLUS_CHAR",
	"MULTIPLY_CHAR",
	"DIVIDE_CHAR",
	"PERCENT_CHAR",
	"OPEN_ANGLE_BRACKET_CHAR",
	"CLOSE_ANGLE_BRACKET_CHAR",
	"CARET_CHAR",
	"PIPE_CHAR",
	"QUESTION_MARK_CHAR",
	"NUMBER_SIGN_CHAR"
};

static const char * l2_token_type_names[43] = {
	"L2_SPACE",
	"L2_NEWLINE",
	"L2_COMMENT",
	"L2_IDENTIFIER",
	"L2_COLON_CHAR",
	"L2_COMMA_CHAR",
	"L2_MINUS_CHAR",
	"L2_OFFSET",
	"L2_RELOCATABLE",
	"L2_IMPLEMENTS",
	"L2_IMPLEMENTED",
	"L2_REQUIRES",
	"L2_REQUIRED",
	"L2_INTERNAL",
	"L2_EXTERNAL",
	"L2_REGISTER",
	"L2_FUNCTION",
	"L2_VARIABLE",
	"L2_CONSTANT",
	"L2_STRING",
	"L2_UNRESOLVED",
	"L2_REGION",
	"L2_START",
	"L2_END",
	"L2_PERMISSION",
	"L2_CONSTANT_HEX",
	"L2_CONSTANT_DECIMAL",
	"L2_ADD",
	"L2_SUB",
	"L2_MUL",
	"L2_DIV",
	"L2_BEQ",
	"L2_BLT",
	"L2_LOA",
	"L2_STO",
	"L2_LL",
	"L2_AND",
	"L2_OR",
	"L2_NOT",
	"L2_SHR",
	"L2_SHL",
	"L2_DW",
	"L2_SW"
};

/*  Interfaces not in .h file to discourage external usage */
unsigned int accept_range(unsigned char, unsigned char, struct common_lexer_state *, unsigned int);
unsigned int accept(unsigned char, struct common_lexer_state *, unsigned int);
unsigned int accept_word(unsigned const char *, struct common_lexer_state *, unsigned int);
unsigned int t_D(struct common_lexer_state *, unsigned int);
unsigned int t_L(struct common_lexer_state *, unsigned int);
unsigned int t_H(struct common_lexer_state *, unsigned int);
unsigned int t_E(struct common_lexer_state *, unsigned int);
unsigned int t_FS(struct common_lexer_state *, unsigned int);
unsigned int t_IS(struct common_lexer_state *, unsigned int);
unsigned int t_comment(struct common_lexer_state *, unsigned int, unsigned int *);
unsigned int t_l2_comment(struct common_lexer_state *, unsigned int);
unsigned int t_l2_register(struct common_lexer_state *, unsigned int);
unsigned int t_keyword(unsigned const char *, struct common_lexer_state *, unsigned int);
unsigned int t_symbol(unsigned const char *, struct common_lexer_state *, unsigned int);
unsigned int t_identifier(struct common_lexer_state *, unsigned int);
unsigned int t_constant_hex(struct common_lexer_state *, unsigned int);
unsigned int t_constant_decimal(struct common_lexer_state *, unsigned int);
unsigned int t_constant_exponent(struct common_lexer_state *, unsigned int);
unsigned int t_constant_float_small(struct common_lexer_state *, unsigned int);
unsigned int t_constant_float_large(struct common_lexer_state *, unsigned int);
unsigned int t_constant_character(struct common_lexer_state *, unsigned int);
unsigned int t_constant_string_part(struct common_lexer_state *, unsigned int);
unsigned int t_constant_string(struct common_lexer_state *, unsigned int);
unsigned int t_newline(struct common_lexer_state *, unsigned int);
unsigned int t_space(struct common_lexer_state *, unsigned int);
void show_lexer_token(struct unsigned_char_list *, const char *, unsigned char *, unsigned char *, unsigned int);

unsigned int count_newlines_in_comment(struct c_lexer_token * t){
	unsigned int count = 0;
	unsigned char * c = t->first_byte;
	while(c != t->last_byte){
		if(*c == '\n'){
			count++;
		}
		c++;
	}
	return count;
}

unsigned int accept_range(unsigned char lo, unsigned char hi, struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	if(tentative_position < common_lexer_state->buffer_size && common_lexer_state->buf[tentative_position] >= lo && common_lexer_state->buf[tentative_position] <= hi){
		return 1;
	}
	return 0;
}

unsigned int accept(unsigned char c, struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	if(tentative_position < common_lexer_state->buffer_size && common_lexer_state->buf[tentative_position] == c){
		return 1;
	}
	return 0;
}

unsigned int accept_word(unsigned const char * c, struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int i = 0;
	while(c[i]){
		if(!(accept(c[i], common_lexer_state, tentative_position + i))){
			return 0;
		}
		i++;
	}
	return i;
}

unsigned int t_D(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	return accept_range('0','9', common_lexer_state, tentative_position);
}

unsigned int t_L(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	/*  Currently treating $ as a letter.  TODO: make this a compiler option. */
	return accept_range('a','z', common_lexer_state, tentative_position) || accept_range('A','Z', common_lexer_state, tentative_position) || accept('_', common_lexer_state, tentative_position) || accept('$', common_lexer_state, tentative_position);
}

unsigned int t_H(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	return accept_range('a','f', common_lexer_state, tentative_position) || accept_range('A','F', common_lexer_state, tentative_position) || accept_range('0','9', common_lexer_state, tentative_position);
}

unsigned int t_E(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	if(accept('e', common_lexer_state, tentative_position + count) || accept('E', common_lexer_state, tentative_position + count)){
		count += 1;
		count += (accept('-', common_lexer_state, tentative_position + count) || accept('+', common_lexer_state, tentative_position + count));
		if(t_D(common_lexer_state, tentative_position + count)){
			count++;
			while(t_D(common_lexer_state, tentative_position + count)){
				count++;
			}
			return count;
		}
	}
	return 0;
}

unsigned int t_FS(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	return accept('f', common_lexer_state, tentative_position) || accept('F', common_lexer_state, tentative_position) || accept('l', common_lexer_state, tentative_position) || accept('L', common_lexer_state, tentative_position);
}

unsigned int t_IS(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	if(accept('u', common_lexer_state, tentative_position + count) || accept('U', common_lexer_state, tentative_position + count) || accept('l', common_lexer_state, tentative_position + count) || accept('L', common_lexer_state, tentative_position + count)){
		count += 1;
		while(accept('u', common_lexer_state, tentative_position + count) || accept('U', common_lexer_state, tentative_position + count) || accept('l', common_lexer_state, tentative_position + count) || accept('L', common_lexer_state, tentative_position + count)){
			count++;
		}
		return count;
	}
	return 0;
}

unsigned int t_comment(struct common_lexer_state * common_lexer_state, unsigned int tentative_position, unsigned int * current_line){
	unsigned int count = 0;
	if(accept('/', common_lexer_state, tentative_position + count) && accept('*', common_lexer_state, tentative_position + count + 1)){
		count += 2;
		while(1){
			if(accept('*', common_lexer_state, tentative_position + count)){
				count++;
				if(accept('/', common_lexer_state, tentative_position + count)){
					count++;
					return count;
				}
			}else{
				if(accept(0, common_lexer_state, tentative_position + count)){
					buffered_printf(common_lexer_state->buffered_output, "Unterminated comment.");
					return 0;
				}
				if(accept('\n', common_lexer_state, tentative_position + count)){
					*current_line = *current_line + 1;
				}else{
					accept_range(1,255, common_lexer_state, tentative_position + count);
				}
				count++;
			}
		}
	}
	return 0;
}

unsigned int t_l2_comment(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	if(accept(';', common_lexer_state, tentative_position + count)){
		count++;
		while(1){
			unsigned int count_before = count;
			if(accept_range(32, 126, common_lexer_state, tentative_position + count)){
				count++;
			}
			if(accept('\t', common_lexer_state, tentative_position + count)){
				count++;
			}
			if(accept('\n', common_lexer_state, tentative_position + count)){
				break;
			}
			if(count_before == count){
				printf("Char is 0x%X\n", common_lexer_state->buf[tentative_position + count]);
				assert(0 && "Bad character in asm comment.");
			}
		}
	}
	return count;
}

unsigned int t_l2_register(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	if(accept('r', common_lexer_state, tentative_position + count)){
		count++;
		while(accept_range('0', '9', common_lexer_state, tentative_position + count)){
			count++;
		}
		if(count > 1){
			return count;
		}else{
			return 0;
		}
	}
	if(accept('F', common_lexer_state, tentative_position + count)){
		count++;
		if(accept('P', common_lexer_state, tentative_position + count) || accept('R', common_lexer_state, tentative_position + count)){
			count++;
			return count;
		}else{
			return 0;
		}
	}
	if(accept('P', common_lexer_state, tentative_position + count)){
		count++;
		if(accept('C', common_lexer_state, tentative_position + count)){
			count++;
			return count;
		}else{
			return 0;
		}
	}
	if(accept('S', common_lexer_state, tentative_position + count)){
		count++;
		if(accept('P', common_lexer_state, tentative_position + count)){
			count++;
			return count;
		}else{
			return 0;
		}
	}
	if(accept('Z', common_lexer_state, tentative_position + count)){
		count++;
		if(accept('R', common_lexer_state, tentative_position + count)){
			count++;
			return count;
		}else{
			return 0;
		}
	}
	if(accept('W', common_lexer_state, tentative_position + count)){
		count++;
		if(accept('R', common_lexer_state, tentative_position + count)){
			count++;
			return count;
		}else{
			return 0;
		}
	}
	return count;
}

unsigned int t_keyword(unsigned const char * word, struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	if((count = accept_word(word, common_lexer_state, tentative_position + count))){
		if(!(t_D(common_lexer_state, tentative_position + count) || t_L(common_lexer_state, tentative_position + count)))
			return count;
	
	}
	return 0;
}

unsigned int t_symbol(unsigned const char * word, struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	return accept_word(word, common_lexer_state, tentative_position);
}

unsigned int t_identifier(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	if(!(count = t_L(common_lexer_state, tentative_position + count))){
		return 0;
	}

	while(t_L(common_lexer_state, tentative_position + count) || t_D(common_lexer_state, tentative_position + count)){
		count += 1;
	}
	return count;
}

unsigned int t_constant_hex(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	if(accept('0', common_lexer_state, tentative_position)){
		unsigned int count = 1;
		if(accept('x', common_lexer_state, tentative_position + count) || accept('X', common_lexer_state, tentative_position + count)){
			count++;
			if(t_H(common_lexer_state, tentative_position + count)){
				unsigned int t_IS_consumed;
				count++;
				while(t_H(common_lexer_state, tentative_position + count)){
					count++;
				}
				t_IS_consumed = t_IS(common_lexer_state, tentative_position + count);
				if(t_IS_consumed){
					count += t_IS_consumed;
				}
				return count;
			}
		}
	}
	return 0;
}

unsigned int t_constant_decimal(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	if(t_D(common_lexer_state, tentative_position)){
		unsigned int t_IS_consumed;
		unsigned int count = 1;
		while(t_D(common_lexer_state, tentative_position + count)){
			count++;
		}
		t_IS_consumed = t_IS(common_lexer_state, tentative_position + count);
		if(t_IS_consumed){
			count += t_IS_consumed;
		}
		return count;
	}
	return 0;
}

unsigned int t_constant_exponent(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	unsigned int e_size;
	if((count = t_D(common_lexer_state, tentative_position + count))){
		while(t_D(common_lexer_state, tentative_position + count)){
			count++;
		}
		if((e_size = t_E(common_lexer_state, tentative_position + count))){
			count += e_size;
			if(t_FS(common_lexer_state, tentative_position + count)){
				count++;
			}
			return count;
		}
	}
	return 0;
}

unsigned int t_constant_float_small(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	unsigned int e_size;
	while(t_D(common_lexer_state, tentative_position + count)){
		count++;
	}
	if(accept('.', common_lexer_state, tentative_position + count)){
		count++;
		if(t_D(common_lexer_state, tentative_position + count)){
			count++;
			while(t_D(common_lexer_state, tentative_position + count)){
				count++;
			}
			if((e_size = t_E(common_lexer_state, tentative_position + count))){
				count += e_size;
				if(t_FS(common_lexer_state, tentative_position + count)){
					count++;
				}
			}
			return count;
		}
	}
	return 0;
}

unsigned int t_constant_float_large(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	unsigned int e_size;
	if((count = t_D(common_lexer_state, tentative_position + count))){
		while(t_D(common_lexer_state, tentative_position + count)){
			count++;
		}
		if(accept('.', common_lexer_state, tentative_position + count)){
			count++;
			while(t_D(common_lexer_state, tentative_position + count)){
				count++;
			}
			if((e_size = t_E(common_lexer_state, tentative_position + count))){
				count += e_size;
				if(t_FS(common_lexer_state, tentative_position + count)){
					count++;
				}
			}
			return count;
		}
	}
	return 0;
}

unsigned int t_constant_character(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	if(accept('\'', common_lexer_state, tentative_position)){
		unsigned int count = 1;
		if(accept('\\', common_lexer_state, tentative_position + count)){
			accept_range(1,255, common_lexer_state, tentative_position + count);
			count +=2;
		}else{
			if(accept('\'', common_lexer_state, tentative_position + count)){
				buffered_printf(common_lexer_state->buffered_output, "Error in character constant.");
				return 0;
			}
			if(accept(0, common_lexer_state, tentative_position + count)){
				buffered_printf(common_lexer_state->buffered_output, "Unexpected end of file in constant expression.");
				return 0;
			}
			accept_range(1,255, common_lexer_state, tentative_position + count);
			count++;
		}
		while(!accept('\'', common_lexer_state, tentative_position + count)){
			if(accept('\\', common_lexer_state, tentative_position + count)){
				accept_range(1,255, common_lexer_state, tentative_position + count);
				count +=2;
			}else{
				if(accept(0, common_lexer_state, tentative_position + count)){
					buffered_printf(common_lexer_state->buffered_output, "Unexpected end of file in constant expression.");
					return 0;
				}
				accept_range(1,255, common_lexer_state, tentative_position + count);
				count++;
			}
		}
		count++;
		return count;
	}
	return 0;
}

unsigned int t_constant_string_part(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	if(accept('"', common_lexer_state, tentative_position)){
		unsigned int count = 1;
		while(!accept('"', common_lexer_state, tentative_position + count)){
			if(accept('\\', common_lexer_state, tentative_position + count)){
				accept_range(1,255, common_lexer_state, tentative_position + count);
				count +=2;
			}else{
				if(accept_range(1,255, common_lexer_state, tentative_position + count)){
					count++;
				}else{
					buffered_printf(common_lexer_state->buffered_output, "Unexpected end of file in constant expression.");
					assert(0 && "Unexpected end of file in constant expression.");
				}
			}
		}
		count++;
		return count;
	}
	return 0;
}

unsigned int t_constant_string(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int total_count = 0;
	unsigned int current_count;
	if((current_count = t_constant_string_part(common_lexer_state, tentative_position))){
		total_count += current_count;
		while(current_count){ /*  While we're taking in string constant parts */
			unsigned int total_whitespace_count = 0;
			while(
				(current_count = t_space(common_lexer_state, tentative_position + total_count + total_whitespace_count)) ||
				(current_count = t_newline(common_lexer_state, tentative_position + total_count + total_whitespace_count)) ||
				(current_count = t_comment(common_lexer_state, tentative_position + total_count + total_whitespace_count, &common_lexer_state->current_line))
			){
				total_whitespace_count += current_count;
			}
			if((current_count = t_constant_string_part(common_lexer_state, tentative_position + total_count + total_whitespace_count))){
				/*  Accept the whitespace, and the last string part */
				total_count += (total_whitespace_count + current_count);
			}
		}
	}
	return total_count;
}

unsigned int t_newline(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	if(accept('\r', common_lexer_state, tentative_position + count)){
		count++;
	}
	if(accept('\n', common_lexer_state, tentative_position + count)){
		count++;
		return count;
	}
	return 0;
}

unsigned int t_space(struct common_lexer_state * common_lexer_state, unsigned int tentative_position){
	unsigned int count = 0;
	while(accept(' ', common_lexer_state, tentative_position + count) || accept('\t', common_lexer_state, tentative_position + count)){
		count += 1;
	}
	return count;
}

void show_lexer_token(struct unsigned_char_list * out_buffer, const char * name, unsigned char * first_byte, unsigned char * last_byte, unsigned int enabled){
	(void)out_buffer;
	if(enabled){
		unsigned int k;
		printf(";%s '", name);
		for(k = 0; k < (unsigned int)((last_byte - first_byte) + 1); k++){
			if(first_byte[k] == '\n'){
				printf("\\n");
			}else{
				printf("%c", first_byte[k]);
			}
		}
		printf("'");
		printf("\n");
	}
}

int lex_c(struct c_lexer_state * c_lexer_state){
	c_lexer_state->c.position = 0;
	c_lexer_state->c.current_line = 0;

	struct_c_lexer_token_ptr_list_create(&c_lexer_state->tokens);

	while(c_lexer_state->c.position < c_lexer_state->c.buffer_size){
		unsigned int rtn = 0;
		unsigned char * first_byte = &c_lexer_state->c.buf[c_lexer_state->c.position];
		enum c_token_type type;
		struct c_lexer_token * new_token;

		if((rtn = t_space(&c_lexer_state->c, c_lexer_state->c.position))){
			type = SPACE;
		}else if((rtn = t_newline(&c_lexer_state->c, c_lexer_state->c.position))){
			type = NEWLINE;
			c_lexer_state->c.current_line = c_lexer_state->c.current_line + rtn;
		}else if((rtn = t_comment(&c_lexer_state->c, c_lexer_state->c.position, &c_lexer_state->c.current_line))){
			type = COMMENT;
		}else if((rtn = t_keyword((const unsigned char *)"auto", &c_lexer_state->c, c_lexer_state->c.position))){
			type = AUTO;
		}else if((rtn = t_keyword((const unsigned char *)"break", &c_lexer_state->c, c_lexer_state->c.position))){
			type = BREAK;
		}else if((rtn = t_keyword((const unsigned char *)"case", &c_lexer_state->c, c_lexer_state->c.position))){
			type = CASE;
		}else if((rtn = t_keyword((const unsigned char *)"char", &c_lexer_state->c, c_lexer_state->c.position))){
			type = CHAR;
		}else if((rtn = t_keyword((const unsigned char *)"const", &c_lexer_state->c, c_lexer_state->c.position))){
			type = CONST;
		}else if((rtn = t_keyword((const unsigned char *)"continue", &c_lexer_state->c, c_lexer_state->c.position))){
			type = CONTINUE;
		}else if((rtn = t_keyword((const unsigned char *)"default", &c_lexer_state->c, c_lexer_state->c.position))){
			type = DEFAULT;
		}else if((rtn = t_keyword((const unsigned char *)"do", &c_lexer_state->c, c_lexer_state->c.position))){
			type = DO;
		}else if((rtn = t_keyword((const unsigned char *)"double", &c_lexer_state->c, c_lexer_state->c.position))){
			type = DOUBLE;
		}else if((rtn = t_keyword((const unsigned char *)"else", &c_lexer_state->c, c_lexer_state->c.position))){
			type = ELSE;
		}else if((rtn = t_keyword((const unsigned char *)"enum", &c_lexer_state->c, c_lexer_state->c.position))){
			type = ENUM;
		}else if((rtn = t_keyword((const unsigned char *)"extern", &c_lexer_state->c, c_lexer_state->c.position))){
			type = EXTERN;
		}else if((rtn = t_keyword((const unsigned char *)"float", &c_lexer_state->c, c_lexer_state->c.position))){
			type = FLOAT;
		}else if((rtn = t_keyword((const unsigned char *)"for", &c_lexer_state->c, c_lexer_state->c.position))){
			type = FOR;
		}else if((rtn = t_keyword((const unsigned char *)"goto", &c_lexer_state->c, c_lexer_state->c.position))){
			type = GOTO;
		}else if((rtn = t_keyword((const unsigned char *)"if", &c_lexer_state->c, c_lexer_state->c.position))){
			type = IF;
		}else if((rtn = t_keyword((const unsigned char *)"int", &c_lexer_state->c, c_lexer_state->c.position))){
			type = INT;
		}else if((rtn = t_keyword((const unsigned char *)"long", &c_lexer_state->c, c_lexer_state->c.position))){
			type = LONG;
		}else if((rtn = t_keyword((const unsigned char *)"register", &c_lexer_state->c, c_lexer_state->c.position))){
			type = REGISTER;
		}else if((rtn = t_keyword((const unsigned char *)"return", &c_lexer_state->c, c_lexer_state->c.position))){
			type = RETURN;
		}else if((rtn = t_keyword((const unsigned char *)"short", &c_lexer_state->c, c_lexer_state->c.position))){
			type = SHORT;
		}else if((rtn = t_keyword((const unsigned char *)"signed", &c_lexer_state->c, c_lexer_state->c.position))){
			type = SIGNED;
		}else if((rtn = t_keyword((const unsigned char *)"sizeof", &c_lexer_state->c, c_lexer_state->c.position))){
			type = SIZEOF;
		}else if((rtn = t_keyword((const unsigned char *)"static", &c_lexer_state->c, c_lexer_state->c.position))){
			type = STATIC;
		}else if((rtn = t_keyword((const unsigned char *)"struct", &c_lexer_state->c, c_lexer_state->c.position))){
			type = STRUCT;
		}else if((rtn = t_keyword((const unsigned char *)"switch", &c_lexer_state->c, c_lexer_state->c.position))){
			type = SWITCH;
		}else if((rtn = t_keyword((const unsigned char *)"typedef", &c_lexer_state->c, c_lexer_state->c.position))){
			type = TYPEDEF;
		}else if((rtn = t_keyword((const unsigned char *)"union", &c_lexer_state->c, c_lexer_state->c.position))){
			type = UNION;
		}else if((rtn = t_keyword((const unsigned char *)"unsigned", &c_lexer_state->c, c_lexer_state->c.position))){
			type = UNSIGNED;
		}else if((rtn = t_keyword((const unsigned char *)"void", &c_lexer_state->c, c_lexer_state->c.position))){
			type = VOID;
		}else if((rtn = t_keyword((const unsigned char *)"volatile", &c_lexer_state->c, c_lexer_state->c.position))){
			type = VOLATILE;
		}else if((rtn = t_keyword((const unsigned char *)"while", &c_lexer_state->c, c_lexer_state->c.position))){
			type = WHILE;
		}else if((rtn = t_identifier(&c_lexer_state->c, c_lexer_state->c.position))){
			type = IDENTIFIER;
		}else if((rtn = t_constant_hex(&c_lexer_state->c, c_lexer_state->c.position))){
			type = CONSTANT_HEX;
		}else if((rtn = t_constant_exponent(&c_lexer_state->c, c_lexer_state->c.position))){
			type = CONSTANT_EXPONENT;
		}else if((rtn = t_constant_float_small(&c_lexer_state->c, c_lexer_state->c.position))){
			type = CONSTANT_FLOAT_SMALL;
		}else if((rtn = t_constant_float_large(&c_lexer_state->c, c_lexer_state->c.position))){
			type = CONSTANT_FLOAT_LARGE;
		}else if((rtn = t_constant_decimal(&c_lexer_state->c, c_lexer_state->c.position))){
			type = CONSTANT_DECIMAL;
		}else if((rtn = t_constant_character(&c_lexer_state->c, c_lexer_state->c.position))){
			type = CONSTANT_CHARACTER;
		}else if((rtn = t_constant_string(&c_lexer_state->c, c_lexer_state->c.position))){
			type = STRING_LITERAL;
		}else if((rtn = t_symbol((const unsigned char *)"...", &c_lexer_state->c, c_lexer_state->c.position))){
			type = ELLIPSIS;
		}else if((rtn = t_symbol((const unsigned char *)">>=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = RIGHT_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)"<<=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = LEFT_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)"+=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = ADD_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)"-=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = SUB_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)"*=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = MUL_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)"/=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = DIV_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)"%=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = MOD_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)"&=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = AND_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)"^=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = XOR_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)"|=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = OR_ASSIGN;
		}else if((rtn = t_symbol((const unsigned char *)">>", &c_lexer_state->c, c_lexer_state->c.position))){
			type = RIGHT_OP;
		}else if((rtn = t_symbol((const unsigned char *)"<<", &c_lexer_state->c, c_lexer_state->c.position))){
			type = LEFT_OP;
		}else if((rtn = t_symbol((const unsigned char *)"++", &c_lexer_state->c, c_lexer_state->c.position))){
			type = INC_OP;
		}else if((rtn = t_symbol((const unsigned char *)"->", &c_lexer_state->c, c_lexer_state->c.position))){
			type = PTR_OP;
		}else if((rtn = t_symbol((const unsigned char *)"--", &c_lexer_state->c, c_lexer_state->c.position))){
			type = DEC_OP;
		}else if((rtn = t_symbol((const unsigned char *)"&&", &c_lexer_state->c, c_lexer_state->c.position))){
			type = AND_OP;
		}else if((rtn = t_symbol((const unsigned char *)"||", &c_lexer_state->c, c_lexer_state->c.position))){
			type = OR_OP;
		}else if((rtn = t_symbol((const unsigned char *)"<=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = LE_OP;
		}else if((rtn = t_symbol((const unsigned char *)">=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = GE_OP;
		}else if((rtn = t_symbol((const unsigned char *)"==", &c_lexer_state->c, c_lexer_state->c.position))){
			type = EQ_OP;
		}else if((rtn = t_symbol((const unsigned char *)"!=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = NE_OP;
		}else if((rtn = t_symbol((const unsigned char *)";", &c_lexer_state->c, c_lexer_state->c.position))){
			type = SEMICOLON_CHAR;
		}else if(((rtn = t_symbol((const unsigned char *)"{", &c_lexer_state->c, c_lexer_state->c.position)) || (rtn = t_symbol((const unsigned char *)"<%", &c_lexer_state->c, c_lexer_state->c.position)))){
			type = OPEN_BRACE_CHAR;
		}else if(((rtn = t_symbol((const unsigned char *)"}", &c_lexer_state->c, c_lexer_state->c.position)) || (rtn = t_symbol((const unsigned char *)"%>", &c_lexer_state->c, c_lexer_state->c.position)))){
			type = CLOSE_BRACE_CHAR;
		}else if(((rtn = t_symbol((const unsigned char *)"[", &c_lexer_state->c, c_lexer_state->c.position)) || (rtn = t_symbol((const unsigned char *)"<:", &c_lexer_state->c, c_lexer_state->c.position)))){
			type = OPEN_SQUARE_BRACKET_CHAR;
		}else if(((rtn = t_symbol((const unsigned char *)"]", &c_lexer_state->c, c_lexer_state->c.position)) || (rtn = t_symbol((const unsigned char *)":>", &c_lexer_state->c, c_lexer_state->c.position)))){
			type = CLOSE_SQUARE_BRACKET_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)",", &c_lexer_state->c, c_lexer_state->c.position))){
			type = COMMA_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)":", &c_lexer_state->c, c_lexer_state->c.position))){
			type = COLON_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"=", &c_lexer_state->c, c_lexer_state->c.position))){
			type = EQUALS_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"(", &c_lexer_state->c, c_lexer_state->c.position))){
			type = OPEN_PAREN_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)")", &c_lexer_state->c, c_lexer_state->c.position))){
			type = CLOSE_PAREN_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)".", &c_lexer_state->c, c_lexer_state->c.position))){
			type = DOT_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"&", &c_lexer_state->c, c_lexer_state->c.position))){
			type = AMPERSAND_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"!", &c_lexer_state->c, c_lexer_state->c.position))){
			type = EXCLAMATION_MARK_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"~", &c_lexer_state->c, c_lexer_state->c.position))){
			type = TILDE_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"-", &c_lexer_state->c, c_lexer_state->c.position))){
			type = MINUS_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"+", &c_lexer_state->c, c_lexer_state->c.position))){
			type = PLUS_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"*", &c_lexer_state->c, c_lexer_state->c.position))){
			type = MULTIPLY_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"/", &c_lexer_state->c, c_lexer_state->c.position))){
			type = DIVIDE_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"%", &c_lexer_state->c, c_lexer_state->c.position))){
			type = PERCENT_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"<", &c_lexer_state->c, c_lexer_state->c.position))){
			type = OPEN_ANGLE_BRACKET_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)">", &c_lexer_state->c, c_lexer_state->c.position))){
			type = CLOSE_ANGLE_BRACKET_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"^", &c_lexer_state->c, c_lexer_state->c.position))){
			type = CARET_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"|", &c_lexer_state->c, c_lexer_state->c.position))){
			type = PIPE_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"?", &c_lexer_state->c, c_lexer_state->c.position))){
			type = QUESTION_MARK_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"#", &c_lexer_state->c, c_lexer_state->c.position))){
			type = NUMBER_SIGN_CHAR;
		}else{
			unsigned int i = 0;
			printf("Lexer stopping on character 0x%02x.  This was character %u of %u\nFollowing chars are:", c_lexer_state->c.buf[c_lexer_state->c.position], (c_lexer_state->c.position + 1), c_lexer_state->c.buffer_size);
			for(i = c_lexer_state->c.position; i < (c_lexer_state->c.position + 100) && i < c_lexer_state->c.buffer_size; i++){
				if(c_lexer_state->c.buf[i]){
					printf("%c", c_lexer_state->c.buf[i]);
				}
			}
			buffered_printf(c_lexer_state->c.buffered_output, "\n");
			assert(0 && "Invalid character in lexer.");
			return 1;
		}

		new_token = struct_c_lexer_token_memory_pool_malloc(c_lexer_state->c.memory_pool_collection->struct_c_lexer_token_pool);
		new_token->type = type;
		new_token->first_byte = first_byte;
		new_token->last_byte = (unsigned char *)((first_byte + rtn) - 1);
		{
			/*
			unsigned char *g = new_token->first_byte;
			printf("Got token: %s ", get_c_token_type_names()[new_token->type]);
			do{
				if(*g == '\n'){
					printf("\\n");
				}else if(*g == '\r'){
					printf("\\r");
				}else{
					printf("%c", *g);
				}
			}while(g++ != new_token->last_byte);
			printf("\n");
			*/
		}

		struct_c_lexer_token_ptr_list_add_end(&c_lexer_state->tokens, new_token);
		show_lexer_token(c_lexer_state->c.buffered_output, get_c_token_type_names()[new_token->type], new_token->first_byte, new_token->last_byte, SHOW_LEXER_TOKENS);
		c_lexer_state->c.position += rtn;
	}
	return 0;
}

void create_c_lexer_state(struct c_lexer_state * state, struct unsigned_char_list * buffered_output, struct memory_pool_collection * memory_pool_collection, unsigned char * in_file, unsigned char * input_buffer, unsigned int size){
	state->c.buffered_output = buffered_output;
	state->c.memory_pool_collection = memory_pool_collection;
	state->c.filename = in_file;
	state->c.buf = input_buffer;
	state->c.buffer_size = size;
}

void destroy_c_lexer_state(struct c_lexer_state * c_lexer_state){
	unsigned int num_tokens = struct_c_lexer_token_ptr_list_size(&c_lexer_state->tokens);
	struct c_lexer_token ** tokens = struct_c_lexer_token_ptr_list_data(&c_lexer_state->tokens);
	unsigned int i;
	for(i = 0; i < num_tokens; i++){
		struct_c_lexer_token_memory_pool_free(c_lexer_state->c.memory_pool_collection->struct_c_lexer_token_pool, tokens[i]);
	}
	struct_c_lexer_token_ptr_list_destroy(&c_lexer_state->tokens);
}

void destroy_l2_lexer_state(struct l2_lexer_state * l2_lexer_state){
	unsigned int num_tokens = struct_l2_lexer_token_ptr_list_size(&l2_lexer_state->tokens);
	struct l2_lexer_token ** tokens = struct_l2_lexer_token_ptr_list_data(&l2_lexer_state->tokens);
	unsigned int i;
	for(i = 0; i < num_tokens; i++){
		struct_l2_lexer_token_memory_pool_free(l2_lexer_state->c.memory_pool_collection->struct_l2_lexer_token_pool, tokens[i]);
	}
	struct_l2_lexer_token_ptr_list_destroy(&l2_lexer_state->tokens);
}

int lex_asm(struct l2_lexer_state * l2_lexer_state, unsigned char * filename, unsigned char * buffer, unsigned int buffer_size){
	l2_lexer_state->c.buf = buffer;
	l2_lexer_state->c.position = 0;
	l2_lexer_state->c.current_line = 0;
	l2_lexer_state->c.filename = filename;
	l2_lexer_state->c.buffer_size = buffer_size;

	struct_l2_lexer_token_ptr_list_create(&l2_lexer_state->tokens);

	while(l2_lexer_state->c.position < buffer_size){
		unsigned int rtn = 0;
		unsigned char * first_byte = &l2_lexer_state->c.buf[l2_lexer_state->c.position];
		enum l2_token_type type;
		struct l2_lexer_token * new_token;

		if((rtn = t_space(&l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_SPACE;
		}else if((rtn = t_newline(&l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_NEWLINE;
			l2_lexer_state->c.current_line = l2_lexer_state->c.current_line + rtn;
		}else if((rtn = t_l2_comment(&l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_COMMENT;
		}else if((rtn = t_symbol((const unsigned char *)":", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_COLON_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)",", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_COMMA_CHAR;
		}else if((rtn = t_symbol((const unsigned char *)"-", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_MINUS_CHAR;
		}else if((rtn = t_keyword((const unsigned char *)"OFFSET", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_OFFSET;
		}else if((rtn = t_keyword((const unsigned char *)"RELOCATABLE", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_RELOCATABLE;
		}else if((rtn = t_keyword((const unsigned char *)"IMPLEMENTS", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_IMPLEMENTS;
		}else if((rtn = t_keyword((const unsigned char *)"IMPLEMENTED", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_IMPLEMENTED;
		}else if((rtn = t_keyword((const unsigned char *)"FUNCTION", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_FUNCTION;
		}else if((rtn = t_keyword((const unsigned char *)"VARIABLE", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_VARIABLE;
		}else if((rtn = t_keyword((const unsigned char *)"CONSTANT", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_CONSTANT;
		}else if((rtn = t_keyword((const unsigned char *)"REQUIRES", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_REQUIRES;
		}else if((rtn = t_keyword((const unsigned char *)"REQUIRED", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_REQUIRED;
		}else if((rtn = t_keyword((const unsigned char *)"INTERNAL", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_INTERNAL;
		}else if((rtn = t_keyword((const unsigned char *)"EXTERNAL", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_EXTERNAL;
		}else if((rtn = t_keyword((const unsigned char *)"STRING", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_STRING;
		}else if((rtn = t_keyword((const unsigned char *)"UNRESOLVED", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_UNRESOLVED;
		}else if((rtn = t_keyword((const unsigned char *)"REGION", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_REGION;
		}else if((rtn = t_keyword((const unsigned char *)"START", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_START;
		}else if((rtn = t_keyword((const unsigned char *)"END", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_END;
		}else if((rtn = t_keyword((const unsigned char *)"PERMISSION", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_PERMISSION;
		}else if((rtn = t_l2_register(&l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_REGISTER;
		}else if((rtn = t_constant_hex(&l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_CONSTANT_HEX;
		}else if((rtn = t_constant_decimal(&l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_CONSTANT_DECIMAL;
		}else if((rtn = t_keyword((const unsigned char *)"add", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_ADD;
		}else if((rtn = t_keyword((const unsigned char *)"sub", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_SUB;
		}else if((rtn = t_keyword((const unsigned char *)"mul", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_MUL;
		}else if((rtn = t_keyword((const unsigned char *)"div", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_DIV;
		}else if((rtn = t_keyword((const unsigned char *)"beq", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_BEQ;
		}else if((rtn = t_keyword((const unsigned char *)"blt", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_BLT;
		}else if((rtn = t_keyword((const unsigned char *)"loa", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_LOA;
		}else if((rtn = t_keyword((const unsigned char *)"sto", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_STO;
		}else if((rtn = t_keyword((const unsigned char *)"ll", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_LL;
		}else if((rtn = t_keyword((const unsigned char *)"and", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_AND;
		}else if((rtn = t_keyword((const unsigned char *)"or", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_OR;
		}else if((rtn = t_keyword((const unsigned char *)"not", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_NOT;
		}else if((rtn = t_keyword((const unsigned char *)"shr", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_SHR;
		}else if((rtn = t_keyword((const unsigned char *)"shl", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_SHL;
		}else if((rtn = t_keyword((const unsigned char *)"DW", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_DW;
		}else if((rtn = t_keyword((const unsigned char *)"SW", &l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_SW;
		}else if((rtn = t_identifier(&l2_lexer_state->c, l2_lexer_state->c.position))){
			type = L2_IDENTIFIER;
		}else{
			unsigned int i = 0;
			buffered_printf(l2_lexer_state->c.buffered_output, "Lexer stopping on character 0x%02x.  This was character %u of %u\nFollowing chars are:", l2_lexer_state->c.buf[l2_lexer_state->c.position], (l2_lexer_state->c.position + 1), l2_lexer_state->c.buffer_size);
			for(i = l2_lexer_state->c.position; i < (l2_lexer_state->c.position + 100) && i < l2_lexer_state->c.buffer_size; i++){
				if(l2_lexer_state->c.buf[i]){
					buffered_printf(l2_lexer_state->c.buffered_output, "%c", l2_lexer_state->c.buf[i]);
				}
			}
			buffered_printf(l2_lexer_state->c.buffered_output, "\n");
			return 1;
		}

		new_token = struct_l2_lexer_token_memory_pool_malloc(l2_lexer_state->c.memory_pool_collection->struct_l2_lexer_token_pool);
		new_token->type = type;
		new_token->first_byte = first_byte;
		new_token->last_byte = (unsigned char *)((first_byte + rtn) - 1);

		struct_l2_lexer_token_ptr_list_add_end(&l2_lexer_state->tokens, new_token);
		show_lexer_token(l2_lexer_state->c.buffered_output, get_c_token_type_names()[new_token->type], new_token->first_byte, new_token->last_byte, SHOW_LEXER_TOKENS);
		l2_lexer_state->c.position += rtn;
	}
	return 0;
}

const char ** get_c_token_type_names(void){
	return c_token_type_names;
}

const char ** get_l2_token_type_names(void){
	return l2_token_type_names;
}