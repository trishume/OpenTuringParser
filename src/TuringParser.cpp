#include "TuringParser/TuringParser.h"

namespace TuringParser {
    TuringFileParser::TuringFileParser(Lexer lex) : Parser(lex) {
        // -----------------------------------------------------------------
        // register all the prefix parselets: Unary operators and primaries
        // -----------------------------------------------------------------
        registerPrefixOp(Token::IDENTIFIER, new Parselet::PrimaryParselet(ASTNode::VAR_REFERENCE));
        registerPrefixOp(Token::INTLITERAL, new Parselet::PrimaryParselet(ASTNode::INT_LITERAL));
        registerPrefixOp(Token::REALLITERAL, new Parselet::PrimaryParselet(ASTNode::REAL_LITERAL));
        registerPrefixOp(Token::OP_MINUS, new Parselet::UnaryOp(ASTNode::UNARY_OP));
        // -----------------------------------------------------------------
        // register the infix parselets: Binary and postfix operators, calls
        // -----------------------------------------------------------------
        Parselet::InfixOp *op;
        // additive operators
        op = new Parselet::BinaryOp(ASTNode::BIN_OP, Precedence::ADD,false);
        registerInfixOp(Token::OP_MINUS, op);
        registerInfixOp(Token::OP_PLUS, op);
        registerInfixOp(Token::OP_XOR, op);
        op = new Parselet::BinaryOp(ASTNode::BIN_OP, Precedence::MULTIPLY,false);
        registerInfixOp(Token::OP_MULT, op);
        registerInfixOp(Token::OP_DIVIDE, op);
        registerInfixOp(Token::OP_DIV, op);
        registerInfixOp(Token::OP_MOD, op);
        registerInfixOp(Token::OP_REM, op);
        registerInfixOp(Token::OP_SHL, op);
        registerInfixOp(Token::OP_SHR, op);
        op = new Parselet::BinaryOp(ASTNode::BIN_OP, Precedence::MODIFIER,false);
        registerInfixOp(Token::OP_EXPONENT, op);
        
    }
    void TuringFileParser::registerPrefixOp(Token::ID i, Parselet::PrefixOp *op) {
        Parselets.insert((void*)op); // keep it to be freed
        registerOp(i, op);
    }
    void TuringFileParser::registerInfixOp(Token::ID i, Parselet::InfixOp *op) {
        Parselets.insert((void*)op); // keep it to be freed
        registerOp(i, op);
    }
    namespace Parselet {
        ASTNode *PrimaryParselet::parse(Parser *parser, Token token) {
            return new ASTNode(Type,token.Begin,token.String);
        }
    }
}