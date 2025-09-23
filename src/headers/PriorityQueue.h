#pragma once

#include "DataStructure.h"
#include "Node.h"
#include <queue>

// Make sure AstarNode is defined or included
#include "AstarNode.h"

struct CompareNodes {
    bool operator()(Node* a, Node* b) const {
        // Tenta fazer cast para AstarNode
        AstarNode* na = dynamic_cast<AstarNode*>(a);
        AstarNode* nb = dynamic_cast<AstarNode*>(b);

        if (na && nb) {
            return na->f_cost > nb->f_cost; // menor f_cost tem prioridade
        }

        // fallback: se não forem A*, não mudar a ordem
        return false;
    }
};

class PriorityQueue : public DataStructure {
private:
    std::priority_queue<AstarNode*, std::vector<AstarNode*>, CompareNodes> pq;
    // std::priority_queue<AstarNode, std::vector<AstarNode>, std::greater<AstarNode>> pq;
    std::unordered_map<Cube,int> g_costs;
    Cube start;


public:
    PriorityQueue() = default;
    ~PriorityQueue() override =default;

    void insert(Node* node) override;
    // void insert(AstarNode* node) override;
    AstarNode* remove() override;
    bool isEmpty() const override;
};