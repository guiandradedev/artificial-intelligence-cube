#pragma once

#include "DataStructure.h"
#include <stack>

class Stack : public DataStructure {
private:
    std::stack<Solver::Node*> stack;

public:
    Stack() = default;
    ~Stack() override = default;

    void insert(Solver::Node* node) override;
    Solver::Node* remove() override;
    bool isEmpty() const override;
};