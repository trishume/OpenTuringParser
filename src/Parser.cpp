#include "TuringParser/Parser.h"

#include <cassert>

#include "TuringParser/ParseError.h"

namespace TuringParser {
    namespace Parselet {
        BinaryOp::BinaryOp(ASTNode::Token type, int precedence, bool isRight) : Type(type), 
        Precedence(precedence), IsRight(isRight) {
            
        }
        ASTNode *BinaryOp::parse(Parser *parser, ASTNode *left, Token token) {
            ASTNode *node = new ASTNode(Type,token.Begin);
            node->addChild(left);
            node->addChild(parser->parseExpression()); // right
            return node;
        }
        int BinaryOp::getPrecedence() {
            return Precedence;
        }
    }
    
    Parser::Parser(Lexer lex) : Lex(lex), Pos(0) {
        
    }
    ASTNode *Parser::parse() {
        return parseExpression();
    }
    void Parser::registerOp(Token::ID tok, Parselet::PrefixOp *parselet) {
        PrefixOps[tok] = parselet;
    }
    void Parser::registerOp(Token::ID tok, Parselet::InfixOp *parselet) {
        InfixOps[tok] = parselet;
    }
    Token Parser::consume() {
        Token tok = curTok();
        ++Pos;
        return tok;
    }
    Token Parser::lookahead(int n) {
        unsigned int index = Pos+n;
        while (index >= Lookahead.size()) {
            Lookahead.push_back(Lex.nextToken());
        }
        
        return Lookahead[index];
    }
    Token Parser::curTok() {
        return lookahead(0);
    }
    void Parser::match(Token::ID i) {
        if (i == curTok().Type) {
            consume();
        } else {
            std::ostringstream os;
            os << "Expected " << Token::getHumanTokenName(i) << "; found " << 
                    Token::getHumanTokenName(lookahead(0).Type);
            SourceLoc begin = curTok().Begin;
            SourceLoc end = curTok().getEnd();
            ParseError err(begin,os.str());
            err.setEnd(end);
            throw err;
        }
    }
    ASTNode *Parser::parseExpression(int precedence) {
        Token token = consume();
        
        if (PrefixOps.find(token.Type) == PrefixOps.end()) {
            std::ostringstream os;
            os << "Could not parse \"" << token.String << "\"";
            ParseError err(curTok().Begin,os.str());
            err.setEnd(curTok().getEnd());
            throw err;

        }
        Parselet::PrefixOp *prefix = PrefixOps[token.Type];
        
        ASTNode *left = prefix->parse(this, token);
        
        while (precedence < getPrecedence()) {
            token = consume();
            
            // getPrecedence returns 0 when op is not found so < should stop this from
            // being called
            assert(InfixOps.find(token.Type) != InfixOps.end() && 
                   "Tokens with negative precedences are not supported right now");
            Parselet::InfixOp *infix = InfixOps[token.Type];
            left = infix->parse(this, left, token);
        }
        
        return left;
    }
    int Parser::getPrecedence() {
        Token::ID type = curTok().Type;
        if (InfixOps.find(type) == InfixOps.end()) {
            return 0;
        }
        return InfixOps[type]->getPrecedence();
    }
}