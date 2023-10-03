//
// Created by Yormingandr on 10/3/2023.
//

#ifndef AXODB_AST_H
#define AXODB_AST_H

#include <string>
#include <vector>
#include <unordered_map>

namespace axodb {

    enum class CRUDOperation {
        SELECT,
        INSERT,
        UPDATE,
        DELETE
    };

    class ASTNode {
    public:
        virtual ~ASTNode() = default;
        virtual CRUDOperation getOperationType() = 0;
    };

    class Expression {
    public:
        std::string column;
        std::string value; // Keeping it as string for now

        enum class Operator {
            EQUALS,
            NOT_EQUALS,
            GREATER_THAN,
            LESS_THAN,
        } op;
    };

    class SelectNode : public ASTNode {
    public :
        CRUDOperation getOperationType() const override { return CRUDOperation::SELECT; }

        std::vector<std::string> columns;
        std::string table;
        Expression condition;
    };


    class InsertNode : public ASTNode {
    public :
        CRUDOperation getOperationType() const override { return CRUDOperation::INSERT; }

        std::string table;
        std::unordered_map<std::string, std::string> columnValues;
    };

    class UpdateNode : public ASTNode {
    public:
        CRUDOperation getOperationType() const override { return CRUDOperation::UPDATE; }

        std::string table;
        std::unordered_map<std::string, std::string> columnValues;
        Expression condition;
    };


    class DeleteNode : public ASTNode {
    public:
        CRUDOperation getOperationType() const override { return CRUDOperation::DELETE; }

        std::string table;
        Expression condition;
    };
}
#endif //AXODB_AST_H
