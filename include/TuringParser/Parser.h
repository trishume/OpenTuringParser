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
        //! Parselet for prefix operations and, confusingly, primary expressions
        //! An identifier is a prefix expression
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
            BinaryOp(ASTNode::Token type,int precedence, bool isRight);
            virtual ASTNode *parse(Parser *parser, ASTNode *left, Token token);
            virtual int getPrecedence();
        private:
            ASTNode::Token Type;
            int Precedence;
            bool IsRight;
        };
    }
	//! Implements a general recursive descent parser
    //! Uses a Pratt parser for expressions, because they're cool!
	class Parser {
    public:
        Parser(Lexer lex);
        virtual ASTNode *parse();
        
        // Called from parselets ----
        // TODO maybe use the friend system to avoid making these public
        //! get the nth token in the lookahead buffer
        Token lookahead(int n);
        Token curTok();
        //! move the buffer forward by one token
        //! \returns the token that was consumed
        Token consume();
        void match(Token::ID i);
        //! Pratt expression parser using the registered parselets
        ASTNode *parseExpression(int precedence = 0);
    protected:
        //! registers a parselet for an operator
        //! \param tok  the token that identifies the operator.
        //!             I.E the - token for unary minus.
        void registerOp(Token::ID tok, Parselet::PrefixOp *parselet);
        void registerOp(Token::ID tok, Parselet::InfixOp *parselet);
    private:
        //! Helper to get precedence of current operator
        int getPrecedence();
        
        Lexer Lex;
        //! The lookahead buffer
        std::vector<Token> Lookahead;
        //! Current index into the lookahead buffer
        unsigned int Pos;
        //! Storage for operators
        std::map<Token::ID, Parselet::PrefixOp*> PrefixOps;
        std::map<Token::ID, Parselet::InfixOp*> InfixOps;
	};
}

#endif