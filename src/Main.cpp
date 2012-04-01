#include <iostream> 
#include <cassert>
#include <fstream>

#include "TuringParser/File.h"
#include "TuringParser/Lexer.h"
#include "TuringParser/ParseError.h"
#include "TuringParser/TuringParser.h"

using namespace TuringParser;

std::string getFileContents(const std::string &filePath) {
    std::ifstream in(filePath.c_str(), std::ios::in | std::ios::binary);
    if (in)
    {
        return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
    }
    return "";
}

void testLexer(std::string fileName) {
    SourceFile *f = new SourceFile(getFileContents(fileName));
    Lexer lex(f);
    Token tok;
    
    try {
        do {
            tok = lex.nextToken();
            std::cout << tok.Begin.getLine() << "," <<
            tok.Begin.getColumn() << " - " <<
            Token::getTokenName(tok.Type) << "(" << tok.String << ")" <<
            " [" << Token::getHumanTokenName(tok.Type) << "]" << std::endl;
        } while (tok.Type != Token::EOF_TKN);
    } catch (ParseError err) {
        std::cerr   << "Lexer error on line " << err.Begin.getLine() << 
        " column " << err.Begin.getColumn() << ": " <<
        err.getMessage() << std::endl;
    }
}

int main(int argc, char** argv) 
{        
    SourceFile *f = new SourceFile("6*7 + 4 - variable div lol**6.0 and true or false");
    Lexer lex(f);
    TuringFileParser parser(lex);
    
    try {
        ASTNode *root = parser.parseExpression();
        std::cout << "PARSED:\n" << root->stringTree() << std::endl;
    } catch (ParseError err) {
        std::cerr   << "Parser error on line " << err.Begin.getLine() << 
        " column " << err.Begin.getColumn() << ": " <<
        err.getMessage() << std::endl;
    }
    
    return 0;
}