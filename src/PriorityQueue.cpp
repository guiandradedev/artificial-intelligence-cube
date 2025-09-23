#include "DataStructure.h"
#include "Node.h"
#include "AstarNode.h"
#include <queue>
#include <vector>
#include <functional>
#include "PriorityQueue.h"
#include "Hasher.h"

// Comparador que funciona com ponteiros de Node, mas usa f_cost se for AstarNode
// struct CompareNodes {
//     bool operator()(Node* a, Node* b) const {
//         // Tenta fazer cast para AstarNode
//         AstarNode* na = dynamic_cast<AstarNode*>(a);
//         AstarNode* nb = dynamic_cast<AstarNode*>(b);

//         if (na && nb) {
//             return na->f_cost > nb->f_cost; // menor f_cost tem prioridade
//         }

//         // fallback: se não forem A*, não mudar a ordem
//         return false;
//     }
// };


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
// void PriorityQueue::insert(AstarNode* node) {
//     int g = 0;
//     if (node->root) {
//         AstarNode* parent = dynamic_cast<AstarNode*>(node->root);
//         g = parent ? parent->g_cost + 1 : 1;
//     }
//     int h = Hasher::get_distance(node->cube);
//     int f = g + h;

//     node->g_cost = g;
//     node->f_cost = f;
//     pq.push(*node);
// }
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