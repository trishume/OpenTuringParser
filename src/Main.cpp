#include <iostream> 
#include <cassert>
#include <fstream>

#include "TuringParser/File.h"
#include "TuringParser/Lexer.h"
#include "TuringParser/ParseError.h"
#include "TuringParser/TuringParser.h"

using namespace OTParser;

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
    SourceFile *f = new SourceFile("6*(7 + 4) - Math.pow(7,9) div 6**6.0 < 8 xor variable.field->troll and true or false");
    Lexer lex(f);
    TuringParser parser(lex);
    
    try {
        ASTNode *root = parser.parseExpression();
        std::cout << "PARSED:\n" << root->stringTree() << std::endl;
    } catch (ParseError err) {
        std::cerr   << "Syntax error on line " << err.Begin.getLine() << 
        " column " << err.Begin.getColumn();
        if (err.End.isValid()) {
            std::cerr << " to " << err.End.getColumn();
        }
        std::cerr << ": " << err.getMessage() << "\n";
    }
    
    return 0;
}