#pragma once
#include <string>
#include "tokenizer.hpp"

/*
	must have a symbol element, indexes don't matter, type doesn't matter, just used as an identifier.
*/

enum class mips_token_type
{
	invalid,
	symbol,
	space,
	comma,
	lparen,
	rparen,
	dollar
};

/*

ATTENTION!

all token classes must have a type field and a text field

the type field should be the enum that is passed in as the first template arg to tokenize
the text field should be std::string or a compatible replacement

constructor needs to take in the type and text field

*/
class mips_token
{
public:
	mips_token(const mips_token_type type, const std::string& text) : type(type), text(text) {}
	
	mips_token_type type;
	std::string		text;
};

const static mips_token token_space = { mips_token_type::space,   " " };
const static mips_token token_comma = { mips_token_type::comma,   "," };
const static mips_token token_lparen = { mips_token_type::lparen, "(" };
const static mips_token token_rparen = { mips_token_type::rparen, ")" };
const static mips_token token_dollar = { mips_token_type::dollar, "$" };

using mips_token_vector = token_vector<mips_token>;


/* put all tokens in this vector/deque */
static inline mips_token_vector tokens = {
	token_space, token_comma, token_lparen, token_rparen, token_dollar
};



inline mips_token_vector mips_tokenize(const std::string& raw)
{
	// tokenize "raw" to a deque of "mips_token"s given the tokens from "tokens" and ignore the space token
	return tokenize<mips_token_type, mips_token>(raw, tokens, { mips_token_type::space });
}


int main() {

	auto tokens = mips_tokenize("lbu $t1, imm($t2)");

	return 1;
}