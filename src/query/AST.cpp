//
// Created by Yormingandr on 10/3/2023.
//

#include "AST.h"

namespace axodb {
    AST::AST(ASTNode *rootNode) : rootNode_(rootNode) {}

    AST::~AST() {
        delete rootNode_;
    }

//    AST::AST(AST&& other) noexcept : rootNode_(other.rootNode_) {
//        other.rootNode_ = nullptr;
//Copilot suggestion

    ASTNode *AST::getRootNode() const {
        return rootNode_;
    }
}