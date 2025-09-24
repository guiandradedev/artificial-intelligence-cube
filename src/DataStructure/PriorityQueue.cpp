#include <queue>
#include <vector>
#include <functional>
#include "Node/Node.h"
#include "Node/AstarNode.h"
#include "Hasher.h"
#include "DataStructure/PriorityQueue.h"

void PriorityQueue::insert(Node* node) {
    if (AstarNode* f = dynamic_cast<AstarNode*>(node)) {
        int g = 0;
        if (f->root) {
            if (AstarNode* parent = dynamic_cast<AstarNode*>(f->root)) {
                g = parent->g_cost + 1;
            } else {
                g = 1; // fallback if root is not an AstarNode
            }
        }
        int h = Hasher::get_distance(node->cube);
        int z = g + h;

        // Assuming pq is std::priority_queue<AstarNode*, ...>
        f->g_cost = g;
        f->f_cost = z;
        pq.push(f); // Push the object, not the pointer
    } else {
        std::cout << "errorororororo" << std::endl;
    }
    
}

AstarNode* PriorityQueue::remove() {
    if (pq.empty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    AstarNode* topNode = pq.top();
    pq.pop();
    return topNode;
}

bool PriorityQueue::isEmpty() const {
    return pq.empty();
}