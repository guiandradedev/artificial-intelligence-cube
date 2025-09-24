#include "DataStructure/Queue.h"
#include "Node/Node.h"

void Queue::insert(Node* node) {
    queue.push(node);
}

Node* Queue::remove() {
    if (queue.empty()) {
        return nullptr;
    }
    Node* topNode = queue.front();
    queue.pop();
    return topNode;
}

bool Queue::isEmpty() const {
    return queue.empty();
}