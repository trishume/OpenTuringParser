#include "TuringParser/Token.h"

namespace TuringParser {
	const char *Token::getTokenName(Token::ID i) {
	    switch (i) {
	        case EOF_TKN:
	            return "<EOF>";
#define TURING_TKN(x,h) case x: return #x;
#include "TuringParser/LexerTokens.h"
#undef TURING_TKN
	        default:
	            return "<UNKNOWN>";
	    }
	}
    const char *Token::getHumanTokenName(Token::ID i) {
	    switch (i) {
	        case EOF_TKN:
	            return "<EOF>";
#define TURING_TKN(x,h) case x: return #h;
#include "TuringParser/LexerTokens.h"
#undef TURING_TKN
	        default:
	            return "<UNKNOWN>";
	    }
	}

}