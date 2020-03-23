#pragma once
#include <vector>
#include <deque>
#include <string>
#include <string_view>
#include <algorithm>

template<typename Token_Type>
using token_vector = std::deque<Token_Type>;


inline bool try_match_token(const std::string_view& raw, const std::string_view& to_match)
{
	/* Can't match if smaller. */
	if (raw.size() < to_match.size()) return false;


	/* If perfect match, return true. */
	return std::memcmp(static_cast<void const*>(raw.data()), static_cast<void const*>(to_match.data()), to_match.size()) == 0;
}

template<typename TokenType, typename Token>
token_vector<Token> tokenize(const std::string_view& raw, const token_vector<Token> tokens, const std::vector<TokenType>& to_ignore = std::vector<TokenType>())
{
	token_vector<Token> out;
	
	std::uint64_t symbol_end_index				= 0;
	std::uint64_t symbol_start_index			= 0;

	auto check_for_symbol = [&]()
	{
		if (symbol_end_index > 0)
		{

			// Symbol we need to save.
			out.emplace_back(
				TokenType::symbol,
				std::string(raw.substr(symbol_start_index, symbol_end_index - symbol_start_index))
			);

			symbol_end_index = 0;
			symbol_start_index = 0;
		}
	};
	
	
	for (std::uint64_t i = 0; i < raw.size(); i++)
	{
		auto sub = raw.substr(i);

		bool found_token = false;
		
		for(auto& possible_token : tokens)
		{

			if(try_match_token(sub, possible_token.text))
			{
				check_for_symbol();
				
				// found token...

				if(std::find(to_ignore.begin(), to_ignore.end(), possible_token.type) == to_ignore.end())
					out.push_back(possible_token);
				
				i += possible_token.text.size() - 1;
				found_token = true;
				break;
			}
		}

		if(!found_token)
		{
			if (symbol_end_index == 0) {
				symbol_start_index = i;
				symbol_end_index = i;
			}
			
			symbol_end_index++;
		}
		
	}

	check_for_symbol();

	return out;
}