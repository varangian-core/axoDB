//
// Created by Yormingandr on 10/3/2023.
//

#include "QueryParser.h"
#include <sstream>
#include <vector>
#include <string>


namespace axodb {
    AST QueryParser::parse(const std::string& query) {
        AST ast;
        std::vector<std::string> tokens = tokenize(query);
        if (tokens.size() >= 4 && tokens[0] == "SELECT" && tokens[2] == "FROM") {
            ast.operation = AST::Operation::SELECT;
            ast.columns.push_back(tokens[1]);
            ast.table = tokens[3];
        }
        return ast;
    }



    std::vector<std::string> QueryParser::tokenize(const std::string& query){
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(query);

        while (std::getline(tokenStream, token, ' ') {
            tokens.push_back(token);
        }
        return token;
    }
}; // namespace axodb
