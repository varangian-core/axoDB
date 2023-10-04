//
// Created by Yormingandr on 10/3/2023.
//

#include "QueryParser.h"
#include <sstream>
#include <vector>
#include <string>


namespace axodb {
    ASTNode *QueryParser::parse(const std::string &query) {
        //TODO: work through parse logic here
        auto tokens = tokenize(query);
        if (tokens[0] == "SELECT") {
            SelectNode *node = new SelectNode();
            node->columns.push_back("*"); //not sure
            node->table = tokens[3];
            return node;
        }

        return nullptr;
    }


    std::vector<std::string> QueryParser::tokenize(const std::string &str, const std::string &delim) {
        std::vector<std::string> tokens;
        size_t prev = 0, pos  = 0;
        do {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos - prev);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }
} // namespace axodb
