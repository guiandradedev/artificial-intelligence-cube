#include "Queue.h"

void Queue::insert(Solver::Node* node) {
    queue.push(node);
}

Solver::Node* Queue::remove() {
    if (queue.empty()) {
        return nullptr;
    }
    Solver::Node* topNode = queue.front();
    queue.pop();
    return topNode;
}

bool Queue::isEmpty() const {
    return queue.empty();
}