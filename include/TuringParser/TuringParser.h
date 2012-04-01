#ifndef _TuringParser_TuringParser_H_
#define _TuringParser_TuringParser_H_

#include <set>

#include "TuringParser/Parser.h"
#include "TuringParser/Lexer.h"

namespace TuringParser {
    namespace Precedence {
        //! Precedence levels from weakest to strongest binding
        enum Levels {
            ASSIGNMENT = 1,
            IMPLIES,
            OR,
            AND,
            NOT,
            COMPARE, // <, >, =, <=, >=, not=, in, not in
            ADD, // +, -, xor
            MULTIPLY, // *, /, div, mod, rem, shl, shr
            PREFIX,
            MODIFIER, // **, ^, #
            CALL // calling is an operator
        };
    }
	//! A pratt Expression Parser for Turing
	class TuringFileParser : public Parser {
    public:
        explicit TuringFileParser(Lexer lex);
        ~TuringFileParser();
    private:
        // helpers that keep track of memory to be freed later
        void registerPrefixOp(Token::ID i, Parselet::PrefixOp *op);
        void registerInfixOp(Token::ID i, Parselet::InfixOp *op);
        // Kept so they can be freed later
        std::set<Parselet::PrefixOp*> PrefixParselets;
        std::set<Parselet::InfixOp*> InfixParselets;

	};
    namespace Parselet {
        class PrimaryParselet : public PrefixOp {
        public:
            explicit PrimaryParselet(ASTNode::Token type) : Type(type) {}
            virtual ASTNode *parse(Parser *parser, Token token);
        private:
            ASTNode::Token Type;
        };
    }
}

#endif