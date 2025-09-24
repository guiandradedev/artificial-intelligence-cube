#pragma once

#include "AlgorithmStrategy.h"
class DFSStrategy : public AlgorithmStrategy
{
public:
    DFSStrategy();
    bool poda(Node *state) override;
    void sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited) override;

    Node *create_root_node(Cube &cube) override;
    DataStructure *create_data_structure() override;
};