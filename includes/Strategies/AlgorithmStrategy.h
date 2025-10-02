#pragma once

#include <unordered_set>
#include "Cube/Cube.h"

class Node;
class DataStructure;

class AlgorithmStrategy {
public:
    virtual bool poda(Node* state) = 0;
    virtual void sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited, std::vector<Node*>& all_nodes) = 0;
    virtual ~AlgorithmStrategy() = default;
    virtual Node* create_root_node(Cube& cube) = 0;
    virtual DataStructure* create_data_structure() = 0;
};