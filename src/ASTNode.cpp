#include "TuringParser/ASTNode.h"

namespace TuringParser {
    
    typedef std::vector<ASTNode*> NodeList;

    const char *ASTNode::getTokenName(ASTNode::Token tok) {
        switch(tok) {
            case ASTNode::UNDEFINED: return "<undefined/null>";
#define AST_TOKEN(tok) case ASTNode::tok: return #tok;
#include "TuringParser/ASTTokens.h"
#undef AST_TOKEN
        }
        return "<UNKNOWN TOKEN!>";
    }

    // get the line number of the node (or try to derive it from the child node)
    ASTNode::ASTNode(ASTNode::Token tok, int line) : root(tok) , Line(line) {}

    //! deep copy constructor
    ASTNode::ASTNode(ASTNode *other) {
        root = other->root;
        str = other->str;
        setLine(other->getLine());
        
        // recursively copy children
        for(NodeList::iterator it = other->children.begin(), e = other->children.end(); it < e; ++it) {
            addChild(new ASTNode(*it));
        }
    }

    //! free the children! (Craig Keilburger reference)
    ASTNode::~ASTNode() { 
        while(!children.empty()) {
            delete children.back();
            children.pop_back();
        }
    }

    int ASTNode::getLine() {
        if ( Line != 0 )
            return Line;
        if( children.size() != 0 )
            return children[0]->getLine();
        return 0;
    }
    void ASTNode::setLine(int line) {
        Line = line;
    }

    void ASTNode::addChild(ASTNode *child) {
        children.push_back(child);
    }

    std::string ASTNode::stringTree(int indent) {
        std::string out;
        out += "("; 
        out += ASTNode::getTokenName(root);
        out += "[";
        out += str;
        out += "]";
        
        NodeList::iterator it;
        for(it = children.begin(); it < children.end(); ++it) {
            out += "\n";
            for (int i = 0; i < indent; ++i) {
                out += "\t";
            }
            ASTNode *child = *it;
            if(child == NULL) {
                out += "NULL";
            } else {
                out += child->stringTree(indent+1);
            }
        }
        out += ")";
        return out;
    }
}