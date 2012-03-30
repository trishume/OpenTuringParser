#ifndef _TuringParser_Lexer_H_
#define _TuringParser_Lexer_H_

#include <string>
#include <map>
#include <sstream>

#include "TuringParser/Token.h"
#include "TuringParser/SourceLoc.h"
#include "TuringParser/File.h"

namespace TuringParser {
	//! Hand-written lexer
	class Lexer {
        public:
		Lexer(SourceFile *file);
        
        Token nextToken();
    protected:
        void consume();
        void match(char x);
        char lookahead(int n);
        Token newToken(Token::ID i, const std::string &str);
        
        static bool isLetter(char x);
        static bool isDigit(char x);
        
        Token identifier();
        Token numLiteral();
        Token stringOrCharLiteral(bool isCharLiteral);
        
        void skipLineComment();
        void skipBlockComment();
        void skipWhitespace();
        
        //! The whole file
        SourceFile *Input;
        //! Current char
        char C;
        static const char EOF_CHAR = 0;
        //! Character position in input
        unsigned int Pos;
        std::map<std::string, Token::ID> Keywords;
    private: // helpers
        void consumeDigits(std::ostringstream &os);
	};
}

#endif