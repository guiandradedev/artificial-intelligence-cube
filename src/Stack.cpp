#include "Stack.h"

void Stack::insert(Solver::Node* node) {
    stack.push(node);
}

Solver::Node* Stack::remove() {
    if (stack.empty()) {
        return nullptr;
    }
    Solver::Node* topNode = stack.top();
    stack.pop();
    return topNode;
}

bool Stack::isEmpty() const {
    return stack.empty();
}