#ifndef _TuringParser_ASTNode_H_
#define _TuringParser_ASTNode_H_

#include <vector>
#include <string>

namespace TuringParser {
class ASTNode {
public:
    enum Token {
    UNDEFINED
#define AST_TOKEN(tok) ,tok
#include "ASTTokens.h"
#undef AST_TOKEN
    };

    ASTNode(Token tok, int line = 0);
    ASTNode(ASTNode *other);
    ~ASTNode();
    static const char *getTokenName(Token t);

    int getLine();
    void setLine(int line);
    
    std::string stringTree(int indent = 0);
    
    void addChild(ASTNode *child);
    
    Token root; // the operation of this AST node
    std::string str; // string data
    
    std::vector<ASTNode*> children; // sub node
    
private:
    int Line;
    std::string FileName;
};
}

#endif