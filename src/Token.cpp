#include "TuringParser/Token.h"

namespace TuringParser {
	const char *Token::getTokenName(Token::ID i) {
	    switch (i) {
	        case EOF_TKN:
	            return "<EOF>";
#define TURING_TKN(x) case x: return #x;
#include "TuringParser/LexerTokens.h"
#undef TURING_TKN
	        default:
	            return "<UNKNOWN>";
	    }
	}
}