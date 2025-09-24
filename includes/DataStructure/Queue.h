#pragma once

#include "DataStructure.h"
#include <queue>

class Queue : public DataStructure {
private:
    std::queue<Node*> queue;

public:
    void insert(Node *node) override;
    Node *remove() override;
    bool isEmpty() const override;
};