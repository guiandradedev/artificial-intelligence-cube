#pragma once

#include "DataStructure.h"
#include <queue>

class Queue : public DataStructure {
private:
    std::queue<Solver::Node*> queue;

public:
    Queue() = default;
    ~Queue() override =default;

    void insert(Solver::Node* node) override;
    Solver::Node* remove() override;
    bool isEmpty() const override;
};