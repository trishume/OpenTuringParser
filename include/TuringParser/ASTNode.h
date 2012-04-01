#ifndef _TuringParser_ASTNode_H_
#define _TuringParser_ASTNode_H_

#include <vector>
#include <string>

#include "TuringParser/SourceLoc.h"

namespace OTParser {
class ASTNode {
public:
    enum Token {
    UNDEFINED
#define AST_TOKEN(tok) ,tok
#include "ASTTokens.h"
#undef AST_TOKEN
    };

    ASTNode(Token tok, SourceLoc loc, std::string string = "");
    ASTNode(ASTNode *other);
    ~ASTNode();
    static const char *getTokenName(Token t);

    SourceLoc getLoc() { return Loc;}
    
    std::string stringTree(int indent = 0);
    
    void addChild(ASTNode *child);
    
    Token root; // the operation of this AST node
    std::string str; // string data
    
    std::vector<ASTNode*> children; // sub node
    
private:
    SourceLoc Loc;
    std::string FileName;
};
}

#endif