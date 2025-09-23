#include "Stack.h"
#include "Node.h"

void Stack::insert(Node* node) {
    stack.push(node);
}

Node* Stack::remove() {
    if (stack.empty()) {
        return nullptr;
    }
    Node* topNode = stack.top();
    stack.pop();
    return topNode;
}

bool Stack::isEmpty() const {
    return stack.empty();
}