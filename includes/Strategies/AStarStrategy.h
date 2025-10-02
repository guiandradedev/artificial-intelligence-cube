#pragma once

#include "AlgorithmStrategy.h"
#include <unordered_map>

class AStarStrategy : public AlgorithmStrategy
{
public:
    AStarStrategy();
    bool poda(Node *state) override;
    void sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited, std::vector<Node*>& all_nodes) override;

    Node *create_root_node(Cube &cube) override;
    DataStructure *create_data_structure() override;
    std::unordered_map<Cube, int> g_costs;

    // Valor do ruído funciona em módulo, -noise a +noise, logo noise >= 0
    int noise = 2; // -2 a +2
    void setNoise(int noise);
    int return_noise(int noise);
};
