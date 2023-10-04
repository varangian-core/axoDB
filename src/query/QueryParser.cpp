//
// Created by Yormingandr on 10/3/2023.
//

#include "QueryParser.h"
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


namespace axodb {
    //Looks like I need some Bison work here. Alternative is ANTLR

    ASTNode *QueryParser::parse(const std::string &query) {
        auto tokens = tokenize(query);

        if (tokens[0] == "SELECT") {
            return parseSelect(tokens);
        } else if (tokens[0] == "INSERT") {
            return parseInsert(tokens);
        } else if (tokens[0] == "UPDATE") {
            return parseUpdate(tokens);
        } else if (tokens[0] == "DELETE") {
            return parseDelete(tokens);
        }

        throw std::runtime_error("Unsupported SQL operation");
    }


    std::vector<std::string> QueryParser::tokenize(const std::string &str, const std::string &delim) {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos - prev);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }

    SelectNode *QueryParser::parseSelect(const std::vector<std::string> &tokens) {
        //Covers only: SELECT columns FROM table WHERE condition
        auto selectNode = new SelectNode();
        size_t fromIndex = std::find(tokens.begin(), tokens.end(), "FROM") - tokens.begin();
        for (size_t i = 1; i < fromIndex; ++i) {
            selectNode->columns.push_back(tokens[i]);
        }

        selectNode->table = tokens[fromIndex + 1];

        size_t whereIndex = std::find(tokens.begin(), tokens.end(), "WHERE") - tokens.begin();
        if (whereIndex != tokens.size()) {
            selectNode->condition = parseCondition(tokens[whereIndex + 1]);
        }

        return selectNode;
    }

    InsertNode *QueryParser::parseInsert(const std::vector<std::string> &tokens) {
        //Covers only: INSERT INTO table (columns) VALUES (values)
        auto insertNode = new InsertNode();
        insertNode->table = tokens[2];
        size_t valuesIndex = std::find(tokens.begin(), tokens.end(), "VALUES") - tokens.begin();
        return insertNode;
    }

    UpdateNode *QueryParser::parseUpdate(const std::vector<std::string> &tokens) {
        //Covers only: Update table SET column1 = value1,  ... WHERE condition
        auto updateNode = new UpdateNode();
        updateNode->table = tokens[1];
        size_t setIndex = std::find(tokens.begin(), tokens.end(), "SET") - tokens.begin();
        size_t whereIndex = std::find(tokens.begin(), tokens.end(), "WHERE") - tokens.begin();

        if (whereIndex != tokens.size()) {
            updateNode->condition = parseCondition(tokens[whereIndex + 1]);
            return updateNode;
        }
    }

    DeleteNode *QueryParser::parseDelete(const std::vector<std::string> &tokens) {
        auto deleteNode = new DeleteNode();
        //Covers only DELETE FROM table WHERE condition
        deleteNode->table = tokens[2];
        size_t whereIndex = std::find(tokens.begin(), tokens.end(), "WHERE") - tokens.begin();
        if (whereIndex != tokens.size()) {
            deleteNode->condition = parseCondition(tokens[whereIndex + 1]);
        }
        return deleteNode;
    }

    Expression QueryParser::parseCondition(const std::string &conditionStr) {
        Expression expr;
        std::size_t pos;
        if ((pos = conditionStr.find("=")) != std::string::npos) {
            expr.op = Expression::Operator::EQUALS;
        } else if ((pos = conditionStr.find("<>")) != std::string::npos) {
            expr.op = Expression::Operator::NOT_EQUALS;
        } else if ((pos = conditionStr.find(">")) != std::string::npos) {
            expr.op = Expression::Operator::GREATER_THAN;
        } else if ((pos = conditionStr.find("<")) != std::string::npos) {
            expr.op = Expression::Operator::LESS_THAN;
        } else {
            throw std::runtime_error("Unsupported operator");
        }


        expr.column = conditionStr.substr(0, pos);
        expr.value = conditionStr.substr(pos + 1);


        //Remove whitespaces
        expr.column.erase(expr.column.begin(),
                          std::find_if(expr.column.begin(), expr.column.end(), [](unsigned char ch) {
                              return !std::isspace(ch);
                          }));
        expr.column.erase(std::find_if(expr.column.rbegin(), expr.column.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), expr.column.end());

        expr.value.erase(expr.value.begin(), std::find_if(expr.value.begin(), expr.value.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));

        expr.value.erase(std::find_if(expr.value.rbegin(), expr.value.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), expr.value.end());

        return expr;
    }

} // namespace axodb
