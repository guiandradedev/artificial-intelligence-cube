#pragma once

#include "DataStructure/DataStructure.h"
#include <stack>

class Stack : public DataStructure
{
private:
    std::stack<Node *> stack;

public:
    Stack() = default;
    ~Stack() override = default;

    void insert(Node *node) override;
    Node *remove() override;
    bool isEmpty() const override;
};