#include "TuringParser/TuringParser.h"

namespace OTParser {
    TuringParser::TuringParser(Lexer lex) : Parser(lex) {
        // -----------------------------------------------------------------
        // register all the prefix parselets: Unary operators and primaries
        // -----------------------------------------------------------------
        // primary expressions
        registerPrefixOp(Token::BRACKET_O, new Parselet::GroupParselet());
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
        op = new Parselet::CallParselet();
        registerInfixOp(Token::BRACKET_O, op);
        
    }
    TuringParser::~TuringParser() {
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
    void TuringParser::registerPrefixOp(Token::ID i, Parselet::PrefixOp *op) {
        PrefixParselets.insert(op); // keep it to be freed
        registerOp(i, op);
    }
    void TuringParser::registerInfixOp(Token::ID i, Parselet::InfixOp *op) {
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
        ASTNode *GroupParselet::parse(Parser *parser, Token token) {
            ASTNode *node = parser->parseExpression();
            parser->match(Token::BRACKET_C);
            return node;
        }
        ASTNode *CallParselet::parse(Parser *parser, ASTNode *left, Token token) {
            ASTNode *node = new ASTNode(ASTNode::CALL,token.Begin);
            node->addChild(left); // TODO check for callable expression?
            // we may have no arguments, so check for an immediate )
            if (parser->curTok().Type != Token::BRACKET_C) {
                do {
                    node->addChild(parser->parseExpression());
                } while (parser->curTok().Type == Token::COMMA);
            }
            parser->match(Token::BRACKET_C);
            return node;
        }
        int CallParselet::getPrecedence(Parser *parser) {
            return Precedence::CALL;
        }
        /* Turing does not allow assignment as an expression but you can uncomment this and
           use it if you want them.
        ASTNode *PossibleAssignBinOp::parse(Parser *parser, ASTNode *left, Token token) {
            bool assign = isAssign(parser);
            if(assign) parser->consume(); // consume the =
            ASTNode *node = new ASTNode(assign ? ASTNode::ASSIGN_OP : ASTNode::BIN_OP,token.Begin);
            node->addChild(left); // TODO check for callable expression?
            
            // Assignment has different precedence. It is also right associative so subtract one
            int precedence = assign ? Precedence::ASSIGN - 1 : Prec;
            node->addChild(parser->parseExpression(precedence)); // right side
            return node;
        }
        int PossibleAssignBinOp::getPrecedence(Parser *parser) {
            return isAssign(parser) ? Precedence::ASSIGN : Prec;
        }
        bool PossibleAssignBinOp::isAssign(Parser *parser) const {
            return parser->lookahead(0).Type == Token::OP_EQ;
        }*/
    }
}