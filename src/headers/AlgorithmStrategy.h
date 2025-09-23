#pragma once

#include <unordered_set>

class Node;
class DataStructure;
class Cube;

class AlgorithmStrategy {
public:
    virtual bool poda(Node* state) = 0;
    virtual void sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited) = 0;
    virtual ~AlgorithmStrategy() = default;
};