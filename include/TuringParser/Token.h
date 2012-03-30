#ifndef _TuringParser_Token_H_
#define _TuringParser_Token_H_

#include <string>

#include "TuringParser/SourceLoc.h"

namespace TuringParser {
	//! Custom Token Class
	class Token {
    public:
        enum ID {
            EOF_TKN = 0
#define TURING_TKN(x) ,x
#include "TuringParser/LexerTokens.h"
#undef TURING_TKN
        };
        Token() : Id(Token::EOF_TKN), String("") {}
		Token(Token::ID i, std::string str) : Id(i), String(str) {}
        Token::ID Id;
		SourceLoc Begin;
		std::string String;
        
        //! \returns the name of a token. Or <UNKNOWN> for a bogus id.
        static const char *getTokenName(Token::ID i);
	};
}

#endif