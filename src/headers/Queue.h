#pragma once

#include "DataStructure.h"
#include "Node.h"
#include <queue>

class Queue : public DataStructure {
private:
    std::queue<Node*> queue;

public:
    Queue() = default;
    ~Queue() override =default;

    void insert(Node* node) override;
    Node* remove() override;
    bool isEmpty() const override;
};