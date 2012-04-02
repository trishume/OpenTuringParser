#include "TuringParser/Parser.h"

#include <cassert>
#include <iostream>

#include "TuringParser/ParseError.h"

namespace OTParser {
    namespace Parselet {
        UnaryOp::UnaryOp(ASTNode::Token type) : Type(type) {}
        ASTNode *UnaryOp::parse(Parser *parser, Token token) {
            ASTNode *node = new ASTNode(Type,token.Begin);
            node->str = token.String;
            node->addChild(parser->parseExpression()); // parse operand
            return node;
        }
        BinaryOp::BinaryOp(ASTNode::Token type, int precedence, bool isRight) : Type(type), 
        Precedence(precedence), IsRight(isRight) {}
        ASTNode *BinaryOp::parse(Parser *parser, ASTNode *left, Token token) {
            ASTNode *node = new ASTNode(Type,token.Begin);
            node->str = token.String;
            node->addChild(left);
            try {
                // right-assocative operators need to call it with 1 lower precedence
                node->addChild(parser->parseExpression(IsRight ? Precedence - 1 : Precedence));
            } catch (ParseError err) {
                if (err.getType() != ParseError::unexpected_token_in_expression) {
                    throw err; // we are not interested in these
                }
                // if this type of error happens here it is likely that the user
                // forgot the other side of an operator. Change the error to reflect that.
                ParseError newErr(token.getEnd(),ParseError::possible_missing_op_rhs);
                newErr.setEnd(err.End);
                newErr << err.getMessage() << Token::getHumanTokenName(token.Type);
                throw newErr;
            }
            
            return node;
        }
        int BinaryOp::getPrecedence(Parser *parser) {
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
            SourceLoc begin = curTok().Begin;
            SourceLoc end = curTok().getEnd();
            ParseError err(begin,ParseError::match_fail);
            err <<  Token::getHumanTokenName(i) << 
                    Token::getHumanTokenName(lookahead(0).Type);
            err.setEnd(end);
            throw err;
        }
    }
    ASTNode *Parser::parseExpression(int precedence) {
        Token token = consume();
        
        if (PrefixOps.find(token.Type) == PrefixOps.end()) {
            ParseError err(curTok().Begin,ParseError::unexpected_token_in_expression);
            err << Token::getHumanTokenName(token.Type) << token.String; // args
            err.setEnd(curTok().getEnd());
            throw err;

        }
        Parselet::PrefixOp *prefix = PrefixOps[token.Type];
        
        ASTNode *left = prefix->parse(this, token);
        
        //std::cout << "OPERATOR:" << Token::getTokenName(curTok().Type) << std::endl;
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
        return InfixOps[type]->getPrecedence(this);
    }
}