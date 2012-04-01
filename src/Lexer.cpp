#include "TuringParser/Lexer.h"

#include "TuringParser/ParseError.h"

#define DIGRAPH(c1,s1,t1,c2,s2,t2)  case c1: \
                                    consume(); \
                                    switch (C) { \
                                        case c2: \
                                            consume(); \
                                            return newToken(t2, s2); \
                                        default: \
                                            return newToken(t1, s1); \
                                    }
#define KEYWORD(k,tok) Keywords[#k] = Token::tok

namespace TuringParser {
    Lexer::Lexer(SourceFile *file) : Input(file), Pos(0) {
        C = Input->Data[Pos];
        
        // initialize keyword tokens
        
        // operators
        Keywords["div"] = Token::OP_DIV;
        Keywords["mod"] = Token::OP_MOD;
        Keywords["rem"] = Token::OP_REM;
        Keywords["shl"] = Token::OP_SHL;
        Keywords["shr"] = Token::OP_SHR;
        Keywords["xor"] = Token::OP_XOR;
        Keywords["or"] = Token::OP_OR;
        Keywords["and"] = Token::OP_AND;
        Keywords["in"] = Token::OP_IN;
        
        // general
        KEYWORD(addressint,ADDRESSINT);
        KEYWORD(all,ALL);
        KEYWORD(array,ARRAY);
        KEYWORD(asm,ASM);
        KEYWORD(assert,ASSERT);
        KEYWORD(begin,BEGIN);
        KEYWORD(bind,BIND);
        KEYWORD(bits,BITS);
        KEYWORD(body,BODY);
        KEYWORD(break,BREAK);
        KEYWORD(by,BY);
        KEYWORD(case,CASE);
        KEYWORD(cheat,CHEAT);
        KEYWORD(checked,CHECKED);
        KEYWORD(class,CLASS);
        KEYWORD(close,CLOSE);
        KEYWORD(collection,COLLECTION);
        KEYWORD(condition,CONDITION);
        KEYWORD(const,CONST);
        KEYWORD(decreasing,DECREASING);
        KEYWORD(def,DEF);
        KEYWORD(deferred,DEFERRED);
        KEYWORD(else,ELSE);
        KEYWORD(elseif,ELSEIF);
        KEYWORD(elsif,ELSIF);
        KEYWORD(end,END);
        KEYWORD(enum,ENUM);
        KEYWORD(exit,EXIT);
        KEYWORD(export,EXPORT);
        KEYWORD(external,EXTERNAL);
        KEYWORD(false,FALSE);
        KEYWORD(fcn,FCN);
        KEYWORD(flexible,FLEXIBLE);
        KEYWORD(for,FOR);
        KEYWORD(fork,FORK);
        KEYWORD(forward,FORWARD);
        KEYWORD(free,FREE);
        KEYWORD(function,FUNCTION);
        KEYWORD(get,GET);
        KEYWORD(handler,HANDLER);
        KEYWORD(if,IF);
        KEYWORD(implement,IMPLEMENT);
        KEYWORD(import,IMPORT);
        KEYWORD(include,INCLUDE);
        KEYWORD(inherit,INHERIT);
        KEYWORD(init,INIT);
        KEYWORD(invariant,INVARIANT);
        KEYWORD(label,LABEL);
        KEYWORD(loop,LOOP);
        KEYWORD(module,MODULE);
        KEYWORD(monitor,MONITOR);
        KEYWORD(nat,NAT);
        KEYWORD(nat1,NAT1);
        KEYWORD(nat2,NAT2);
        KEYWORD(nat4,NAT4);
        KEYWORD(new,NEW);
        KEYWORD(not,NOT);
        KEYWORD(objectclass,OBJECTCLASS);
        KEYWORD(of,OF);
        KEYWORD(opaque,OPAQUE);
        KEYWORD(open,OPEN);
        KEYWORD(packed,PACKED);
        KEYWORD(pause,PAUSE);
        KEYWORD(pervasive,PERVASIVE);
        KEYWORD(pointer,POINTER);
        KEYWORD(post,POST);
        KEYWORD(pre,PRE);
        KEYWORD(priority,PRIORITY);
        KEYWORD(proc,PROC);
        KEYWORD(procedure,PROCEDURE);
        KEYWORD(process,PROCESS);
        KEYWORD(put,PUT);
        KEYWORD(quit,QUIT);
        KEYWORD(read,READ);
        KEYWORD(record,RECORD);
        KEYWORD(register,REGISTER);
        KEYWORD(result,RESULT);
        KEYWORD(return,RETURN);
        KEYWORD(seek,SEEK);
        KEYWORD(self,SELF);
        KEYWORD(set,SET);
        KEYWORD(signal,SIGNAL);
        KEYWORD(skip,SKIP);
        KEYWORD(string,STRING);
        KEYWORD(tag,TAG);
        KEYWORD(tell,TELL);
        KEYWORD(then,THEN);
        KEYWORD(timeout,TIMEOUT);
        KEYWORD(to,TO);
        KEYWORD(true,TRUE);
        KEYWORD(type,TYPE);
        KEYWORD(unchecked,UNCHECKED);
        KEYWORD(union,UNION);
        KEYWORD(unqualified,UNQUALIFIED);
        KEYWORD(var,VAR);
        KEYWORD(wait,WAIT);
        KEYWORD(when,WHEN);
        KEYWORD(write,WRITE);
    }
    void Lexer::consume() {
        ++Pos;
        if (Pos >= Input->Data.size()) {
            C = EOF_CHAR;
        } else {
            C = Input->Data[Pos];
        }
    }
    char Lexer::lookahead(int n) {
        if (Pos >= Input->Data.size()) {
            return EOF_CHAR;
        } else {
            return Input->Data[Pos+n];
        }
    }
    void Lexer::match(char x) {
        if (C == x) {
            consume();
        } else {
            std::ostringstream os;
            os << "Expected '" << x << "'; found '" << C << "'";
            SourceLoc begin(Input,Pos);
            SourceLoc end(Input,Pos+1);
            ParseError err(begin,os.str());
            err.setEnd(end);
            err.setHint(FixItHint::CreateReplacement(SourceRange(begin,end),
                                                     std::string(1,x)));
            throw err;
        }
    }
    Token Lexer::newToken(Token::ID i, const std::string &str) {
        Token tkn(i,str);
        // subtract str.size() for the pos to get the beginning instead of the end
        tkn.Begin = SourceLoc(Input,Pos-str.size());
        return tkn;
    }
    bool Lexer::isLetter(char x) {
        return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');
    }
    bool Lexer::isDigit(char x) {
        return x >= '0' && x <= '9';
    }
    Token Lexer::nextToken() {
        while (C!=EOF_CHAR) {
            switch (C) {
                // skip whitespace
                case ' ': case '\n': case '\t': case '\r': skipWhitespace(); continue;
                case '%': skipLineComment(); break;
                case '"': return stringOrCharLiteral(false);
                case '\'': return stringOrCharLiteral(true);
                    
                case ',': consume(); return newToken(Token::COMMA, ",");
                case '(': consume(); return newToken(Token::BRACKET_O, "(");
                case ')': consume(); return newToken(Token::BRACKET_C, ")");
                case '[': consume(); return newToken(Token::SQUARE_BRACKET_O, "[");
                case ']': consume(); return newToken(Token::SQUARE_BRACKET_C, "]");
                case '^': consume(); return newToken(Token::OP_DEREF, "^");
                case '&': consume(); return newToken(Token::OP_AND, "&");
                case '|': consume(); return newToken(Token::OP_OR, "|");
                    
                case '*':
                    consume();
                    switch (C) {
                        case '*':
                            consume();
                            return newToken(Token::OP_EXPONENT, "**");
                        case '=':
                            consume();
                            return newToken(Token::OP_ASSIGN_MULT, "*=");
                        default:
                            return newToken(Token::OP_MULT, "*");
                    }
                case '-':
                    if(isDigit(lookahead(1))) { // literal of form -234
                        return numLiteral();
                    }
                    consume(); // if it is not a number we can consume the -
                    if (C=='=') {
                        consume();
                        return newToken(Token::OP_ASSIGN_MINUS, "-=");
                    } else {
                        return newToken(Token::OP_MINUS, "-");
                    }
                case '/':
                    consume();
                    switch (C) {
                        case '*':
                            skipBlockComment();
                        case '=':
                            consume();
                            return newToken(Token::OP_ASSIGN_DIVIDE, "/=");
                        default:
                            return newToken(Token::OP_DIVIDE, "/");
                    }
                    break;
                case '.':
                    if (isDigit(lookahead(1))) { // real literal of form .25
                        return numLiteral();
                    }
                    consume();
                    if (C == '.') {
                        consume();
                        return newToken(Token::DOTDOT, "..");
                    }
                    return newToken(Token::OP_DOT, ".");
                // the macro expands in to a case statement for the first character
                // which then checks for the second character.
                DIGRAPH('+', "+", Token::OP_PLUS, '=', "+=", Token::OP_ASSIGN_PLUS)
                DIGRAPH(':', ":", Token::COLON, '=', ":=", Token::OP_ASSIGN)
                DIGRAPH('=', "=", Token::OP_EQ, '=', "=>", Token::OP_IMPLIES)
                DIGRAPH('<', "<", Token::OP_LT, '=', "<=", Token::OP_LE)
                DIGRAPH('>', ">", Token::OP_GT, '=', ">=", Token::OP_GE)
                DIGRAPH('~', "~", Token::OP_NOT, '=', "~=", Token::OP_NOT_EQ)
                    
                    
                default:
                    if (isLetter(C)) return identifier();
                    if (isDigit(C)) return numLiteral();
                    // don't recognize token
                    std::ostringstream os;
                    os << "Unexpected character: '" << C;
                    SourceLoc begin(Input,Pos);
                    SourceLoc end(Input,Pos+1);
                    ParseError err(SourceLoc(Input,Pos),os.str());
                    err.setEnd(end);
                    throw err;
                    break;
            }
        }
        return newToken(Token::EOF_TKN, "");
    }
    Token Lexer::numLiteral() {
        std::ostringstream os;
        if (C == '-') {
            os << C; consume();
        }
        consumeDigits(os);
        bool isRealLiteral = false;
        // look for a decimal but be careful not to consume part of a ..
        if (C == '.' && lookahead(1) != '.') {
            isRealLiteral = true;
            os << C;
            consume();
            consumeDigits(os);
        }
        if (C == 'e') {
            isRealLiteral = true;
            os << C;
            consume();
            if (C == '-') {
                os << C; consume();
            }
            consumeDigits(os);
        }
        
        return newToken(isRealLiteral ? Token::REALLITERAL : Token::INTLITERAL, os.str());
    }
    Token Lexer::identifier() {
        std::ostringstream os;
        do {
            os << C;
            consume();
        } while (isLetter(C) || isDigit(C) || C == '_');
        
        std::string str = os.str();
        if (Keywords.find(str) == Keywords.end()) {
            return newToken(Token::IDENTIFIER, str);
        }
        return newToken(Keywords[str], str);
    }
    Token Lexer::stringOrCharLiteral(bool isCharLiteral) {
        char delimiter = (isCharLiteral ? '\'' : '"');
        std::ostringstream os;
        
        // match the opening quote and then add it to the token string
        match(delimiter); os << delimiter;
        bool escaped; // used to check for escaped quote
        do {
            escaped = (C == '\\');
            os << C;
            consume();
        } while (C != delimiter || escaped);
        // match the closing quote and then add it to the token string
        match(delimiter); os << delimiter;
        
        return newToken(isCharLiteral ? Token::CHARLITERAL : Token::STRINGLITERAL, os.str());
    }
    
    void Lexer::skipLineComment() {
        consume(); //consume %
        while (C != '\n') {
            consume();
        }
    }
    void Lexer::skipBlockComment() {
        //consume opening '/'
        //consume();
        //consume '*'
        consume();
        
        bool sawStar; // used to check for '*' before '/'
        do { // skip until */
            sawStar = (C == '*');
            consume();
        } while ( !(C == '/' && sawStar) );
        consume(); // consume final '/'
    }
    void Lexer::skipWhitespace() {
        while (C == ' ' || C == '\n' || C == '\t' || C == '\r') {
            consume();
        }
    }
    void Lexer::consumeDigits(std::ostringstream &os) {
        while (isDigit(C)) {
            os << C;
            consume();
        }
    }
}