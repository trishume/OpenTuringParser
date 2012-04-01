#include "TuringParser/TuringParser.h"

namespace TuringParser {
    TuringFileParser::TuringFileParser(Lexer lex) : Parser(lex) {
        // -----------------------------------------------------------------
        // register all the prefix parselets: Unary operators and primaries
        // -----------------------------------------------------------------
        // primary expressions
        registerPrefixOp(Token::IDENTIFIER, new Parselet::PrimaryParselet(ASTNode::VAR_REFERENCE));
        registerPrefixOp(Token::INTLITERAL, new Parselet::PrimaryParselet(ASTNode::INT_LITERAL));
        registerPrefixOp(Token::REALLITERAL, new Parselet::PrimaryParselet(ASTNode::REAL_LITERAL));
        registerPrefixOp(Token::TRUE, new Parselet::PrimaryParselet(ASTNode::BOOL_LITERAL));
        registerPrefixOp(Token::FALSE, new Parselet::PrimaryParselet(ASTNode::BOOL_LITERAL));
        registerPrefixOp(Token::STRINGLITERAL, 
                         new Parselet::StringLiteralParselet(ASTNode::STRING_LITERAL));
        registerPrefixOp(Token::CHARLITERAL, 
                         new Parselet::StringLiteralParselet(ASTNode::CHAR_LITERAL));
        // unary operators
        registerPrefixOp(Token::OP_MINUS, new Parselet::UnaryOp(ASTNode::UNARY_OP));
        registerPrefixOp(Token::OP_NOT, new Parselet::UnaryOp(ASTNode::UNARY_OP));
        registerPrefixOp(Token::OP_DEREF, new Parselet::UnaryOp(ASTNode::UNARY_OP));
        // -----------------------------------------------------------------
        // register the infix parselets: Binary and postfix operators, calls
        // -----------------------------------------------------------------
        Parselet::InfixOp *op;
        op = new Parselet::BinaryOp(ASTNode::ASSIGN_OP, Precedence::ASSIGN,false);
        registerInfixOp(Token::OP_ASSIGN, op);
        registerInfixOp(Token::OP_ASSIGN_DIVIDE, op);
        registerInfixOp(Token::OP_ASSIGN_MINUS, op);
        registerInfixOp(Token::OP_ASSIGN_MULT, op);
        registerInfixOp(Token::OP_ASSIGN_PLUS, op);
        op = new Parselet::BinaryOp(ASTNode::BIN_OP, Precedence::OR,false);
        registerInfixOp(Token::OP_OR, op);
        op = new Parselet::BinaryOp(ASTNode::BIN_OP, Precedence::AND,false);
        registerInfixOp(Token::OP_AND, op);
        op = new Parselet::BinaryOp(ASTNode::BIN_OP, Precedence::COMPARE,false);
        registerInfixOp(Token::OP_GT, op);
        registerInfixOp(Token::OP_GE, op);
        registerInfixOp(Token::OP_LT, op);
        registerInfixOp(Token::OP_LE, op);
        registerInfixOp(Token::OP_IN, op);
        // TODO not in operator
        op = new Parselet::BinaryOp(ASTNode::EQUALITY_OP, Precedence::COMPARE,false);
        registerInfixOp(Token::OP_EQ, op);
        registerInfixOp(Token::OP_NOT_EQ, op);
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
    TuringFileParser::~TuringFileParser() {
        // Free all the parselets, we no longer need them
        for (std::set<Parselet::PrefixOp*>::iterator it = PrefixParselets.begin(),
             end = PrefixParselets.end(); it != end; ++it) {
            //delete *it;
        }
        for (std::set<Parselet::InfixOp*>::iterator it = InfixParselets.begin(),
             end = InfixParselets.end(); it != end; ++it) {
            //delete *it;
        }
    }
    void TuringFileParser::registerPrefixOp(Token::ID i, Parselet::PrefixOp *op) {
        PrefixParselets.insert(op); // keep it to be freed
        registerOp(i, op);
    }
    void TuringFileParser::registerInfixOp(Token::ID i, Parselet::InfixOp *op) {
        InfixParselets.insert(op); // keep it to be freed
        registerOp(i, op);
    }
    namespace Parselet {
        ASTNode *PrimaryParselet::parse(Parser *parser, Token token) {
            return new ASTNode(Type,token.Begin,token.String);
        }
        ASTNode *StringLiteralParselet::parse(Parser *parser, Token token) {
            // strip the opening and closing quotes
            return new ASTNode(Type,token.Begin,
                               token.String.substr(1,token.String.size()-2));
        }
    }
}