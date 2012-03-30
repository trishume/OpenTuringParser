#ifndef _TuringParser_Parser_H_
#define _TuringParser_Parser_H_

#include <vector>
#include <map>

#include "TuringParser/Lexer.h"
#include "TuringParser/ASTNode.h"
#include "TuringParser/Token.h"

namespace TuringParser {
    // Parselets for the Pratt expression parser
    class Parser;
    namespace Parselet {
        class PrefixOp {
        public:
            virtual ASTNode *parse(Parser *parser, Token token) = 0;
        };
        class InfixOp {
        public:
            virtual ASTNode *parse(Parser *parser, ASTNode *left, Token token) = 0;
            virtual int getPrecedence() = 0;
        };
        class BinaryOp : public InfixOp {
        public:
            //! \param precedence the binding power of the operator
            //! \param isRight Is the operator right associative?
            BinaryOp(int precedence, bool isRight);
            virtual ASTNode *parse(Parser *parser, ASTNode *left, Token token);
            virtual int getPrecedence();
        };
    }
	//! Implements a general recursive descent parser
    //! Uses a Pratt parser for expressions, because they're cool!
	class Parser {
    public:
        Parser(Lexer lex);
        ASTNode *parse();
    protected:
        //! registers a parselet for an operator
        //! \param tok  the token that identifies the operator.
        //!             I.E the - token for unary minus.
        void registerOp(Token tok, Parselet::PrefixOp *parselet);
        void registerOp(Token tok, Parselet::InfixOp *parselet);
        //! get the nth token in the lookahead buffer
        Token lookahead(int n);
        //! move the buffer forward by one token
        void consume();
    private:
        //! The lookahead buffer
        std::vector<Token> Lookahead;
        //! Current index into the lookahead buffer
        unsigned int Pos;
        //! Storage for operators
        std::map<Token, Parselet::PrefixOp*> PrefixOps;
        std::map<Token, Parselet::InfixOp*> InfixOps;
	};
}

#endif