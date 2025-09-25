#pragma once

#include "AlgorithmStrategy.h"
class DFSStrategy : public AlgorithmStrategy
{
public:
    DFSStrategy();
    int max_depth = 14;
    bool poda(Node *state) override;
    void sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited, std::vector<Node*>& all_nodes) override;
    
    Node *create_root_node(Cube &cube) override;
    DataStructure *create_data_structure() override;
    
private:
    bool isAncestor(Node *currentNode, const Cube &targetCube);
    
};