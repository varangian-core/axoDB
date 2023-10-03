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
    AST parse(const std::string& query);


private:
    std::vector<std::string> split(const std::string& str, const std::string& delim);
};


#endif //AXODB_QUERYPARSER_H
