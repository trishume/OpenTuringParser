#ifndef _TuringParser_TuringParser_H_
#define _TuringParser_TuringParser_H_

#include <set>

#include "TuringParser/Parser.h"
#include "TuringParser/Lexer.h"

namespace OTParser {
    namespace Precedence {
        //! Precedence levels from weakest to strongest binding
        enum Levels {
            //ASSIGN, // Assignment is not an operator
            IMPLIES = 1,
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
	class TuringParser : public Parser {
    public:
        explicit TuringParser(Lexer lex);
        ~TuringParser();
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
        // works for string AND character literals
        class StringLiteralParselet : public PrefixOp {
        public:
            explicit StringLiteralParselet(ASTNode::Token type) : 
            Type(type) {}
            virtual ASTNode *parse(Parser *parser, Token token);
        private:
            ASTNode::Token Type;
        };
        //! parses bracketed expressions (expr)
        class GroupParselet : public PrefixOp {
        public:
            virtual ASTNode *parse(Parser *parser, Token token);
        };
        //! parses bracketed call expressions expr(expr[,expr]*)
        class CallParselet : public InfixOp {
        public:
            virtual ASTNode *parse(Parser *parser, ASTNode *left,
                                   Token token);
            virtual int getPrecedence(Parser *parser);
        };
        //! parses binary operators that can use the short assign
        //! syntax. I.E +/+= div/div= shl/shl=
        /*class PossibleAssignBinOp : public InfixOp {
        public:
            PossibleAssignBinOp(int precedence) : 
                                Prec(precedence) {}
            virtual ASTNode *parse(Parser *parser, ASTNode *left,
                                   Token token);
            virtual int getPrecedence(Parser *parser);
        private:
            bool isAssign(Parser *parser) const;
            int Prec;
        };*/
    }
}

#endif