//
// Created by Yormingandr on 10/3/2023.
//

#ifndef AXODB_QUERYPARSER_H
#define AXODB_QUERYPARSER_H


#include <string>
#include "AST.h"

namespace axodb {

    class QueryParser {
    public:
        ASTNode* parse(const std::string &query);


    private:
        std::vector<std::string> tokenize(const std::string &query , const std::string &delim = " ");
        SelectNode* parseSelect(const std::vector<std::string>& tokens);
        InsertNode* parseInsert(const std::vector<std::string>& tokens);
        UpdateNode* parseUpdate(const std::vector<std::string>& tokens);
        DeleteNode* parseDelete(const std::vector<std::string>& tokens);
        Expression parseCondition(const std::string& conditionStr);
    };
}


#endif //AXODB_QUERYPARSER_H
