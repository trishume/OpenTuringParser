#include <iostream> 
#include <cassert>
#include <fstream>

#include "TuringParser/File.h"
#include "TuringParser/Lexer.h"
#include "TuringParser/ParseError.h"

using namespace TuringParser;

std::string getFileContents(const std::string &filePath) {
    std::ifstream in(filePath.c_str(), std::ios::in | std::ios::binary);
    if (in)
    {
        return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
    }
    return "";
}

int main(int argc, char** argv) 
{        
    SourceFile *f = new SourceFile(getFileContents(argv[1]));
    Lexer lex(f);
    Token tok;
    
    try {
        do {
            tok = lex.nextToken();
            std::cout << tok.Begin.getLine() << "," <<
            tok.Begin.getColumn() << " - " <<
            Token::getTokenName(tok.Type) << "(" << tok.String << ")" << std::endl;
        } while (tok.Type != Token::EOF_TKN);
    } catch (ParseError err) {
        std::cerr   << "Lexer error on line " << err.Begin.getLine() << 
                    " column " << err.Begin.getColumn() << ": " <<
                    err.getMessage() << std::endl;
    }
    
    
    
    return 0;
}