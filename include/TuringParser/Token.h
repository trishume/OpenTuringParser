#ifndef _TuringParser_Token_H_
#define _TuringParser_Token_H_

#include <string>

#include "TuringParser/SourceLoc.h"

namespace OTParser {
	//! Custom Token Class
	class Token {
    public:
        enum ID {
            EOF_TKN = 0
#define TURING_TKN(x,h) ,x
#include "TuringParser/LexerTokens.h"
#undef TURING_TKN
        };
        Token() : Type(Token::EOF_TKN), String("") {}
		Token(Token::ID i, std::string str) : Type(i), String(str) {}
        Token::ID Type;
		SourceLoc Begin;
		std::string String;
        
        SourceLoc getEnd() {
            return Begin.advance(String.size());
        }
        
        //! \returns the name of a token. Or <UNKNOWN> for a bogus id.
        static const char *getTokenName(Token::ID i);
        //! Get the human english name of the token for example "+ operator"
        static const char *getHumanTokenName(Token::ID i);
	};
}

#endif